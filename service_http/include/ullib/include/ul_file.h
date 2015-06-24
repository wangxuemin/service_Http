/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: ul_file.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_file.h
 * @author baonh(baonh@baidu.com)
 * @date 2007/12/06 22:34:07
 * @version $Revision: 1.2 $ 
 * @brief �ļ�������
 *  
 **/

#ifndef __UL_FILE_H
#define __UL_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "dep/dep_file.h"


/**
 * @brief ��path �� fname ��ϳ�һ��������·������������ֶ��'/'�����
 *
 * @param [in] path   : ·��
 * @param [in] fname   : �ļ���
 * @param [out] fullpath   : �������ļ���
 * @param [in] size   : fullpath����󳤶�,����'\0'
 * @return  0�ɹ� -1ת��ʧ�� 
 * @author baonh
**/
int ul_fullpath(const char *path, const char *fname, char *fullpath, size_t size);

/**
 * @brief �ж��ļ��Ƿ����
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fname : �ļ���
 * @return 1���ڣ�0������
 */
int ul_fexist(const char *path,const char *fname);

/**
 * @brief ����ļ��ĳ���
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fname : �ļ���
 * @return -1�ļ������ڣ�����Ϊ�ļ�����
 */
off_t ul_fsize(const char *path, const char *fname);

/**
 * @brief ����ļ���һЩ����ͳ����Ϣ,�����ı��ļ�������,���������ַ���
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fname : �ļ���
 * @param [out] nline : �ļ�����
 * @param [out] nword : ������
 * @param [out] nchar : �ַ���
 * @return 1�ɹ���-1�ļ�������
 */
int ul_finfo(const char *path, const char *fname,int *nline,int *nword,int *nchar);

/**
 * @brief ����һ�����ļ������������ضϵ�0������������򴴽�
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fname : �ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_nullfile(const char *path, const char *fname);

/**
 * @brief ��ͬһ��Ŀ¼�¿����ļ�
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fsrc : Դ�ļ���
 * @param [in] fdest :  Ŀ���ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_cpfile(const char *path, const char *fsrc, const char *fdest);

/**
 * @brief ��ͬһ��Ŀ¼�½�Դ�ļ�������ӵ�Ŀ���ļ���ĩβ
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] fsrc : Դ�ļ���
 * @param [in] fdest : Ŀ���ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_appfile(const char *path, const char *fsrc, const char *fdest);

/**
 * @brief ��ͬһ��Ŀ¼��Ϊ�ļ�����
 *
 * @param [in] path :  �ļ�����Ŀ¼
 * @param [in] fsrc :  ���ļ���
 * @param [in] fdest :  ���ļ���
 * @return 0�ɹ���-1ʧ��
 */
int ul_mvfile(const char *path, const char *fsrc, const char *fdest);

/**
 * @brief ��һ���ļ�����ȫ�������ڴ���
 *
 * @param [in] path :  �ļ�����Ŀ¼
 * @param [in] fname :  �ļ���
 * @param [in] buf :  ���뻺����
 * @param [in] size :  ��������С
 * @return -1ʧ��, ����Ϊ�����ֽ���
 */
ssize_t ul_readfile(const char *path, const char *fname, void *buf, int size);

/**
 * @brief ���ڴ��е�����д���ļ�
 *
 * @param [in] path :  �ļ�����Ŀ¼
 * @param [in] fname :  �ļ���
 * @param [in] buf :  ���뻺����
 * @param [in] size :  ��������С
 * @return -1ʧ�ܣ�����Ϊд���ֽ���
 */
ssize_t ul_writefile(const char *path, const char *fname, void *buf, int size);
 
/**
 * @brief �����ļ�
 *
 * @param [in] path : �ļ�����Ŀ¼
 * @param [in] sname : �ļ���s
 * @param [in] dname : �ļ���d
 * @return 1�ɹ���-1ʧ��
 */
int ul_exchangedir(const char *path, const char *sname, const char *dname);

#endif // __UL_FILE_H_
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
