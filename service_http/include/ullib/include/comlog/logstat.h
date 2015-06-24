/***************************************************************************
* 
* Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
* $Id: logstat.h,v 1.2.22.2 2010/04/05 13:30:46 zhang_rui Exp $ 
* 
**************************************************************************/



/**
* @file logstat.h
* @author xiaowei(xiaowei@baidu.com)
* @date 2008/02/12 23:54:03
* @version $Revision: 1.2.22.2 $ 
* @brief 
*  
**/


#ifndef  __LOGSTAT_H_
#define  __LOGSTAT_H_

#include <ul_def.h>

//////#ifndef u_int64
////#define u_int64 unsigned long long
//#endif

namespace comspace
{

class LogStat
{
protected:
	//�ж�һ����־�ȼ��Ƿ���Դ�ӡ��ʱ��ֻ��Ҫ
	//(1<<level) & _level����
	unsigned long long _level;	//��ǰ��ϵͳ��־�ȼ�����bitmap��ʽ�洢���ȼ�����Ҫ����&һ��
	int _tty;

	char _conf_file[1024];	//�����ļ���
	//���ý����ķ���
	//int (*_load)(LogStat *);

public:
	//���ڴ������ļ���load ����������������ʱ̬��̬������־��������
	//confΪ�����ļ�����λ��
	//�ڵ������������ʱ����ж�_pid�߳��Ƿ񴴽������û�д�������������̡߳�
	//���þ��ע�ᵽ����load���߳�ɨ��������
	//int setAutoUpdate(const char *conf, int (*load)(LogStat *));
	//����ϵͳ�ȼ����û��ȼ���ϵͳ�ȼ���һ��int���û��ȼ����Զ��Ż��߿ո�ָ���Զ�����־��
	int setLevel(u_int sysmask, char *userlevel);
	inline int setTty(u_int tty) {
		return (_tty = tty);
	}
	inline bool unAccept(int level) {
		return ((((unsigned long long)1)<<level) & _level) == (unsigned long long)0;
	}

private:
	LogStat();

public:
	//����һ���µľ��
	static LogStat *createLogStat();
	//���ٴ���������LogStat
	//static int destroyLogStats();

	friend class Category;
};


//extern LogStat * g_def_logstat;LogStat * comlog_get_def_logstat();void comlog_set_def_logstat(LogStat *st);
};
#endif  //__LOGSTAT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
