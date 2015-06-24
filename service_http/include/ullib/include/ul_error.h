/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: ul_error.h,v 1.3 2009/12/29 03:24:00 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_error.h
 * @author xiaowei(xiaowei@baidu.com)
 * @version $Revision: 1.3 $ 
 * @brief 
 *  
 **/


#ifndef _UL_ERROR_H
#define _UL_ERROR_H

enum {
	UL_SUCCESS = 0,				//����ɹ�
	UL_DETAIL_ERR,				//ϸ�ڴ���ul�ڲ���������Ϣ��ӡ���̻߳�����ȥ
	UL_ALLOC_ERR,				//�ڴ�������
	UL_MEMSEG,					//�ڴ�Խ��
	UL_READ_ERR,				//io��ʧ��
	UL_WRITE_ERR,				//ioдʧ��
	UL_INVALID_FD,				//��Ч�ľ��
	UL_NETCONNET_ERR,			//��������ʧ��
	UL_INVALID_PARAM,			//��Ч�Ĵ������
	UL_OPEN_FILE_ERR,			//���ļ����ʧ��
};

/**
 * @brief ���ô����
 *
 * @param [in] err   : int	Ҫ���õĴ���Ŵ���
 * @return  int �ɹ�����0������ʧ��
 * @retval   
 * @see 
 * @author xiaowei
 * @date 2007/12/03 21:13:41
**/
int ul_seterrno(int err);

/**
 * @brief ��ȡ�����
 *
 * @return  int ���ش���Ŵ���
 * @retval   
 * @see 
 * @author xiaowei
 * @date 2007/12/03 21:14:21
**/
int ul_geterrno();

/**
 * @brief ���ݴ���Ż�ȡ������Ϣ
 *
 * @return  const char* ���ش���ŵĴ�������
 * @param [in] err : int ����Ŵ���
 * @retval   
 * @see 
 * @author xiaowei
 * @date 2007/12/05 13:56:12
**/
const char *ul_geterrstr(int err);


/**
 * @brief ���ô�����ʾ
 *
 * @param [in] format   : const char* ���ô�����Ϣ
 * @return  int ���óɹ�����0������ʧ��
 * @retval   
 * @see 
 * @author xiaowei
 * @date 2007/12/03 21:14:45
**/
int ul_seterrbuf(const char *format, ...);


/**
 * @brief ��ȡ��ʾ��Ϣ������
 *
 * @return  const char* �ɹ����س���������
 * 						ʧ�ܷ���""�ַ���
 * 						���᷵��NULLָ��
 * @retval   
 * @see 
 * @author xiaowei
 * @date 2007/12/03 21:15:28
**/
const char *ul_geterrbuf();

#endif
/* vim: set ts=4 sw=4 tw=100 noet: */
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
