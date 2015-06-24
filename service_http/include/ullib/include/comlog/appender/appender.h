/***************************************************************************
* 
* Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
* $Id: appender.h,v 1.2.22.3 2010/04/05 13:30:46 zhang_rui Exp $ 
* 
**************************************************************************/



/**
* @file appender.h
* @author xiaowei(xiaowei@baidu.com)
* @date 2008/02/12 23:54:09
* @version $Revision: 1.2.22.3 $ 
* @brief 
*  
**/


#ifndef  __APPENDER__APPENDER_H_
#define  __APPENDER__APPENDER_H_

#include "comlog/comlog.h"

namespace comspace
{
class Appender
{
public:
	com_device_t _device;	//�豸��		  /**<        */
	int  _id;			//�豸���		  /**<        */
	int _open;		  /**<        */
	Layout *_layout;				//layout		  /**<        */
	//u_int64 _mask;					//��־�ȼ�����		  /**<        */
	unsigned long long _mask;					//��־�ȼ�����		  /**<        */
	pthread_mutex_t _lock;		  /**<        */
	Appender * _bkappender;		  /**<        */

public:	
	/**
	 * @brief destructor
	 *
	**/
	virtual ~Appender();
	/**
	 * @brief set layout
	 *
	 * @param [in/out] layout   : Layout*
	 * @return  int 
	 * @retval   
	**/
	int setLayout(Layout *layout);	//����ͼ��
	/**
	 * @brief set device info
	 *
	 * @param [in/out] dev   : com_device_t&
	 * @return  int 
	 * @retval   
	**/
	int setDeviceInfo(com_device_t &dev);
	
	/**
	 * @brief reset mask
	 *
	 * @return  int 
	 * @retval   
	**/
	int resetMask();	//������־�ȼ����룬Ĭ��������֧��ϵͳ��־�ȼ��Ĵ�ӡ
	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	int emptyMask();	//�����־�ȼ������룬�����Ͳ�֧�ִ�ӡ�κ���־�ȼ�
	/**
	 * @brief 
	 *
	 * @param [in/out] id   : int
	 * @return  int 
	 * @retval   
	**/
	int addMask(int id);	//���֧��һ����־�ȼ�
	/**
	 * @brief 
	 *
	 * @param [in/out] id   : int
	 * @return  int 
	 * @retval   
	**/
	int delMask(int id);	//����֧��һ����־�ȼ�
	/**
	 * @brief 
	 *
	 * @param [in/out] id   : int
	 * @return  bool 
	 * @retval   
	**/
	bool unInMask(int id);	//�Ƿ���yanma��

	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	virtual int open(void *) = 0;	//���豸���
	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	virtual int close(void *) = 0;	//�ر��豸���
	//stop(): ֹͣ������־��FileAppender�������Ӵ���Ϣ��
	//��AsyncFileAppender/NetAppender���첽��ӡ����־����ʱӦ�˳��Լ����߳�
	//��Ҫ�����������̼߳�������comlog.cpp�е�g_close_atomc��
	virtual int stop(){return 0;}

	/**
	 * @brief print
	 *
	 * @param [in/out] evt   : Event*
	 * @return  int 
	 * @retval   
	**/
	virtual int print(Event *evt) = 0;	//����־ʵ��׷�ӵ��豸��
	/**
	 * @brief binprint
	**/
	virtual int binprint(void *, int siz) = 0;	//�������������

	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	virtual int flush();	//���̽�����д��Ӳ��
protected:
	/**
	 * @brief creator
	**/
	Appender(); 

public:
	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	virtual int syncid(void *);	//��⵱ǰid���豸�Ƿ�һ�£������һ�¸����豸������id������0��ʾ�ɹ�������ʧ�ܡ�

protected:

	//���ݴ���Ĳ�������ȡһ���豸
//	static pthread_mutex_t getlock;
public:
	/**
	 * @brief get appender
	 *
	 * @param [in/out] dev   : com_device_t&
	 * @return  Appender* 
	 * @retval   
	**/
	static Appender * getAppender(com_device_t &dev);
	/**
	 * @brief 
	 *
	 * @param [in/out] dev   : com_device_t&
	 * @return  Appender* 
	 * @retval   
	**/
	static Appender * tryAppender(com_device_t &dev);
	//Ϊclose��־��ʱ���ṩ����Դͳһ�ͷ�
	/**
	 * @brief 
	 *
	 * @return  int 
	 * @retval   
	**/
	static int destroyAppenders();
	friend class AppenderFactory;		  /**<        */
};

};
#endif  //__APPENDER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
