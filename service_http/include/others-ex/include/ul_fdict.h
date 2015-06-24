/**
 * @file
 * @brief ��һ��256�������������ʵ�֣����ַ�����һ������ֵ
 */
#ifndef __UL_FDICT_H__
#define __UL_FDICT_H__

#define FDICT_SIZE 65536
#define DF_INVALID_DATA -2147483647

typedef struct _fnode_t {
	int data;
	unsigned short index[256];
} fnode_t;

typedef struct _fdict_t {
	int size;
	int num;
	fnode_t *nodes;
} fdict_t;



/**
 *  ����һ��dict
 *  
 *  @param[in]  �� 
 *  @param[out] ��
 *  @return �ʵ��ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
extern fdict_t *df_create();

/**
 *  ���ֵ������һ��str - data ��
 *  
 *  @param[in]  pd      �ֵ�ָ��
 *  @param[in]  in      �ַ���
 *  @param[in]  data    �ַ�����Ӧ��data
 *  @param[out] ��
 *  @return dataֵ
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
extern int df_add(fdict_t *pd, char *in, int data);


/**
 *  �����ַ������ֵ��в��Ҷ�Ӧ��data
 *  
 *  @param[in]  pd      �ֵ�ָ��
 *  @param[in]  in      �ַ���
 *  @param[out] ��
 *  @return dataֵ
 * - dataֵ          ���ҳɹ�
 * - DF_INVALID_DATA ����ʧ��
 */
extern int df_seek(fdict_t *pd, char *in);


/**
 *  �����ֵ�,����size����������Ҫ�Ľڵ��ڴ�
 *  
 *  @param[in]  pd      �ֵ�ָ��
 *  @param[out] ��
 *  @return ��������ֵ
 * - 0    �ɹ�
 * - -1   ʧ��
 */
extern int df_adjust(fdict_t *pd);


/**
 *  ɾ���ֵ�
 *  
 *  @param[in]  pd   �ֵ�ָ��
 *  @param[out] ��
 *  @return 0
 */
extern int df_delete(fdict_t *pd);


/**
 *  copy�ֵ�
 *  
 *  @param[in]  pd   �ֵ�ָ��
 *  @param[out] ��
 *  @return ���ֵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
extern fdict_t *df_copy(fdict_t *pd);

#endif
