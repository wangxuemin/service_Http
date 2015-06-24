

/**
 * @file crm_correction.h
 * @author chenghengqi
 * @brief  服务端头文件
 *  
 **/

#ifndef _SU_SUSVR_H_
#define _SU_SUSVR_H_
#include <stdio.h>
#include <ul_strdict.h>
#include <ul_dict.h>
#include <ul_net.h>
#include "ul_sign.h"
#include "ul_strdict.h"
#include "ul_pendingpool.h"
#include "ul_thr.h"
#include "ul_url.h"
#include "ul_log.h"
enum t_type {URL, QUERY};
#define LOAD_STATIC_DICT 11
#define LOAD_QUERYFILTER_DICT 12
#define LOAD_ALL_STATIC_DICT 10
#define LOAD_EC_DICT 16
#define LOAD_HOUR_DICT 17
#define LOAD_SEX_DICT 19
#define LOAD_NEWS_DICT 20
#define STATIC_DICT_NAME "se_keyword.txt"
#define QUERY_FILETER_NAME "rssug_exact_mask"
#define G_SU_MAX_STATIC_BUFSIZE 22000
#define DEFAULT_HTTH_HEAD_STATUS 200
#define BAIDU_PARSE_COOKIE 1
#define UNION_NO_COOKIE 0
#define RANK_SUSVR_LOG 1            ///<只打印sug日志
#define RANK_COOKIE_LOG 2           ///<只打印cookie日志
#define RANK_SUSVR_COOKIE_LOG 3     ///<打印cookie和结果日志
#define PY_COOKIE_OPEN 1            ///<开启拼音sug功能
#define CN_COOKIE_OPEN 2            ///<开启中文sug
#define ALL_COOKIE_OPEN 3           ///<sug功能开启
#define ALL_COOKIE_CLOSE 0          ///<sug功能关闭
#define ACTION_OPENSEARCH 0         ///<opensearch接口
#define ACTION_BAIDU 1              ///<百度接口

const int G_SU_MAX_STR_LEN = 4096*10;
const int G_SU_MAX_QUERY_LEN = 4096;
const int STRATEGY_STATIC = 1;      ///<命中静态配置su
const int STRATEGY_DAY = 2;         ///<天级sug覆盖
const int STRATEGY_HOUR = 4;        ///<小时级sug覆盖
typedef enum{TRANCHAR_TYPE_QUERY,TRANCHAR_TYPE_SUGQUERY};
typedef enum{ACCONTS_DENY, ACCONTS_ALLOW};
#endif

