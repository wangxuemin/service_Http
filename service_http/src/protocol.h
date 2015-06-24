/********************************************************************
 *
 ********************************************************************/

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define MAX_HEADERS_OUT         15
#define CONTENT_ENCODING_RAW    0
#define CONTENT_ENCODING_GZIP   1

/* default configuation */
#define DFT_READ_TIMEOUT        3500
#define DFT_WRITE_TIMEOUT       15000
#define DFT_INBUF_LEN           4096
#define DFT_OUTBUF_LEN          163840
#define DFT_HEADER_LEN          2048
#define DFT_KEEP_ALIVE          1

/* define encoding type */
#define ENCODING_UNKNOW         0
#define ENCODING_RAW            1
#define ENCODING_GZIP           2


/* define method of http request */
#define METHOD_UNKNOW           0
#define METHOD_GET              1
#define METHOD_HEAD             2

/* define HTTP version */
#define HTTP1_1                 0
#define HTTP1_0                 1
#define HTTP0_9                 2

/* define encoding type */
#define ENCODING_UNKNOW         0
#define ENCODING_RAW            1
#define ENCODING_GZIP           2

/* define cookie style */
#define CT_UNSET                0
#define CT_NETSCAPE             1
#define CT_COOKIE               2
#define CT_COOKIE2              3

#define LOCATION_LEN		1024
typedef struct
{
    int read_timeo;
    int write_timeo;
    int inbuf_len;
    int outbuf_len;
    int header_len;
    int keep_alive;
}protocol_conf_t;

/* http content type */
extern const char txt_html[];
extern const char wap_html[];
extern const char xml_html[];

typedef struct
{
    struct in_addr client_addr;     /* client's address */
    char    *read_buf;              /* buffer for reading */
    int     read_size;              /* actual data size in buffer */

    char    *send_buf;              /* buffer for sending page to client
                                     * the content here is encoded  
                                     */
    int     send_size;

    int     method;                 /* method filds in http headers */
    char    *uri;                   /* uri fields in http headers */
    int     version;                /* versions 1.1 or 1.0 */

    char    *refer;                 /* http headers */
    char    *user_agent;
    char    *host;
    char    *accept_encoding;
    char    *cookie;
    int     cookie_style;           /* cookie or cookie2 */
    
    char    *headers_out[MAX_HEADERS_OUT];  /* heads out */
    int     headers_out_size;       /* actual heads number */

    char    *headers_buf;           /* buffers for headers out */
    char    *headers_pos;           /* postion in buffers of headers out */

    char    *headers;               /* headers ready to send */
    int     headers_size;           /* the length of the headers */
        
    char    *content;               /* real content to send */
    int     content_len;            /* the length of the content */

    char    *content_type;          /* Content-Type: text/html */

    int     chunked;                /* need chunked encoding */
    int     content_encoding;       /* if gzip is support */
    int     gzip_rate;              /* gzip compression rate */
    int     status;                 /* http response status */
    char    location[LOCATION_LEN]; /* this field use to redirect*/
}conn_t;

/* 
 *  load the configuation of protocol
 *  this will be called by config modules
 *  return 0, if success
 */
extern int load_protocol_conf(Ul_confdata *conf_data);

/*
 *  static alloc memory for one connection
 *  return NULL, if fails
 */
extern void *new_conn();

/*
 *  initialize one connection 
 */
extern int init_conn(conn_t *conn);

/*
 *  destroy the connection memory
 *  return 0, if success
 */
extern int destroy_conn(void *conn);

/*
 *  read a complete http request, blocks if request is not ready
 *  return 0, if success
 */
extern int get_request(conn_t *conn, int fd);

/*
 *  parse the request, and fill in the connection structure 
 *  return 0, if success
 */
extern int parse_request(conn_t *conn);

/*
 *  add a new header out to buffer
 *  hdname:  headers name
 *  hdvalue: headers value
 *  return 0, if success
 */
extern int set_headers_out(conn_t *conn, const char *hdname, const char *hdvalue);

/*
 *  write user content in to connction buffer,
 *  encode the user content if necessary
 *  return 0, if success
 */
extern int write_content(conn_t *conn, char *page, int len, int status);

/* 
 *  send the buffer to client
 *  return 0, if success
 */
extern int http_send(conn_t *conn, int fd);

/* 
 *  send the error page 
 *  status: http status
 *  title:  html page title
 *  form:   content form, %s can be included
 *  arg:    arguments to be filled in the form
 *  return 0, if success
 */
extern int httpd_send_err(conn_t *conn, int status, char *arg);

/* 
 *  return the string of method
 */
extern char *method_str(int method);

/*
 *  return the string of http version
 */
extern char *http_ver_str(int ver);
          
#endif // _PROTOCOL_H_
