/**
 * @file
 * @brief �ַ���ӳ��ʵ�
 */
/**
 * @brief �ַ���ӳ��ʵ��ǽ��ַ�������ʵ�ʱ�᷵��һ����֮��Ӧ����������ʵ���ַ����Ͷ�Ӧ������֮����໥���ҡ�
 */

/********************************************************************
 * Filename    : $Id: ul_strdict.h,v 1.2 2007/02/09 10:35:38 wangjp2 Exp $
 * Author      : $Author: wangjp2 $
 * Create Date : 2005-01-20
 * Description : some data structures and functions defined in
 *             : this file
 * Recently Update : $Date: 2007/02/09 10:35:38 $
 * Version     : $Revision: 1.2 $
 * Update log list here :
 * $Log: ul_strdict.h,v $
 * Revision 1.2  2007/02/09 10:35:38  wangjp2
 * doxygen�ĵ��ع�
 *
 * Revision 1.1.14.1  2007/02/02 04:59:33  wangjp2
 * doxygen�ĵ��ع�cvs
 *
 * Revision 1.1  2006/06/28 09:35:55  qiuzd
 * ullib��֣���ʼ�汾
 *
 * Revision 1.3  2006/01/11 09:12:03  wangjian
 * ullib_2-7-8-7_PD_BL
 *
 * Revision 1.1  2005/10/09 07:22:00  tany
 * new file
 *
 * Revision 1.2  2005/06/10 03:22:28  yangeb
 * cin
 *
 * Revision 1.1  2005/03/11 07:33:02  yangeb
 * add keyword module
 *
 * Revision 1.1  2005/03/04 02:39:45  yangeb
 * *** empty log message ***
 *
 * Revision 1.1  2005/02/02 07:53:28  chenjk
 * Add new  subject keyword extraction and topic page recognise to cvs.
 *
 ********************************************************************/     
#ifndef STRDICT_H
#define STRDICT_H

#include <ul_dict.h>


typedef struct UL_STRDICT_T
{
	unsigned int m_bufsize;
	unsigned int m_curpos;
	unsigned int m_count;
	char* m_strbuf;
	Sdict_build * m_dict;
}ul_strdict_t;

/**
 *  �õ��ֵ䵱ǰ�洢�Ľڵ�����
 *  
 *  @param[in]  pstrdict  �ֵ��ָ��
 *  @param[out] ��
 *  @return �ڵ�����
 */

int ul_strd_size(const ul_strdict_t * pstrdict);

/**
 *  �����ַ���ӳ��ʵ�
 *  
 *  @param[in]  hashnum  �ʵ�Ĺ�ϣͰ�Ĵ�С
 *  @param[in]  bufsize  �ʵ仺�����ĳ�ʼ��С��ÿ�����ӵ��ֽ���
 *  @param[out] ��
 *  @return �ֵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */ 
ul_strdict_t * ul_strd_create(int hashnum,int bufsize);


/**
 *  �����ַ���ӳ��ʵ�
 *  
 *  @param[in]  pstrdict  �ֵ��ָ��
 *  @param[out] ��
 *  @return ��
 */ 
void ul_strd_destroy(ul_strdict_t *pstrdict);

/**
 *  ���ַ���ӳ��ʵ��в���һ���ַ���
 *  
 *  @param[in]  pstrdict  ָ��ʵ��ָ��
 *  @param[in]  str       ��������ַ���
 *  @param[in]  pcode     ���ڴ洢���ַ�����Ӧ�����Ŀռ�
 *  @param[out] pcode     ��������ַ�����Ӧ������
 *  @return ��������ֵ
 * - 1   �ɹ�
 * - 0   �ַ����Ѵ���
 * - -1  ʧ��
 */    
int ul_strd_insert(ul_strdict_t* pstrdict,const char * const str,int* pcode);

 
/**
 *  ����ַ���ӳ��ʵ�
 *  
 *  @param[in]  pstrdict  ָ��ʵ��ָ��
 *  @param[out] ��
 *  @return ��
 */ 
void ul_strd_reset(ul_strdict_t *pstrdict);

 
/**
 *  ͨ���ַ������������Ӧ��code
 *  
 *  @param[in]  pstrdict  ָ��ʵ��ָ��
 *  @param[in]  str       �������������ַ���
 *  @param[out] ��
 *  @return code
 * - >=0   ���ҵ������ַ�����Ӧ��code
 * - -1  ʧ��
 */ 
int ul_strd_getcode(const ul_strdict_t*pstrdict,const char* str);


 
/**
 *  ͨ��code���������Ӧ���ַ���
 *  
 *  @param[in]  pstrdict  ָ��ʵ��ָ��
 *  @param[in]  code      �������ַ�����code
 *  @param[out] ��
 *  @return ָ����ҵ����ַ�����ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note the string will be change when new string is insert the dict.BE SURE NOT to keep this string after a new string had been added to the strdict.
 */
const char* ul_strd_getstr(const ul_strdict_t* pstrdict,const int code);

#endif
