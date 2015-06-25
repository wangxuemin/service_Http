/**
 *  
 * @brief 检索端代码
 *  
 **/
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string>
#include <set>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <fstream>

#include "service_http.h"
#include "protocol.h"
#include "utility.h"
#include "sdlog.h"

#include <json/json.h>
#include <json/value.h>
#include <vector>


using namespace std;

const char* charset = "utf-8";
Json::Value conf;



static int G_RS_MAX_CONF_NUM = 100;
#define SUSVR_PATH "service_http.conf"

bool load_server_config(const string& file)
{
return true;
    ifstream conf_file(file.c_str(), ios::in);
	Json::Reader jreader;
    if (!jreader.parse(conf_file, conf)) {
        FMTLOG(ERROR, "app_log", "parsing configure file failed.");
		return false;
    }
	string fixed_data = "../data";//conf["FIXED_DATA"].asString();
//	SDLOG_INIT(conf["LOGCXX_CONFIG"].asString().c_str());

	return true;
}

int route(const std::string& id)
{
    int r = 0;
    sscanf(id.substr(0, 2).c_str(), "%x", &r);
    return r;
}

/**
 * @brief 配置文件结构
 *
 */

typedef struct _conf_info_t
{
	char home_path[G_SU_MAX_STR_LEN];
	char conf_path[G_SU_MAX_STR_LEN];
	char index_path[G_SU_MAX_STR_LEN];
	char data_path[G_SU_MAX_STR_LEN];
	char log_path[G_SU_MAX_STR_LEN];             ///<rs log path
	char log_name[G_SU_MAX_STR_LEN];             ///<rs log name
	char UTREntrance[G_SU_MAX_QUERY_LEN];           ///<utr接入
	int  log_events;                             ///<log event for ullib
	int  log_to_sys;                             ///<whether write to system's log or not
	int  log_spec;
	int  pp_queue_len;
	int  pp_sock_num;	
	int  max_query_len;
	int  port;
	int  thread_num;
	int  valid_time;		///<包有效时间，单位秒
	int  loader_port;
	int  max_index_buf_size;
	int  max_result_num;
	int  max_static_num;	///<静态库最多配置的结果数
	int  default_result_num;
	int  max_multistyle_num;
	int  log_rank;
	int  log_refer_ip;
	
	
	int prefix_query;	
} conf_info_t;



/*********************************************************/
static PendingPool g_pendingpool;
static conf_info_t g_conf;
static ul_logstat_t g_logstat;

/***********new dict define begin here***********/


/**
 *  载入配置文件
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */

static int load_conf(char *home_path, conf_info_t &conf_info)
{
	strncpy(conf_info.home_path, home_path, G_SU_MAX_STR_LEN);
	conf_info.home_path[G_SU_MAX_STR_LEN - 1] = 0;
	Ul_confdata *pd_conf = ul_initconf(G_RS_MAX_CONF_NUM);
	if (pd_conf == NULL)
	{
		fprintf(stderr, "Initialize conf failed\n");
		return -1;
	}
	sprintf(conf_info.conf_path, "%s/conf/", conf_info.home_path);
	if(ul_readconf(conf_info.conf_path, SUSVR_PATH, pd_conf) < 0)
	{
		fprintf(stderr, "Read conf file failed: [%s/%s]\n", conf_info.conf_path , SUSVR_PATH);
		ul_freeconf (pd_conf);
		return -1;
	}
	load_protocol_conf(pd_conf);
	char tmpstr[G_SU_MAX_STR_LEN];
	if(ul_getconfstr(pd_conf, "LOG_PATH", tmpstr))
	{
		sprintf(conf_info.log_path, "%s/%s", conf_info.home_path, tmpstr);
	}
   	else
	{
		sprintf(conf_info.log_path, "../%s", "log/");
	}
	if(ul_getconfstr(pd_conf, "INDEX_PATH", tmpstr))
	{
		sprintf(conf_info.index_path, "%s/%s", conf_info.home_path, tmpstr);
	}
   	else
	{
		sprintf(conf_info.index_path, "../%s", "index/");
	}

	if(ul_getconfstr(pd_conf, "DATA_PATH", tmpstr))
	{
		sprintf(conf_info.data_path, "%s/%s", conf_info.home_path, tmpstr);
	}
   	else
	{
		sprintf(conf_info.data_path, "../%s", "data/");
	}
	
	if(ul_getconfstr(pd_conf, "UTR_ENTRANCE", tmpstr))
	{
		snprintf(conf_info.UTREntrance, G_SU_MAX_QUERY_LEN,"%s?",  tmpstr);
		conf_info.UTREntrance[G_SU_MAX_QUERY_LEN - 1] = '\0';
	}
   	else
	{
		sprintf(conf_info.UTREntrance, "%s?", "search");
	}
	if (ul_getconfstr(pd_conf, "LOG_NAME", conf_info.log_name) == 0)
	{
		strcpy(conf_info.log_name, "service_http.");
	}
	if (ul_getconfint(pd_conf, "LOG_EVENTS", &(conf_info.log_events)) == 0)
	{
		conf_info.log_events = 0x10; //default : RSDEBUG
 	}
	if (ul_getconfint(pd_conf, "LOG_TO_SYS", &(conf_info.log_to_sys)) == 0)
	{
		conf_info.log_to_sys = 0;
	}
	if (ul_getconfint(pd_conf, "LOG_SPEC", &(conf_info.log_spec)) == 0)
 	{
		conf_info.log_spec = 0;
	}
	if (ul_getconfint(pd_conf, "PP_QUEUE_LEN", &(conf_info.pp_queue_len)) == 0)
	{
		conf_info.pp_queue_len = 6000;
	}
	if (ul_getconfint(pd_conf, "PP_SOCK_NUM", &(conf_info.pp_sock_num)) == 0)
	{
		conf_info.pp_sock_num = 6000;
	}
	if (ul_getconfint(pd_conf, "PORT", &(conf_info.port)) == 0)
	{
		conf_info.port = 6337; //port
	}
	if (ul_getconfint(pd_conf, "THREAD_NUM", &(conf_info.thread_num)) == 0)
	{
		conf_info.thread_num = 1; //thread num
	}
	if (ul_getconfint(pd_conf, "VALIDTIME", &(conf_info.valid_time)) == 0)
	{
		conf_info.valid_time = 3600;
	}
	if (ul_getconfint(pd_conf, "LODERPORT", &(conf_info.loader_port)) == 0)
	{
		conf_info.loader_port = 1106;
	}
	if (ul_getconfint(pd_conf, "MAX_INDEX_BUF_SIZE", &(conf_info.max_index_buf_size)) == 0)
	{
		conf_info.max_index_buf_size = 40000000;
	}
	if (ul_getconfint(pd_conf, "MAX_RESULT_NUM", &(conf_info.max_result_num)) == 0)
	{
		conf_info.max_result_num = 20;
	}
	if (ul_getconfint(pd_conf, "DEFAULT_RESULT_NUM", &(conf_info.default_result_num)) == 0)
	{    
		conf_info.default_result_num = 10;
	} 
	
	if (ul_getconfint(pd_conf, "LOG_RANK", &(conf_info.log_rank)) == 0)
	{
		conf_info.log_rank = RANK_SUSVR_LOG;
	}
	if (ul_getconfint(pd_conf, "LOG_REFER_IP", &(conf_info.log_refer_ip)) == 0)
	{    
		conf_info.log_refer_ip = 0; 
	}
	if (ul_getconfint(pd_conf, "MAX_STATIC_NUM", &(conf_info.max_static_num)) == 0)
	{
		conf_info.max_static_num = 10;
	}
 	
	return 0;
}


/**
 *  @brief 将二进制的query转换为汉字
 *  
 *  @param[in]  p_src_start  待转换字符串的开始指针
 *  @param[in]  p_src_end  待转换字符串的结束指针
 *  @param[in]  c_type  字符串类型
 *  @param[out]  p_des 输出转换后的字符串
 *  @return 函数操作结果
 *  - -1  失败
 *  - 0  成功
 */ 
int str_dec_2_hex(const char* p_src_start, 
					const char * p_src_end, 
					char* p_des,
                t_type c_type)
{
	char des_t[G_SU_MAX_STR_LEN];
	char * des = des_t;

		while ( *p_src_start && p_src_start != p_src_end ) {
				if ( *p_src_start < 0x20 && *p_src_start>0 ) {
						if ( c_type == QUERY ) {
								*des= ' ';
								des++;
								p_src_start++;
								continue;
						} else {
								return -1;
						}
				}

				if ( *p_src_start == '+' && c_type == QUERY ) {
						*des= ' ';
						des++;
						p_src_start++;
						continue;
				}

				if ( (*p_src_start == '\\' && *(p_src_start+1) == 'x'
					  && p_src_start <= p_src_end - 4 )
					 ||(  *p_src_start== '%' && p_src_start <= p_src_end -3 ) ) {

						if ( *p_src_start == '%' ) {
								p_src_start++;
						} else {
								p_src_start+=2;
						}

						unsigned char tmp = 0;
						if ( *p_src_start>='A' && *p_src_start<='Z' ) {
								tmp += *p_src_start -'A'+10;
						} else if ( *p_src_start >= '0' && *p_src_start <='9' ) {
								tmp += *p_src_start-'0';
						} else if ( *p_src_start>='a' && *p_src_start<='z' ) {
								tmp += *p_src_start-'a'+10;
						} else {
								////printf("%s\n",p_src_start);
								return -1;
						}

						tmp = tmp << 4;
						p_src_start++;

						if ( *p_src_start>='A' && *p_src_start<='Z' ) {
								tmp += *p_src_start-'A'+10;
						} else if ( *p_src_start >= '0' && *p_src_start <='9' ) {
								tmp += *p_src_start-'0';
						} else if ( *p_src_start>='a' && *p_src_start<='z' ) {
								tmp += *p_src_start -'a'+10;
						} else {
								return -1;
						}
						p_src_start++;

						if ( tmp < 0x20 && tmp>0 ) {
								if ( c_type == QUERY ) {
										*des= ' ';
										des++;
								} else {
										return -1;
								}
						} else {
								*des = tmp;
								des++;
						}

				} else {
						*des = *p_src_start;
						des ++;
						p_src_start++;
				}
		}

		*des = 0;

		if ( (c_type == QUERY && (des - des_t) >= (int) G_SU_MAX_QUERY_LEN) ) {
				return -1;
		} else {
				strncpy(p_des,des_t, G_SU_MAX_QUERY_LEN);
				p_des[G_SU_MAX_QUERY_LEN - 1] = '\0';
				return 0;
		}
}


/**
 *  初始化
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */ 
static int init()
{
	//INIT PENDPOOL
	g_pendingpool.set_queuelen(g_conf.pp_queue_len + 1);
	g_pendingpool.set_socknum(g_conf.pp_sock_num + 1);
	
	
       //INIT STATIC DICT..
	
	return 0;
}


int get_parameter(char* uri, const std::string& nm, char* value)
{
	char *start = strstr(uri, (std::string("?")+nm+"=").c_str());
	if(start == NULL)
		start = strstr(uri, (std::string("&")+nm+"=").c_str());
	
	if(start != NULL){
		start += nm.length() + 2;
		char *end = start;
		while(*end != '\0' && *end != '&')
			end++;
		if(str_dec_2_hex(start, end, value, QUERY) < 0)
			*value = 0;
		return 0;
	}
	
	return -1;
}

/**
 *  parse uri
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */

int parse_uri(char *uri, 
              char *q)
{
	// cout << "start in parse_uri" << endl;
	if(uri == NULL)
		return -1;

	if(strstr(uri, g_conf.UTREntrance) == NULL)
		return -1;
	
	// query
	if(get_parameter(uri, "q", q) < 0)return -1;

	return 0;
}


/**
 *  取数据包失效时间
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */ 
 void getexpire(char *expiretime)
{
	static const char* rfc1123fmt = "%a, %d %b %Y %H:%M:%S GMT";
	if(expiretime == NULL)
	{
	    return ;	
	}
	time_t timep;
	struct tm result;
	timep = time(0) + g_conf.valid_time;
	strftime(expiretime, G_SU_MAX_STR_LEN, rfc1123fmt, gmtime_r(&timep, &result));
}
/**
 *  返回出错包
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */ 

void send_error(conn_t *g_conn, int work_sock, char *send_buf)
{
	if(send_buf == NULL)
	{
	   return;
	}
	strcpy(send_buf, "[\"\",[]]");
	send_buf[G_SU_MAX_STR_LEN - 1] = '\0';
    write_content(g_conn,send_buf,strlen(send_buf),DEFAULT_HTTH_HEAD_STATUS);
    g_conn->content = g_conn->send_buf;
    http_send(g_conn, work_sock);
}


char *aton_r(struct in_addr addr, char *str)
{
    unsigned int s = addr.s_addr;
    
    sprintf(str, "%d.%d.%d.%d", 
            s & 0xff, (s >> 8) & 0xff, (s >> 16) & 0xff, (s >> 24) & 0xff);
    return str;
}


void *server_thread(void *arg)
{
	static const int MAX_URI_LEN = G_SU_MAX_STR_LEN;
	ul_pthread_detach(ul_pthread_self());
	bool bRun = true;
	bool bkeepalive = false;
	int handle = -1;
	int work_sock = -1;
	conn_t *g_conn = NULL;
	bool bret;
	char send_buf[G_SU_MAX_STR_LEN];
	char query[G_SU_MAX_QUERY_LEN] = {'\0'};
	
	
	char expires_val[G_SU_MAX_STR_LEN];
	struct timeval s, e;
	int time_used;
	if (ul_openlog_r("server_thread", &g_logstat) == -1)
	{
		ul_writelog(UL_LOG_FATAL, "Open log inner fail");
		bRun = false;
	}

	g_conn = (conn_t *)new_conn();
	if(g_conn == NULL)
	{
	    ul_writelog(UL_LOG_FATAL, "init conn fail");
		bRun = false;
	}	

	while (bRun) {
		// cout << "start in server_thread while" << endl;
		try {
            
            char* tquery = NULL;
            std::string s_q = "";
            std::string json_result = "Hello World!";

			bret = g_pendingpool.work_fetch_item(handle, work_sock);
			if (!bret) {
				goto session_exit;
			}

			gettimeofday(&s, NULL);
			init_conn(g_conn);
			
			if (get_request(g_conn,work_sock) != 0) {
				ul_writelog(UL_LOG_WARNING, "get request fail");
				goto session_exit;
			}
			
			if (parse_request(g_conn) != 0) {
				ul_writelog(UL_LOG_WARNING, "parse request fail");
				goto session_exit;
			}
			
			if ((int)strlen(g_conn->uri) > MAX_URI_LEN) {
				ul_writelog(UL_LOG_WARNING, "uri length is to long");
				goto session_exit;
			}
			
			ul_writelog(UL_LOG_TRACE, "URI: %s", g_conn->uri);
			memset(query, 0, sizeof(char)*G_SU_MAX_QUERY_LEN);
			
			if (parse_uri(g_conn->uri, query) < 0) {
				ul_writelog(UL_LOG_WARNING, "parse uri  fail");
				goto session_exit;
			}

			//get query text 
			{
			    tquery = query;
			    s_q = "";
			    while(tquery != NULL && *tquery != '\0')
                {
                    s_q += *tquery;
                    ++tquery;
                }
            }
            
			json_result = s_q;
			ul_writelog(UL_LOG_TRACE,"URI: %s\tRECOMM: %s",g_conn->uri,json_result.c_str());
			strcpy(send_buf, json_result.c_str());

			//写回~	
			if(write_content(g_conn,send_buf,strlen(send_buf),DEFAULT_HTTH_HEAD_STATUS) != 0) {
				goto session_exit;
			}
			g_conn->content =  g_conn->send_buf;
			getexpire(expires_val);
			if (set_headers_out(g_conn,"Expires", expires_val) != 0) {
				goto session_exit;
			}
			http_send(g_conn, work_sock);
			gettimeofday(&e, NULL);
			time_used = TIMEDIFF(s, e);
			if (g_conf.log_rank == RANK_COOKIE_LOG) {
				ul_writelog(UL_LOG_TRACE, "request ok timeused [%d]", time_used);
			}

			g_pendingpool.work_reset_item(handle, bkeepalive);
			continue;
			session_exit:
			if (bret) {
				send_error(g_conn, work_sock, send_buf);
			}
			g_pendingpool.work_reset_item(handle, bkeepalive);
		} catch (...) {
			;
		}
		memset(send_buf, 0, sizeof(char)*G_SU_MAX_STR_LEN);
	}
	//free

	if (g_conn != NULL) {
		destroy_conn(g_conn);
	}
	ul_writelog(UL_LOG_NOTICE, "Thread %ld exit", pthread_self());
	ul_closelog_r(0);
	ul_pthread_exit(NULL);
	
	return (void*)0;
}



/**
 *  loaddict thread
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */
void* reload_thread(void *arg)
{

   return (void*)0;

}

/**
 *  watch thread
 *  
 *  @param[in]  无
 *  @param[out]  无
 *  @return 操作结果
 *  - -1    失败
 *  - 0     成功
 */

void *watch(void *arg)
{
	if(!arg || *(int *)arg < 0)
	{
	    return 0;
	}
	int listen_sock = *(int*)arg;
	int acc_sock;
	int max_sockfd;
	bool bNewConn;
	fd_set fs;
	const timeval TV_TIMEOUT = {0, 5000}; 
	timeval tv;	
	uint ip = 0;
	int ret;
	while(1)
	{
		FD_ZERO(&fs);
        FD_SET(listen_sock, &fs);
		max_sockfd = g_pendingpool.mask(&fs);
        if( max_sockfd <= listen_sock )
		{
		    max_sockfd = listen_sock + 1;
        }
		tv = TV_TIMEOUT;
		ret = select(max_sockfd, &fs, NULL, NULL, &tv);		
        if( ret <= 0 )
		{
		    continue;
        }
		bNewConn = false;
        if( FD_ISSET(listen_sock, &fs) )
        {
            bNewConn = true;
        }
		if(bNewConn)
		{
			acc_sock = x_accept(listen_sock, ip);
			if(acc_sock >= 0)
			{
				ul_writelog(UL_LOG_DEBUG, "accept connection succeed");
			}
			else
			{
				ul_writelog(UL_LOG_WARNING, "accept connection failed");
				continue;
			}
			int ret = g_pendingpool.insert_item(acc_sock);
			if(ret < 0)
			{
				ul_sclose(acc_sock);
				ul_writelog(UL_LOG_WARNING, "close sock to control overflow");
			}
		}
		g_pendingpool.check_item(&fs);
	}
}


void show_help()
{
	printf("\n");
        printf("Version\t: %s\n", VERSION);
        printf("\n");
        printf("Usage: service_http homepath [-v] [-h]\n");
        printf("\t-h\tshow help\n");
        printf("\t-v\tshow version\n");
        printf("\n\n");
        return; 
}


int main(int argc, char *argv[])
{

	pthread_t	*tids = NULL;
	pthread_t	load_tid;
	
	/*
	if (argc != 3 ||
            (argc ==2 && (strcmp (argv[1], "-v") == 0 || strcmp (argv[1], "-h") == 0)))
        {
                show_help();
                exit(0);
        }
	*/

	signal(SIGPIPE, SIG_IGN);	
	SDLOG_INIT("../conf/log4cxx.cfg");
	if (load_conf(argv[1],g_conf)<0 || !load_server_config(argv[2])) {
		fprintf(stderr,"load conf error\n");
		return -1;
	}	
	g_logstat.events = g_conf.log_events;
	g_logstat.to_syslog = g_conf.log_to_sys;
   	g_logstat.spec = g_conf.log_spec;
	if (ul_openlog(g_conf.log_path, g_conf.log_name,&g_logstat, 1000) == -1) {
		fprintf(stderr,"open log file error!\n");
		return -1;
	}
	
	int ret = init();
	if (ret < 0) {
		ul_writelog(UL_LOG_FATAL, "init fail");
		return -1;
	}
	printf("ready...\n");
	ul_writelog(UL_LOG_NOTICE, "Service start");
	//----------------------------------------------------------------//
	int sock_listen = x_server(g_conf.port, 500);

	if (sock_listen < 0) {
		ul_writelog(UL_LOG_FATAL, "Can't create watch socket on [%d]", g_conf.port);
		return -1;
	}
	pthread_create(&load_tid, NULL, reload_thread, NULL);
	tids = (pthread_t *)malloc(sizeof(pthread_t) * g_conf.thread_num);
	if (tids == NULL) {
		ul_writelog(UL_LOG_FATAL, "create tids fail");
		return -1;
	}

	//for (long i = 0; i < 10; i++) {
	for (long i = 0; i < g_conf.thread_num; i++) {
        // cout << "initialize thread: " << i << endl;
		if(pthread_create(&(tids[i]), NULL, server_thread, (void *)i) != 0) {       
			tids[i] = 0;
			ul_writelog(UL_LOG_FATAL, "Can't create server thread [%d]", (int)i);
		}
		sleep(1);
	}
    // cout << "--- --- initialize all server_thread " << g_conf.thread_num << endl;
	watch(&sock_listen);
	for (long i = 0; i < g_conf.thread_num; i++) {
		if( tids[i] != 0 ) {
		    pthread_join(tids[i], NULL);
		}
	}	
	return 0;
}


