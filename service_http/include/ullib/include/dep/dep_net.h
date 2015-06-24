/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_net.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_net_dep.h
 * @author xiaowei(com@baidu.com)
 * @date 2007/12/20 12:07:51
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __UL_NET_DEP_H_
#define  __UL_NET_DEP_H_

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

typedef struct Rline Rline;


/*
 * ����Ĳ��Ƽ��ĺ������и��õİ汾����
 */

//****************************************************************
// function : a  time-out version of connect().
// while exit on error,close sockfd
// sockfd,saptr,socklen, as the same as connect
// secs, the ovet time, in second
//****************************************************************
/**
 * ����ͬ@ref ul_connecto()���������ر�sockfd
 *
 * @param sockfd,saptr,secs ������connect()��ͬ
 * @param secs ��ʱֵ��s��
 * @return 0�ɹ���-1ʧ��
 */
extern int ul_connecto_sclose(int sockfd, const struct sockaddr *saptr, socklen_t socklen, int secs);


/**
 * ��socket��ȡָ�����ȵ����ݣ�ֱ������������socket�����Է��ر�(block mode)
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 *
 * @note socket��Ҫ��������ģʽ
 */
extern ssize_t ul_sread(int fd, void *ptr1, size_t nbytes);



/**
 * ����ͬ@ref ul_sreado()����ʱֵ��λΪ����
 *
 * @param fd ��ȡsocket
 * @param ptr ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param mseconds ��ʱֵ��ms��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 * @deprecated ����ͬ@ref ul_sreado()
 */
extern ssize_t ul_sreado_ms(int fd, void *ptr, size_t nbytes, int mseconds);



/**
 * ����ʱ���Ƶ�@ref ul_sread()
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param seconds ��ʱֵ��s��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 *
 * @deprecated ��ʱ���������⣬���ܵ�������ʱ���󳬹�seconds
 */
extern ssize_t ul_sreado(int fd, void *ptr, size_t nbytes, int seconds);

/**
 * ����ʱ���Ƶ�@ref ul_sread()
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param seconds ��ʱֵ��s��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 *
 * @note �Ͼ�ȷ�ĳ�ʱ���ƣ��Ƽ�ʹ��
 */
extern ssize_t ul_sreado_ex(int fd, void *ptr, size_t nbytes, int seconds);


/**
 * ����ͬ@ref ul_swriteo()
 *
 * @param fd д��socket
 * @param ptr ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param mseconds ��ʱֵ��ms��
 * @return -1��������Ϊʵ��д���ֽ���
 *
 * @deprecated ��ʱ���������⣬���ܵ��³�ʱ������
 */
extern ssize_t ul_swriteo_ms(int fd, void *ptr, size_t nbytes, int mseconds);


/**
 * ����ʱ���Ƶ�@ref ul_swrite()
 *
 * @param fd д��socket
 * @param ptr ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param seconds ��ʱֵ��s��
 * @return -1��������Ϊʵ��д���ֽ���
 *
 * @deprecated ��ʱ���������⣬���ܵ��³�ʱ������
 */
extern ssize_t ul_swriteo(int fd, void *ptr, size_t nbytes, int seconds);

/**
 * ����ʱ���Ƶ�@ref ul_swrite()
 *
 * @param fd д��socket
 * @param ptr ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param seconds ��ʱֵ��s��
 * @return -1��������Ϊʵ��д���ֽ���
 *
 * @note �Ͼ�ȷ�ĳ�ʱ���ƣ��Ƽ�ʹ��
 */
extern ssize_t ul_swriteo_ex(int fd, void *ptr, size_t nbytes, int seconds);


/**
 * ����ʱ���Ƶ�@ref ul_read()
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param secs ��ʱֵ��s��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 */
extern ssize_t ul_reado(int fd, void *ptr1, size_t nbytes, int secs);


/**
 * ����ͬ@ref ul_writeo()����ʱֵ��λΪ����
 *
 * @param fd д��socket
 * @param ptr1 ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param mseconds ��ʱֵ��ms��
 * @return -1��������Ϊʵ��д���ֽ���
 */
extern ssize_t ul_writeo_ms(int fd, void *ptr, size_t nbytes, int mseconds);


/**
 * ����ʱ���Ƶ�@ref ul_write()
 *
 * @param fd д��socket
 * @param ptr1 ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param seconds ��ʱֵ��s��
 * @return -1��������Ϊʵ��д���ֽ���
 */
extern ssize_t ul_writeo(int fd, void *ptr, size_t nbytes, int seconds);


/**
 * ���socket��ָ��ʱ�����Ƿ�ɶ�
 *
 * @param fd socket���
 * @param seconds ��ʱֵ��s��
 * @return -1����0��ʱ��>0�ɶ�
 */
extern int ul_sreadable(int fd, int seconds);


/**
 * ���socket��ָ��ʱ�����Ƿ��д
 *
 * @param fd socket���
 * @param seconds ��ʱֵ��s��
 * @return -1����0��ʱ��>0��д
 */
extern int ul_swriteable(int fd, int seconds);


//****************************************************************
// function : a  time-out version of connect().
// sockfd,saptr,socklen, as the same as connect
// secs, the ovet time, in second
//****************************************************************
/**
 * ����ʱ���Ƶ�connect()�汾
 *
 * @param sockfd,saptr,secs ������connect()��ͬ
 * @param secs ��ʱֵ��s��
 * @return 0�ɹ���-1ʧ��
 */
extern int ul_connecto(int sockfd, const struct sockaddr *saptr, socklen_t socklen, int secs);


/**
 * ��socket�ж�ȡһ���ַ�����ֱ����������������socket������߹ر�
 *
 * @param fd ��ȡsocket
 * @param vptr ���ݽ��ջ�����
 * @param maxlen ��������С
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���������\n��
 */
ssize_t ul_readline(int fd, void *vptr, size_t maxlen);


ssize_t ul_readline_speed(int fd, void *vptr, size_t maxlen, Rline * rlin);
ssize_t ul_readline_speedo(int fd, void *vptr, size_t maxlen, Rline * rlin, int secs);


/**
 * ����ʹ�ø��ӷ����connect()�汾
 *
 * @param host ����������ַ��IP��������
 * @param port ���Ӷ˿�
 * @return -1ʧ�ܣ�����Ϊ����socket
 */
extern int ul_tcpconnect(char *host, int port);

/**
 * ����ʱ���Ƶ�@ref ul_tcpconnect()
 *
 * @param host ����������ַ��IP��������
 * @param port ���Ӷ˿�
 * @param secs ��ʱֵ��s��
 * @return -1ʧ�ܣ�����Ϊ����socket
 */
extern int ul_tcpconnecto(char *host, int port, int secs);

//*******************************************************
// Get IP address of one host.  Return the h_addr item.
// Return value:    0 :success;
//                  -1:hostname is error.
//                  -2:gethostbyname() call is error.
// Note:This function is not safe in MT-thread process
//******************************************************
extern int ul_gethostipbyname(const char *hostname, struct sockaddr_in *sin);




#endif  //__UL_NET_DEP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
