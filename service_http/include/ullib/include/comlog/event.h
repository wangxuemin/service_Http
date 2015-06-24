/***************************************************************************
* 
* Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
* $Id: event.h,v 1.3.14.1 2010/03/25 08:18:08 zhang_rui Exp $ 
* 
**************************************************************************/



/**
* @file event.h
* @author xiaowei(xiaowei@baidu.com)
* @date 2008/01/30 18:56:39
* @version $Revision: 1.3.14.1 $ 
* @brief 
*  
**/


#ifndef  __EVENT_H_
#define  __EVENT_H_

#include <sys/time.h>
#include <pthread.h>

namespace comspace
{

class Layout;
class Appender;

class Event
{
	static const int MAXMSGSIZE = 2048;
	static const int MAXRENDERMSGSIZE = 2048;
	static const int PROCNAMESIZE = 64;
//	static int _max_msgsize;//
//	static int _max_render_msgsize;
public:
	static const int NDCSIZE = 64;
	static const int NDCNUM = 32;
public:
	//��־��ӡ����
	unsigned int _log_level;	//��־�ȼ� %L
	timeval _print_time;	//��־��ӡʱ�� %A

	char _proc_name[PROCNAMESIZE];	//������
	pthread_t _thread_id;		//�߳�id %T

	struct node_t
	{
		char key[NDCSIZE];
		char value[NDCSIZE];
	} _ndcs[NDCNUM];		//�����ӡ��key value ��
	int _ndc_num;	//push������ndc�� %N

	char *_msgbuf;	//��־��ӡbuf %R
	int _msgbuf_size;	//��ӡ��־��buf��С
	int _msgbuf_len;	//ʵ�ʴ���ĳ���

	//��һ����Ⱦ��layout���������ϴ���Ⱦ��layout�����һ��������Ҫ��Ⱦֱ�����
	//Layout *_layout;		

	char *_render_msgbuf;		//��Ⱦ��־�Ŀռ�
	int _render_msgbuf_size;	//��Ⱦ�ռ�ĳ���
	int _render_msgbuf_len;

	Appender *_nowapp;	//��ǰ��������appender
public:
	int reset();	//��event�������
	Event();
	~Event();

	static Event *getEvent();
	/**
	 * @brief ��־����󳤶�
	 *			��Ҫ��openlog֮ǰ������
	 * @param [in] n   : int ��󳤶ȣ�< 0ʱȡĬ��ֵ
	 * @return  int ���ú����־��󳤶�
	 * @retval   
	 * @see 
	 * @author yingxiang
	 * @date 2009/03/26 22:53:03
	**/
	static int setMaxLogLength(int n);

public:
	int push(const char *key, const char *val);
};

};
#endif  //__EVENT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
