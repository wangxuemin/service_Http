/**
 * @file
 * @brief 字符串映射词典
 */
/**
 * @brief 字符串映射词典是将字符串加入词典时会返回一个与之对应的整数，并实现字符串和对应的整数之间的相互查找。
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
 * doxygen文档回归
 *
 * Revision 1.1.14.1  2007/02/02 04:59:33  wangjp2
 * doxygen文档回归cvs
 *
 * Revision 1.1  2006/06/28 09:35:55  qiuzd
 * ullib拆分，初始版本
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
 *  得到字典当前存储的节点数量
 *  
 *  @param[in]  pstrdict  字典的指针
 *  @param[out] 无
 *  @return 节点数量
 */

int ul_strd_size(const ul_strdict_t * pstrdict);

/**
 *  创建字符串映射词典
 *  
 *  @param[in]  hashnum  词典的哈希桶的大小
 *  @param[in]  bufsize  词典缓冲区的初始大小及每次增加的字节数
 *  @param[out] 无
 *  @return 字典指针
 * - 非NULL   成功
 * - NULL     失败
 */ 
ul_strdict_t * ul_strd_create(int hashnum,int bufsize);


/**
 *  销毁字符串映射词典
 *  
 *  @param[in]  pstrdict  字典的指针
 *  @param[out] 无
 *  @return 无
 */ 
void ul_strd_destroy(ul_strdict_t *pstrdict);

/**
 *  向字符串映射词典中插入一个字符串
 *  
 *  @param[in]  pstrdict  指向词典的指针
 *  @param[in]  str       待插入的字符串
 *  @param[in]  pcode     用于存储与字符串对应整数的空间
 *  @param[out] pcode     存放有与字符串对应的整数
 *  @return 操作返回值
 * - 1   成功
 * - 0   字符串已存在
 * - -1  失败
 */    
int ul_strd_insert(ul_strdict_t* pstrdict,const char * const str,int* pcode);

 
/**
 *  清空字符串映射词典
 *  
 *  @param[in]  pstrdict  指向词典的指针
 *  @param[out] 无
 *  @return 无
 */ 
void ul_strd_reset(ul_strdict_t *pstrdict);

 
/**
 *  通过字符串查找与其对应的code
 *  
 *  @param[in]  pstrdict  指向词典的指针
 *  @param[in]  str       待查找整数的字符串
 *  @param[out] 无
 *  @return code
 * - >=0   查找到的与字符串对应的code
 * - -1  失败
 */ 
int ul_strd_getcode(const ul_strdict_t*pstrdict,const char* str);


 
/**
 *  通过code查找与其对应的字符串
 *  
 *  @param[in]  pstrdict  指向词典的指针
 *  @param[in]  code      待查找字符串的code
 *  @param[out] 无
 *  @return 指向查找到的字符串的指针
 * - 非NULL   成功
 * - NULL     失败
 *  @note the string will be change when new string is insert the dict.BE SURE NOT to keep this string after a new string had been added to the strdict.
 */
const char* ul_strd_getstr(const ul_strdict_t* pstrdict,const int code);

#endif
