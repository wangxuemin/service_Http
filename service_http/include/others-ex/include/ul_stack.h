/**
 * @file
 * @brief ջ��LIFO�����ݽṹ��ͨ������һ�麯����ʹ���߿��Խ���������ջ����ջ��ѹ��͵�����ͬ��������Ԫ�أ��ж�ջ�ĵ�ǰ״̬�ȡ�
 */

#ifndef __UL_STACK__
#define __UL_STACK__


typedef enum
{
    T_CHAR,
    T_SHORT,
    T_INT,
    T_LONG,
    T_VOID
}StackItemType;

typedef struct
{
	int size;
	int top;
	void *stack_buff;
}Stack;

/**
 *  ��ʼ��ջ
 *  
 *  @param[in]  size  ջ�Ĵ�С
 *  @param[out] ��
 *  @return ջָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
Stack *ul_stack_init(int size);

/**
 *  �ͷ�ջ
 *  
 *  @param[in]  stack  ջָ��
 *  @param[out] ��
 *  @return ��
 */
void ul_stack_destroy(Stack *stack);



/**
 *  pushһ���ַ�
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  �ַ�
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_stack_push_char(Stack *stack, char value);


/**
 *  popһ���ַ�
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  �ַ���ŵ�ָ��
 *  @param[out] value  �ַ�ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_popup_char(Stack *stack, char *value);


/**
 *  ��ջ������ȡһ��char��ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  �ַ���ŵ�ָ��
 *  @param[out] value  �ַ�ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_char(Stack *stack, char *value);


/**
 *  pushһ��short
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  shortֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_stack_push_short(Stack *stack, short value);


/**
 *  popһ��short
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  short��ŵ�ָ��
 *  @param[out] value  shortֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_popup_short(Stack *stack, short *value);


/**
 *  ��ջ������ȡһ��short��ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  short��ŵ�ָ��
 *  @param[out] value  shortֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_short(Stack *stack, short *value);


/**
 *  pushһ��int
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  intֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_stack_push_int(Stack *stack, int value);


/**
 *  popһ��int
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  int��ŵ�ָ��
 *  @param[out] value  intֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_popup_int(Stack *stack, int *value);

/**
 *  ��ջ������ȡһ��int��ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  int��ŵ�ָ��
 *  @param[out] value  intֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_int(Stack *stack, int *value);



/**
 *  pushһ��long
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  longֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_stack_push_long(Stack *stack, long value);


/**
 *  popһ��long
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  long��ŵ�ָ��
 *  @param[out] value  longֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_popup_long(Stack *stack, long *value);


/**
 *  ��ջ������ȡһ��long��ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  long��ŵ�ָ��
 *  @param[out] value  longֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_long(Stack *stack, long *value);


/**
 *  pushһ��void ָ��
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  ָ��
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_stack_push_void(Stack *stack, void *value);


/**
 *  popһ��void *
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  ���ָ���ָ��
 *  @param[out] value  ָ��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_popup_void(Stack *stack, void **value);


/**
 *  ��ջ������ȡһ��ָ�룬ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  value  ���ָ���ָ��
 *  @param[out] value  ָ��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_void(Stack *stack, void **value);



/**
 *  ȡջ��Ԫ�ص����ͣ�ջ���������仯
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  type   ������͵�ָ��
 *  @param[out] type   �������
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_stack_peek_type(Stack *stack, StackItemType *type);


/**
 *  ��ȡջ��С
 *  
 *  @param[in]  stack  ջָ��
 *  @param[out] ��
 *  @return ��С
 */
int ul_stack_get_size(Stack *stack);


/**
 *  ��ȡջʣ��ռ�Ĵ�С
 *  
 *  @param[in]  stack  ջָ��
 *  @param[out] ��
 *  @return �ռ��С
 */
int ul_stack_get_space(Stack *stack);




/**
 *  �ж�ջ�Ƿ�Ϊ��
 *  
 *  @param[in]  stack  ջָ��
 *  @param[out] ��
 *  @return �Ƿ�Ϊ��
 * - true  ��
 * - false ����
 */
bool ul_stack_is_empty(Stack *stack);


/**
 *  �ж�ջ�Ƿ�����
 *  
 *  @param[in]  stack  ջָ��
 *  @param[out] ��
 *  @return �Ƿ�Ϊ��
 * - true  ��
 * - false ����
 */
bool ul_stack_is_full(Stack *stack);

#endif
