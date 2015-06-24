/**
 * @file
 * @brief �����Ե��ض����ַ�������
 */


/**
 * @brief ��һ���ַ����в����ض������ַ��������Ƚ�������Ҫ���ҵ����ַ������뵽���ַ������У���洢���ļ��У�\n
 * ͨ����������ķ�ʽ���뵽���ַ������С�\n
 * ͨ����������ķ�ʽ�����ַ������뵽�ʵ�����ҪԤ�Ƚ����ַ����������Դ�����ı��ļ��С��ļ��ĸ�ʽ���£�\n
 *                ���ַ���         ����\n                  
 *                ���ַ���         ����\n                    
 * ÿ��һ����¼��ǰ��Ϊ���ַ���������Ϊ���ԣ��м��ÿո���Ʊ���ֿ����������ַ�������ʽ��ʾ�����ڼ����ֵ�ʱ\n
 * ��Ҫ��ʱ���͵�����ֵ������Ҫ��Ӧ�ó����ṩ���ַ�����ʽ������ӳ���������ʽ�����Եĺ�����������ʽ������ֵ\n
 * ������2�ı�������ֻ��ռ������ֵ�е�ĳһλ��\n
 */
#ifndef _PTDEF_H
#define _PTDEF_H
/*********************************************************************************
 * Filename	: dictmatch.h
 * Descript	: search for a set of words in a long string. those set of words can 
 * 			: construct a dict; search in a string from beginning to the end, 
 * 			: save every result that can be found in dict.
 * Author	: Paul Yang, zhenhaoji@sohu.com
 * Create	: 2005-05-26
 * Modified	: 2005-05-26
 ********************************************************************************/


//	{{{	macros defined here
#define u_int unsigned int
#define DM_DENTRY_NULL          0xFFFFFFFF
#define DM_DENTRY_FIRST         0xFFFFFFFE
#define DM_SUFENTRY_NULL        0xFFFFFFFF
#define DM_LEMMA_NULL           0xFFFFFFFF
#define DM_COMMON_NULL          0xFFFFFFFF

//match operation type
#define DM_OUT_ALL	0
#define DM_OUT_FMM	1
//	}}}

// {{{ enum type
//charset type
enum dm_charset_t{
    DM_CHARSET_GB18030, 
    DM_CHARSET_UTF8,
    DM_CHARSET_NUM
};
//}}}

//	{{{ data type defined here
//lemma structure for ppack
typedef struct _DM_LEMMA
{
	u_int len;
	u_int prop;
	char * pstr;
	u_int bpos;
}dm_lemma_t;

//lemma structure for dict
typedef struct _DM_INLEMMA
{
	u_int len;
	u_int prop;
	u_int bpos;
}dm_inlemma_t;

typedef struct _DM_ENTRY
{
	u_int value;
	u_int lemma_pos;
	u_int suffix_pos;
}dm_entry_t;

typedef struct _DM_DICT
{
	char*		strbuf;   // buffer for store word  result;
	u_int		sbsize;
	u_int		sbpos; // the next position in word buf

	dm_entry_t* dentry; // the dict entry list
	u_int		desize;
	u_int		depos; // the first unused pos in de list

	u_int* 		seinfo; // the suffix entry list
	u_int 		seisize;
	u_int		seipos;

	dm_lemma_t* lmlist; // the lemma list
	u_int 		lmsize;
	u_int		lmpos; // the first unused pos in lemma list

	u_int 		entrance;
}dm_dict_t;

typedef struct _DM_PACK{
	u_int			maxterm;	// �дʽ��������������������
	dm_lemma_t**	ppseg;
	u_int*			poff;
	u_int			ppseg_cnt;
}dm_pack_t;
//	}}}

//	{{{	module interface declared here

extern int (*dm_prop_str2int_p)(char *);
extern void (*dm_prop_int2str_p)(int, char *);




/**
 *  �������Ҵʵ�
 *  
 *  @param[in]  lemma_num  ���ַ���������
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_dict_create(int lemma_num);

/**
 *  �������Ҵʵ�
 *  
 *  @param[in]  lemma_num  ���ַ���������
 *  @param[in]  charset    �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_dict_create(int lemma_num, dm_charset_t charset);

/**
 *  load�������ļ��洢�Ĵʵ�
 *  
 *  @param[in]  fullname  �洢�Ĵ�·�����ļ���
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_binarydict_load(const char* fullname);

/**
 *  load�������ļ��洢�Ĵʵ�
 *  
 *  @param[in]  fullname  �洢�Ĵ�·�����ļ���
 *  @param[in]  charset   �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_binarydict_load(const char* fullname, dm_charset_t charset);

/**
 *  �����Ʒ�ʽ���ʵ�洢���ļ���
 *  
 *  @param[in]  pdict  �洢�Ĵ�·�����ļ���
 *  @param[in]  fullname  �洢�Ĵ�·�����ļ���
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - 1   �ɹ�
 * - -1  �ļ�����ʧ��
 * - -2  д����ʧ��
 * - -3  ����dictʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_binarydict_save(dm_dict_t * pdict, const char* fullname);

/**
 *  �����Ʒ�ʽ���ʵ�洢���ļ���
 *  
 *  @param[in]  pdict  �洢�Ĵ�·�����ļ���
 *  @param[in]  fullname  �洢�Ĵ�·�����ļ���
 *  @param[in]  charset   �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - 1   �ɹ�
 * - -1  �ļ�����ʧ��
 * - -2  д����ʧ��
 * - -3  ����dictʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_binarydict_save(dm_dict_t * pdict,const char* fullname, dm_charset_t charset);

/**
 *  �������ڴ洢���ַ����Ĵʵ䲢���ļ������ַ������شʵ���
 *  
 *  @param[in]  fullpath   �ʵ��ļ���
 *  @param[in]  lemma_num  ���ַ���������
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_dict_load(const char* fullpath, int lemma_num);

/**
 *  �������ڴ洢���ַ����Ĵʵ䲢���ļ������ַ������شʵ���
 *  
 *  @param[in]  fullpath   �ʵ��ļ���
 *  @param[in]  lemma_num  ���ַ���������
 *  @param[in]  charset    �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_dict_t* dm_dict_load(const char* fullpath, int lemma_num, dm_charset_t charset);

/**
 *  ɾ�����Ҵʵ�
 *  
 *  @param[in]  pdict   �ʵ�ָ��
 *  @param[out] ��
 *  @return ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
void dm_dict_del(dm_dict_t* pdict);

/**
 *  ɾ�����Ҵʵ�
 *  
 *  @param[in]  pdict   �ʵ�ָ��
 *  @param[in]  charset �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
void dm_dict_del(dm_dict_t* pdict, dm_charset_t charset);

/**
 *  �������ҽ���洢�ṹ
 *  
 *  @param[in]  max_wnum   ���ɴ洢�Ľ����
 *  @param[out] ��
 *  @return   ���ҽ���洢�ṹ
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_pack_t* dm_pack_create(int max_wnum);

/**
 *  �������ҽ���洢�ṹ
 *  
 *  @param[in]  max_wnum   ���ɴ洢�Ľ����
 *  @param[in]  charset    �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return   ���ҽ���洢�ṹ
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
dm_pack_t* dm_pack_create(int max_wnum, dm_charset_t charset);

/**
 *  ɾ�����ҽ���洢�ṹ
 *  
 *  @param[in]  ppack   ���ҽ���洢�ṹ
 *  @param[out] ��
 *  @return ��
 *  @note Ϊ����Ӧ32λ�ʵ���64λ�����������أ����ʵ��ڲ������Ľṹ���дʽṹ�������ˣ���ǰ��һ���ṹ�����ֱ���dm_inlemma_t��dm_lemma_t������ע��dm_pack_t* dm_pack_create(int max_wnum);��max_wnum�����ĺܴ�Ļ����ڴ�����������ӡ�
 */
void dm_pack_del(dm_pack_t* ppack);

/**
 *  ɾ�����ҽ���洢�ṹ
 *  
 *  @param[in]  ppack   ���ҽ���洢�ṹ
 *  @param[in]  charset �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return ��
 *  @note Ϊ����Ӧ32λ�ʵ���64λ�����������أ����ʵ��ڲ������Ľṹ���дʽṹ�������ˣ���ǰ��һ���ṹ�����ֱ���dm_inlemma_t��dm_lemma_t������ע��dm_pack_t* dm_pack_create(int max_wnum);��max_wnum�����ĺܴ�Ļ����ڴ�����������ӡ�
 */
void dm_pack_del(dm_pack_t* ppack, dm_charset_t charset);

/**
 *  ��ʵ��м���һ�����ַ���
 *  
 *  @param[in]  pdict   ���ַ������Ҵʵ�
 *  @param[in]  plm     ָ�����ַ����ṹ��ָ��
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �ɹ�
 * - 0     ���ַ����Ѵ���
 * - -1    ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_add_lemma(dm_dict_t* pdict, dm_lemma_t* plm);

/**
 *  ��ʵ��м���һ�����ַ���
 *  
 *  @param[in]  pdict   ���ַ������Ҵʵ�
 *  @param[in]  plm     ָ�����ַ����ṹ��ָ��
 *  @param[in]  charset �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �ɹ�
 * - 0     ���ַ����Ѵ���
 * - -1    ʧ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_add_lemma(dm_dict_t* pdict, dm_lemma_t* plm, dm_charset_t charset);

/**
 *  �����ַ������е�ƥ���ַ���
 *  
 *  @param[in]  pdict     ���ַ������Ҵʵ�
 *  @param[in]  ppack     �洢���ҽ���Ļ�����
 *  @param[in]  inbuf     �����ҵ��ַ���
 *  @param[in]  inlen     �ַ����ĳ���
 *  @param[in]  opertype  Ĭ�����ò���opertypeΪDM_OUT_FMM��Ҳ���Ǵ�����������ƥ�䣬��Ӧ��DM_OUT_ALL�Ǵ����ȫƥ��
 *  @param[out] ppack     ���в��ҽ��
 *  @return   ��������ֵ
 * - 0     �ɹ�
 * - -1    ʧ��
 *  @note ������سɹ���ͨ��ppack->ppseg_cnt�жϲ��ҵ��Ĵ�����������Ϊ0��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_search(dm_dict_t* pdict, dm_pack_t* ppack, const char* inbuf, int inlen, int opertype = DM_OUT_FMM);

/**
 *  �����ַ������е�ƥ���ַ���
 *  
 *  @param[in]  pdict     ���ַ������Ҵʵ�
 *  @param[in]  ppack     �洢���ҽ���Ļ�����
 *  @param[in]  inbuf     �����ҵ��ַ���
 *  @param[in]  inlen     �ַ����ĳ���
 *  @param[in]  opertype  ����opertype��ΪDM_OUT_FMM���Ǵ�����������ƥ�䣬��Ӧ��DM_OUT_ALL���Ǵ����ȫƥ��
 *  @param[in]  charset   �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ppack     ���в��ҽ��
 *  @return   ��������ֵ
 * - 0     �ɹ�
 * - -1    ʧ��
 *  @note ������سɹ���ͨ��ppack->ppseg_cnt�жϲ��ҵ��Ĵ�����������Ϊ0��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_search(dm_dict_t* pdict, dm_pack_t* ppack, const char* inbuf, int inlen, int opertype, dm_charset_t charset);

//notice : the function matches words in sentence by "opertype" match method,
//the return value is the OR(|) of all the property of the matched words,
//the type num user defined should less than 32
//1 type should occupy 1 bit of an int;
/**
 *  the function matches words in sentence by "opertype" match method
 *  
 *  @param[in]  pdict     ���ַ������Ҵʵ�
 *  @param[in]  inbuf     �����ҵ��ַ���
 *  @param[in]  inlen     �ַ����ĳ���
 *  @param[in]  opertype  Ĭ�����ò���opertypeΪDM_OUT_FMM��Ҳ���Ǵ�����������ƥ�䣬��Ӧ��DM_OUT_ALL�Ǵ����ȫƥ��
 *  @return   ����
 *  @note ���Ǹ��½ӿڣ��䷵�ؽ�������������inbuf��������а����Ĵ���������������ͣ�Ĭ�ϲ���opertype��Ϊ�������ƥ�䡣��Ҫע����Ǵʵ��еĴ������ֻ����32�����ͣ�ÿ�����͵�ֵӦ��ռ��u_intֵ��1λ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
u_int dm_search_prop(dm_dict_t* pdict,const char* inbuf, int inlen, int opertype = DM_OUT_FMM);

//notice : the function matches words in sentence by "opertype" match method,
//the return value is the OR(|) of all the property of the matched words,
//the type num user defined should less than 32
//1 type should occupy 1 bit of an int;
/**
 *  the function matches words in sentence by "opertype" match method
 *  
 *  @param[in]  pdict     ���ַ������Ҵʵ�
 *  @param[in]  inbuf     �����ҵ��ַ���
 *  @param[in]  inlen     �ַ����ĳ���
 *  @param[in]  opertype  ����opertype��ΪDM_OUT_FMM���Ǵ�����������ƥ�䣬��Ӧ��DM_OUT_ALL���Ǵ����ȫƥ��
 *  @param[in]  charset   �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @return   ����
 *  @note ���Ǹ��½ӿڣ��䷵�ؽ�������������inbuf��������а����Ĵ���������������ͣ�Ĭ�ϲ���opertype��Ϊ�������ƥ�䡣��Ҫע����Ǵʵ��еĴ������ֻ����32�����ͣ�ÿ�����͵�ֵӦ��ռ��u_intֵ��1λ��
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
u_int dm_search_prop(dm_dict_t* pdict,const char* inbuf, int inlen, int opertype, dm_charset_t charset);

/**
 *  �鿴�ַ������Ƿ����ض����Ե��Ӵ�
 *  
 *  @param[in]  pdict    ���ַ������Ҵʵ�
 *  @param[in]  type     �����ҵ�����
 *  @param[in]  inbuf    �����ҵ��ַ���
 *  @param[in]  inlen    �ַ����ĳ���
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �����ض����͵��Ӵ������type�Ƕ������ֵ��'|'��һ�𣩣�����һ�����Է�������������1
 * - 0     �������ض����͵��Ӵ�
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_has_word(dm_dict_t* pdict, int type, const char* inbuf, int inlen, int opertype = DM_OUT_FMM);

/**
 *  �鿴�ַ������Ƿ����ض����Ե��Ӵ�
 *  
 *  @param[in]  pdict    ���ַ������Ҵʵ�
 *  @param[in]  type     �����ҵ�����
 *  @param[in]  inbuf    �����ҵ��ַ���
 *  @param[in]  inlen    �ַ����ĳ���
 *  @param[in]  charset  �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �����ض����͵��Ӵ������type�Ƕ������ֵ��'|'��һ�𣩣�����һ�����Է�������������1
 * - 0     �������ض����͵��Ӵ�
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dm_has_word(dm_dict_t* pdict, int type, const char* inbuf, int inlen, int opertype, dm_charset_t charset);

/**
 *  �鿴���ҽ�����Ƿ����ض����͵��Ӵ���������ĳһ�ض�����ֵ���Ӵ�
 *  
 *  @param[in]  ppack    ָ����ҽ��
 *  @param[in]  type     �����ҵ����ͣ��������ҵ��Ӵ�������ֵ
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �����ض����͵��Ӵ������type�Ƕ������ֵ��'|'��һ�𣩣�����һ�����Է�������������1
 * - 0     �������ض����͵��Ӵ�
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dmpack_has_type(dm_pack_t* ppack, int type);

/**
 *  �鿴���ҽ�����Ƿ����ض����͵��Ӵ���������ĳһ�ض�����ֵ���Ӵ�
 *  
 *  @param[in]  ppack    ָ����ҽ��
 *  @param[in]  type     �����ҵ����ͣ��������ҵ��Ӵ�������ֵ
 *  @param[in]  charset  �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return   ��������ֵ
 * - 1     �����ض����͵��Ӵ������type�Ƕ������ֵ��'|'��һ�𣩣�����һ�����Է�������������1
 * - 0     �������ض����͵��Ӵ�
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
int dmpack_has_type(dm_pack_t* ppack, int type, dm_charset_t charset);

/**
 *  �ڴʵ��в����Ƿ���term��Ӧ������
 *  
 *  @param[in]  pdict ���ַ������Ҵʵ�
 *  @param[in]  term  ���ҵ��ַ���
 *  @param[in]  len   �ַ����ĳ��� 
 *  @param[out] ��
 *  @return   ��list�е�λ��
 * - >0                �ҵ�������λ��
 * - DM_LEMMA_NULL     δ�ҵ�
 *  @note �ڲ�ʹ��,�ӿڲ����ע 
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
u_int dm_seek_lemma(dm_dict_t * pdict, const char* term, int len);//for test;

/**
 *  �ڴʵ��в����Ƿ���term��Ӧ������
 *  
 *  @param[in]  pdict ���ַ������Ҵʵ�
 *  @param[in]  term  ���ҵ��ַ���
 *  @param[in]  len   �ַ����ĳ��� 
 *  @param[in]  charset  �ַ�����, DM_CHARSET_GB18030/DM_CHARSET_UTF8
 *  @param[out] ��
 *  @return   ��list�е�λ��
 * - >0                �ҵ�������λ��
 * - DM_LEMMA_NULL     δ�ҵ�
 *  @note �ڲ�ʹ��,�ӿڲ����ע 
 *  @see ::dm_dict_create  ::dm_binarydict_load  ::dm_binarydict_save  ::dm_dict_load  ::dm_dict_del  ::dm_pack_create  ::dm_pack_del  ::dm_add_lemma  ::dm_search  ::dm_has_word  ::dmpack_has_type  ::dm_seek_lemma
 */
u_int dm_seek_lemma(dm_dict_t * pdict, const char* term, int len, dm_charset_t charset);//for test;

//	}}}

#endif

