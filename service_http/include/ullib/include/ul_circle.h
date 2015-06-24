/////////////////////////////////////////////////////////////////////
//            Data struct abd function about data circle           //
/////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief �����ַ�����
 */
#ifndef __CIRCLEB_H__
#define __CIRCLEB_H__

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "ul_log.h"
#include "ul_func.h"

/* 
** Return code for function below 
*/

#define DEF_ERR_CQFULL		-2
#define DEF_ERR_NOTINIT		-3
#define DEF_ERR_CQEMPTY		-4
#define DEF_ERR_INITAGAIN	-5
#define DEF_ERR_PARTOOLITTLE	-6
#define DEF_ERR_MALLOC		-7
#define DEF_ERR_INVALID_PARAM -8

struct circleB_t 
{
	void *pbyBuf; // store the data of the circle
	int sBufLen;  // length of the circle
	int sHead;    // head of the circle
	int sTail;    // tail of the circle
};


/**
 * ��������������
 *  @param[in] pstCB  ָ���ζ��е�ָ��
 *  @param[in] pbyPut ����ӵ�����
 *  @param[in] nSize  ��������ݵ��ֽ���
 *  @param[out] ��
 *  @return �����������
 *  - 0 ��ʾ�ɹ�
 *  - DEF_ERR_CQFULL  ��ʾʧ��
 */ 
extern int nCBput( struct circleB_t *pstCB, void *pbyPut, int nSize );

/**
 * �Ӷ�����ȡ����
 *  @param[in] pstCB  ָ���ζ��е�ָ��
 *  @param[in] pbyPut ����ӵ�����
 *  @param[in] nSize  ��������ݵ��ֽ���
 *  @param[out] pbyGet ���յ�������
 *  @return �����������
 *  - 0 ��ʾ�ɹ�
 *  - DEF_ERR_CQEMPTY  ��ʾʧ�� 
 */ 
extern int nCBget( struct circleB_t *pstCB, void *pbyGet, int nSize );

/**
 * ��ʼ�������ַ�����
 *
 *  @param[in] npmBufSize ���ζ��еĿռ��С
 *  @param[out] ��
 *  @return ָ���ζ��е�ָ��
 *  - NULL ��ʾʧ��
 *  - ��NULL ��ʾ��ʼ���ɹ� 
 *  @note ��ʼ������ִ�к󣬽���ʱ����ʹ�� ::vCBfree �����ͷ� 
 */ 
extern struct circleB_t *pstCBinit( int npmBufSize );

/**
 * �ͷŻ����ַ�����
 *
 *  @param[in] pstCB ָ���ζ��е�ָ��
 *  @param[out] ��
 *  @return ��
 *  @note ��ʼ������::pstCBinitִ�к󣬽���ʱʹ�ô˺���
 */ 
extern void vCBfree( struct circleB_t *pstCB );

 
/**
 * �Ӷ�����ȡ���ݣ����ݲ��Ӷ������Ƴ�
 *
 *  @param[in] pstCB  ָ���ζ��е�ָ��
 *  @param[in] pbyGet �������ݵĻ�����ָ��
 *  @param[in] nSize  �������ݻ������Ĵ�С
 *  @param[out] pbyGet ���յ�������
 *  @return �����������
 *  - 0 ��ʾ�ɹ�
 *  - DEF_ERR_CQEMPTY  ��ʾʧ�� 
 */  
extern int nCBlookup( struct circleB_t *pstCB, void *pbyGet, int nSize );

 
/**
 * ȡ���ζ��������ݵĳ���
 *
 *  @param[in] pstCB ָ���ζ��е�ָ��
 *  @param[out] ��
 *  @return ���ݳ���
 */
extern int nCBgetdatalen( struct circleB_t *pstCB );

 
/**
 * ȡ���ζ�����ʣ��ռ�Ĵ�С
 *
 *  @param[in] pstCB ָ���ζ��е�ָ��
 *  @param[out] ��
 *  @return �ռ��С
 */
extern int nCBgetbufreelen( struct circleB_t *pstCB );

#endif
