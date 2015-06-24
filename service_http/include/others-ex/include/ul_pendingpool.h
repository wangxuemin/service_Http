/**
 * @file
 * @brief PendingPool��C++��ķ�ʽ�ṩ����һ��TCP���ӳأ��൱��ΪTCP�����ṩһ��������������ΪPendingPool�ṩ\n
 * ��һ�鷽��������ͨ����work_reset_itemʱ����bKeepAlive���ó�������
 */


#ifndef __HEAD_PENDINGPOOL_
#define __HEAD_PENDINGPOOL_

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

class PendingPool {
  public:
	PendingPool();
	
/**
 *  ���Ѿ����Ķ�������ȡһ���ѽ����õ�����
 *  
 *  @param[in]  handle  ���ڴ洢���Ӿ��������
 *  @param[in]  sock    ���ڴ洢����socket������
 *  @param[out] handle  ���Ӿ��
 *  @param[out] sock    ����socket
 *  @return ��������ֵ
 * - true   �ɹ�
 * - false  ʧ��
 */
	bool work_fetch_item(int &handle, int &sock);
	
	
	
	/**
	 * @brief �ر����Ӿ�� 
	 *
	 * @param [in] handle   : ���Ӿ��
	 * @param [in] bKeepAlive   : false�����Ӿ���رգ�true�����Ӿ�������Ϲر�
	 * @return  void 
	**/
	void work_reset_item(int handle, bool bKeepAlive); 
	int mask(fd_set * pfs);
	
/**
 *  ��PendingPool����һ������
 *  
 *  @param[in]  sock_work       �ѽ������ӵ��׽���
 *  @param[out] ��
 *  @return ������PendingPool�е�λ��
 * - >=0 ������PendingPool�е�λ��
 * - -1  ʧ��
 */
	int insert_item(int sock_work); 
	void check_item(fd_set * pfs);


/**
 *  ��offsetλ�õ����Ӽ��뵽�Ѿ����Ķ�����
 *  
 *  @param[in]  offset       ������PendingPool�е�λ��(insert_item()�ķ���ֵ)
 *  @param[out] ��
 *  @return ������PendingPool�е�λ��
 * - 0  �ɹ�
 * - -1 ʧ��
 */
	int queue_in(int offset);
	void set_timeout(int sec);
	
/**
 *  �����Ѿ������еĳ��ȣ�ע�⣺�˺�����set_socknum��������������֮ǰ���е��ã��������߳�\n
 *  ����poolǰ���ò��Ҳ��ܶ�̬����
 *  
 *  @param[in]  len       �����õĳ��ȣ�ע��������ʵ�ʿ��Դ洢������Ϊlen-1
 *  @param[out] ��
 *  @return ��
 */
	void set_queuelen(int len);
	
/**
 *  ���ÿɴ洢socket��������ע�⣺�˺�����set_queuelen��������������֮ǰ���е��ã��������߳�\n
 *  ����poolǰ���ò��Ҳ��ܶ�̬����
 *  
 *  @param[in]  num       �����õ�����
 *  @param[out] ��
 *  @return ��
 */
	void set_socknum(int num);
	
/**
 *  ��ȡ�ȴ���ȡ���ӵ��߳���
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return �ȴ���ȡ���ӵ��߳���
 */
	int get_freethread();
	
/**
 *  ��ȡ�Ѿ������еĳ��ȣ����صĳ��ȱ�set_queuelen()���õĳ�����һ��
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return �Ѿ������еĳ���
 */
	int get_queuelen();
	
	enum { MAX_SOCK = 500 };
	enum { QUEUE_LEN = 100 };
	enum { DEFAULT_TIMEOUT_SEC = 60 };
	typedef enum { NOT_USED = 0, READY, BUSY } eumStatus;
  private:
	struct SItem {
		int nSock;
		int nLastActive;
		int status;
	};

	int   m_socketNum;
	SItem *m_aySocket;

	int m_queueLen;
	int *m_ayReady;
	int m_nGet;
	int m_nPut;

	int m_nFreeThread;
	int m_nTimeOut;				// connection timeout value, in seconds

	pthread_mutex_t m_mutex;
	pthread_cond_t m_condition;

	pthread_mutex_t m_mutexCPU;
	pthread_cond_t m_condCPU;
	int m_nMaxSock;
};
#endif
