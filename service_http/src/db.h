#ifndef _DB_H_
#define _DB_H_

#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string>
#include <set>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <fstream>
#include <mysql.h>
#include <my_global.h>

class DbAccess{
    std::string host_;
    std::string user_;
    std::string pwd_;
    uint32_t port_;
    MYSQL* mysql_;

    void connect_()
    {
        mysql_close(mysql_);
        while (mysql_real_connect(mysql_, host_.c_str(), user_.c_str(), pwd_.c_str(), 
              NULL, 0, NULL, 0) == NULL) {
            fprintf(stderr, "%s\n", mysql_error(mysql_));
            mysql_close(mysql_);
            sleep(2);
        }
    }

    int route_(const std::string& id) 
    {
        int r = 0;
        sscanf(id.substr(0, 2).c_str(), "%x", &r);
        return r;
    }

    std::string exception_()
    {
        fprintf(stderr, "%s\n", mysql_error(mysql_));
        return  mysql_error(mysql_);
    }

public:
    DbAccess(const std::string& host
      ,const std::string& user
      ,const std::string& pwd
      ,uint32_t port = 3306
      )
      :host_(host)
       ,user_(user)
       ,pwd_(pwd)
       ,port_(port)
       ,mysql_(NULL)
    {
        mysql_ = mysql_init(NULL);
        if (mysql_ == NULL){
            fprintf(stderr, "%s\n", mysql_error(mysql_));
            exit(1);
        }

        connect_();
    }

    int get_doc(const std::string& id, 
      Json::Value& r,
      std::string& info,
      const std::string& fields=""
      )
    {
        if (mysql_errno(mysql_) == 2006)
            connect_();

        if (fields.length() == 0)
            fields = "docid,cluster_id,title,site,merchant, knn,tags,ori_cat,url,sales,cmt_count,opics,pics,attr,price1,price_sum/updt_num as mean_price,min_price,spu";

        char st[1024];memset(st, 0 ,sizeof(st));
        sprintf(st, "select %s from commodity_%d where docid=\"%s\"", fields.c_str(), route_(id), id.c_str());
        if(mysql_query(mysql_, st)){
            info = exception_();
            return -1;
        }
        MYSQL_RES *result = mysql_store_result(mysql_);
        if (result == NULL){
            info = exception_();
            return -1;
        }
        std::vector<string> cols;
        MYSQL_FIELD *fd;
        for(uint32_t i=0;fd=mysql_fetch_field(result);i++)
            cols.push_back(fd->name);

        uint32_t fldnum = mysql_num_fields(result);
        assert(fldnum == cols.size());
        MYSQL_ROW sql_row;
        while(sql_row=mysql_fetch_row(result))
            for (uint32_t i=0;i<fldnum;i++){
                Json::Value v;
                v[cols[i]] = sql_row[i];
                r.appand(v);
            }

        info = "success";
        return r.size();
    }
};

#endif

