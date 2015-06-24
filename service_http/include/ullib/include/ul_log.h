/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: ul_log.h,v 1.2.40.1 2010/04/15 06:38:17 zhang_rui Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_log.h
 * @author baonh(baonh@baidu.com)
 * @version $Revision: 1.2.40.1 $ 
 * @brief  ��־�� 
 * 
 * ��־��ʹ������
 * 
 * ���̳߳���:
 *
 * ������              ���߳� 1         ���߳� 2 ...
 *
 *  ul_openlog
 *
 *      |
 *
 *      ------------------------------------
 *
 *      |               |               |
 *
 *  ul_writelog  ul_openlog_r       ul_openlog_r
 *
 *     ...              |               |
 *
 *     ...       ul_writelog        ul_writelog
 *
 *     ...           ...              ...
 *
 *               ul_closelog_r      ul_closelog_r
 *
 *                      |               |
 *
 *      --------------------------------------
 *
 *      |
 *
 *  ul_closelog
 *
 * ������
 *
 *  ul_openlog
 *
 *      |
 *
 *  ul_writelog
 *
 *     ...
 *
 *      |
 *
 *  ul_closelog
 *
 *  �����ul_openlogǰ����ul_writelog,
 *  ��־��Ϣ�ᱻ�������׼����(stderr)��,��־��֧�ֶ��̳߳���,����֧�ֶ���̳���,
 *  �������ʹ���뱣֤ÿ������ʹ�õ��ǲ��õ���־�ļ�
 *
 **/

#ifndef __UL_LOG_H__
#define __UL_LOG_H__

#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <syslog.h>
#include <signal.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

#include "ul_def.h"
#include "dep/dep_log.h"

#define ERR_NOSPACE		-1
#define ERR_OPENFILE	-2
#define ERR_EVENT		-3
#define ERR_FILEFULL	-4

#define LOG_FILE_NUM	2048		      /**< ����ͬʱ�򿪵��ļ���      */
#define LOG_BUFF_SIZE_EX 2048			  /**< һ����־buff��С       */

#define MAX_FILE_SIZE		2045		  /**< ����ļ���С��λ(MB)      */
#define MAX_FILENAME_LEN	1024		  /**< ��־�ļ�������󳤶�       */


/** @brief �¼�����  */
#define UL_LOG_WFSTART	-2
#define UL_LOG_START	-1
#define UL_LOG_END		UL_LOG_START
#define UL_LOG_WFEND	UL_LOG_WFSTART

#define UL_LOG_NONE		0
#define UL_LOG_FATAL	0x01    /**<   fatal errors */
#define UL_LOG_WARNING	0x02    /**<   exceptional events */
#define UL_LOG_NOTICE   0x04    /**<   informational notices */
#define UL_LOG_TRACE	0x08    /**<   program tracing */
#define UL_LOG_DEBUG	0x10    /**<   full debugging */
#define UL_LOG_ALL		0xff    /**<   everything     */

#define UL_LOG_SELF_BEGIN   0x100
#define UL_LOG_SELF_END     0x107
#define UL_LOG_SELF_MASK    0xff

/* ul_log_t  log_sepc */
#define UL_LOGTTY		0x02    /**<   ��־���������־�ļ���ͬʱ�������׼����(stderr)�� */
#define UL_LOGNEWFILE	0x08    /**<   �����µ���־�ļ�,����ʹÿ���̶߳�����־�򵽲�ͬ�ļ���*/
#define UL_LOGSIZESPLIT 0x10    /**<  ����С�ָ���־�ļ������ع�*/
/* ul_file_t  flag */
#define UL_FILE_TRUNCATE	0x01
#define UL_FILE_FULL		0x02

#define UL_LOG_RECORD	15	

#define MAX_SELF_DEF_LOG 8		  /**< ���������Զ�����־����־������      */
/** @brief ��־��ز��� */

struct ul_logstat_t {
        int events;		/**< ��Ҫ�����־���� 0-15 */
        int to_syslog;	/**< �����syslog �е���־����, 0-15 */
        int spec;		/**< ��չ���� 0 or @ref UL_LOGTTY or @ref UL_LOGNEWFILE */
};
typedef struct ul_logstat_t ul_logstat_t;

struct ul_file_t {
	FILE *fp;							/**< �ļ���� */
	int  flag;							/**< ��־  @ref UL_FILE_TRUNCATE | @ref UL_FILE_FULL */
	int  ref_cnt;						/**< ���ü��� */
	int  max_size;						/**< �ļ����Լ�¼����󳤶� */
	pthread_mutex_t file_lock;			/**< д�ļ��� */
	char file_name[MAX_FILENAME_LEN+1];	/**< �ļ����� */
};
typedef struct ul_file_t ul_file_t;

struct ul_log_t {
	char used;							/**< 0-δʹ��  1-��ʹ�� */
	ul_file_t *pf;						/**< log */
	ul_file_t *pf_wf;					/**< log.wf */
	pthread_t tid;						/**< �߳�id */
	int  mask;							/**< ���Լ�¼���¼������� */
	int  log_syslog;					/**< �����ϵͳ��־���¼����� */
	int  log_spec;						/**< UL_LOGTTY | UL_LOGNEWFILE */
	ul_file_t *spf[MAX_SELF_DEF_LOG];	/**< �Զ�����־�ļ���� */
};
typedef struct ul_log_t ul_log_t;

typedef struct Ul_log_self {					/**< ���ݾ�ģʽ�����岻�� _t       */
	char name[MAX_SELF_DEF_LOG][PATH_SIZE];		/**< �Զ�����־�ļ�����ϵͳ�Զ����ļ�����Ӻ�׺.sdf */
	char flags[MAX_SELF_DEF_LOG];				/**<������ǰ�Զ������־�Ƿ����,����Ϊ1�������Զ�����־,0������ */
	int  log_number;							/**< �Զ����ļ�����Ŀ,������Ϊ0ʱ,�������Զ����ļ� */
}; //�Զ�����־������,����ul_openlog�Լ�ul_openlog_r����Ϊ��������,����UL_LOGNEWFILEʱ,�Զ�����־��������־һ��,
			 //Ϊ�߳��ļ�,����,�Զ�����־Ϊ���̼���־
typedef struct Ul_log_self ul_log_self_t;


/**
 * @brief ����־�ļ���log��log.wf������ʼ����־����(����attach�����ڴ�)
 *
 * @param [in] log_path : ��־�ļ�����Ŀ¼ 
 * @param [in] log_procname : ��־�ļ���ǰ׺������ļ����а���'_'����ض�Ϊ'_'֮ǰ���ַ���
 * @param [in] l_stat : ��־��ز���(��������log������)
 * @param [in] maxlen : ������־�ļ�����󳤶ȣ�unit: MB��
 * @param [in] self :  �����Զ���log,����ʹ�÷�ʽ��μ��ṹ˵��
 * @return 0�ɹ���-1ʧ��
 * @note �˳�ʱ��Ҫ����ul_closelog�ͷ���Դ
 * @see ul_closelog ul_openlog_r ul_closelog_r
 */
extern int ul_openlog(const char *log_path, const char *log_procname, ul_logstat_t  *l_stat,
		int maxlen, Ul_log_self *self = NULL);


/**
 * @brief ��ӡָ��������ַ�������Ӧ����־�ļ�
 *
 * @param [in] event : ��־���� (include UL_LOG_DEBUG,UL_LOG_TRACE,UL_LOG_NOTICE,UL_LOG_WARNING,UL_LOG_FATAL)
 * @param [in] fmt : ��ʽ��
 * @param [in] ... : ��ӡ�����б�
 * @return 0�ɹ���<0ʧ��
 * @note ��־���Ⱦ�����չ���̼߳���־��֧�����Ϊ2048�ֽڣ������ڴ��е�log��Ϣ�ڳ���640�ֽ���Ȼ��ضϡ�
 */
#ifdef  _UN_WRITELOG_FORMAT_CHECK
extern int ul_writelog(const int event, const char* fmt, ... );
#else
extern int ul_writelog(const int event, const char* fmt, ... ) __attribute__ ((format (printf,2,3)));
#endif

/**
 * @brief �ر���־�ļ����ͷ������Դ
 *
 * @param [in] iserr : ����־�м�¼����״̬��0Ϊ��������0Ϊ������
 * @return 0�ɹ���-1ʧ��
 */
extern int ul_closelog(int iserr);

/**
 * @brief Ϊ���̴߳���־
 *
 * @param [in] threadname ���ڴ�ӡ���߳�����(���������UL_LOGNEWFILE,�����threadname�����µ�log�ļ�)
 * @param [in] l_stat ��־��ز���
 * @param [in] self : �����Զ���log,����ʹ�÷�ʽ��μ��ṹ˵��
 * @return 0�ɹ���-1ʧ��
 * @see ul_closelog_r ul_openlog ul_closelog
 * @note ���߳��˳��Ժ�Ҫʹ��ul_closelog_r���ͷ���Դ
 */
extern int ul_openlog_r(const char *threadname, ul_logstat_t  *l_stat, Ul_log_self *self = NULL);

/**
 * @brief �رձ��̵߳���־
 *
 * @param [in] iserr : ����־�м�¼����״̬��0Ϊ��������0Ϊ������
 * @return 0�ɹ���-1ʧ��
 */
extern int ul_closelog_r(int iserr);

/**
 * @brief ���ȫ����־�ȼ�
 *
 * @return  int 
**/
extern int ul_get_log_level();

#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
