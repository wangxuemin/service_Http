/**
 * @file
 * @brief wml��webҳ���һ�ָ�ʽ�����ʽ��html���ƣ���Ҫ������wap�ֻ��Ͻ�����ʾ����ת���ӿ�ת���ṩ�����ֵ�ת��,\n
 * һ���ǽ�html��ʽ��urlת����wml��ʽ��url����һ���ǽ����ı���֧�����ģ�ת����wml��ʽ��unicode�����ݡ�
 */




#ifndef __WML_CONV__
#define __WML_CONV__

#include "ul_fdict.h"


/**
 *  ��html��ʽ��urlת����wml��ʽ��url
 *  
 *  @param[in]  url    url
 *  @param[in]  ulen   ����url�ĳ���
 *  @param[in]  wapurl �����bufָ��
 *  @param[in]  wlen   ���buf�ĳ���
 *  @param[out] wapurl
 *  @return ���url�ĳ���
 */
int ul_convert_to_wml_url(char *url, int ulen, char *wapurl, int wlen);



/**
 *  �����ı�ת����wml��ʽ������
 *  
 *  @param[in]  src             �����html�ı�
 *  @param[in]  dest            ���buf��ָ��
 *  @param[in]  destlen         ���buf�ĳ���
 *  @param[in]  pwmlKeepDict    ��Ҫ���ֵ��ַ������ֵ�
 *  @param[in]  pwmlConvDict    ��Ҫת�����ַ������ֵ�
 *  @param[in]  pwmlConvList    ת����Ϣ�б�
 *  @param[out] dest            ת������ı�
 *  @return ���url�ĳ���
 */
int ul_convert_to_wml_content(char *src, char *dest, int destlen, fdict_t *pwmlKeepDict, fdict_t *pwmlConvDict, char *pwmlConvList);


/**
 *  ��ʼ������wmlת���Ļ���
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return ��ʼ���Ƿ�ɹ�
 * - 0   �ɹ�
 * - -1  ʧ��
 *  @note ��ȫ�ֱ������г�ʼ�����޲���
 */
int ul_init_wml_conv_env(void);


/**
 *  ����wmlת���Ĵʵ�
 *  
 *  @param[in]  path            load�ֵ��·��
 *  @param[in]  keep_name       �����ֵ���ļ���
 *  @param[in]  conv_name       ת���ֵ���ļ���
 *  @param[in]  pwmlKeepDict    ��Ҫ���ֵ��ַ������ֵ��ָ��
 *  @param[in]  pwmlConvDict    ��Ҫת�����ַ������ֵ��ָ��
 *  @param[in]  pwmlConvList    ת����Ϣ�б��ָ��
 *  @param[out]  pwmlKeepDict   ��Ҫ���ֵ��ַ������ֵ�
 *  @param[out]  pwmlConvDict   ��Ҫת�����ַ������ֵ�
 *  @param[out]  pwmlConvList   ת����Ϣ�б�
 *  @return ��ʼ���Ƿ�ɹ�
 * - 0   �ɹ�
 * - -1  ʧ��
 */
int ul_load_wml_dict(char *path, char *keep_name, char *conv_name,
						fdict_t **pwmlKeepDict, fdict_t **pwmlConvDict, char **pwmlConvList);
						
						
						
/**
 *  �ͷ�wmlת���ʵ�

 *  
 *  @param[in]  pwmlKeepDict    ��Ҫ���ֵ��ַ������ֵ��ָ��
 *  @param[in]  pwmlConvDict    ��Ҫת�����ַ������ֵ��ָ��
 *  @param[in]  pwmlConvList    ת����Ϣ�б��ָ��
 *  @return ��
 */						
void ul_release_wml_dict(fdict_t *pwmlKeepDict, fdict_t *pwmlConvDict, char *pwmlConvList);

#endif
