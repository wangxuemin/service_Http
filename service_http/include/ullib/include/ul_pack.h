/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: ul_pack.h,v 1.3 2009/09/18 11:02:57 sun_xiao Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_pack.h
 * @author baonh(baonh@baidu.com)
 * @version $Revision: 1.3 $ 
 * @brief pack����д
 *  
 **/

#ifndef __PACK_UL_H__
#define __PACK_UL_H__

#include <errno.h>
#include <unistd.h>

#include "ul_log.h"
#include "ul_net.h"
#include "ul_func.h"

#include "dep/dep_pack.h"

#define MAX_PACK_ITEM_NUM  200			/**< ���Բ����name:value���������       */
#define MAX_ITEM_SIZE  256				/**< name��value����󳤶�       */
#define SIZE_NUM  20
#define MAX_HEAD_SIZE  26000				/**< ����ͷ��󳤶� */

typedef struct ul_package {
    char name[MAX_PACK_ITEM_NUM][MAX_ITEM_SIZE];
    char value[MAX_PACK_ITEM_NUM][MAX_ITEM_SIZE];
    int pairnum;      /**< name:value �Եĸ�����������MAX_PACK_ITEM_NUM       */
    int bufsize;      /**< �����buff����       */
    char *buf;        /**< �����buff��ʹ��ʱ��Ҫ�ⲿ������뺯��       */
} ul_package_t;

//typedef struct ul_package_t ul_package_t;

/**
 *  @brief ����pack�ռ�
 *
 *  
 *  @note û�з��� char *buf�õĿռ�, ʹ��ʱ�� @ref ul_pack_putbuf ��ӻ�����
 *  @see ul_pack_free ul_pack_putbuf
 *  @return ָ��pack�ռ��ָ��
 *  - NULL   ��ʾʧ��
 *  - ��NULL ��ʾ�ɹ�
 */
ul_package_t *ul_pack_init();

/**
 *  @brief �ͷ�pack�ռ�
 * 
 *
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @note buff�еĿռ���Ҫ�û��Լ��ͷ�
 *  @return ָ��pack�ռ��ָ��
 *  - 0   ��ʾ�ɹ�
 */
int ul_pack_free(ul_package_t *ppack);

/**
 *  @brief ��pack������ӻ�����
 *  
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @param[in]  buffer :  ����ӵĻ�����
 *  @param[in]  size :  �������Ĵ�С
 *  @return �����������
 *  - 0   ��ʾ�ɹ�
 *  - <0  ��ʾʧ��
 */
int ul_pack_putbuf(ul_package_t *ppack, char *buffer, int size);

/**
 *  @brief ��pack���л�ȡ��������ַ
 *  
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @return ָ�򻺳�����ָ��
 *  - ��NULL   ��ʾ�ɹ�
 *  - NULL     ��ʾʧ��
 */ 
char *ul_pack_getbuf(ul_package_t *ppack);

/**
 *  @brief ��pack����������ֺ�ֵ
 *  
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @param[in]  pname : ��ӵ�����
 *  @param[in]  pvalue : ���ֶ�Ӧ��ֵ
 *  @return �����������
 *  - 1  �����Ѵ��ڣ���ӳɹ�
 *  - 0  �ɹ�
 *  - -1 ���ֻ�ֵ���������ȣ�ʧ��
 *  - -2 packû�пռ䣬ʧ��
 */  
int ul_pack_putvalue(ul_package_t *ppack, const char *pname, const char *pvalue);

/**
 *  @brief ��pack��ȡָ�����ֵ�ֵ
 *  
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @param[in]  pname  : ��ӵ�����
 *  @param[out]  pvalue : ���ֶ�Ӧ��ֵ
 *  @param[in]   size : pvalue�ĳ�������,����'\\0'
 *  @return �����������
 *  @see ul_pack_putvalue
 *  - 1  �ɹ�
 *  - 0  ʧ��
 */ 
int ul_pack_getvalue_ex(ul_package_t *ppack, const char *pname, char *pvalue, size_t size);

/**
 * @brief ɾ��ָ�����ֵ�ֵ
 *
 * @param [in] ppack   : ul_package_t*
 * @param [in] pname   : const char* delete key name
 * @return  int 
 * -1 : ������� ���� key������
 * 0 : �ɹ�
 * @retval   
 * @see 
 * @note 
 * @author sun_xiao
 * @date 2009/08/26 15:33:16
**/
int ul_pack_delvalue(ul_package_t *ppack, const char *pname);

/**
 *  @brief ��ָ���ľ����ȡpack����֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd   :   ���Ӿ��
 *  @param[in]  ppack    :   ָ��pack�ռ�
 *  @param[in]  msec     :   ��ʱʱ��
 *  @param[out] ppack    :   ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 *
 */
int ul_pack_reado_ms(int sockfd, ul_package_t *ppack, int msec);

/**
 *  @brief д��socketдpack,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd   :   ���Ӿ��
 *  @param[in]  ppack    :   ��д��pack��
 *  @param[in]  msec     :   ��ʱʱ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 *  - -2  �������
 *  @note ע��дʱ����buff��������@ref ul_pack_putbufָ����size, ������buff����󳤶�
 *  
 */
int ul_pack_writeo_ms(int sockfd, const ul_package_t *ppack, int msec);


/**
 *  дpack�����Ƚ�pack���������ʱ���������ٽ�������������ͨ�����Ӿ��д��,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd :   ���Ӿ��
 *  @param[in]  ppack  :   ��д��pack��
 *  @param[in]  msec   :   ��ʱʱ��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_write_mo_ms(int sockfd, ul_package_t *ppack, int msec);

/**
 *  @brief ���pack����ͷ����pack�������ֺ�ֵ
 *  
 *  @param[in]  ppack   :  ָ��pack�ռ�
 *  @return �����������
 *  - 1    �ɹ�
 *  - -1   ʧ��
 */
int ul_pack_cleanhead(ul_package_t* ppack);

 
/**
 *  @brief ���pack���е���������(buff ʹ�õ�ָ��û�б�free, ��ע�����ⲿ�ͷſռ�)
 *  
 *  @param[in]  ppack   :  ָ��pack�ռ�
 *  @return �����������
 *  - 1    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_cleanall(ul_package_t* ppack);


#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
