#include "utility.h"

#include <string>
using namespace std;

#include "ul_log.h"
#include "ul_sign.h"

void x_pdebug(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	fflush(stdout);
}

int x_flog(FILE * fp, char *fmt, ...)
{
	int l = 0;
	va_list ap;
	time_t t;
	struct tm tmdate;
	struct tm *date = &tmdate;

	if( !fp )
		return -1;

	t = time(NULL);
	date = localtime_r(&t, date);

	va_start(ap, fmt);
	l = fprintf(fp, "%02d/%02d %02d:%02d:%02d %d ",
				date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min,
				date->tm_sec, getpid());
	l += vfprintf(fp, fmt, ap);
	l += fprintf(fp, "\n");
	va_end(ap);

	fflush(fp);

	return l;
}


int x_server(unsigned short port, int listennum)
{
	int sock = -1, on = 1;
	struct sockaddr_in local;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		// printf("\nError: create socket fail. [%s]\n\n", strerror(errno));
		return -1;
	}

	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(port);

	if (0 > setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) {
		perror("setsockopt");
		return -1;
	}

	if (bind(sock, (struct sockaddr *) &local, sizeof(local)) < 0) {
//		printf("\nError: server socket bind port %d fail. [%s]\n\n", port, strerror(errno));
		return -1;
	}

	if (listen(sock, listennum) < 0) {
//		printf("\nError: server socket %d listen fail. [%s]\n\n", port, strerror(errno));
		return -1;
	}

	return sock;
}

int x_accept(int socksvr, unsigned int &ip)
{
	int socket = -1, on = 1;
	socklen_t len;
	struct sockaddr_in that;

	len = sizeof(that);
	socket = accept(socksvr, (struct sockaddr *) &that, &len);
	if (socket < 0) {
//		printf("\nError: socket accept fail. [%s]\n\n", strerror(errno));
		return -1;
	}
	ip = that.sin_addr.s_addr;

	setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));

	return socket;
}

int x_connect(char *ip, unsigned short port, char trytimes, int interval)
{
	int sock = -1, ret = 0, on = 1;
	struct sockaddr_in to;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
//		printf("\nError: create socket fail. [%s]\n\n", strerror(errno));
		return -1;
	}

	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));

	bzero(&to, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_addr.s_addr = inet_addr(ip);
	to.sin_port = htons(port);

	while (trytimes > 0) {
		ret = connect(sock, (struct sockaddr *) &to, sizeof(to));
		if (ret == 0) {
			return sock;
		}
		trytimes--;
		if (interval > 0)
			sleep(interval);
	}

//	printf("\nError: connect to server %s:%d fail. [%s]\n\n", ip, port, strerror(errno));
	close(sock);

	return -1;
}


int x_readsock(int sock, char *pool, char *e, int *len)
{
	int size = 0;

	size = read(sock, pool + *len, e - pool - *len + 1);
	if (size < 0) {
//		printf("\nError: read socket error. [%s]\n\n", strerror(errno));
	} else {
		*len += size;
		pool[*len] = 0;
	}
	return size;
}

int x_read(int sock, char *buf, int nbytes)
{
	int nread = 0, nleft = nbytes;

	while (nleft > 0) {
		nread = read(sock, buf, nleft);
		if (nread < 0) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		} else if (nread == 0)
			return 0;
		buf += nread;
		nleft -= nread;
	}

	return (nbytes - nleft);
}

int x_read_o(int sock, char *buf, int nbytes, int nSec)
{
	fd_set fs;
	int ret;

	struct timeval tv;
	tv.tv_sec = nSec;
	tv.tv_usec = 0;	
	
	FD_ZERO(&fs);
	FD_SET(sock, &fs);
	ret = select(sock + 1, &fs, NULL, NULL, &tv);
	if (ret < 0) {
		return ret;
	} else if (ret == 0 ) {
		errno = ETIMEDOUT;
		return -1;
	}	
		
	return x_read(sock, buf, nbytes);
}

int x_read_o(int sock, char *buf, int nbytes, struct timeval* tv)
{
	fd_set fs;
	int ret;
	struct timeval tmptv;


again:
	tmptv = *tv;
	FD_ZERO(&fs);
	FD_SET(sock, &fs);
	ret = select(sock + 1, &fs, NULL, NULL, &tmptv);
	if (ret < 0) {
		if (errno == EINTR) {
			goto again;
		}
		return ret;
	} else if (ret == 0 ) {
		errno = ETIMEDOUT;
		return -1;
	}		
	return x_read(sock, buf, nbytes);
}


int x_write(int sock, char *buf, int nbytes)
{
	int nwrite = 0, nleft = nbytes;

	while (nleft > 0) {
		nwrite = write(sock, buf, nleft);
		if (nwrite < 0) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		} else if (nwrite == 0)
			return 0;
		buf += nwrite;
		nleft -= nwrite;
	}

	return (nbytes - nleft);
}

int signdict_seek_other( SignDict *dict, Sdict_snode *node ) 
{	
	u_int sign[2];
	sign[0] = node->sign1;
	sign[1] = node->sign2;
	u_int data[2];
	data[0] = node->other;
	
	int ret = signdict_search( dict, sign, (u_char*)data );
	if ( ret==SIGNDICT_ERR_NOT_FOUND ) {
		return 0;
	} else if ( ret!=SIGNDICT_OK ) {
		node->other = 0;
		node->code = -1;
		return -1;
	}
	
	// ok.	
	node->other = data[0];
	node->code = 0;
	return 1;
}
int signdict_seek_code( SignDict *dict, Sdict_snode *node ) 
{	
	u_int sign[2];
	sign[0] = node->sign1;
	sign[1] = node->sign2;
	u_int data[2];
	data[0] = node->code;
	
	int ret = signdict_search( dict, sign, (u_char*)data );
	if ( ret==SIGNDICT_ERR_NOT_FOUND ) {
		return 0;
	} else if ( ret!=SIGNDICT_OK ) {
		node->other = 0;
		node->code = -1;
		return -1;
	}
	
	// ok.	
	node->code = data[0];
	node->other = 0;
	return 1;
}

int signdict_seek_all( SignDict *dict, Sdict_snode *node ) 
{	
	u_int sign[2];
	sign[0] = node->sign1;
	sign[1] = node->sign2;
	u_int data[2];
	data[0] = node->other;
	data[1] = node->code;
	
	int ret = signdict_search( dict, sign, (u_char*)data );
	if ( ret==SIGNDICT_ERR_NOT_FOUND ) {
		return 0;
	} else if ( ret!=SIGNDICT_OK ) {
		node->other = 0;
		node->code = -1;
		return -1;
	}
	
	// ok.	
	node->other = data[0];
	node->code = data[1];
	return 1;
}

SignDict* signdict_load( const char* path, const char* name )
{
	string fn = string(path) + "/" + name;
	FILE* fp = fopen( fn.c_str(), "r" );
	if ( !fp ) {
		ul_writelog( UL_LOG_WARNING, "signdict_load() failed on opening file [%s]", fn.c_str() );
		return NULL;
	}

	SignDict* dict = NULL;
	if((dict = signdict_load(fp)) == NULL) {
		ul_writelog( UL_LOG_WARNING, "load SignDict failed");
		return NULL;
	}

	fclose( fp );
	return dict;
}
/**
* @brief 初始化拼音概率向量
* @author unknown
*
* @param[in] fn			拼音概率向量文件名
* @return int*			拼音概率向量
*/
int * read_vector(const char *fn)
{
    FILE *fp = fopen(fn, "rb");
	if(fp == NULL)
	{
	    return NULL;
	}
	int size = 0;
	int ret = fread(&size, sizeof(int), 1, fp);
	if(ret != 1)
	{
	    return NULL;
	}
	int *tmp_freq = (int *)malloc((size+1) * sizeof(int));
	if(tmp_freq == NULL)
	{
	    return NULL;
	}
	ret = fread(tmp_freq, sizeof(int), size, fp);
	if(ret != size)
	{
	    return NULL;
	}
	return tmp_freq;
}

