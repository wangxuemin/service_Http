/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_exlink.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/



/**
 * @file ul_exlink.h
 * @author com-dev (com-dev@baidu.com)
 * @date 2007/12/14 11:07:50
 * @version $Revision: 1.2 $ 
 * @brief url��ȡ 
 */



#ifndef __DEP_EXLINK_H__
#define __DEP_EXLINK_H__
#include "ul_url.h"

#define  UL_MAX_LINK_NUM     2000
#define  UL_MAX_TEXT_LEN   100

#define UL_METHOD_BAIDU		0
#define UL_METHOD_WGET16	1
#define UL_METHOD_WGET18	2


typedef struct _link_info_t {
	char domain[UL_MAX_SITE_LEN];
	char port[UL_MAX_PORT_LEN];
	char path[UL_MAX_PATH_LEN];
	char text[UL_MAX_TEXT_LEN];
	char url[UL_MAX_URL_LEN];
} link_info_t;



/**
 * ����url����Ե�url���ϳ��µ�url
 * 
 * @param[in]  url ��url
 * @param[in]  relurl ��ص�url�����url
 * @param[in]  absurl �������ݵ�buf��ַ
 * @param[out] absurl ���غϳɵ�url
 * @return �������
 * - 1  �ɹ�
 * - 0  ʧ��
 *  @note ע�����buffer url�Ŀռ���Ҫ�㹻��ͨ��Ҫ����UL_MAX_URL_LENΪ����
 */
int ul_absolute_url(char *url, char *relurl, char *absurl);



/**
 * ����url��Ӧ��page���ݣ��õ��µ�url(��ȡ����)
 * 
 * @param[in]  url       page��url
 * @param[in]  page      page������
 * @param[in]  pagesize  page�Ĵ�С������ܳ���256K(>0)
 * @param[in]  link_info ����link��Ϣ�Ļ���ṹָ��
 * @param[in]  num       �ܹ��洢��url��Ϣ�ĸ���(>0)
 * @param[in]  method    �����ķ���
 * - UL_METHOD_BAIDU 
 * - UL_METHOD_WGET16
 * - UL_METHOD_WGET18	
 * @param[out]  link_info ���ؽ��������µ�url�Ľṹ
 * @return �������
 * - >=0   �ɹ���������ȡ�ɹ���url��
 * - <0    ʧ��
 * @note ʹ��UL_METHOD_BAIDU method����ʱ�����������ڲ���Ҫ��������256K��ջ�ռ䡣
 */
int extract_link(char *url, char *page, int pagesize, link_info_t * link_info, int num, int method);
#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
