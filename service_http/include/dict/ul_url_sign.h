/* -*- c++ -*- 
   copy[write] by dirlt(dirtysalt1987@gmail.com) */
#ifndef _UL_URL_SIGN_H_
#define _UL_URL_SIGN_H_


/**
 * @brief calc 64bit site sign & 64bit url sign for a url string
 *
 * @param [in] urlstr   : const char*  null terminated url string
 * @param [out] site_sign   : unsigned long long& 
 * @param [out] url_sign   : unsigned long long&
 * @return  int  0 on sucess -1 on failure
 * @author liuchengcheng
 * @date 2010/07/05 14:38:14
 **/
//��urlstr���й�һ��,Ȼ��ʹ��murmurhash������site��url��ǩ��.
//����site_sign[0]��url_sign[0]Ϊ��32λ,site_sign[1]��url_sign[1]Ϊ��32λ.
int create_url_sign(const char *urlstr,unsigned int site_sign[2],unsigned int url_sign[2]);
int create_url_sign(const char* urlstr, unsigned long long& site_sign, unsigned long long& url_sign);


//��������������������������������ͬ
//�����ڴ���url����,֧��������������url
//http://6wq-.blog.sohu.com/106289.html
//����.֮ǰ����-����������url.��create_url_sign����������url�ᱨ��.
//Ϊpssearcher���ɳ��ṩ20101026.
//��Ҫ���ullib3.1.37.0�����Ǹ��߰汾ʹ��.
int create_url_sign2(const char *urlstr,unsigned int site_sign[2],unsigned int url_sign[2]);
int create_url_sign2(const char* urlstr, unsigned long long& site_sign, unsigned long long& url_sign);

#endif
