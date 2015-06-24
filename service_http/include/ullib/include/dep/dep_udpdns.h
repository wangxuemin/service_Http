/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_udpdns.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_udpdns_dep.h
 * @author xiaowei(com@baidu.com)
 * @date 2007/12/21 11:22:23
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __UL_UDPDNS_DEP_H_
#define  __UL_UDPDNS_DEP_H_


/**
 *  ��DNS��������ȡ������Ӧ��IP
 *  
 *  @param[in]  sockfd    UDP�ͻ����׽���
 *  @param[in]  servaddr  �����������ַ
 *  @param[in]  domain    ������������
 *  @param[out] ip        DNS���������صĽ�������IP
 *  @return ���ؽ��
 * - 0   �ɹ�
 * - -1  ʧ��
 */
extern int gethostwithfd_r(int sockfd, struct sockaddr *servaddr, char *domain, char *ip);



/**
 *  ��DNS��������ȡ������Ӧ��IP
 *  
 *  @param[in]  dnshost    DNS��������
 *  @param[in]  port       ����˿�
 *  @param[in]  domain     ������������
 *  @param[out] ip         DNS���������صĽ�������IP
 *  @return ���ؽ��
 * - 0   �ɹ�
 * - -1  ʧ��
 */
extern int gethostipbyname_r(char *dnshost, int port, char *domain, char *ip);

















#endif  //__UL_UDPDNS_DEP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
