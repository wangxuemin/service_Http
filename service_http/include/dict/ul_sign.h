/**
 * @file
 * @brief ��������ǩ��
 */
//***********************************************************************
//			Signature Utilities (SU) 1.0
//
//   programmed by Ming Lei, Jul, 2000
//***********************************************************************


#ifndef __UL_SIGN_H__
#define __UL_SIGN_H__

#include <ul_func.h>

/**
 *  Ϊ�ַ�������Ψһ��64λ����ǩ��
 *  
 *  @param[in]  psrc  Դ�ַ���
 *  @param[in]  slen  �ַ����ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * - 1   �ɹ�
 * - -1  ʧ��
 *  @note �쳣�����
 * - if slen<0���п��ܳ��ֳ����쳣��
 * - if slen==0��sign = 0:0��
 */
int creat_sign_f64 (char* psrc, int slen, unsigned int* sign1 , unsigned int* sign2);



/**
 *  Ϊһ��data����Ψһ��64λ����ǩ��
 *  
 *  @param[in]  psrc  src data
 *  @param[in]  slen  data�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * - 1   �ɹ�
 * - -1  ʧ��
 *  @note �쳣�����
 * - if slen<0���п��ܳ��ֳ����쳣��
 * - if slen==0��sign = 0:0��
 */
int creat_sign_fs64 (char* psrc, int slen, unsigned int* sign1 , unsigned int* sign2);



/**
 *  Ϊ�ַ�������Ψһ��56λ����ǩ��
 *  
 *  @param[in]  psrc  src str
 *  @param[in]  slen  str�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * - 1   �ɹ�
 * - -1  ʧ��
 *  @note �쳣�����
 * - if slen<0���п��ܳ��ֳ����쳣��
 * - if slen==0��sign = 0:0��
 */
int creat_sign_7_host (char* psrc, int slen, unsigned int* sign1 , unsigned int* sign2);



/**
 *  Ϊ�ַ�������Ψһ��md5 64λ����ǩ��
 *  
 *  @param[in]  psrc  src str
 *  @param[in]  slen  str�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * -  1   �ɹ�
 */
int creat_sign_md64(char* psrc,int slen,unsigned int* sign1,unsigned int*sign2);

/**
 *  Ϊһ�����ݴ���Ψһ��md5 64λ����ǩ��
 *  
 *  @param[in]  psrc  src data
 *  @param[in]  slen  data�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * - 1   �ɹ�
 */
int creat_sign_mds64(char* psrc,int slen,unsigned int* sign1,unsigned int*sign2);

/**
 *  Ϊ�ַ�������Ψһ��murmurhash 64λ����ǩ��
 *  
 *  @param[in]  psrc  src str
 *  @param[in]  slen  str�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * -  1   �ɹ�
 */
int creat_sign_murmur64(const char* psrc,int slen,unsigned int* sign1,unsigned int*sign2,unsigned int seed=0);

/**
 *  Ϊһ�����ݴ���Ψһ��murmurhash 64λ����ǩ��
 *  
 *  @param[in]  psrc  src data
 *  @param[in]  slen  data�ĳ���
 *  @param[out] sign1 ���ص�����ǩ���ĸ�32λ
 *  @param[out] sign2 ���ص�����ǩ���ĵ�32λ
 *  @return �������
 * - 1   �ɹ�
 */
int creat_sign_murmurs64(const char* psrc,int slen,unsigned int *sign1,unsigned int *sign2,unsigned int seed=0);

#endif
