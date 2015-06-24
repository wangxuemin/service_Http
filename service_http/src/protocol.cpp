/********************************************************************
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ul_log.h>
#include <ul_net.h>

#include "protocol.h"
//#include "encode.h"
//#include "config.h"

/* local config of protocol */
static protocol_conf_t conf;
//#ifdef RSDEBUG
#define	SERVER_NAME "crm_correction.snda"
//#endif

/* define the state of http request */
#define HS_START                0
#define HS_LF                   1
#define HS_LFCR                 2
#define HS_LFCRLF               3
#define HS_LFCRLFCR             4
#define HS_CR                   5


#define MAX_PATH_LEN 4096
#define DFT_CONF_PATH   "./"
#define DFT_CONF_FILE   "bws.conf"
#define NEW(type, len) ((type *)malloc(sizeof(type)*(len)))
#define DELETE(p) (free(p))
#define LWS " \t\n\r"
#define HS_HTTP_COMPLETE        4
static int HS_STATES[2][6] = {
    {1, 0, 3, 0, 4, 1},
    {5, 2, 4, 4, 4, 4}};

/* define the http error message */
static char* http_err302title = "Found";
static char* http_err302form = "The actual URL is not here.\n";

static char* http_err400title = "Bad Request";
static char* http_err400form =
    "Your request has bad syntax or is inherently impossible to satisfy.\n";

    static char* http_err404title = "Not Found";
static char* http_err404form =
"The requested URL was not found on this server.\n";


static char* http_err408title = "Request Timeout";
static char* http_err408form =
"No request appeared within a reasonable time period.\n";

static char* http_err500title = "Internal Error";
static char* http_err500form =
"There was an unusual problem serving the requested URL.\n";

static char* http_err501title = "Not Implemented";
static char* http_err501form =
    "The requested method is not implemented by this server.\n";

static char* http_err503title = "Service Temporarily Overloaded";
static char* http_err503form =
"The requested URL is temporarily overloaded.  Please try again later.\n";

//const char txt_html[] = "text/html";
const char txt_html[] = "application/x-javascript";
const char wap_html[] = "text/vnd.wap.wml";
const char xml_html[] = "text/xml";



int get_conf_int(Ul_confdata *conf_data, char *name, int *pv, const int defaultv)
{
        if(ul_getconfint(conf_data, name, pv))
    {
        ul_writelog(UL_LOG_DEBUG, "%s = %d", name, *pv);
    }
    else
    {
        *pv = defaultv;
        ul_writelog(UL_LOG_DEBUG, "%s = %d(DFT)", name, *pv);
    }
    return 0;
}



/* 
 *  load the configuation of protocol
 *  this will be called by config modules
 *  return 0, if success
 */
int load_protocol_conf(Ul_confdata *conf_data)
{
    get_conf_int(conf_data, "READ_TIMEOUT", &(conf.read_timeo), DFT_READ_TIMEOUT);
    get_conf_int(conf_data, "WRITE_TIMEOUT", &(conf.write_timeo), DFT_WRITE_TIMEOUT);
    get_conf_int(conf_data, "INBUF_LEN", &(conf.inbuf_len), DFT_INBUF_LEN);
    get_conf_int(conf_data, "OUTBUF_LEN", &(conf.outbuf_len), DFT_OUTBUF_LEN);
    get_conf_int(conf_data, "HEADER_LEN", &(conf.header_len), DFT_HEADER_LEN);
    get_conf_int(conf_data, "KEEP_ALIVE", &(conf.keep_alive), DFT_KEEP_ALIVE);
    return 0;
}

/*
 *  static alloc memory for one connection
 *  return NULL, if fails
 */
void *new_conn()
{
    conn_t *conn;

    conn = NEW(conn_t, 1);
    if(conn == NULL)
    {
        goto error;
    }
    memset(conn, 0, sizeof(conn_t));

    /* alloc in buffer */
    conn->read_buf = NEW(char, conf.inbuf_len);
    if(conn->read_buf == NULL)
    {
        goto error;
    }

    /* alloc out buffer */
    conn->send_buf = NEW(char, conf.outbuf_len);
    if(conn->send_buf == NULL)
    {
        goto error;
    }
 
    /* alloc headers buffer */
    conn->headers_buf = NEW(char, conf.header_len);
    if(conn->headers_buf == NULL)
    {
        goto error;
    }
    
    /* alloc headers ready to send */
    conn->headers = NEW(char, conf.header_len);
    if(conn->headers == NULL)
    {
        goto error;
    }

    /* success */
    return (void *)conn;
error:
    ul_writelog(UL_LOG_FATAL, 
            "%s %d new_conn: alloc connection error",
            __FILE__, __LINE__);
 
    destroy_conn(conn);
    return NULL;
}

/*
 *  destroy the connection memory
 *  return 0, if success
 */
int destroy_conn(void *data)
{
    conn_t *conn = (conn_t *)data;

    if(conn)
    {
        DELETE(conn->read_buf);
        DELETE(conn->send_buf);
        DELETE(conn->headers_buf);
        DELETE(conn->headers);
        DELETE(conn);
    }
    return 0;
}

/*
 *  initialize one connection 
 */
int init_conn(conn_t *conn)
{
    conn->read_size = 0;
    conn->send_size = 0;
    conn->method = 0;
    conn->uri = NULL;
    conn->version = 0;
    conn->refer = NULL;
    conn->user_agent = NULL;
    conn->host = NULL;
    conn->accept_encoding = NULL;
    conn->cookie = NULL;
    conn->cookie_style = 0;
    conn->headers_out_size = 0;      
    conn->headers_pos = conn->headers_buf;
    conn->headers_size = 0;
    conn->content_len = 0;
    conn->content_type = (char *)txt_html;
    conn->chunked = 0;
    conn->content = NULL;
    conn->content_encoding = 0;
    conn->gzip_rate = 0;
    conn->status = 0;
    conn->location[0] = 0;
	memset(conn->headers, 0, sizeof(conn->headers));
	memset(conn->send_buf,0,sizeof(conn->send_buf));
	//inet_aton("127.0.0.1", &conn->client_addr);
    return 0;
}

/*
 *  get a line from a buffer, mark \0 when necessary
 *  buf: source buffer
 *  pos: point to the current postion
 *  len: total length of the buffer
 *  return a line start pointer.
 */
char *buf_getline(char *buf, int *pos, int len)
{
    int i, last_pos = *pos;
    int is_line_end = 0;
    for(i = *pos; i < len; ++i)
    {
		if( ('\r' == buf[i])
			&& ((i + 1 < len) && ('\n' == buf[i+1])))
		{
			buf[i] = 0;
			++i;		
			buf[i] = 0;
			is_line_end = 1;
		}
		if('\n' == buf[i]){
			buf[i] = 0;
			is_line_end = 1;
		}	
		if(is_line_end){
			*pos = i + 1;
			return (buf + last_pos);
		}
    }    
    return NULL;
}
/* 
 *  process this buf to check if the http request is complete
 *  this operation depend on the state before
 *  state: state before processing
 *  return the state after processing
 */
static int http_got_request(int state, char *buf, int len)
{
    while(--len >= 0)
    {
        if(*buf == '\r') 
        {
            state = HS_STATES[0][state];
        }
        else if(*buf == '\n') 
        {
            state = HS_STATES[1][state];
        }
        else
        {
            state = HS_START;
        }
        ++buf;
    }
   return state; 
}

/*
 *  read a complete http request, blocks if request is not ready
 *  return 0, if success
 */
int get_request(conn_t *conn, int fd)
{
    int res;
    int state = HS_START;
        
    while(state != HS_HTTP_COMPLETE)
    {
        /* read client with time out */
        /* XXX: time out need to be fix up */
        res = ul_reado_ms(fd, conn->read_buf + conn->read_size,
                conf.inbuf_len - conn->read_size - 1, conf.read_timeo);
        if(res == 0)
        {
            /* client close the connection */
            /*ul_writelog(UL_LOG_WARNING, "[%s][%d]: get_request: client closed the connection",
                    inet_ntoa(conn->client_addr), conn->read_size);*/
			ul_writelog(UL_LOG_WARNING, "[%d]: get_request: client closed the connection",
                    conn->read_size);
            return -1;
        }
        else if(res < 0)
        {
            /* some error occurs */
            /*ul_writelog(UL_LOG_WARNING, "[%s][%d]: get_request: read socket error:%s", 
                    inet_ntoa(conn->client_addr), conn->read_size, strerror(errno));*/
			ul_writelog(UL_LOG_WARNING, "[%d]: get_request: read socket error:%s", 
                    conn->read_size, strerror(errno));
            return -2;
        }
        /* correctly read a packet, check if the request is complete */
        state = http_got_request(state, conn->read_buf + conn->read_size, res);
        conn->read_size += res;

        /* the request is too long */
        if(conn->read_size >= conf.inbuf_len - 1)
        {
            /*ul_writelog(UL_LOG_WARNING, "[%s][%d]: get_request: the request is too long",
                    inet_ntoa(conn->client_addr), conn->read_size);*/
			ul_writelog(UL_LOG_WARNING, "[%d]: get_request: the request is too long",
                    conn->read_size);
            return -1;
        }
    }

    conn->read_buf[conn->read_size] = 0;
    return 0; 
}
/* 
 *  set the method field of a connection , if the method is validated
 */
static int check_method(conn_t *conn, const char *method)
{
    if(strncasecmp(method, "GET", 3) == 0)
    {
        conn->method = METHOD_GET;
        return 0;
    }
    else if (strncasecmp(method, "HEAD", 4) == 0)
    {
        conn->method = METHOD_HEAD;
        return 0;
    }
    return -1;
}

/*
 *  parse the first line of the http request
 *  return 0, if success
 */
static int parse_first_line(conn_t *conn, char *line)
{
    char *start;
    char *end;
    
    start = line;
    
    end = strpbrk(start, LWS);
    if(end == NULL)
    {
        httpd_send_err(conn, 400, "");
        return -1;
    }
    *end = '\0';
    if(check_method(conn, start))
    {
        httpd_send_err(conn, 501, start);
        return -1;
    }
    
    /* get uri */
    start = end + 1;
    start += strspn(start, LWS);//跳过多余的LWS
    end = strpbrk(start, LWS);
    if(end == NULL)
    {
        conn->version = HTTP0_9;
    }
    else
    {
        *end = '\0';
    }
    conn->uri = start;

    /* get version */
    if(end != NULL)
    {
        start = end + 1;
        start += strspn(start, LWS);
        if(*start == '\0')
        {
            conn->version = HTTP0_9;
        }
        else
        {
            if(strncasecmp(start, "HTTP/1.1", 8) == 0 && start[8] == '\0')
            {
                conn->version = HTTP1_1;
            }
            else if(strncasecmp(start, "HTTP/1.0", 8) == 0 && start[8] == '\0')
            {
                conn->version = HTTP1_0;
            }
            else
            {
                httpd_send_err(conn, 400, "");
                return -1;
            }
        }
    }
    
    /* Check for HTTP/1.1 absolute URL. */
    if(strncasecmp(conn->uri, "http://", 7) == 0)
    {
        /* some users use it, although it is forbidden */
        /*
        if(conn->version == HTTP0_9 || conn->version == HTTP1_0)
        {
            httpd_send_err(conn, 400, "");
            return -1;
        }
        */
        conn->uri = strchr(conn->uri + 7, '/');
        if(conn->uri == NULL)
        {
            httpd_send_err(conn, 400, "");
            return -1;
        }
    }
    
    if(*(conn->uri) != '/')
    {
        httpd_send_err(conn, 400, "");
        return -1;
    }

    return 0;
}
/*
 *  parse the request, and fill in the connection structure 
 *  (learn from thttpd)
 *  return 0, if success
 */
int parse_request(conn_t *conn)
{
    int     idx = 0;
    char    *start;
    char    *end;
    struct in_addr transmit_addr;

    /* HTTP header structure is like this
     *
     *  GET<LWS><URI><LWS>HTTP/<1.0|1.1><CRLF>
     * <Headers> <Value>
     * <Headers> <Value>
     * ...
     * 
     *  <URI>=[http://<HOST>]/<filename>[?<args>&<args>...]
     */

    /* read first line */
	
    start = buf_getline(conn->read_buf, &idx, conn->read_size);

    if(start == NULL)
    {
        return -1;
    }
    if(parse_first_line(conn, start))
    {
        return -1;
    }
    
    /* read the MIME headers. */
    while((start = buf_getline(conn->read_buf, &idx, conn->read_size)) != NULL)
    {
        switch(start[0])
        {
        case 'R': 
        case 'r':
            if(strncasecmp(start, "Referer:", 8) == 0)
            {
                start += 8;
                start += strspn(start, " \t");
                conn->refer = start;
            }
            break;
        case 'U': 
        case 'u':
            if(strncasecmp(start, "User-Agent:", 11) == 0)
            {
                start += 11;
                start += strspn(start, " \t");
                conn->user_agent = start;
            }
            break;
        case 'H':
        case 'h':
            if(strncasecmp(start, "Host:", 5) == 0)
            {
                start += 5;
                start += strspn(start, " \t");
                conn->host = start;
                end = strchr(conn->host, ':');
                if(end != NULL)
                {
                    *end = '\0';
                }
                if(strchr(conn->host, '/' ) != NULL || conn->host[0] == '.' )
                {
                    httpd_send_err(conn, 400, "");
                    return -1;
                }
            }
            break;
        case 'A':
        case 'a':
            if(strncasecmp(start, "Accept-Encoding:", 16) == 0)
            {
                start += 16;
                start += strspn(start, " \t");
                conn->accept_encoding = start;
            }
            break;
        case 'C':
        case 'c':
            if(strncasecmp(start, "Cookie:", 7) == 0)
            {
                start += 7;
                start += strspn(start, " \t");
                conn->cookie = start;
                conn->cookie_style = CT_COOKIE;
            }
            else if(strncasecmp(start, "Cookie2:", 8) == 0 
                    && conn->cookie == NULL)
            {
                start += 8;
                start += strspn(start, " \t");
                conn->cookie = start;
                conn->cookie_style = CT_COOKIE2;
            }
            else if(strncasecmp(start, "CLIENTIP:", 9) == 0)
            {
                start += 9;
                start += strspn(start, " \t");
                if(inet_aton(start, &transmit_addr) != 0)
                {
                    conn->client_addr = transmit_addr;
                }
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

/*
 *  add a new header out to buffer
 *  hdname:  headers name
 *  hdvalue: headers value
 *  return 0, if success
 */
int set_headers_out(conn_t *conn, const char *hdname, const char *hdvalue)
{
    int res, i;
   
    res = snprintf(conn->headers_pos, 
            conf.header_len - (conn->headers_pos - conn->headers_buf), 
            "%s: %s\r\n", hdname, hdvalue);
    if(res == -1 || conn->headers_out_size >= MAX_HEADERS_OUT)
    {
        /*ul_writelog(UL_LOG_WARNING, "[%s]: headers out buffer is full",
                inet_ntoa(conn->client_addr));*/
		ul_writelog(UL_LOG_WARNING, " headers out buffer is full");
        return -1;
    }
    
    /* the header maybe already exists */
    for(i = 0;i < conn->headers_out_size; ++i)
    {
        if(strncasecmp(conn->headers_out[i], hdname, strlen(hdname)) == 0)
        {
            break;
        }
    }
    conn->headers_out[i] = conn->headers_pos;
    
    /* actually new header */
    if(i == conn->headers_out_size)
    {
        conn->headers_out_size++;
    }

    /* include the trailing \0 */
    conn->headers_pos += (res + 1);

    return 0;
}

/*
 *  write status string
 *  return the number of the characters
 */
static int write_status(char *buf, int status)
{
    const static char *status_fmt = "HTTP/1.1 %d %s\r\n";
    int res;

    switch(status)
    {
    case 200:
        res = sprintf(buf, status_fmt, 200, "OK"); 
        break;
    case 302:
        res = sprintf(buf, status_fmt, 302, "Found"); 
        break;
    case 400:
        res = sprintf(buf, status_fmt, 400, "Bad Request"); 
        break;
    case 404:
        res = sprintf(buf, status_fmt, 404, "Not Found"); 
        break;
    case 408:
        res = sprintf(buf, status_fmt, 408, "Request Timeout"); 
        break;
    case 500:      
        res = sprintf(buf, status_fmt, 500, "Internal Error"); 
        break;
    case 501:
        res = sprintf(buf, status_fmt, 501, "Not Implemented"); 
        break;
    case 503:        
        res = sprintf(buf, status_fmt, 503, "Service Temporarily Overloaded"); 
        break;
    default:
        ul_writelog(UL_LOG_WARNING, "[%d]: error http status", status);
      
        res = -1;
        break;
    }
    return res;
}

static const char* rfc1123fmt = "%a, %d %b %Y %H:%M:%S GMT";
/*
 *  set base headers 
 */
static int set_base_headers(conn_t *conn, int content_len, int status)
{
    char        date[100];
    time_t      now;
    struct tm   result;
    int         res;
    
    /*  200 OK
     *  Date:   xxx
     *  Server: BWS
     *  Content-Type: text/html
     */

    /* write status */
    res = write_status(conn->headers, status);
    if(res == -1)
    {
        return -1;
    }
    conn->headers_size += res;
    
     /* build date string */
    now = time(0);
    strftime(date, sizeof(date), rfc1123fmt, gmtime_r(&now, &result));

    /* write base headers */
    res = snprintf(conn->headers + conn->headers_size, conf.header_len - conn->headers_size,
            "Date: %s\r\n"
            "Server: %s\r\n"
            "Content-Length: %d\r\n"
            "Content-Type: %s\r\n"
	    "Cache-Control: private\r\n",
            date, SERVER_NAME, content_len, conn->content_type);
    if(res == -1)
    {
         /*ul_writelog(UL_LOG_WARNING, "[%s]: send buffer is full",
                inet_ntoa(conn->client_addr));*/
		ul_writelog(UL_LOG_WARNING, " send buffer is full");
         return -1;
    }
    conn->headers_size += res;
   
    /* if we do not support keep alive, add Connection: close */
    if(conf.keep_alive == 0)
    {
        res = snprintf(conn->headers + conn->headers_size, 
                conf.header_len - conn->headers_size,
            "Connection: close\r\n");
        if(res == -1)
        {
            ul_writelog(UL_LOG_WARNING, "send buffer is full"); 
                   // inet_ntoa(conn->client_addr));
            return -1;
        }
        conn->headers_size += res;
    }
    return 0;
}

/*
 *  encode the content if nessary
 *  from buf to conn->content
 *  return 0, if success
 */
static int do_encode(conn_t *conn, char *buf, int len)
{
     /*if gzip is needed */
/*
    if(need_gzip(conn, len))
    {
        conn->send_size = gzip_buf(conn->send_buf, conf.outbuf_len, buf, len);
        if(conn->send_size > 0)
        {
            if(len > 0)
            {
                conn->gzip_rate = 100 - conn->send_size * 100 / len;
            }
            if(0 <= conn->gzip_rate && conn->gzip_rate <= 100)
            {
                conn->content = conn->send_buf;
                conn->content_len = conn->send_size;
                set_headers_out(conn, "Content-Encoding", "gzip");
                return 0;
            }
            conn->gzip_rate = 0;
        }
    }
*/
	int real_len = (len < conf.outbuf_len)?len:conf.outbuf_len;
	if(buf != conn->send_buf){
		memcpy(conn->send_buf, buf, real_len);
	}
	conn->content = conn->send_buf;
	conn->content_len = real_len;
	
    return 0;
}

/*
 *  build http header
 *  return 0, if success
 */
static int build_header(conn_t *conn)
{
    int res;
    int i;
    /* write buildin headers */ 
    if(set_base_headers(conn, conn->content_len, conn->status))
    {
        return -1;
    }
    /* write the headers */
    for(i = conn->headers_out_size - 1;i >= 0;--i)
    {
        res = snprintf(conn->headers + conn->headers_size,
                conf.header_len - conn->headers_size,
                "%s", conn->headers_out[i]);
        if(res == -1)
        {
            /*ul_writelog(UL_LOG_WARNING, "[%s]: headers buffer is full",
                    inet_ntoa(conn->client_addr));*/
			 ul_writelog(UL_LOG_WARNING, "headers buffer is full");
            return -1;
        }
        conn->headers_size += res;
    }
    /* add on a new line */
    res = snprintf(conn->headers + conn->headers_size, 
            conf.header_len - conn->headers_size, "\r\n");
    if(res == -1)
    {
        /*ul_writelog(UL_LOG_WARNING, "[%s]: headers buffer is full",
                inet_ntoa(conn->client_addr));*/
		 ul_writelog(UL_LOG_WARNING, "headers buffer is full");
        return -1;
    }
    conn->headers_size += res;
    return 0;
}

/*
 *  write user content in to connction buffer
 *  encode the user content if necessary
 *  return 0, if success
 */
int write_content(conn_t *conn, char *page, int len, int status)
{
    conn->status = status;
    /* process encoding */
    if(do_encode(conn, page, len))
    {
        return -1;
    }
    return 0;
}

/* 
 *  send the buffer to client
 *  return 0, if success
 */
int http_send(conn_t *conn, int fd)
{
    int res;
    
    if(build_header(conn)) 
    {
        return -1;
    }
    
    /* XXX: fix me, use writev instead */

    res = ul_swriteo_ms_ex(fd, conn->headers, conn->headers_size, conf.write_timeo);
    if(res < 0)
    {
       /* ul_writelog(UL_LOG_WARNING, "[%s][%d]: protocol.c:write headers error:%s",
                inet_ntoa(conn->client_addr), conn->headers_size, strerror(errno));*/
		ul_writelog(UL_LOG_WARNING, "[%d]: protocol.c:write headers error:%s",
                conn->headers_size, strerror(errno));
        return -1;
    }

    res = ul_swriteo_ms_ex(fd, conn->content, conn->content_len, conf.write_timeo);
    if(res < 0)
    {
        /*ul_writelog(UL_LOG_WARNING, "[%s][%d]: protocol.c:write contents error:%s",
                inet_ntoa(conn->client_addr), conn->content_len, strerror(errno));*/
		ul_writelog(UL_LOG_WARNING, "[%d]: protocol.c:write contents error:%s",
                conn->content_len, strerror(errno));
        return -1;
    }
    return 0;
}

/*
 *  fill title and form due to the http status code
 */
static int fill_err_page(int status, char **title, char **form)
{
    switch(status)
    {
    case 302:
        *title = http_err302title;
        *form = http_err302form;
        break;
    case 400:
        *title = http_err400title;
        *form = http_err400form;
        break;
    case 404:
        *title = http_err404title;
        *form = http_err404form;
        break;
    case 408:
        *title = http_err408title;
        *form = http_err408form;
        break;
    case 500:      
        *title = http_err500title;
        *form = http_err500form;
        break;
    case 501:
        *title = http_err501title;
        *form = http_err501form;
        break;
    case 503:        
        *title = http_err503title;
        *form = http_err503form;
        break;
    default:
        ul_writelog(UL_LOG_WARNING, "[%d]: protocol.c:error fill error page", status);
        *title = NULL;
        *form = NULL;
        return -1;
    }
    return 0;
}
        
/* 
 *  send the error page 
 *  status: http status
 *  title:  html page title
 *  form:   content form, %s can be included
 *  arg:    arguments to be filled in the form
 *  return 0, if success
 */
int httpd_send_err(conn_t *conn, int status, char *arg)
{
    int res;
    int len = 0;
    char *buf = conn->send_buf;
    char *title;
    char *form; 

    conn->content_encoding = ENCODING_RAW;

    /* title and form */
    if(fill_err_page(status, &form, &title))
    {
        return -1;
    }
    
    /* header */
    res = snprintf(buf, conf.outbuf_len, 
            "<HTML>"
            "<HEAD><TITLE>%d %s</TITLE></HEAD>\r\n"
            "<BODY BGCOLOR=\"#cc9999\" TEXT=\"#000000\" LINK=\"#2020ff\" VLINK=\"#4040cc\">\r\n"
            "<H2>%d %s</H2>\r\n",
            status, title, status, title);
    if(res == -1)
    {
        /*ul_writelog(UL_LOG_WARNING, "[%s]: httpd_send_err buffer is full",
                inet_ntoa(conn->client_addr));*/
		ul_writelog(UL_LOG_WARNING, "httpd_send_err buffer is full");
        return -1;    
    }
    len += res;
    
    /* form */
    res = snprintf(buf + len, conf.outbuf_len - len, form, arg);
    if(res == -1)
    {
        /*ul_writelog(UL_LOG_WARNING, "[%s]: httpd_send_err buffer is full",
                inet_ntoa(conn->client_addr));*/
		ul_writelog(UL_LOG_WARNING, "httpd_send_err buffer is full");
        return -1;    
    }
    len += res;
    
    /* tail */
    res = snprintf(buf + len, conf.outbuf_len - len, 
            "<HR>\r\n"
            "</BODY>\r\n"
            "</HTML>\r\n");
    if(res == -1)
    {
         /*ul_writelog(UL_LOG_WARNING, "[%s]: httpd_send_err buffer is full",
                inet_ntoa(conn->client_addr));*/
		ul_writelog(UL_LOG_WARNING, "httpd_send_err buffer is full");
        return -1;    
    }
    len += res;

    /* write response */
    if(write_content(conn, buf, len, status))
    {
        return -1;
    }
    return 0;
}

/* 
 *  return the string of method
 */
char *method_str(int method)
{
    switch(method)
    {
    case METHOD_GET:    
	    return "GET";
    case METHOD_HEAD:   
	    return "HEAD";
    default :
	    break;
    }
    return "UNKNOW";
}

/*
 *  return the string of http version
 */
char *http_ver_str(int ver)
{
    switch(ver)
    {
    case HTTP0_9:   return "HTTP/0.9";
    case HTTP1_0:   return "HTTP/1.0";
    case HTTP1_1:   return "HTTP/1.1";
    }
    return "UNKNOW";
}
