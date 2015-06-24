/**
 * @file
 * @brief �����
 */
//**********************************************************
//          Net Utility 1.0
//
//  Description:
//   Wrap and functional functions about net communication.
//
// Author: Wang Chengqing
//         cwang@baidu.com
//**********************************************************

#ifndef __UL_NETLIB_H__
#define	__UL_NETLIB_H__

//******************************************
//include area 
//*****************************************
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
#include "dep/dep_net.h"
#include "ul_conf.h"

#define IPACCESS_GRANT_LEN                     256
extern char ul_ipaccess_grant[IPACCESS_GRANT_LEN + 1];

/**
 * socket()�İ�װ����
 *
 * @note �����ͷ���ֵ��socket()��ͬ
 */
extern int ul_socket(int family, int type, int protocol);

/**
 * connect()�İ�װ����
 *
 * @note �����ͷ���ֵ��connect()��ͬ
 */
extern int ul_connect(int sockfd, const struct sockaddr *sa, socklen_t addrlen);

/**
 * bind()�İ�װ����
 *
 * @note �����ͷ���ֵ��bind()��ͬ
 */
extern int ul_bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);

/**
 * listen()�İ�װ����
 *
 * @note �����ͷ���ֵ��listen()��ͬ
 */
extern int ul_listen(int sockfd, int backlog);

/*
 * function : read the global ip access grant in config struct.
 *          : only those ips matching the grant string will be
 *          : allowed
 * argu-in  : pd_conf, the config struct
 * argu-out : the global variable ul_ipaccess_grant
 * return   : 0 always
 * notice   : the name-value pair format:
 *          : ip-access-grant : grant-string
 *          : grant-string as 
 *          : *.192.168-160.*;127.*.*.*;...
 *          : if  ip-access-grant does not exist, default string 
 *          :    ("127.0.0.1;192.168.1.*") will be set.
 *          : if this function have never been called, all ip are allowed
 */
extern int ul_read_ipaccess_grant(ul_confdata_t * pd_conf);

/**
 * accept()�İ�װ����ǿ����
 * �����������accept֮ǰ��reset�����⣨<b>UNPv1:Connection Abort before \c accept Returns</b> ��\n
 * �ṩip���ʿ��ƣ�����ul_ipaccess_grant��
 *
 * @note �����ͷ���ֵ��accept()��ͬ
 */
extern int ul_accept(int sockfd, struct sockaddr *sa, socklen_t * addrlen);

/**
 * getsockname()�İ�װ����
 *
 * @note �����ͷ���ֵ��getsockname()��ͬ
 */
extern int ul_getsockname(int sockfd, struct sockaddr *localaddr, socklen_t * addrlen);

/**
 * getpeername()�İ�װ����
 *
 * @note �����ͷ���ֵ��getpeername()��ͬ
 */
extern int ul_getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t * addrlen);

/**
 * setsockopt()�İ�װ����
 *
 * @note �����ͷ���ֵ��setsockopt()��ͬ
 */
extern int ul_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/**
 * getservbyname_r()�İ�װ����
 *
 * @note �����ͷ���ֵ��getservbyname_r()��ͬ
 */
extern int ul_getservbyname_r(const char *name, const char *proto, struct servent *result_buf,
							  char *buf, size_t buflen, struct servent **result);

/**
 * getservbyport_r()�İ�װ����
 *
 * @note �����ͷ���ֵ��getservbyport_r()��ͬ
 */
extern int ul_getservbyport_r(int port, const char *proto, struct servent *result_buf,
							  char *buf, size_t buflen, struct servent **result);

/**
 * select()�İ�װ����
 * ���ź��ж��Ժ���Զ�����
 *
 * @note �����ͷ���ֵ��select()��ͬ
 */
extern int ul_select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds,
					 struct timeval *timeout);

/**
 * ��ñ������ֽ���
 *
 * @return 1ΪBig-endian��0ΪLittle-endian��-1Ϊ�жϳ���
 */
extern int ul_gethostbyteorder();

# define	UL_GET	1
# define	UL_SET	0
/******************************************************
 * function : Operate the receive buff of socket.
 * argu     : s:the socket id;
 *          : optval: the address which store the buffer size.
 *          : mode: operate mode.one is UL_GET and the other is UL_SET.
 * return   : just a simple wrap of getsockopt and setsockopt
 *          : return value is same with them
 ******************************************************/
extern int ul_opsockopt_rcvbuf(int s, void *optval, char mode);

//******************************************************
// Operate the send buff of socket.
// para:
//      s:the socket id;
//      optval: the address which store the buffer size.
//      mode:   operate mode.one is GET and the other is UL_SET.
//******************************************************
extern int ul_opsockopt_sndbuf(int s, void *optval, char mode);

#define		UL_CLOSE	0
#define		UL_OPEN	1
//******************************************************
// Operate the switch SO_REUSEADDR. Use this function you could 
// find the state<OPEN/CLOSE> of this switch 
// para:
//      s:      the socket id;
//      optval: the address which store the operation.the relevant value is OPEN/CLOSE
//      mode:   operate mode.one is UL_GET and the other is UL_SET.
//******************************************************
extern int ul_opsockopt_ruseaddr(int s, int *op, char mode);
#if SO_REUSEPORT
extern int ul_opsockopt_ruseport(int s, int *op, char mode);
#endif

//******************************************************************
// Operate the switch SO_KEEPALIVE. Use this function you could 
// find the state<OPEN/CLOSE> of this switch 
// para:
//      s:      the socket id;
//      optval: the address which store the operation.the relevant value is OPEN/CLOSE
//      mode:   operate mode.one is UL_GET and the other is UL_SET.
//******************************************************************
extern int ul_opsockopt_keepalive(int s, int *op, char mode);

//****************************************************************** 
// Operate the option SO_SNDTIMEO. Use this function you could
// find the current value of this option
// para:
//      sockfd:      the socket id;
//      struct timeval : the time struct which store the time.
//      mode:   operate mode.one is UL_GET and the other is UL_SET.
//******************************************************
int ul_opsockopt_sndtimeo(int sockfd, struct timeval *tv, char mode);

//******************************************************
// /Get/Set socket read timeout
// Operate the option SO_RCVTIMEO. Use this function you could
// find the current value of this option
// para:
//      sockfd:      the socket id;
//      struct timeval : the time struct which store the time.
//      mode:   operate mode.one is UL_GET and the other is UL_SET.
//******************************************************
int ul_opsockopt_rcvtimeo(int sockfd, struct timeval *tv, char mode);

//********************************************************************
// Fill data struct <struct sockaddr_in> of IPV4.
//********************************************************************
int ul_fillsa4(struct sockaddr_in *sin, char *ip, int port);

//********************************************************************
//  TcpListen:
//      Start a server on local machine at port number with ANY address
//  queue, the listen sock backlog number
//********************************************************************
/**
 * ��ָ���˿ں����б���IP����������
 *
 * @param port �˿�
 * @param queue ���Ӷ��г��ȣ�listen�е�backlog������
 * @return -1ʧ�ܣ�����Ϊ����socket
 */
extern int ul_tcplisten(int port, int queue);

//****************************************************************
// function : a  time-out version of connect() 
// for millisecond
// while exit on error,close sockfd
// sockfd,saptr,socklen, as the same as connect
// secs, the ovet time, in second
//****************************************************************
extern int ul_connecto_sclose_ms(int sockfd, const struct sockaddr *saptr, socklen_t socklen,
								 int msecs);
//****************************************************************
// function : a  time-out version of connect().
// sockfd,saptr,socklen, as the same as connect
// isecs, the ovet time, in millisecond 
// msec = 0 return immediately
// msec < 0 not return until connected
//****************************************************************
/**
 * ����ͬ@ref ul_connecto()����ʱֵ��λΪ����
 *
 * @param sockfd,saptr,secs ������connect()��ͬ
 * @param msecs ��ʱֵ��ms��
 * @return 0�ɹ���-1ʧ��
 */
extern int ul_connecto_ms_ex(int sockfd, const struct sockaddr *saptr, socklen_t socklen,
							 int msecs);


//********************************************************************
//  ul_tcpconnecto_ms
//      Time out version for millisecond
//      Build up a TCP connection to host at port.  This is used at
//      client part, returns the socket fd on success, or -1 on error
// argu  : host,port, the target host and it's port
//         secs, the over time, in second
//         �̲߳���ȫ
//********************************************************************
extern int ul_tcpconnecto_ms(char *host, int port, int msecs);

//******************************************************
// Start a unix domain server on a path.
// Return value:
// On success,return a socket descriptor.Otherwise,return -1.
//*******************************************************
extern int ul_tcpdomainlisten(char *path, int queue);

//********************************************************************
// Bulid up a unix domain connection.
// On success,return the socket descriptor.Otherwise,return -1.
//********************************************************************
extern int ul_tcpdomainconnect(char *path);

/**
 * ��socketд��ָ�����ȵ����ݣ�ֱ��д�����socket����(block mode)
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @return -1��������Ϊʵ��д���ֽ���
 *
 * @note socket��Ҫ��������ģʽ
 */
extern ssize_t ul_swrite(int fd, void *ptr1, size_t nbytes);

/**
 * recv()�İ�װ����
 *
 * @note �����ͷ���ֵ��recv()��ͬ
 */
ssize_t ul_recv(int sockfd, void *buf, size_t len, int flags);

/**
 * send()�İ�װ����
 *
 * @note �����ͷ���ֵ��send()��ͬ
 */
ssize_t ul_send(int sockfd, const void *buf, size_t len, int flags);

/**
 * ����ͬ@ref ul_sreadable()����ʱֵ��λΪ����
 *
 * @param fd socket���
 * @param mseconds ��ʱֵ��ms��
 * @return -1����0��ʱ��>0�ɶ�
 */
extern int ul_sreadable_ms(int fd, int mseconds);

/**
 * ����ͬ@ref ul_swriteable()����ʱֵ��λΪ����
 *
 * @param fd socket���
 * @param mseconds ��ʱֵ��ms��
 * @return -1����0��ʱ��>0��д
 */
extern int ul_swriteable_ms(int fd, int mseconds);

/**
 * ����ͬ@ref ul_sreadable_tv
 *
 * @param fd socket���
 * @param timeval ��ʱʱ��
 * @return -1����0��ʱ��>0��д
 */
extern int ul_sreadable_tv(int fd, struct timeval *tv);

/**
 * ����ͬ@ref ul_sreado_ex()����ʱֵ��λΪ����
 *
 * @param fd ��ȡsocket
 * @param ptr ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param mseconds ��ʱֵ��ms��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 */
extern ssize_t ul_sreado_ms_ex(int fd, void *ptr, size_t nbytes, int mseconds);
extern ssize_t ul_reado_tv(int fd, void *ptr1, size_t nbytes, struct timeval *tv);


/**
 * ����ͬ@ref ul_reado()����ʱֵ��λΪ����
 *
 * @param fd ��ȡsocket
 * @param ptr1 ���ݽ��ջ�����
 * @param nbytes Ҫ��ȡ���ֽ���
 * @param msecs ��ʱֵ��ms��
 * @return -1��������Ϊʵ�ʶ�ȡ�ֽ���
 */
extern ssize_t ul_reado_ms(int fd, void *ptr1, size_t nbytes, int msecs);

/**
 * ����ͬ@ref ul_swrite_ex()����ʱֵ��λΪ����
 *
 * @param fd д��socket
 * @param ptr ���ݷ��ͻ�����
 * @param nbytes Ҫд����ֽ���
 * @param mseconds ��ʱֵ��ms��
 * @return -1��������Ϊʵ��д���ֽ���
 */
extern ssize_t ul_swriteo_ms_ex(int fd, void *ptr, size_t nbytes, int mseconds);



/**
 * @brief ����ʱ��ʵ����ul_sreado_ms_ex��ͬ, CPU�����ĸ���
 *
 * @param [in] socket   : ����socket�ֱ�
 * @param [out] ptr   : ��Ҫ����buff
 * @param [in] nbytes   : ��Ҫ�������ݳ���
 * @param [in] msecs   : ��ʱʱ��
 * @return  -1 ����,������errno�жϳ����� 
**/
extern ssize_t ul_sreado_ms_ex2(int socket, void *ptr, size_t nbytes, int msecs);

/**
 * @brief д��ʱ��ʵ����ul_writeo_ms_ex�� CPU�����ĸ���
 *
 * @param [in] socket   : д��socket���
 * @param [in] ptr   : ��Ҫд��buff
 * @param [in] nbytes   : ��Ҫд�ĳ���
 * @param [in] msecs   : ��ʱʱ��
 * @return  -1 ����,������errno�жϳ�����
**/
extern ssize_t ul_swriteo_ms_ex2(int socket, const void *ptr, size_t nbytes, int msecs);

/**
 * @brief ���buff������
 *
 * struct iovec �ṹ ��ϵͳͷ�ļ� sys/uio.h�ж���
 *
 * struct iovec {
 *     __ptr_t iov_base;
 *     size_t iov_len;
 * };
 *
 * @param [in] socket   : ��Ҫ���ݵ�socket
 * @param [out] ve   : ���ܵĶ��buff
 * @param [in] count   : buff�ĸ���
 * @param [in] msecs   : ��ʱʱ��
 * @note  count�Ĵ�С���ܳ�����  IOV_MAX
 * @return  -1 ���� ������errno�жϳ��Ľ�� 
**/
extern ssize_t ul_sreadv_ms(int socket, const struct iovec *ve, int count, int msecs);

/**
 * @brief д����buff������
 *
 * struct iovec �ṹ ��ϵͳͷ�ļ� sys/uio.h�ж���
 *
 * struct iovec {
 *     __ptr_t iov_base;
 *     size_t iov_len;
 * };
 *
 * @param [in] socket   : ��Ҫд���ݵ�socket
 * @param [out] ve   : ��Ҫд���ݵĶ��buff
 * @param [in] count   : buff�ĸ���
 * @param [in] msecs   : ��ʱʱ��
 * @note  count�Ĵ�С���ܳ�����  IOV_MAX
 * @return  -1 ���� ������errno�жϳ��Ľ�� 
**/

extern ssize_t ul_swritev_ms(int socket, const struct iovec *ve, int count, int msecs); 

//****************************************************************
// Read a line data from socket speed. For safety in mutithreads,you should defined
// data struct Rline.In this function ,will read MAXLINE data from socket once.
//****************************************************************
#define	MAXLINE	1240
typedef struct Rline{
	int read_fd;
	char *read_ptr;
	size_t read_maxlen;
	int rl_cnt;
	char *rl_bufptr;
	char rl_buf[MAXLINE];
} Rline;

/** ��socket��ȡһ���ַ�����ֱ����������������socket������ʱ���߹ر�
 *
 * @param fd ��ȡ���ݵ�Դsocket���
 * @param p  ���ݽ��ջ�����
 * @param len ���ݻ�������С
 * @param Rline ��ȡ������
 * @param msecs ��ʱʱ�� ��λ����
 * @return -1 ���������߳�ʱ�� ����Ϊʵ�ʶ�ȡ�ֽ���
 */ 
extern ssize_t ul_readline_speedo_ms_ex(int fd, void *p, size_t len, Rline *rlin, int msecs);

/**
 * close()�İ�װ����
 *
 * @note �����ͷ���ֵ��close()��ͬ
 */
extern int ul_sclose(int fd);

//*******************************************************
// Close one socket and force FIN created and sent whenever this socket was
// been open by other process.
// argument howto include:
//              SHUT_RD<0>//SHUT_WR<1>//SHUT_RDWR<2>
//*******************************************************
/**
 * shutdown()�İ�װ����
 *
 * @note �����ͷ���ֵ��shutdown()��ͬ
 */
extern int ul_shutdown(int sockid, int howto);

//**************************************
//  Get datat struct hostent of one host
//  mutithread safe and for LINUX version
//  note: you should define the size of buf was less then 8192
//      error code was returned by point h_err.
//  the error code is in err:
//  ERANGE:  buf size too small
//  HOST_NOT_FOUND: Authoritive Answer Host not found
//  TRY_AGAIN:   Non-Authoritive Host not found, or SERVERFAIL
//  NO_RECOVERY: Non recoverable errors, FORMERR, REFUSED, NOTIMP
//  NO_DATA:     Valid name, no data record of requested type
//  NO_ADDRESS:  no address, look for MX record
//  MutliThread:    safe
//**************************************
/**
 * gethostbyname_r()�İ�װ����
 *
 * @note ������gethostbyname_r()��ͬ
 * @return 0�ɹ���-1����
 */
extern int ul_gethostbyname_r(const char *hostname, struct hostent *result_buf, char *buf,
							  int buflen, struct hostent **result, int *h_err);

//*******************************************************
//  Get IP address of one host. Return the h_addr item.
//  Return value:   0 :success;
//                  -1:hostname is error.
//                  -2:gethostbyname_r() call is error.
//                  You can look the errno number by Global Variable errno.
//  Out Mode:       #define BD_ASCII    0
//                  #define BD_NET      1
//  MutliThread:    safe
//******************************************************
# define	BD_ASCII	0
# define	BD_NET		1
extern int ul_gethostipbyname_r(const char *hostname, struct sockaddr_in *sin, int mode,
								char *asc_str);

# define IP_GROUP_NUM      10
typedef struct {
	int addrtype;
	u_int ip[IP_GROUP_NUM];
} sip_group;

//*******************************************************
//  Get IP address group of one host. Return the h_addr item.
//  MutliThread:        safe
//*****************************************************************************

extern int ul_gethostallipbyname_r(const char *hostname, struct sockaddr_in *sin, int mode,
								   char *asc_str, sip_group * sip);


//********************************************************
// Set a socket descriptor's flag about non_block
// Return value:
//      0:success;      -1:failed.
//********************************************************
int ul_setsocktonoblock(int sd);

//********************************************************
// Set a socket descriptor's flag about block
// Return value:
//      0:success;      -1:failed.
//********************************************************
int ul_setsocktoblock(int sd);

//**************************************************************
// Check the size of data in receive queue.
// Return value:
// on success,return the data size.Otherwise return -1
// �õ����ն��л������������ֽ���
//**************************************************************
ssize_t ul_getrecvqueuesize(int sd);

//****************************************************************
// Get the port by server name
// Return value: on success,return the port. Otherwise,return -1.
// ���ݷ������õ���Ӧ�Ķ˿ںš�
//****************************************************************
int ul_getportbyserv(const char *name, const char *proto, int *port);

#endif
