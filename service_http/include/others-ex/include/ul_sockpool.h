/**
 * @file
 * @brief �ṩһ�������������ӳصķ���,֧���̼߳�����
 */


#ifndef __SOCKPOOL_H_
#define __SOCKPOOL_H_

#include <pthread.h>

#define ERR_SOCKPOOL_EXIST -2
#define ERR_SOCKPOOL_FULL -3
#define ERR_SOCKPOOL_EMPTY -4
#define ERR_SOCKPOOL_OVERTIME -5
#define ERR_SOCKPOOL_SYSERR -6
#define SOCKPOOL_MAXSIZE 4096

typedef struct _socket_pool_t{
	int m_size;
	pthread_cond_t m_empty_cond;
	pthread_mutex_t m_pool_mutex;
	int m_curnum;
	int m_freenum;
	int m_overtime;		//overtime count in seconds
	int m_socks[SOCKPOOL_MAXSIZE];
} Sockpool;

 
/**
 *  ��ʼ���׽��ֳ�
 *  
 *  @param[in]  sp       ָ���ѷ�����׽��ֳصĿռ��ָ��
 *  @param[in]  size     �׽��ֳصĴ�С������ܳ���4096
 *  @param[in]  overtime ��ʱʱ�䣨�룩
 *  @param[out] ��
 *  @return ��������ֵ
 * - 0  �ɹ�
 * - -1 ʧ��
 */
int sockpool_init(Sockpool *sp ,const int size,const int overtime);








/**
 *  ���׽��ֳ�������׽���
 *  
 *  @param[in]  sp       �׽��ֳ�
 *  @param[in]  sock     ��������׽���
 *  @param[out] ��
 *  @return ��������ֵ
 * - 0                  �ɹ�
 * - ERR_SOCKPOOL_FULL  ����
 * - ERR_SOCKPOOL_EXIST �Ѵ���
 */
int sockpool_add(Sockpool *sp, int sock);





/**
 *  ���׽��ֳ���ȡһ����׼���õ��׽��ֻ����г�ʱ���׽���
 *  
 *  @param[in]  sp          �׽��ֳ�
 *  @param[in]  sock        ���ڴ洢�Ѿ������׽��ֵ�����
 *  @param[in]  ot_socklist ָ��洢��ʱ���׽��ֵĿռ�
 *  @param[in]  otcount     ���ڴ洢��ʱ���׽��ֵĸ���������
 *  @param[out] sock        ��������0ʱ���洢�Ѿ������׽���
 *  @param[out] ot_socklist ��������ERR_SOCKPOOL_OVERTIMEʱ���洢��ʱ���׽���
 *  @param[out] otcount     ��������ERR_SOCKPOOL_OVERTIMEʱ���洢��ʱ���׽��ֵĸ���
 *  @return ��������ֵ
 * - 0                     �ɹ�
 * - ERR_SOCKPOOL_EMPTY    �׽��ֳ�Ϊ��
 * - ERR_SOCKPOOL_SYSERR   ϵͳ����
 * - ERR_SOCKPOOL_OVERTIME ��ʱ
 */
int sockpool_pick(Sockpool *sp,int &sock, int *ot_socklist, int &otcount);





/**
 *  ��ȡ�����׽������·Żص��׽��ֳ���
 *  
 *  @param[in]  sp          �׽��ֳ�
 *  @param[in]  sock        �׽��֣����Ϊ-1�����׽��ֳ����׽��ֵļ�����1
 *  @param[out] ��
 *  @return ��������ֵ
 * - 0                     �ɹ�
 */
int sockpool_unpick(Sockpool * sp,int sock);



/**
 *  �ж��׽��ֳ��Ƿ�����
 *  
 *  @param[in]  sp          �׽��ֳ�
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 ����
 * - 0 δ��
 */
int sockpool_isfull(Sockpool * sp);

#endif
