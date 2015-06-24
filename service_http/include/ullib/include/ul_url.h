/**
 * @file 
 * @brief URL�����
 */
#include <stdio.h>
#ifndef __UL_URL_H__
#define __UL_URL_H__
#define  UL_MAX_URL_LEN_EX 1024
#define UL_MAX_SITE_LEN_EX 128
#define UL_MAX_PATH_LEN_EX 800
#define  UL_MAX_URL_LEN      256
#define  UL_MAX_SITE_LEN     48
#define  UL_MAX_PORT_LEN     7 //64k 5+:+1
#define UL_MAX_PATH_LEN 203

#define UL_MAX_URL_LEN_EX2 2048
#define UL_MAX_SITE_LEN_EX2 256
#define UL_MAX_PATH_LEN_EX2 1600


/**
 * ����url���������еĸ�������
 *
 * @param input �����url
 * @param[out] site վ����������
 * @param[out] port �˿�
 * @param[out] path ·��
 * @return 1������0��Чurl��ʽ
 */
int ul_parse_url(const char *input,char *site,char *port,char *path);

/**
 * ��һ��URL·��
 *
 * @param[in,out] path ·��
 * @return 1������0��Чurl��ʽ
 */
int ul_single_path(char *path);

/**
 * ����url���������е�·������
 *
 * @param url �����url
 * @param[out] path ·��
 * @return NULLʧ�ܣ�����Ϊָ��path��ָ��
 */
char *ul_get_path(const char *url, char *path);

/**
 * ����url���������е�վ��������
 *
 * @param url �����url
 * @param[out] site վ����( be sure it is enough,larger than UL_MAX_SITE_LEN)
 * @return NULLʧ�ܣ�����Ϊָ��site��ָ��
 */
char *ul_get_site(const char *url, char *site);

/**
 * �淶��·������ʽ\n
 * ��'\\', './', '/.', '../', '/..', '//'����ʽ���й淶��
 *
 * @param[in,out] path ��ת����·��
 */
void ul_normalize_path(char *path);

/**
 * ��url�л�ȡ�˿���Ϣ
 *
 * @param url �����url
 * @param[out] pport �˿�
 * @return 1�ɹ���0ʧ��
 */
int ul_get_port(const char* url,int* pport);

/**
 * ��url�л�ȡ��̬�Ĳ��֣�?����;֮ǰ�Ĳ��֣�
 *
 * @param url �����url
 * @param[out] staticurl ��̬���ֻ�����
 */
void ul_get_static_part(const char *url, char *staticurl);

/*
 * to compitable old version lib, still keep the non-const functions
 * see the above functions for detail
 */
int ul_parse_url(char *input,char *site,char *port,char *path);
char *ul_get_path(char *url, char *path);
char *ul_get_site(char *url, char *site);
int ul_get_port(char* url,int* pport);
void ul_get_static_part(char *url, char *staticurl);

/**
 * �ж�url�Ƿ��Ƕ�̬url
 *
 * @param str url
 * @returnu 0���Ƕ�̬url����0���Ƕ�̬url
 */
int ul_isdyn(char* str);

/**
 * �ж�url�Ƿ�Ϸ�
 *
 * @param url ����url
 * @returnu 1�Ϸ���0���Ϸ�
 */
int ul_check_url(char* url);



/**
 * ��վ�����л�ȡ���ɲ���\n
 * ����"www.baidu.com"�����"baidu"
 *
 * @param site վ����
 * @param[out] trunk ������ɲ��ֵĻ�����
 * @param size ��������С
 * @return 1�ɹ���-1δ֪����-2վ��û�����ɲ��֣�-3վ�㲻����'.'
 */
int ul_fetch_trunk(const char* site,char *trunk,int size);

/**
 * ���վ�����Ƿ���IP��ַ
 *
 * @param sitename վ����
 * @return 0���ǣ���0��
 */
int ul_is_dotip(const char *sitename);

/**
 * ��վ�����л�ȡ���ɲ��֣�������ͬ@ref ul_fetch_trunk()
 *
 * @param site վ����
 * @param[out] domain ������ɲ��ֵĻ�����
 * @param size ��������С
 * @return NULLʧ�ܣ�����Ϊָ��site���ɲ��ֵ�ָ��
 */
const char* ul_fetch_maindomain(const char* site,char *domain,int size);

/**
 * ���url�Ƿ�淶��
 *
 * @param url ����url
 * @return 1�ǣ�0����
 */
int ul_isnormalized_url(const char *url);

/**
 * ��urlת��Ϊͳһ����ʽ\n
 * ִ��@ref ul_normalize_site, @ref ul_normalize_port, @ref ul_single_path, @ref ul_normalize_path
 *
 * @param url ��ת����url
 * @param[out] buf ת�����url������
 * @return 1�ɹ���0��Чurl
 * @note you can use ul_normalize_url(buf, buf) to save an extra buffer.
 */
int ul_normalize_url(const char* url, char* buf);

/**
 * ��վ�������й淶������дתΪСд��
 *
 * @param site վ����
 * @return 1�ɹ���0ʧ��
 */
int ul_normalize_site(char *site);

/**
 * ���˿��ַ������й淶�������˿ڷ�Χ�Ϸ��ԣ���ȥ��80�˿ڵ��ַ�����
 *
 * @param port ָ��Ķ˿ڵ�ָ��
 * @return 1�ɹ���0ʧ��
 */
int ul_normalize_port(char *port);



 
 
/**
 *  ����url���������еĸ�������,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *  
 *  @param[in]  input          �����url
 *  @param[in]  site           site�ֶεĴ洢bufָ��
 *  @param[in]  site_size      site�������Ĵ�С���ɸ��ݴ��ֶ����ú����site����,Ĭ��Ϊ128,ʹ��ʱ���ʵ���С.
 *  @param[in]  port           port�ֶεĴ洢bufָ��
 *  @param[in]  port_size      port�ֶεĴ�С
 *  @param[in]  path           path�ֶεĴ洢bufָ��
 *  @param[in]  max_path_size  path�ֶεĴ�С,�ɸ��ݴ��ֶ����ú����path����,Ĭ��Ϊ800,ʹ��ʱ���ʵ���С.
 *  @param[out] site           siteֵ
 *  @param[out] port           portֵ
 *  @param[out] path           path·��
 *  @return �����������
 *  - 1   ��ʾ����
 *  - 0  ��Чurl��ʽ
 *  - @note Ϊ��֤����ȫ,�����buf��С��Ĭ�����ֵ
 */ 
int ul_parse_url_ex(const char *input, char *site,size_t site_size,
		                char *port, size_t port_size,char *path, size_t max_path_size);
                                
                                
                                
                                

/**
 *  ����url���������е�·������,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *  
 *  @param[in]  url          �����url
 *  @param[in]  path         site�ֶεĴ洢bufָ��
 *  @param[in]  path_size    path�ֶεĴ�С,�ɸ��ݴ��ֶ����ú����path����,Ĭ��Ϊ800,ʹ��ʱ���ʵ���С.
 *  @param[out] path         path·��
 *  @return �����������
 *  - ��NULL   ָ��·����ָ��
 *  - NULL     ��ʾʧ��
 *  - @note Ϊ��֤����ȫ,�����path_size��С��Ĭ�����ֵ
 */
char *ul_get_path_ex(const char *url, char *path,size_t path_size);





/**
 *  ����url���������е�վ��������,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *  
 *  @param[in]  url            �����url
 *  @param[in]  site           site�ֶεĴ洢bufָ��
 *  @param[in]  site_size      site�������Ĵ�С���ɸ��ݴ��ֶ����ú����site����,Ĭ��Ϊ128,ʹ��ʱ���ʵ���С.
 *  @param[out] site           siteֵ
 *  @return �����������
 *  - ��NULL   ָ��site��ָ��
 *  - NULL     ��ʾʧ��
 *  - @note Ϊ��֤����ȫ,�����site_size��С��Ĭ�����ֵ
 */ 
char *ul_get_site_ex(const char *url, char *site,  size_t site_size);




/**
 *  ��url�л�ȡ�˿���Ϣ,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *  
 *  @param[in]  input          �����url
 *  @param[in]  pport          port�ֶεĴ洢bufָ��
 *  @param[out] pport          portֵ
 *  @return �����������
 *  - 1   ��ʾ�ɹ�
 *  - 0   ��ʾʧ��
 */ 
int ul_get_port_ex(const char* url, int* pport);








/**
 *  ��urlת��Ϊͳһ����ʽ\n,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *  ִ��@ref ul_normalize_site, @ref ul_normalize_port, @ref ul_single_path, @ref ul_normalize_path
 *
 *  @param[in]  url           ��ת����url
 *  @param[in]  buf           ת�����url������
 *  @param[in]  buf_size      buf�Ĵ�С
 *  @param[out] buf           ת�����url
 *  @return �����������
 *  - 1   �ɹ�
 *  - 0   ��Чurl
 *  - @note Ϊ��֤����ȫ,�����site_size��С��Ĭ�����ֵ
 */ 
int ul_normalize_url_ex(const char* url, char* buf,size_t buf_size);






/**
 *  ��url�л�ȡ��̬�Ĳ��֣�?����;֮ǰ�Ĳ��֣�,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *
 *  @param[in]  url                 �����url
 *  @param[in]  staticurl           ��̬���ֻ�����
 *  @param[in]  staticurl_size      buf�Ĵ�С
 *  @param[out] staticurl           ��̬����
 *  @return ��
 */
void ul_get_static_part_ex(const char *url , char *staticurl ,size_t staticurl_size);







/**
 *  ���url�Ƿ�淶��,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *
 *  @param[in]  url                 ����url
 *  @param[out] ��
 *  @return �����жϽ��
 *  - 1   ��
 *  - 0   ����
 */
int ul_isnormalized_url_ex(const char *url);




/**
 *  �淶��·������ʽ\n,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 * ��'\\', './', '/.', '../', '/..', '//'����ʽ���й淶��
 *
 *  @param[in]  path           ��ת����·��
 *  @param[out] path           ת�����·��
 *  @return ��
 */ 
void ul_normalize_path_ex(char *path);




/**
 *  ��һ��URL·��,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *
 *  @param[in]  path         path·��
 *  @param[out] path         ��һ������·��
 *  @return ���ع�һ�����
 *  - 1   ����
 *  - 0   ��Чurl��ʽ·��
 */
int ul_single_path_ex(char *path);



/**
 *  �ж�url�Ƿ�Ϸ�,֧�ּӳ���url����߿�֧�ֵ�1024��path��ɵ�800��site��ɵ�128
 *
 *  @param[in]  url           ��ת����url
 *  @param[out] ��
 *  @return �����������
 *  - 1   �Ϸ�
 *  - 0   ���Ϸ�
 */
int ul_check_url_ex(char *url);

/////////////////////////////////////////////////////////////////////
//modified by zhangyan04@baidu.com..
 
/**
 *  ����url���������еĸ�������,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *  
 *  @param[in]  input          �����url
 *  @param[in]  site           site�ֶεĴ洢bufָ��
 *  @param[in]  site_size      site�������Ĵ�С���ɸ��ݴ��ֶ����ú����site����,Ĭ��Ϊ256,ʹ��ʱ���ʵ���С.
 *  @param[in]  port           port�ֶεĴ洢bufָ��
 *  @param[in]  port_size      port�ֶεĴ�С
 *  @param[in]  path           path�ֶεĴ洢bufָ��
 *  @param[in]  max_path_size  path�ֶεĴ�С,�ɸ��ݴ��ֶ����ú����path����,Ĭ��Ϊ1600,ʹ��ʱ���ʵ���С.
 *  @param[out] site           siteֵ
 *  @param[out] port           portֵ
 *  @param[out] path           path·��
 *  @return �����������
 *  - 1   ��ʾ����
 *  - 0  ��Чurl��ʽ
 *  - @note Ϊ��֤����ȫ,�����buf��С��Ĭ�����ֵ
 */ 
int ul_parse_url_ex2(const char *input, char *site,size_t site_size,
		     char *port, size_t port_size,char *path, size_t max_path_size);
                                
                                
                                
                                

/**
 *  ����url���������е�·������,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *  
 *  @param[in]  url          �����url
 *  @param[in]  path         site�ֶεĴ洢bufָ��
 *  @param[in]  path_size    path�ֶεĴ�С,�ɸ��ݴ��ֶ����ú����path����,Ĭ��Ϊ1600,ʹ��ʱ���ʵ���С.
 *  @param[out] path         path·��
 *  @return �����������
 *  - ��NULL   ָ��·����ָ��
 *  - NULL     ��ʾʧ��
 *  - @note Ϊ��֤����ȫ,�����path_size��С��Ĭ�����ֵ
 */
char *ul_get_path_ex2(const char *url, char *path,size_t path_size);





/**
 *  ����url���������е�վ��������,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *  
 *  @param[in]  url            �����url
 *  @param[in]  site           site�ֶεĴ洢bufָ��
 *  @param[in]  site_size      site�������Ĵ�С���ɸ��ݴ��ֶ����ú����site����,Ĭ��Ϊ256,ʹ��ʱ���ʵ���С.
 *  @param[out] site           siteֵ
 *  @return �����������
 *  - ��NULL   ָ��site��ָ��
 *  - NULL     ��ʾʧ��
 *  - @note Ϊ��֤����ȫ,�����site_size��С��Ĭ�����ֵ
 */ 
char *ul_get_site_ex2(const char *url, char *site,  size_t site_size);




/**
 *  ��url�л�ȡ�˿���Ϣ,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *  
 *  @param[in]  input          �����url
 *  @param[in]  pport          port�ֶεĴ洢bufָ��
 *  @param[out] pport          portֵ
 *  @return �����������
 *  - 1   ��ʾ�ɹ�
 *  - 0   ��ʾʧ��
 */ 
int ul_get_port_ex2(const char* url, int* pport);





/**
 *  ��urlת��Ϊͳһ����ʽ\n,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *  ִ��@ref ul_normalize_site, @ref ul_normalize_port, @ref ul_single_path, @ref ul_normalize_path
 *
 *  @param[in]  url           ��ת����url
 *  @param[in]  buf           ת�����url������
 *  @param[in]  buf_size      buf�Ĵ�С
 *  @param[out] buf           ת�����url
 *  @return �����������
 *  - 1   �ɹ�
 *  - 0   ��Чurl
 *  - @note Ϊ��֤����ȫ,�����site_size��С��Ĭ�����ֵ
 */ 
int ul_normalize_url_ex2(const char* url, char* buf,size_t buf_size);






/**
 *  ��url�л�ȡ��̬�Ĳ��֣�?����;֮ǰ�Ĳ��֣�,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *
 *  @param[in]  url                 �����url
 *  @param[in]  staticurl           ��̬���ֻ�����
 *  @param[in]  staticurl_size      buf�Ĵ�С
 *  @param[out] staticurl           ��̬����
 *  @return ��
 */
void ul_get_static_part_ex2(const char *url , char *staticurl ,size_t staticurl_size);







/**
 *  ���url�Ƿ�淶��,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *
 *  @param[in]  url                 ����url
 *  @param[out] ��
 *  @return �����жϽ��
 *  - 1   ��
 *  - 0   ����
 */
int ul_isnormalized_url_ex2(const char *url);



/**
 *  �淶��·������ʽ\n,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 * ��'\\', './', '/.', '../', '/..', '//'����ʽ���й淶��
 *
 *  @param[in]  path           ��ת����·��
 *  @param[out] path           ת�����·��
 *  @return ��
 */ 
void ul_normalize_path_ex2(char *path);




/**
 *  ��һ��URL·��,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *
 *  @param[in]  path         path·��
 *  @param[out] path         ��һ������·��
 *  @return ���ع�һ�����
 *  - 1   ����
 *  - 0   ��Чurl��ʽ·��
 */
int ul_single_path_ex2(char *path);



/**
 *  �ж�url�Ƿ�Ϸ�,֧�ּӳ���url����߿�֧�ֵ�2048��path��ɵ�1600��site��ɵ�256
 *
 *  @param[in]  url           ��ת����url
 *  @param[out] ��
 *  @return �����������
 *  - 1   �Ϸ�
 *  - 0   ���Ϸ�
 */
int ul_check_url_ex2(char *url);


#endif
