/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: category.h,v 1.2 2009/03/25 12:34:11 yingxiang Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file category.h
 * @author xiaowei(xiaowei@baidu.com)
 * @date 2008/01/30 20:10:09
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __CATEGORY_H_
#define  __CATEGORY_H_

#include <stdio.h>
#include <stdarg.h>

#include "comlog.h"
#include "logstat.h"
#include "appender/appender.h"
#include "event.h"

namespace comspace
{

typedef void(* log_callback_t)(int loglevel, const char *format, va_list ap, void *param);

class Category
{
	class Push
	{
		Category * _cate;
	public:
		Push(Category *);
		Push & operator () (const char *key, const char *fmt, ...);
		int operator () (int level, const char *fmt, ...);
	};

	public:
		Event *_event;		                          /**<        */

	protected:
		Category *_parent;	//���׾��
		LogStat *_logstat;	//��־״̬���ƾ��

		Appender *_appenders[COM_MAXDEVICENUM];		  /**<        */
		int _appnum;		                          /**<        */

	protected:
		Category(Category *parent = NULL);

        static log_callback_t _g_callback;		  /**<  �ص�����      */
        static void *_g_callback_param;		      /**<  �ص������Զ������      */
	public:
		virtual ~Category();

		int setLogStat(LogStat *logstat = NULL);	//�������ÿ��ƾ��
		int print(u_int level, const char *fmt, ...);	//������־�ȼ���ӡ��־

		//���,ɾ�������appender
		int addAppender(Appender *);
		int removeAppender(Appender *);
		int clearAppender();

		int print(u_int level, const char *fmt, va_list args);
		inline LogStat * logstat() {
			return _logstat;
		}
		inline int appender_num() {
			return _appnum;
		}
	public:
		Push push;

	public:
		//static pthread_mutex_t glock;
		static Category * getInstance(const char *name);
		static void setCallback(log_callback_t callback, void *callback_param)
        {
            _g_callback = callback;
            _g_callback_param = callback_param;
        }
		//�Զ�����־�ȼ�
		//������־�ȼ�����־���Ķ�Ӧ��ϵ
		//�Զ�����־id��USERLOGLEVEL(32)��
		//���ݵȼ����õ��ȼ�id������ȼ��������ڣ���ô���Զ�����һ��id����಻�������Զ�����id��
		//static unsigned int getLogID(const char *name);
};
};

#endif  //__CATEGORY_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
