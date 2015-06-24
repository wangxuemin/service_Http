/***************************************************************************
 * 
 * Copyright (c) 2008 Baidu.com, Inc. All Rights Reserved
 * $Id: mempool.h,v 1.2 2009/03/25 12:34:11 yingxiang Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file mempool.h
 * @author xiaowei(xiaowei@baidu.com)
 * @date 2008/03/07 21:53:09
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __MEMPOOL_H_
#define  __MEMPOOL_H_

#include "comlog/comempool/dlist.h"

namespace comspace
{

#define SIZEOFPTR(x) \
	((*((int *)((size_t)(x) - sizeof(int)))) - (int)sizeof(int))

struct memlist_t
{
	memlist_t *next;
	long  used;
	char cnt[0];
};

class FixMem
{
	//������ڴ�����
	memlist_t *_mem;
	//Ŀǰ���ڷ�����ڴ�����
	memlist_t *_now;
	//��������ͷ
	memlist_t *_free;

	//�������
	int _nowb;
	int _reab;

	//�����ڴ��Ĵ�С
	long _size;

	//���������Ĵ�С
	int _bsize;
	//ÿ�η�����ٿ�
	int _bnum;
public:
	int create(int bnum, int bsize);
	void destroy();
	void *alloc();
	void dealloc(void *);
	void reset();
};


class MemPool
{
	static const int DEFLEVEL = 11;
	static const int DEFMAXMEM = 1<<20;
	static const int DEFMINMEM = 1<<10;

	//������ڴ����䣬��С�ڴ浽����ڴ棬������ͷint
	int _maxmem;
	int _minmem;
	//Ŀǰ���ܷ��������ڴ棬��������ֱ��malloc
	int _allocmem;
	//���������ı���
	float _rate;
	//Ŀǰ���ļ���
	int _level;
	//�ڴ�����
	FixMem _fixmem[DEFLEVEL];
	//���ڴ�Ļ�������
	dlist_t *_biglist;
public:
	/**
	 * @brief �����ڴ��
	 *
	 * @param [in/out] minmem   : int	��С���ڴ���䵥Ԫ
	 * @param [in/out] maxmem   : int	�������������ڴ�
	 * @param [in/out] rate   : float	������С��Ԫÿ�������ı�����������������������ڴ�
	 * 									���10��
	 * @return  int 	�ɹ�����0��ʧ�ܣ�1
	 * @retval   
	 * @see 
	 * @author xiaowei
	 * @date 2008/03/10 11:31:54
	**/
	int create(int minmem=DEFMINMEM, int maxmem=DEFMAXMEM, float rate=2.0f);

	/**
	 * @brief ɾ��mempool
	 *
	 * @return  void 
	 * @retval   
	 * @see 
	 * @author xiaowei
	 * @date 2008/03/10 14:21:45
	**/
	void destroy();

	/**
	 * @brief �����ڴ�
	 *
	 * @param [in/out] size   : int ��Ҫ������ڴ��С
	 * @return  void* ���ؿ��õ��ڴ�ָ�룬ʧ�ܷ���-1
	 * @retval   
	 * @see 
	 * @author xiaowei
	 * @date 2008/03/10 11:33:17
	**/
	void *alloc(int size);

	/**
	 * @brief �ͷ��ڴ�
	 *
	 * @return  void 
	 * @retval   
	 * @see 
	 * @author xiaowei
	 * @date 2008/03/10 14:20:27
	**/
	void dealloc(void *);

	void reset();

public:
	int getidx(int size);
};


};

#endif  //__MEMPOOL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
