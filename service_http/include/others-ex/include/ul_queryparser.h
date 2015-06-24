/**
 * @file
 * @brief ����������
 */

/**
 * @brief ���û�����ļ��������й淶�������������ɱ�׼��ʽ��Ӧ�ý�һ��ʹ�á�
 */

#ifndef __QUERYPARSER_H__
#define __QUERYPARSER_H__

#define QP_MAX_STRLEN 256
#define QP_MAX_QUERYLEN 76

#define SYNTAX_QUERY_END  '\0'
#define SYNTAX_WORD       ' '
#define SYNTAX_ADD        '+'
#define SYNTAX_MINUS      '-'
#define SYNTAX_OR         '|'
#define SYNTAX_ADJUST     'A'
#define SYNTAX_ESCAPE     'E'
#define SYNTAX_URL        'W'
#define SYNTAX_INURL      'U'
#define SYNTAX_TITLE      'T'
#define SYNTAX_SITE       'S'
#define SYNTAX_ANCHOR     'L'
#define SYNTAX_CONT       'C'
#define SYNTAX_COLON_END  '#'
#define SYNTAX_L_BRACKET  '('
#define SYNTAX_R_BRACKET  ')'
#define SYNTAX_L_BOOKMARK '<'
#define SYNTAX_R_BOOKMARK '>'
#define SYNTAX_QUOTATION  '\"'

#define SYMBOL_L_BOOKMARK "\0\0��"
#define SYMBOL_R_BOOKMARK "\0\0��"

#define SYN_SUG_QUOTATION   1
#define SYN_SUG_BOOKMARK    2

#define MAX_SEG_WORDS	  100
#define MAX_SEG_WORD_LEN	8

#define FILE_TYPE_NONE  -1
#define FILE_TYPE_ALL	0
#define	FILE_TYPE_DOC	1
#define	FILE_TYPE_PDF	2
#define	FILE_TYPE_PPT	3
#define	FILE_TYPE_XLS	4
#define	FILE_TYPE_WPS	5
#define	FILE_TYPE_RTF	6

typedef struct MutiDoc_fType
{
	char len;
	char val;
	char *name;
}mType_t;


/**
 *  ֧�ִ�˫�ֽڵ�trim
 *  
 *  @param[in]  inStr  �����ַ���
 *  @param[in]  outStr trim��������ַ�����ŵ�buf
 *  @param[out] outStr trim��������ַ���
 *  @return ����ַ����ĳ���
 */
int trimString(const char *inStr, char *outStr);


/**
 *  ȥ��seg��ǵ��ַ�,����ÿո����
 *  
 *  @param[in]  inStr  �����ַ���
 *  @param[in]  outStr ȥ��seg���ַ�����ŵ�buf
 *  @param[out] outStr ȥ��seg���ַ���
 *  @return 0
 */
int removeSeg(char *inStr, char *outStr);	


/**
 *  ��ʼ�������������������߳̿�ʼ������һ��
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return 1
 */
int queryInit();


/**
 *  �Լ��������н���
 *  
 *  @param[in]  inStr              �������ļ�����
 *  @param[in]  termStr            �洢���������ʵĻ��������������ĳ��������QP_MAX_STRLEN
 *  @param[in]  opStr              �洢���������������еĻ��������������ĳ��������QP_MAX_STRLEN
 *  @param[in]  opt                ����ѡ���λ��ʾ��0x01: ���ż���; 0x02:��Ҫճ��
 *  @param[in]  suggest            �洢����Ļ�������������256���ֽڣ�����Ϊ��
 *  @param[in]  site_cluster_flag  �洢վ�ھ����־�Ļ�����������Ϊ��
 *  @param[in]  haveSyntax         �洢�﷨��־�Ļ�����������Ϊ��
 *  @param[in]  fType              ָ���ַ���ָ�룬���ڴ洢�����ĵ����ͣ�����Ϊ��
 *  @param[out] termStr            ��Ž������ĵ���
 *  @param[out] opStr              ��Ž������Ĳ���������   
 *  @param[out] suggest            ��Ž�����Ϣ��ǰ�沿��Ϊ���ʣ���'\0'������suggest[255]�����ʾ����:SYN_SUG_BOOKMARK��SYN_SUG_QUOTATION
 *  @param[out] site_cluster_flag  ����վ�ھ����־���������Ҫվ����ۣ�������������site�﷨�����򷵻�0�����򽫲��ı�ʱ���������	
 *  @param[out] haveSyntax         ����﷨��־��0�����﷨��������1�����﷨������
 *  @param[out] fType              ��ż����ĵ�������
 *  @return ��������ֵ
 * - 0  �ɹ�
 * - <0 ʧ��
 *  @note fType����:
 * - FILE_TYPE_ALL
 * - FILE_TYPE_DOC
 * - FILE_TYPE_PDF
 * - FILE_TYPE_PPT
 * - FILE_TYPE_XLS
 * - FILE_TYPE_WPS
 * - FILE_TYPE_RTF
 *  @note termStr��opStr��˵��:
 * opStr��termStr�ĳ���һ�£�����ÿ���ֽڶ��Ƕ�Ӧ��ϵ, ����:\n
 *    termStr: "hello world"\n
 *    opStr:   "     |     "\n
 *    opStr����5��SYNTAX_WORD��1��SYNTAX_OR��5��SYNTAX_WORD��\n
 *             1��SYNTAX_QUERY_END\n
 * ��: termStr�ж�ӦopStr�е�SYNTAX_WORD�Ĳ���Ϊ���ʣ���\n
 * termStr�ж�ӦopStr����Ĳ������Ĳ���û�����塣\n
 * opStr�пɴ�ŵĲ��������£�\n
 *      SYNTAX_QUERY_END        '\0'\n
 *      SYNTAX_WORD             ' '\n
 *      SYNTAX_ADD              '+'\n
 *      SYNTAX_MINUS            '-'\n
 *      SYNTAX_OR               '|'\n
 *      SYNTAX_ADJUST           'A'\n
 *      SYNTAX_ESCAPE           'E'\n
 *      SYNTAX_URL              'W'\n
 *      SYNTAX_INURL            'U'\n
 *      SYNTAX_TITLE            'T'\n
 *      SYNTAX_SITE             'S'\n
 *      SYNTAX_ANCHOR           'L'\n
 *      SYNTAX_CONT             'C'\n
 *      SYNTAX_COLON_END        '#'\n
 *      SYNTAX_L_BRACKET        '('\n
 *      SYNTAX_R_BRACKET        ')'\n
 *      SYNTAX_L_BOOKMARK       '<'\n
 *      SYNTAX_R_BOOKMARK       '>'\n
 *      SYNTAX_QUOTATION        '\"'
 */
int queryParser(char *inStr, char *termStr, char *opStr, int opt, char *suggest, 
		int *site_cluster_flag, int *haveSyntax,char *fType);
		
		
		
/**
 *  �������������������߳��˳�ǰ����
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return 1
 */
int queryFinish();

#endif
