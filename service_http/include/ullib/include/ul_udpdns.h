/**
 * @file
 * @brief DNS�ͻ��˺���
 */
#ifndef __UDPDNS_H__
#define __UDPDNS_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h>


#define UDP_DNS_PORT              1280
#define SITE_NAME_LEN             64
#define UDP_MSGLEN                128

// struct 
struct host_struct {
	char domain[SITE_NAME_LEN + 1];
	char ip[INET_ADDRSTRLEN + 1];
};

#include "dep/dep_udpdns.h"

/**
 *  ����UDP������׽���(function include "socket and bind")
 *  
 *  @param[in]  udp_port �˿ں�
 *  @param[out] ��
 *  @return �׽���
 * - >=0 UDP������׽���
 * - -1  ʧ��
 */
extern int ul_udplisten(int udp_port);

/**
 *  ����UDP�ͻ����׽���
 *  
 *  @param[in]  host     ������IP��ַ
 *  @param[in]  udp_port ����˶˿ں�
 *  @param[out] servaddr �����������ַ
 *  @return �׽���
 * - >=0 UDP�ͻ����׽���
 * - -1  ʧ��
 */
extern int ul_udpconnect(char *host, int udp_port, struct sockaddr_in *servaddr);

/**
 *  ���Ͳ�����UDP��Ϣ��֧�ֳ�ʱ
 *  
 *  @param[in]  sockfd     UDP�ͻ����׽���
 *  @param[in]  pservaddr  �����������ַ
 *  @param[in]  datamsg    �����͵���Ϣ
 *  @param[in]  datalen    ��Ϣ����
 *  @param[in]  sec        ��ʱʱ����벿��
 *  @param[in]  usec       ��ʱʱ���΢�벿��
 *  @param[out] datamsg    ��Ž��յ�������
 *  @return ���յ������ݳ���
 * - >=0 ���յ������ݳ���
 * - -1  ʧ��
 */
extern int send_recv_msgo(int sockfd, struct sockaddr *pservaddr, char *datamsg, int datalen,
						  int sec, int usec);

/**
 *  ��DNS��������ȡ������Ӧ��IP��֧�ֳ�ʱ
 *  
 *  @param[in]  sockfd    UDP�ͻ����׽���
 *  @param[in]  servaddr  �����������ַ
 *  @param[in]  domain    ������������
 *  @param[in]  sec       ��ʱʱ����벿��
 *  @param[in]  usec      ��ʱʱ���΢�벿��
 *  @param[out] ip        DNS���������صĽ�������IP
 *  @return ���ؽ��
 * - 0   �ɹ�
 * - -1  ʧ��
 */
extern int gethostwithfd_r_o(int sockfd, struct sockaddr *servaddr, char *domain, char *ip, int sec,
							 int usec);

/**
 *  ��DNS��������ȡ������Ӧ��IP��֧�ֳ�ʱ
 *  
 *  @param[in]  dnshost    DNS��������
 *  @param[in]  port       ����˿�
 *  @param[in]  domain     ������������
 *  @param[in]  sec        ��ʱʱ����벿��
 *  @param[in]  usec       ������������
 *  @param[out] ip         ��ʱʱ���΢�벿��
 *  @return ���ؽ��
 * - 0   �ɹ�
 * - -1  ʧ��
 */
extern int gethostipbyname_r_o(char *dnshost, int port, char *domain, char *ip, int sec, int usec);

#endif
