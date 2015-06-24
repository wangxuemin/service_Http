/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: eventsvr.h,v 1.2 2009/03/25 12:34:11 yingxiang Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file eventsvr.h
 * @author xiaowei(xiaowei@baidu.com)
 * @date 2008/02/12 23:57:32
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __EVENTSVR_H_
#define  __EVENTSVR_H_
namespace comspace
{
/*
 * ���̵߳�������У�����������־���ȫ������
 * ��ǰ�õ��ľ���ע��һ����������־�Ļص�������������ʱ̬��̬�޸���־
 */
class EventSvr
{
public:
	//������¼���ʽ
	struct event_t
	{
		void *_param;	//�ص������Ĳ���
		void *(*_callback)(void *param);	//�����¼��Ļص�����
	};

public:
	//����̴߳���ʱ��
	int addEvent(event_t *evt);
	//�����̴߳���ʱ��
	int removeEvent(event_t *evt);
	//���̰߳�ȫ�˳�
	int safexit();

private:
	//�����̣߳��ڵ�һ�ε���addevent��ʱ�����
	int startThread();
	EventSvr();

private:

	pthread_t _tid;	//�߳�id

	int _monitor_time;	//���ʱ����
	bool _running;		//�Ƿ�������
public:
	//��ȡȫ��Ψһ�ľ��
	static LogThread * getInstance();
};
}
#endif  //__LOGTHREAD_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
