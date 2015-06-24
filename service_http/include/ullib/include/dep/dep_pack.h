/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_pack.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_pack.h
 * @author baonh(baonh@baidu.com)
 * @version $Revision: 1.2 $ 
 * @brief pack����д
 *  
 **/

#ifndef __DEP_PACK_H__
#define __DEP_PACK_H__



/**
 *  @brief Ϊ�����ϰ汾��ul_package������
 *
 *  @deprecated �����¹淶�ṹ�������Ӧ�� _t��β, �µİ汾Ӧ��ʹ��ul_package
 *
 */
typedef struct ul_package ul_package;

typedef struct ul_package ul_package_t;
/**
 *  @brief ��pack��ȡָ�����ֵ�ֵ, ���ȡ������pvalueû�г�������,�������дԽ��
 *  
 *  @param[in]  ppack :  ָ��pack�ռ�
 *  @param[in]  pname  : ��ӵ�����
 *  @param[out]  pvalue : ���ֶ�Ӧ��ֵ
 *  @return �����������
 *  @see ul_pack_getvalue_ex ul_pack_putvalue
 *  - 1  �ɹ�
 *  - 0  ʧ��
 *  @deprecated pvalueû�г�������,�������дԽ��
 */ 
int ul_pack_getvalue(ul_package_t *ppack, char *pname, char *pvalue);


/**
 *  @brief ��ָ���ľ����ȡpack��, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  sockfd  ���Ӿ��
 *  @param[in]  ppack   ָ��pack�ռ�
 *  @param[out] ppack   ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 *  @deprecated ������ʱ����,���Ƽ�ʹ��
 */
int ul_pack_read(int sockfd, ul_package_t *ppack);

 
/**
 *  @brief ��ָ���ľ�� ��ȡ����, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  fd   :   ���Ӿ��
 *  @param[in]  ptr1 :   ���ջ�����
 *  @param[in]  nbytes :  Ҫ��ȡ���ݵ��ֽ���
 *  @param[out] ptr1   :  ��ȡ������
 *  @return �����������
 *  - >0  ʵ�ʶ�ȡ���ֽ���
 *  - <=0   ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */ 
int ul_pack_readall(int fd, void *ptr1, size_t nbytes);

/**
 *  @brief ��ȡ���Ľ�����־, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  fd   :   ���Ӿ��
 *  @return �����������
 *  - 0  �ɹ�
 *  - -1 ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��, �ڲ�������Ӧ�ö��⿪��
 */ 
int ul_pack_readend(int sockfd);


/**
 *  @brief д��socketдpack, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  sockfd   :   ���Ӿ��
 *  @param[in]  ppack    :   ��д��pack��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */ 
int ul_pack_write(int sockfd, ul_package_t *ppack);

 
/**
 *  @brief ��ָ���ľ��д����(Inner function), �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  sockfd  :  ���Ӿ��
 *  @param[in]  buf     :  ��д����
 *  @param[in]  n       :  ���ݵ��ֽ���
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */
int ul_pack_writeall(int sockfd, char *buf, int n);



/**
 *  @brief дpack�����Ƚ�pack���������ʱ��������
 *  �ٽ�������������ͨ�����Ӿ��д��, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  sockfd  :  ���Ӿ��
 *  @param[in]  ppack   :  ��д��pack��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */ 
int ul_pack_write_m(int sockfd, ul_package_t *ppack);


 
/**
 *  @brief ��ָ���ľ����ȡ����, �򲻴���ʱ����,���Ƽ�ʹ��
 *  
 *  @param[in]  sockfd    :  ���Ӿ��
 *  @param[in]  ppack     :  ָ��pack�ռ�
 *  @param[in]  over_time :  ��ʱʱ��
 *  @param[out] ppack     :  ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */
int ul_pack_reado(int sockfd, ul_package_t *ppack, int over_time);

 
/**
 *  @brief д��socketдpack,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd   :   ���Ӿ��
 *  @param[in]  ppack    :   ��д��pack��
 *  @param[in]  sec      :   ��ʱʱ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 *  @deprecated �򲻴���ʱ����,���Ƽ�ʹ��
 */
int ul_pack_writeo(int sockfd, ul_package_t *ppack, int sec);


/**
 *  @brief ��ָ���ľ��д����,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd  :  ���Ӿ��
 *  @param[in]  buf     :  ��д����
 *  @param[in]  n       :  ���ݵ��ֽ���
 *  @param[in]  sec     :  ��ʱʱ��
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 *  @deprecated �Ƽ�ʹ�ú��뼶��ʱ����
 */
int ul_pack_writeallo(int sockfd, char *buf, int n, int sec);


/**
 *  дpack�����Ƚ�pack���������ʱ���������ٽ�������������ͨ�����Ӿ��д��,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd  :  ���Ӿ��
 *  @param[in]  ppack   :  ��д��pack��
 *  @param[in]  sec     :  ��ʱʱ��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 *  @deprecated �Ƽ�ʹ�ú��뼶��ʱ����
 */ 
int ul_pack_write_mo(int sockfd, ul_package_t *ppack, int sec);


/**
 *  @brief ��ָ���ľ����ȡ���ݣ�֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  fd       :  ���Ӿ��
 *  @param[in]  ptr1     :  ���ջ�����
 *  @param[in]  nbytes   :  Ҫ��ȡ���ݵ��ֽ���
 *  @param[in]  msec     :  ��ʱʱ��
 *  @param[out] ptr1     :  ��ȡ������
 *  @return �����������
 *  - >0  ʵ�ʶ�ȡ���ֽ���
 *  - <=0   ʧ��
 *  @deprecated �Ƽ�ʹ��ul_net�е�@ref ul_sreado_ms
 */
int ul_pack_readallo_ms(int fd, void *ptr1, size_t nbytes, int msec);

/**
 *  @brief ��ȡ���Ľ�����־��֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd   :   ���Ӿ��
 *  @param[in]  msec     :   ��ʱʱ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 *  @deprecated ��Ӧ����Ϊ�ڲ��������ⲿ��ʹ��
 */ 
int ul_pack_readendo_ms(int sockfd, int msec);


/**
 *  @brief ��ָ���ľ��д����,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd  :  ���Ӿ��
 *  @param[in]  buf     :  ��д����
 *  @param[in]  n       :  ���ݵ��ֽ���
 *  @param[in]  msec    :  ��ʱʱ��
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 *  @deprecated �Ƽ�ʹ��ul_net�е� @ref ul_swriteo_ms_ex ����
 */
int ul_pack_writeallo_ms(int sockfd, char *buf, int n, int msec);



#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
