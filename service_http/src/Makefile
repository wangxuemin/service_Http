version=1.0.0.0
config=output
lang=cn


TARGETS=service_http
CC=g++

CONF_CONF_LIST:=$(addprefix shell/, $(CONF_CONF_LIST))
EXTEND_LIST:=$(addprefix data/, $(EXTEND_LIST))
SHELL_LIST:=./service_http ./start.sh ./stop.sh ./run
PUB_CONF:=$(addprefix $(PUB_OUTPUT), $(PUB_CONF))
WORD_CONF:=$(addprefix $(PUB_OUTPUT), $(WORD_CONF))
WORD_CONF_NLP:=$(addprefix data/, $(WORD_CONF_NLP))
DICT_NLP:=$(addprefix data/, $(DICT_NLP))

THIRD_DIR:=../include/others-ex/lib/
JSON_DIR:=$(THIRD_DIR)/jsoncpp/

ifeq ($(config), debug)
	CPPFLAGS+= -g -DRSDEBUG
else
	CPPFLAGS+= -g -O2
endif
OUT_DIR=$(config)/
version+= $(config)

CPPFLAGS+= -Wall -Wno-deprecated -pipe -D_REENTRANT -pthread -DVERSION=\""$(version)"\" 

ifeq ($(lang), jp)
	CPPFLAGS+= -DRSJP
else
	CPPFLAGS+= -DRSCN
endif


LIBPATH=-L./ \
		-L ../include/dict/lib \
		-L ../include/ullib/lib \
        -L ../include/others-ex/lib \
		-L $(THIRD_DIR)/log4cxx/lib/ -L $(THIRD_DIR)/apr-util/lib/ \
		-L $(JSON_DIR)/lib/ -L $(THIRD_DIR)/util/lib/ -L $(THIRD_DIR)/apr/lib/ \
		-L $(WORD_SEG_DIR)/public/clib/lib  -L $(THIRD_DIR)/libiconv/lib \
		-L /usr/local/lib/

LDFLAGS=-lstdc++ \
		-lullib_ex \
		-luldict -lutil -llog4cxx \
		-lullib -lgcov  -ljson \
		-lm -lpthread -liconv -laprutil-1 -lapr-1 -lexpat -lboost_system  -lboost_thread

INCLUDES= -I./ \
		  -I ../include/ullib/include \
		  -I ../include/dict/include \
		  -I ../include/others-ex/include \
		  -I $(THIRD_DIR)/log4cxx/include \
		  -I $(JSON_DIR)/include/ \


all: $(TARGETS) output
clean:
		/bin/rm -f $(TARGETS) *.o rm -rf $(OUT_DIR) service_http
		/bin/rm -f *~ 


output: $(TARGETS)
	@echo; echo "Copy executable file(s)..."
	@cp -v $(TARGETS) ../bin


service_http:service_http.o protocol.o utility.o signdict.o sdlog.o
	$(CC) $(CPPFLAGS) -o $@ $^ $(INCLUDES) $(LIBPATH) $(LDFLAGS) 

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDES)



