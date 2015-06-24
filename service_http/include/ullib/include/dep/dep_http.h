/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_http.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/



/**
 * @file ul_http.h
 * @author com-dev(com-dev@baidu.com)
 * @date 2007/12/13 22:30:33
 * @version $Revision: 1.2 $ 
 * @brief �ɰ�http�⣬ֻ���ɹ���ά�������������Ը��������� 
 */



#ifndef __DEP_HTTPLIB_H__
#define	__DEP_HTTPLIB_H__



#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <endian.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "ul_net.h"



#define    MAXURL        256	 /**< Max url length */
#define    MAXHOST       64		 /**< Max url host part length */
#define    MAXFILE        192	 /**< Max url file part length */
#define    MAXPAGE        256000 /**< Max http page lenght */
#define    MAXHEAD        4096	 /**< Mac http head length */
#define    MAXGETCMD      1256	 /**< Max http command length */
#define    MAXIP          16	 /**< Max ip string length */
#define    MAXPORTS        8
/* Write, read and connection timeout for socket */
#define    WRITETIMEOUT   60
#define    READTIMEOUT    300
#define    CONNECTTIMEOUT 30
#define    RETRYTIME      1		 /**< Retry times for tcp connection */
#define    SITE_LEN 100
#define    PORT_LEN 10
#define MAX_ETAG_LEN 64
#define METHOD_GET 1
#define METHOD_CHK 2
#define LASTMOD_FLAG 1
#define ETAG_FLAG 2



/**
 * ���ṹ���Ѿ�����,���Ƽ�ʹ��
 */
typedef struct __page_item {
	int method;
	int orilen;
	int head_flag;
	char url[MAXURL];
	char ip[MAXIP];
	char protocol[4];
	int pagesize;
	int status;
	int conlen;
	char lastmod[MAXLINE];
	char contyp[MAXLINE];
	char trnenc[MAXLINE];
	char etag[MAX_ETAG_LEN];
	char redir[MAXURL];
	char *page;
	int proxy_flag;
} PAGE_ITEM;



/**
 * @brief �ж�URL�Ƿ�Ϸ�
 *
 * @param url �����url
 * @return 1 �Ϸ�; 0 �Ƿ�
 * @deprecated ���������Ƽ�ʹ�ã���ʹ��ullib/ul_check_url
 */
extern int check_URL(char *url);



/**
 * @brief  �ж������Ƿ�Ϸ����Ƿ������¸�ʽ
 * - <hostname> ::= <name>*["."<name>]
 * - <name>  ::= <letter>[*[<letter-or-digit-or-hyphen>]<letter-or-digit>]
 * - <hyphen> ::= '-'-or-'_'
 *
 * @param host_name ����Ĵ��ж����� 
 *
 * @return 1 �Ϸ�; 0 �Ƿ� 
 * @note �������Ѿ�����,���Ƽ�ʹ��,�и��°汾 see ul_url.h
 */
extern int check_hostname(char *host_name);



/**
 * @brief ȡ��meta��ǩ�е�����
 *
 * @param page ��<meta url=redir ...> ��buff
 * @param size page����
 * @param redir meta��ǩ�е�����
 * @return 
 * - 1 �ɹ���ȡ����
 * - 0 ʧ��
 * @note size ���ܳ���1024 
 * @see 
 */
int isconredir(char *page, int size, char *redir);



/**
 * @brief ץȡ��ҳ���� 
 *
 * @param url �����url����
 * @param ip ���ip�ǿ�,ʹ�ô�ip����http����,����dns�������� 
 * @param pagesize 
 * - in, page�ĳ���.  *pagesize=0,ֻ��ȡhead,����ȡҳ������; 
 * - out, ���ػ�õ�ҳ�泤�� *
 * @param head ���http����ͷ��buff, �:4096
 * @param page ���ҳ�����ݵ�buff,��С��pagesize ָ��
 * @param redirurl �����ת���ӵ�buff,�:256
 * @param lastmod ���Last-Modified��buff,δָ����󳤶�...
 * @return
 * - <0 �д���
 * - >0 ��ҳhttp����״̬��
 * @deprecated �������Ѿ�����,���Ƽ�ʹ��,�и��°汾 see libsrc/http
 */
extern int ul_gethttpcontent(char *url, char *ip, int *pagesize, char *head, char *page,
							 char *redirurl, char *lastmod);



/**
 * @brief ץȡ��ҳ��������chunkedת��
 *
 * @param pageitem 
 * - in, ����url,ip,port����Ϣ
 * - out, ����ȡ�õ���ҳ
 * @return 
 * - >0 ��ҳhttp����״̬��
 * - -1 ʧ��
 * - -2 ��ʱ
 * @note ��::ul_gethttpcontent_new_notpt�������ǣ�ץȡ��ҳ��get���ͬ������chunk�ķ�ʽҲ������ 
 * @see ul_gethttpcontent_new_notpt
 */
extern int ul_gethttpcontent_new(PAGE_ITEM * pageitem);



/**
 * @brief ץȡ��ҳ��������chunkedת��
 *
 * @param pageitem 
 * - in, ����url,ip,port����Ϣ
 * - out, ����ȡ�õ���ҳ
 * @return 
 * - >0 ��ҳhttp����״̬��
 * - -1 ʧ��
 * - -2 ��ʱ
 * @note ��ul_gethttpcontent_new�������ǣ�ץȡ��ҳ��get���ͬ��������If-Modified-Since��If-None-Match��������,
 *		����chunk�ķ�ʽҲ������
 */
extern int ul_gethttpcontent_new_notpt(PAGE_ITEM * pageitem);

#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
