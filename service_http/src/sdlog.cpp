#include "sdlog.h"
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

void SDLOGFMT_DEBUG(const char* loggername,const char* fmt,...)
{
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_DEBUG(pLogger,buf);
		//pLogger->forcedLog(::log4cxx::Level::DEBUG,buf,__FILE__,__LINE__);
	}
}

void SDLOGFMT_INFO(const char* loggername,const char* fmt,...)
{
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isInfoEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_INFO(pLogger,buf);
		//pLogger->forcedLog(::log4cxx::Level::DEBUG,buf,__FILE__,__LINE__);
	}
}

void SDLOGFMT_WARN(const char* loggername,const char* fmt,...)
{
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isWarnEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_WARN(pLogger,buf);
		//pLogger->forcedLog(::log4cxx::Level::DEBUG,buf,__FILE__,__LINE__);
	}
}

void SDLOGFMT_ERROR(const char* loggername,const char* fmt,...)
{
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isErrorEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_ERROR(pLogger,buf);
		//pLogger->forcedLog(::log4cxx::Level::DEBUG,buf,__FILE__,__LINE__);
	}
}

void SDLOGFMT_FATAL(const char* loggername,const char* fmt,...)
{
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isFatalEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_FATAL(pLogger,buf);
		//pLogger->forcedLog(::log4cxx::Level::DEBUG,buf,__FILE__,__LINE__);
	}
}


void SDLOGFMT_DEBUG(const string loggername,const char* fmt,...){
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_DEBUG(pLogger,buf);
	}
}

void SDLOGFMT_INFO(const string loggername,const char* fmt,...){
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_INFO(pLogger,buf);
	}
}

void SDLOGFMT_WARN(const string loggername,const char* fmt,...){
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_WARN(pLogger,buf);
	}
}

void SDLOGFMT_ERROR(const string loggername,const char* fmt,...){
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_ERROR(pLogger,buf);
	}
}

void SDLOGFMT_FATAL(const string loggername,const char* fmt,...){
	log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger(loggername);
	if (pLogger->isDebugEnabled())
	{
		va_list args;
		va_start(args,fmt);
		char buf[LOG_BUFF_SIZE];
		int rev = vsnprintf(buf,sizeof(buf),fmt,args);
		va_end(args);
		if (-1 == rev)
		{
			std::cout<<"SDLOG MESSAGE TOO LONG\n";
			return;
		}
		LOG4CXX_FATAL(pLogger,buf);
	}
}

