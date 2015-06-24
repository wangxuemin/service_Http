/**
 * @file
 * @brief �����ļ���
 */
/* Description:
 *   This program give some tools to manage the config file.
 *
 * Author: Cui Shanshan
 *         scui@baidu.com
 */
#ifndef _UL_MODULE_CONF_
#define _UL_MODULE_CONF_

#include "ul_def.h"
#include "dep/dep_conf.h"

const int MAX_CONF_ITEM_NUM = 1024 * 4;

typedef struct Ul_confitem {
	char name[WORD_SIZE];
	char value[WORD_SIZE];
}ul_confitem_t;

typedef struct Ul_confdata {
	int num;
	int size;
	ul_confitem_t *item;
}ul_confdata_t;


/**
 * ��ʼ�������ļ��ṹ
 *
 * @param conf_num ������Ŀ�������С��1024�����Զ�ʹ��1024
 * @return NULLʧ�ܣ�����Ϊ�����ļ��ṹָ��
 */
ul_confdata_t *ul_initconf(int conf_num);

/**
 * �ͷ������ļ��ṹ
 *
 * @param pd_conf �ṹָ��
 * @return 1���ǳɹ�
 */
int ul_freeconf(ul_confdata_t * pd_conf);

/**
 * �������ļ����ݶ���ṹ
 *
 * @param work_path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */
int ul_readconf(const char *work_path, const char *fname, ul_confdata_t * pd_conf);

/**
 * @brief �������ļ����ݶ���ṹ���У�֧��$include�﷨��������ȡָ��������
 *  ������ָ�� $include : "conf2" ������ڶ����������֮���conf2�ļ������á�
 *  ���conf2�������Ѿ���conf���ڣ���ô�����ļ�Ϊ����
 * 
 * @param [in/out] work_path   : const char* ����·��
 *    ���include�﷨ָ�����Ǿ���·������ô�ͼ̳����·��
 * @param [in/out] fname   : const char* �������ļ���
 * @param [in/out] pd_conf   : Ul_confdata* 
 * @return  int ����1��ʾ�ɹ�������ʧ��
 * @retval   
 * @see 
 **/
int ul_readconf_ex(const char *work_path, const char *fname, ul_confdata_t * pd_conf);

/**
 * �������ļ����ݶ���ṹ
 *
 * @param fullpath �ļ�ȫ·��
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */
int ul_readconf_no_dir(const char *fullpath, ul_confdata_t * pd_conf);

/**
 * �����ýṹ��Ϣд���ļ�
 *
 * @param work_path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */
int ul_writeconf(const char *work_path, const char *fname, ul_confdata_t * pd_conf);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪchar*����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_modifyconfstr(ul_confdata_t * pd_conf, char *conf_name, char *conf_value);

/**
 * ��������Ϣ�ṹ�����������ֵΪchar*����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_addconfstr(ul_confdata_t * pd_conf, char *conf_name, char *conf_value);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ�����������������ư汾��ֵΪchar*����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @param conf_n conf_name��ȡ����󳤶�
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconfnstr(ul_confdata_t * pd_conf, const char *conf_name, char *conf_value, const size_t n);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪint����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconfint(ul_confdata_t * pd_conf, char *conf_name, int *conf_value);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪint����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param [out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_modifyconfint(ul_confdata_t * pd_conf, char *conf_name, int conf_value);

/**
 * ��������Ϣ�ṹ�������������ֵ��ֵΪint����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_addconfint(ul_confdata_t * pd_conf, char *conf_name, int conf_value);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪfloat����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconffloat(ul_confdata_t * pd_conf, char *conf_name, float *conf_value);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪfloat����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param [out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_modifyconffloat(ul_confdata_t * pd_conf, char *conf_name, float conf_value);

/**
 * ��������Ϣ�ṹ�������������ֵ��ֵΪfloat����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_addconffloat(ul_confdata_t * pd_conf, char *conf_name, float conf_value);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪu_int����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconfuint(ul_confdata_t * pd_conf, char *conf_name, u_int *conf_value);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪu_int����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_modifyconfuint(ul_confdata_t * pd_conf, char *conf_name, u_int conf_value);

/**
 * ��������Ϣ�ṹ�����������ֵΪu_int����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_addconfuint(ul_confdata_t * pd_conf, char *conf_name, u_int conf_value);


/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪlong long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_getconfint64(ul_confdata_t * pd_conf, char *conf_name, long long *conf_value);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪlong long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_modifyconfint64(ul_confdata_t * pd_conf, char *conf_name, long long conf_value);

/**
 * ��������Ϣ�ṹ�����������ֵΪlong long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */
int ul_addconfint64(ul_confdata_t * pd_conf, char *conf_name, long long conf_value);


/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪunsigned long long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */

int ul_getconfuint64(ul_confdata_t * pd_conf, char *conf_name, unsigned long long *conf_value);

/**
 * ��������Ϣ�ṹ���޸��������ֵ��ֵΪunsigned long long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */


int ul_modifyconfuint64(ul_confdata_t * pd_conf, char *conf_name, unsigned long long conf_value);

/**
 * ��������Ϣ�ṹ�������������ֵ��ֵΪunsigned long long����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */

int ul_addconfuint64(ul_confdata_t * pd_conf, char *conf_name, unsigned long long conf_value);

/* 
** command argument 
*/
#define MAX_OPT_CONTENT 256
#define MAX_OPTION_NUM  20
#define MAX_MUTI_OPT    20
#define MAX_MOPT_NUM    10
#define MAX_BASE_OPTLEN 128
#define MAX_BASE_OPTNUM 10

typedef struct arg_option {
	char t_out;
	char option;
	char opt_cont[MAX_OPT_CONTENT];
}arg_option_t;

typedef struct base_arg {
	// 1 -- out ;
	char t_out;
	char b_argument[MAX_BASE_OPTLEN];
}base_arg_t;

typedef struct muti_option {
	char t_out;
	char option[MAX_MUTI_OPT];
	char opt_cont[MAX_OPT_CONTENT];
}muti_option_t;

typedef struct Ul_argu_stru {
//
	int opt_num;
	int cur_opt;
	arg_option_t option[MAX_OPTION_NUM];
//
	int mopt_num;
	int cur_mopt;
	muti_option_t m_option[MAX_MOPT_NUM];
//
	int arg_num;
	int cur_arg;
	base_arg_t b_arg[MAX_BASE_OPTNUM];
}ul_argu_stru_t;

//=====================================================================/
//        function prototype
//=====================================================================
/**
 * @create a ul_argu_stru_t struct
 * @param void
 * @return the pointer is successfully
 *         NULL if failed
 */
ul_argu_stru_t *argument_init();

/**
 * @destroy the struct and free thr resource
 * @param argument_struct, the pointer to the struct
 * @return void
 */
void argument_destroy(ul_argu_stru_t * argument_struct);

/**
 * @convert the argv into ul_argu_stru_t struct
 * @param argc the main function arguments
 * @param argv the main function arguments
 * @param[out] argument_struct  the struct
 * @return 0 if successfully, -1 if failed.
 */
int read_argument(ul_argu_stru_t * argument_struct, int argc, char **argv);

/**
 * @check a option in argus
 * @param option the option char
 * @param argument_struct some member will be changed in this function
 * @param opt_size when input, it is the buffer size of the opt_value
 * if successfully, opt_size will be set with the length of the opt_value. if failed, it will be undefined
 * @param[out]  opt_value the option string buffer
 * @return   0 if not find the option or buffer is not enough, >0 if successfully
 */
int get_one_option(ul_argu_stru_t * argument_struct, char option, char *opt_value, int *opt_size);

/**
 * @check a complex option in argus
 * @param option, the option string
 * @param argument_struct some member will be changed in this function
 * @param opt_size, when input, it is the buffer size of the opt_value
 *        if successfully, opt_size will be set with the length
 *        of the opt_value. if failed, it will be undefined
 * @param[out] opt_value, the option string buffer
 * @return  0 if not find the option or buffer is not enough, >0 if successfully
 * @note  refer get_one_option
 */
int get_one_complex_option(ul_argu_stru_t * argument_struct, char *option, char *opt_value, int *opt_size);

/**
 * @take out the base parameter
 * @param serial serial of the base option
 *        0 means the first parameter
 * @param b_argument the output buffer for base argument
 * @param size when in, it is the max  size of the b_argument
 *             when out, the length of the b_argument is successfully
 *             undefined if failed.
 * @return 0 if not found or the buffer was little, >0 if found
 */
int get_base_argument(ul_argu_stru_t * argument_struct, int serial, char *b_argument, int *size);

#endif
