/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_conf.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_conf_dep.h
 * @author xiaowei(com@baidu.com)
 * @date 2007/12/20 11:51:26
 * @version $Revision: 1.2 $ 
 * @brief 
 *  
 **/


#ifndef  __UL_CONF_DEP_H_
#define  __UL_CONF_DEP_H_

typedef struct Ul_confitem Ul_confitem;
typedef struct Ul_confdata Ul_confdata;
typedef struct Ul_confdata ul_confdata_t;
typedef struct arg_option arg_option;
typedef struct base_arg base_arg;
typedef struct muti_option muti_option;
typedef struct Ul_argu_stru Ul_argu_stru;

/**
 * ����readnumϵ�е�ԭ���ǣ������ļ���Ȼ��conf.n��ȡ������ֵ���Ϊ
 */

/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪint ����
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_readnum_oneint(const char *work_path, const char *fname, char *vname, int *pvalue);


/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪunsigned int ����
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_readnum_oneuint(const char *work_path, const char *fname, char *vname, unsigned int *pvalue);


/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪlong long����
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_readnum_oneint64(const char *work_path, const char *fname, char *vname, long long *pvalue);

/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪunsigned long long����
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_readnum_oneuint64(const char *work_path, const char *fname, char *vname,
						 unsigned long long *pvalue);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪchar*����
 * ��Ϊû���ж��ַ����ĳ��ȣ����Բ���ȫ
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconfstr(ul_confdata_t * pd_conf, char *conf_name, char *conf_value);

/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪint ����. ���û����Ӧ��������, ���ӡ��־
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���-1û���ҵ�
 */
int ul_kreadnum_oneint(const char *work_path, const char *fname, char *vname, int *pvalue);


/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪfloat ����. ���û����Ӧ��������, ���ӡ��־
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���-1û���ҵ�
 */
int ul_kreadnum_onefloat(const char *work_path, const char *fname, char *vname, float *pvalue);


/** 
 * ��ʼ�������ļ�,����ļ��Լ�����,�Ὣ�����
 *
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @return >=0 �ɹ� <0 ʧ��
 */
int ul_writenum_init(const char *work_path, const char *fname);

/**
 * ��һ��������д�������ļ���, ֵΪint����
 *
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param value �������ֵ
 * @return >=0 �ɹ� <0 ʧ��
 */
int ul_writenum_oneint(const char *work_path, const char *fname, const char *vname, int value);

/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪu_int ����. ���û����Ӧ��������, ���ӡ��־
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���-1û���ҵ�
 */
int ul_kreadnum_oneuint(const char *work_path, const char *fname, char *vname, u_int *pvalue);

/**
 * ��һ��������д�������ļ���, ֵΪu_int����
 *
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param value �������ֵ
 * @return >=0 �ɹ� <0 ʧ��
 */
int ul_writenum_oneuint(const char *work_path, const char *fname, const char *vname, u_int value);

/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪint64����. ���û����Ӧ��������, ���ӡ��־
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���-1û���ҵ�
 */
int ul_kreadnum_oneint64(const char *work_path, const char *fname, char *vname, long long *pvalue);

/**
 * ��һ��������д�������ļ���, ֵΪint64����
 *
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param value �������ֵ
 * @return >=0 �ɹ� <0 ʧ��
 */
int ul_writenum_oneint64(const char *work_path, const char *fname, const char *vname, long long value);


/**
 * ֱ�Ӵ������ļ��л�ȡһ���������ֵ, ֵΪunsigned long long����. ���û����Ӧ��������, ���ӡ��־
 * 
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param[out] pvalue �������ֵ
 * @return 1�ɹ���-1û���ҵ�
 */
int ul_kreadnum_oneuint64(const char *work_path, const char *fname, char *vname, unsigned long long *pvalue);

/**
 * ��һ��������д�������ļ���, ֵΪunsigned long long����
 *
 * @param work_path �����ļ�·��
 * @param fname �����ļ���
 * @param vname ��������
 * @param value �������ֵ
 * @return >=0 �ɹ� <0 ʧ��
 */
int ul_writenum_oneuint64(const char *work_path, const char *fname, const char *vname, unsigned long long value);














#endif  //__UL_CONF_DEP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
