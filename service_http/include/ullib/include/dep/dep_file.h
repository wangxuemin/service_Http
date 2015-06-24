/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_file.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file dep/dep_file.h
 * @author baonh(baonh@baidu.com)
 * @version $Revision: 1.2 $ 
 * @brief ���Ƽ�ʹ�õ��ļ�������
 *
 * ����ĺ����ǲ��Ƽ�ʹ�ã�ֻΪ�����ϰ汾ullib��
 *  
 **/
#ifndef __DEP_FILE_H
#define __DEP_FILE_H
/**
 *  Function description: The following three functions are used in display the  running process.
 *  Arguments in: char *remark, int base, int goint.
 */

/**
 * @brief used in display the  running process
 *
 * @deprecated ��file�޹�
**/
int ul_showgo(char *remark, int goint);

/**
 * @brief used in display the  running process
 *
 * @deprecated ��file�޹�
**/
int ul_showgocmp(char *remark, int base, int goint);

/**
 * @brief used in display the  running process
 *
 * @deprecated ��file�޹�
**/
int ul_showgoend(char *remark, int base, int goint);


#endif // __DEP_FILE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
