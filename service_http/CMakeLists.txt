###################################
# Author: JerryShi
# File:http service cmake file
# Date:2015-06-25 10:11:30
##################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(SERVICE_HTTP)


#set the compile property
SET(CMAKE_VERBOSE_MAKEFILE on)
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "")
SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-o -Wall")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#find dependent libraries jsoncpp,libiconv ,log4xx,apr,apr-util
#jsoncpp
FIND_PACKAGE(JSON)
IF(JSON_FOUND)
	INCLUDE_DIRECTORIES(${JSON_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(SERVICE_HTTP ${JSON_LIBRARY})
ELSE(JSON_FOUND)
	MESSAGE(FATAL_ERROR 
	"Json lib not found!
	You can run the install.sh file in this library in include/other-ex/lib
	to install jsoncpp
	")
ENDIF(JSON_FOUND)

#APR
FIND_PACKAGE(APR)
IF(APR_FOUND)
	INCLUDE_DIRECTORIES(${APR_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(SERVICE_HTTP ${APR_LIBRARY})
ELSE(APR_FOUND)
	MESSAGE(FATAL_ERROR 
	"Apr library not found!
	YOU can run the script file(install.sh) in the /include/other-ex/lib 
	to install apr
	")
ENDIF(APR_FOUND)

#APR-UTIL
FIND_PACKAGE(APR-UTIL)
IF(APR-UTIL_FOUND)
	INCLUDE_DIRECTORIES(${APR-UTIL_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(SERVICE_HTTP ${APR-UTIL_LIBRARY})
ELSE(APR-UTIL_FOUND)
	MESSAGE(FATAL_ERROR "Apr-UTIL library not found!
	YOU can run the script file(install.sh) in the /include/other-ex/lib 
	to install apr-util")
ENDIF(APR-UTIL_FOUND)

#log4xx
FIND_PACKAGE(LOG4XX)
IF(LOG4XX_FOUND)
	INCLUDE_DIRECTORIES(${LOG4XX_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(SERVICE_HTTP ${LOG4XX_LIBRARY})
ELSE(LOG4XX_FOUND)
	MESSAGE(FATAL_ERROR "Log4xx library not found!
	YOU can run the script file(install.sh) in the /include/other-ex/lib 
	to install log4xx")
ENDIF(LOG4XX_FOUND)

#libiconv
FIND_PACKAGE(LIBICONV)
IF(LIBICONV_FOUND)
	INCLUDE_DIRECTORIES(${LIBICONV_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(SERVICE_HTTP ${LIBICONV_LIBRARY})
ELSE(LIBICONV_FOUND)
	MESSAGE(FATAL_ERROR 
	"libiconv library not found!
	YOU can run the script file(install.sh) in the /include/other-ex/lib 
	to install libiconv
	")
ENDIF(LIBICONV_FOUND)

AUX_SOURCE_DIRECTORY(./src DIR_SRC)
ADD_EXECUTABLE(SERVICE_HTTP ${DIR_SRC})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/dict/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/other-ex/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/ullib/include)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/ullib/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE}/include/dict/lib)


