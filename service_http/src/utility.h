#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

#include <netdb.h>
#include <sys/un.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include "ul_dict.h"
#include "signdict.h"

#ifndef TIMEDIFF
#define TIMEDIFF(s, e)          ((e.tv_sec-s.tv_sec)*1000000 + e.tv_usec- s.tv_usec)
#endif

void x_pdebug(char *fmt, ...);
int x_flog(FILE * fp, char *fmt, ...);
int x_server(unsigned short port, int listennum);
int x_accept(int socksvr, unsigned int &ip);
int x_connect(char *ip, unsigned short port, char trytimes, int interval);
int x_readsock(int sock, char *pool, char *e, int *len);
int x_read(int sock, char *buf, int nbytes);
int x_read_o(int sock, char *buf, int nbytes, int nSec);
int x_read_o(int sock, char *buf, int nbytes, struct timeval* tv);
int x_write(int sock, char *buf, int nbytes);

/** 
 *  brief: op1 which make it easy to use sign_dict upon old code.
 *  op only support
 *      ADD MOD SEEK.
 */
SignDict* signdict_load( const char* path, const char* fname );
int signdict_seek_other( SignDict* dict, Sdict_snode* node );
int signdict_seek_code( SignDict *dict, Sdict_snode *node ) ;
int signdict_seek_all( SignDict *dict, Sdict_snode *node ) ;
int * read_vector(const char *fn);
#endif
