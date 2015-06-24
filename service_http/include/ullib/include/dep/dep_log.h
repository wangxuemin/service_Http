/***************************************************************************
 * 
 * Copyright (c) 2007 Baidu.com, Inc. All Rights Reserved
 * $Id: dep_log.h,v 1.2 2008/08/13 02:28:55 baonh Exp $ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file dep/dep_log.h
 * @author baonh(baonh@baidu.com)
 * @date 2007/12/09 19:14:25
 * @version $Revision: 1.2 $ 
 * @brief ���Ƽ�ʹ�õ���־�⺯�� 
 *  
 *  �˴��ĺ���Ϊ���Ƽ�ʹ�õĺ���, Ϊ�����ϰ汾������
 **/

#ifndef __DEP_LOG_H_
#define __DEP_LOG_H_

#define LOG_BUFF_SIZE 640     /**< һ����־buff��С,֧���ϰ汾�����ڴ������       */

#define MAX_ATTACH_NUM  1000
#define NAMENUM_INDATA  100
#define NAMELEN_INDATA  32
#define BUFSIZE_INDATA  640
#define SLEEP_INVAL     300

#define SVSEM_MODE      0666
#define SVSHM_MODE      (SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)
#define PRO_NAME_LEN    256
#define TIME_LEN        20

struct ul_log_ctrl {
    char  processname[PRO_NAME_LEN]; /**< �����������Ͳ��� , ����"_" ���ӡ� �� �� start_-d_/usr/mydir_c_myconf */
    int  processid;
    char start_time[TIME_LEN];
    ul_log_ctrl *next;
};

typedef struct ul_log_ctrl  Ul_log_ctrl;

typedef struct {
    char  name[NAMELEN_INDATA];
    int  value;
} Ul_log_item;

typedef struct {
    Ul_log_item  item_str[NAMENUM_INDATA]; // the process information
    char    buff[BUFSIZE_INDATA] ; // record the WARNING and FATAL log
} Ul_log_data;


typedef struct Ul_log_self;
typedef struct Ul_log_self Ul_log_self;

/**
 * @brief �߳���־��ʼ��(�ѷ���)
 *
 * ����Ϊ�����Ͻӿڶ������������Ѿ���ʹ����
 * @deprecated ����Ϊ�����Ͻӿڶ������������Ѿ���ʹ����
**/
extern int ul_threadlog_sup();

/*
 * In order to monitor the state of the process when it is running.
 * we need to export some status information.share memory is a good
 * choise.
 * when we open the log, we will attach a piece of share memory(
 * about 100 name-value pairs and a 640 byte buffer for this process
 * to export the information.
 * when exporting information,
 * use ul_log_assign to assign a name-value pair,
 * use ul_log_getid to get the id of the name-value pair,
 * use ul_log_setval by the id and value to set the value,
 * use ul_log_getval by the id and value to increment the value.
 * when monitor the information,
 * use ul_log_monproc to choise the process data
 * use ul_log_getval to get the value
 * use ul_log_getbuf to get the buffer content
 *
 */




/**
 * @brief assign a share memory variable for the name 
 *
 * @param [in] name   : the variable name
 * @param [in] ini_val   : the initial value
 * @return  0 if successfully, -1 if failed 
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/
extern int ul_log_assign(char *name, int ini_val);


/**
 * @brief get the share memory variable id by the name
 *
 * @param [in/out] name   : the variable name
 * @return  -1 if failed, id(>=0) if successfully
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/
extern int ul_log_getid(char *name);

/**
 * @brief the set the share memory variable
 *
 * @param [in] rel_loc : the shm variable id
 * @param [in] val :  the setting value
 * @return 0 if successfully, -1 if failed
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_log_setval( int rel_loc ,int val);

/**
 * @brief increment the shm variable by a given value
 *
 * @param[in] rel_loc : the shm variable id
 * @param[in] val :  the incremental step
 * @return 0 if successfully, -1 if failed
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_log_addval( int rel_loc, int val);

/*
 * @brief choice the monitor process in share memory
 *
 * @param[in] processname : the processname(as the argu 2 of ul_openlog)
 * @return 0 if successfully, -1 if failed
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_log_monproc(char * processname);

/*
 * @brief get the shm variable by the given name
 *
 * @param[in] name : the variable name
 * @param[out] pval, the buffer for output value
 * @return 0 if successfully, the *pval will be set, -1 if failed
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_log_getval(char * name,int *pval);

/*
 * @brief get the a special buffer in share memory
 *
 * @param[in] buflen, the output buffer size.
 * @param[out] buff, the outbuf buffer
 * @return 0 if successfully, the *pval will be set, -1 if failed
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_log_getbuf(char * buff,int buflen);

/*
 * @brief set item_str's number of Ul_log_data
 *
 * @param[in] namenum : item_str's number, namenum will be set to NAMENUM_INDATA if namenum less than NAMENUM_INDATA
 * @return the item_str's number
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
 */
extern int ul_set_namenum(int namenum);

/**
 * @brief ������־ʹ�õĹ����ڴ� 
 *
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/
extern int ul_log_createshm(void);

/**
 * @brief attach ��־�⣬ʹ�ù����ڴ� 
 *
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/
extern int ul_log_attachshm(void);

/**
 * @brief deattach��־�� ʹ�õĹ����ڴ�
 * 
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/
extern int ul_log_deattachshm(void);

/**
 * @brief �����־�� ʹ�õĹ����ڴ�
 * 
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/

extern int ul_log_cleanshm(char *proc_name, char *item_name, bool clean_buff);

/**
 * @brief ��ȡ������Ϣ
 * 
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/


extern int ul_log_listproc(char *proc_name, Ul_log_ctrl *proc_ctrl);
/**
 * @brief ��ȡ������Ϣ��Ӧ����
 * 
 * @deprecated ����־����ͨ�������ڴ淽ʽ��ȡ���ֽ�����Ϣ�ķ�ʽ�Ѿ��������Ѿ����ٲ�Ʒ��ʹ��
**/


extern int ul_log_listitem(char *proc_name, Ul_log_item *item_str, char *buff, int buff_len);

#endif // __DEP_LOG_H_
/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
