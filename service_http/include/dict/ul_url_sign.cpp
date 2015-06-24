#include "ul_sign.h"
#include "ul_url.h"

int create_url_sign(const char* urlstr,
                    unsigned int site_sign[2],
                    unsigned int url_sign[2]) {
    // ��һ��URL��Ϊ����128λ��URLǩ����׼��������64λ��siteǩ�����Լ�64λ��suburlǩ��
    //URL����ΪMAX_URL_LEN_EX2
    char normalized_url[UL_MAX_URL_LEN_EX2];
    normalized_url[0] = '\0';
    if (!(ul_normalize_url_ex2(urlstr, normalized_url, UL_MAX_URL_LEN_EX2))) {
        return -1;
    }
    //��һ�����Ϊ0.
    normalized_url[UL_MAX_URL_LEN_EX2-1]='\0';

    //Ȼ��õ�site���ֵ�����..
    //SITE����ΪMAX_SITE_LEN_EX2
    char site[UL_MAX_SITE_LEN_EX2];
    site[0] = '\0';
    if (!ul_get_site_ex2(normalized_url, site, UL_MAX_SITE_LEN_EX2)) {
        return -1;
    }
    //��֤�������ȻΪ0.
    site[UL_MAX_SITE_LEN_EX2 - 1] = '\0';

    creat_sign_murmur64(site,strlen(site),site_sign,site_sign+1,0);
    creat_sign_murmur64(normalized_url,strlen(normalized_url),url_sign,url_sign+1,0);
    return 0;
}

int create_url_sign(const char *urlstr,
                    unsigned long long &site_sign,
                    unsigned long long &url_sign) {
    unsigned int x_site_sign[2];
    unsigned int x_url_sign[2];
    if(create_url_sign(urlstr,x_site_sign,x_url_sign)==-1) {
        return -1;
    }
    site_sign=(((unsigned long long)(x_site_sign[0]))<<32) +
              (unsigned long long)(x_site_sign[1]);
    url_sign=(((unsigned long long)(x_url_sign[0]))<<32) +
             (unsigned long long)(x_url_sign[1]);
    return 0;
}


//======================================================================
//Ϊpssearcher���ɳ��ṩ20101026.
//��Ҫ���ullib3.1.37.0ʹ��.
//Ϊpssearcher���ɳ��ṩ20110221.
//��Ҫ���ullib3.1.41.0ʹ��.
int ul_normalize_url_ex2_special_for_ps_20110221(const char* url, char* buf,size_t buf_size);
int create_url_sign2(const char* urlstr,
                     unsigned int site_sign[2],
                     unsigned int url_sign[2]) {
    // ��һ��URL��Ϊ����128λ��URLǩ����׼��������64λ��siteǩ�����Լ�64λ��suburlǩ��
    //URL����ΪMAX_URL_LEN_EX2
    char normalized_url[UL_MAX_URL_LEN_EX2];
    normalized_url[0] = '\0';
    if (!(ul_normalize_url_ex2_special_for_ps_20110221(urlstr, normalized_url, UL_MAX_URL_LEN_EX2))) {
        //�����һ��ʧ�ܵĻ�,
        //��ôֱ��ʹ��ԭ����url�����й�һ��.
        snprintf(normalized_url,sizeof(normalized_url),"%s",urlstr);
        return 0;
    }
    //��һ�����Ϊ0.
    normalized_url[UL_MAX_URL_LEN_EX2-1]='\0';

    //Ȼ��õ�site���ֵ�����..
    //SITE����ΪMAX_SITE_LEN_EX2
    char site[UL_MAX_SITE_LEN_EX2];
    site[0] = '\0';
    if (!ul_get_site_ex2(normalized_url, site, UL_MAX_SITE_LEN_EX2)) {
        return -1;
    }
    //��֤�������ȻΪ0.
    site[UL_MAX_SITE_LEN_EX2 - 1] = '\0';

    creat_sign_murmur64(site,strlen(site),site_sign,site_sign+1,0);
    creat_sign_murmur64(normalized_url,strlen(normalized_url),url_sign,url_sign+1,0);
    return 0;
}

int create_url_sign2(const char *urlstr,
                    unsigned long long &site_sign,
                    unsigned long long &url_sign) {
    unsigned int x_site_sign[2];
    unsigned int x_url_sign[2];
    if(create_url_sign2(urlstr,x_site_sign,x_url_sign)==-1) {
        return -1;
    }
    site_sign=(((unsigned long long)(x_site_sign[0]))<<32) +
            (unsigned long long)(x_site_sign[1]);
    url_sign=(((unsigned long long)(x_url_sign[0]))<<32) +
            (unsigned long long)(x_url_sign[1]);
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
