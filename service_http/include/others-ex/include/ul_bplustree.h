/**
 * @file
 * @brief �ض����ַ�������
 */


/**
 * @brief ��һ���ַ����в����ض������ַ��������Ƚ�������Ҫ���ҵ����ַ������뵽���ַ������У���洢���ļ��У�\n
 * ͨ����������ķ�ʽ���뵽���ַ������С�
 */
#ifndef __BPLUSTREE_H__
#define __BPLUSTREE_H__

#include "stdlib.h"
#include "stdio.h"
#include "ul_log.h"
#include "string.h"
#include "ul_ccode.h"
//#include "asfilter.h"

#define LEAF_BIT 2
#define VALID_BIT 1
#define MAX_ITEM_NUM 100
#define MAX_LENGTH 256
#define IS_LEAF(node) (node->status & LEAF_BIT)
#define IS_VALID(node) (node->status & VALID_BIT)

#define MAX_SNAME_LEN 256

typedef struct _TreeNode TreeNode;

struct _TreeNode
{
   TreeNode **child;		//children node
   unsigned char key;		//node value 
   unsigned char status;	//0bit: whether is a valid word
							//1bit: whether is a leaf node
   unsigned char modkey;	//value to distinguish leaf values         
};
          

typedef struct _SubString 
{
	int begin; //the offset of string start in the original input word
	int end;   //the offset of string end in the original input word
	char name[MAX_SNAME_LEN];
} SubString;




/**
 *  ���ô��ݵ�key����һ��Ҷ�ӽڵ�
 *  
 *  @param[in]  key   keyֵ
 *  @param[out] ��
 *  @return ��Žڵ�ĵ�ַ
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note �ڲ�����,�ӿڲ��ع�ע
 */
extern TreeNode *InitTreeNode(unsigned char key);



/**
 *  ����key���ɵĽڵ���Ϊ��ǰ�ڵ���ӽڵ���뵽����
 *  
 *  @param[in]  node   ��ǰ�ڵ�
 *  @param[in]  key    keyֵ
 *  @param[out] ��
 *  @return �����һkeyֵ�ĵ�ַ
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note �ڲ�����,�ӿڲ��ع�ע
 */
extern TreeNode *InsertToChild(TreeNode* node, unsigned char key);

/**
 *  �ͷŽڵ�
 *  
 *  @param[in]  node  �ڵ��ָ��
 *  @param[out] ��
 *  @return ��
 *  @note �ڲ�����,�ӿڲ��ع�ע
 */
extern void FreeNode(TreeNode *node);
/**
 *  �����ֵ���ƥ���������ַ���
 *  
 *  @param[in]  root   ���ĸ��ڵ�
 *  @param[in]  str    ���ҵ��ַ���
 *  @param[out] ��
 *  @return ��󳤶�
 * - >0   �ɹ�
 * - 0    ʧ��
 *  @note �ڲ�����,�ӿڲ��ع�ע
 */
extern int SearchString(TreeNode *root, char *str);

/**
 *  �������ַ�����
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return ָ�����ַ�������ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
extern TreeNode *InitTree();




/**
 *  ���ַ������뵽tree��
 *  
 *  @param[in]  root   ���ĸ��ڵ�
 *  @param[in]  str    ������ַ���
 *  @param[out] ��
 *  @return �������
 * - 0   �ɹ�
 * - -1  ʧ��
 */
extern int InsertString(TreeNode *root, char *str);



/**
 *  �����ַ����������е����ַ����������һ�����Ի�������
 *  
 *  @param[in]  root   ��״�ֵ�ĸ�
 *  @param[in]  query  �����ҵ��ַ���
 *  @param[in]  len    �ַ�������
 *  @param[in]  result �ڴ洢���ҵ������ַ����Ļ�����
 *  @param[in]  reslen ����buf�ĳ���
 *  @param[out] result �������в��ҽ��,ÿ�����ַ����ԡ�0����β�������洢��result��
 *  @return ���ҵ�item�ĸ���
 *  @note query���ܻᱻ�޸ģ����Բ���ʹ�ó���
 */
extern int seek_string(TreeNode *root, char* query, int len, char* result, int reslen);




/**
 *  �����ַ����������е����ַ����������һ���ṹ���Ļ�������
 *  
 *  @param[in]  root    ��״�ֵ�ĸ�
 *  @param[in]  query   �����ҵ��ַ���
 *  @param[in]  len     �ַ�������
 *  @param[in]  tgbuf   ���ڴ洢���ҵ������ַ����Ļ�����
 *  @param[in]  tgbsize ����buf�ĳ���
 *  @param[out] tgbuf   �������в��ҽ��,ÿ�����ַ����ԡ�0����β�������洢��result��
 *  @return ���в��ҵ������ַ���
 *  @note query���ܻᱻ�޸ģ����Բ���ʹ�ó���
 */
extern int seek_p(TreeNode *root, char* query, int len, SubString* tgbuf, int tgbsize);





/**
 *  �������ַ����������ļ��е����ַ������뵽����
 *  
 *  @param[in]  filepath    �ļ�����·��
 *  @param[in]  filename    �ļ���
 *  @param[out] ��
 *  @return ָ�����ַ�������ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 *  @note �ļ���ʽΪÿ��һ�����ַ���
 */
extern TreeNode *CreateTreeFromFile(char* filepath, char* filename);



/**
 *  �ͷ����ַ�����
 *  
 *  @param[in]  root   ָ�����ĸ���ָ��
 *  @param[out] ��
 *  @return ��
 */
extern void FreeTree(TreeNode *root);




#endif

