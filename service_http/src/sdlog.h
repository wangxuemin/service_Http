#ifndef _SDLOG_H_
#define _SDLOG_H_

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/thread.h>

#include <boost/utility.hpp>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//
//SDLOGʹ��˵��
//1.SDLOG_INITָ��ȫ�������ļ�
//2.ʹ��:SDLOG_WARN��
//
//////////////////////////////////////////////////////////////////////////////////

//Ϊ�����Ժ���չ,SDLOG��װΪ��
//��ȡlog4cxx��ȫ�������ļ�,���������ļ������ø�logger
#define SDLOG_INIT(strLogConfFile) { \
	log4cxx::PropertyConfigurator::configure(strLogConfFile);} \
	{												\
		string timeZoneEnv = "TZ=Asia/Shanghai";	\
		::putenv((char *)(timeZoneEnv.c_str()));	\
		tzset();									\
	}

//�����Դ�ļ����к���Ϣ��log
#define FMTLOG(level, loggername, fmt, arg...) \
	SDLOGFMT_##level(loggername, "[%s][%d][%s]"fmt, \
	__FILE__, __LINE__, __PRETTY_FUNCTION__, ##arg)



//�����־
#define SDLOG_DEBUG(strLogName,msg) {\
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(strLogName); \
	LOG4CXX_DEBUG(pLogger,msg); }
#define SDLOG_INFO(strLogName,msg) {\
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(strLogName); \
	LOG4CXX_INFO(pLogger,msg); }
#define SDLOG_WARN(strLogName,msg) {\
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(strLogName); \
	LOG4CXX_WARN(pLogger,msg); }
#define SDLOG_ERROR(strLogName,msg) {\
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(strLogName); \
	LOG4CXX_ERROR(pLogger,msg); }
#define SDLOG_FATAL(strLogName,msg) {\
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(strLogName); \
	LOG4CXX_FATAL(pLogger,msg); }



/////////////////////////////////////////////////////////////////////////////////////
//
// �ɱ������ʽ��sdlog
//
/////////////////////////////////////////////////////////////////////////////////////

#define  LOG_BUFF_SIZE 1024		//����5��format log����Ҫ��buffer��С

extern void SDLOGFMT_DEBUG(const char* loggername,const char* fmt,...);
extern void SDLOGFMT_INFO(const char* loggername,const char* fmt,...);
extern void SDLOGFMT_WARN(const char* loggername,const char* fmt,...);
extern void SDLOGFMT_ERROR(const char* loggername,const char* fmt,...);
extern void SDLOGFMT_FATAL(const char* loggername,const char* fmt,...);


extern void SDLOGFMT_DEBUG(const string loggername,const char* fmt,...);
extern void SDLOGFMT_INFO(const string loggername,const char* fmt,...);
extern void SDLOGFMT_WARN(const string loggername,const char* fmt,...);
extern void SDLOGFMT_ERROR(const string loggername,const char* fmt,...);
extern void SDLOGFMT_FATAL(const string loggername,const char* fmt,...);

#endif
