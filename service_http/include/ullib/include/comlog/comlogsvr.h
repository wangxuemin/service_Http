/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: comlogsvr.h,v 1.2 2009/03/25 12:34:11 yingxiang Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file comlogsvr.h
 * @author baonh(baonh@baidu.com)
 * @version $Revision: 1.2 $ 
 * @brief comlog����� �ͻ��˽ӿ�ͷ�ļ�
 *  
 **/


#ifndef  __COMLOGSVR_H_
#define  __COMLOGSVR_H_

#include "ul_def.h"
const u_int COMLOG_MODULE_MAXLEN = 32;		  /**< ģ������󳤶�       */
const u_int COMLOG_FILENAME_MAXLEN = 32;	  /**< �ļ�����󳤶�       */
const u_int COMLOG_AUTH_MAXLEN = 32;		  /**< ��֤����󳤶�       */
const u_int COMLOG_RESERVED_MAXLEN = 8;		  /**< ��������󳤶�       */



enum {		  /**< ����˷��͵������,��д�ڿͻ��˵�nsheadͷ��reserved�ֶ�       */
	COMLOG_CREATE = 1,		  /**< ����־�������ļ�       */
	COMLOG_CLOSE = 2,		  /**< �ر���־�������ļ�       */
	COMLOG_FLUSH = 3,		  /**< ��־flush���ѻ���д���ļ�       */
	COMLOG_SET = 4,	          /**< ���ò���������       */
	COMLOG_CHECK = 5,         /**< ��־����ͬ�����       */
	COMLOG_PRINT = 6          /**< ����־       */
};

enum {		  /**< ����η��صĴ����       */
	COMLOG_SEND_SUCCESS = 0,		  /**< �������� �����ɹ�       */
	COMLOG_SEND_FAIL = -1		      /**< �������� ����ʧ��      */
};


enum {		  /**< ѹ���洢       */
	COMLOG_UNCOMPRESS = 0,		/**< ��־��ѹ���洢     */  
	COMLOG_COMPRESS = 1		    /**< ��־ѹ���洢       */
};

#pragma pack(push, 4)
typedef struct _logsvr_req_t {		  /**< �ͻ��˷��͵�����ͷ,��nsheadͷ����֮��       */
	char path[COMLOG_MODULE_MAXLEN];	   /**< ģ����       */
	char filename[COMLOG_FILENAME_MAXLEN]; /**< ��ӡ���ļ��� */
	char auth[COMLOG_AUTH_MAXLEN];         /**< ��֤�룬������������־��Ҫ��һ����־�ļ���ʱʹ��*/
										   /**< ����Ҫʹ��ʱʹ�ÿմ��� */
	u_int handle;		                       /**< ��־�ľ������CREATE�������ɣ�д��־ʱ��Ҫ�ṩ */
	int compress;		                   /**< �Ƿ�ѹ��@ref COMLOG_COMPRESS,@ref COMLOG_UNCOMPRESS*/
	char reserved[COMLOG_RESERVED_MAXLEN]; /**< ������ */
} logsvr_req_t;


typedef struct _logitem_t {	  /**< �ͻ��˴���ĵ�����־�ṹ��������ڿͻ��˷��͵�����ͷ��       */
	u_int handle; /**< ��־�ľ������COMLOG_CREATE�������ɣ�д��־ʱ��Ҫ�ṩ */
	u_int time;   /**< ��־��ʱ�� */
	u_int size;   /**< ��־�ĳ��� */
	char log[0];	  /**< ʵ����־����       */
} logitem_t;

typedef struct _logsvr_res_t{		  /**< ����˸�������صĽ��       */
	int error_code;  /**< ���ؽ���Ĵ���ţ�@ref COMLOG_SEND_SUCCESS�� @ref COMLOG_SEND_FAIL */
	u_int handle;      /**< ��־��� */
    int count;     /**< ��־�� */
} logsvr_res_t;


typedef	struct _log_index_t {
		u_int min_time; 
		u_int max_time;
		u_int offset;  //�ļ�ƫ��
} log_index_t;


#pragma pack(pop)

#endif  //__COMLOGSVR_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
