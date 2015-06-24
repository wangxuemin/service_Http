/**
 * @file
 * @brief ������FIFO�����ݽṹ��ͨ������һ�麯����ʹ���߿��Խ��������ٶ��У�������м���ʹӶ�����ȡ����ͬ��������Ԫ�أ��ж϶��еĵ�ǰ״̬�ȡ����̼��������߳�ʹ�������
 */

#ifndef __UL_QUEUE__
#define __UL_QUEUE__


typedef enum
{
    T_CHAR,
    T_SHORT,
    T_INT,
    T_LONG,
    T_VOID
}QueueItemType;

typedef struct
{
	int size;
	int head;
	int tail;
	void *queue_buff;
}Queue;



/**
 *  ��ʼ������
 *  
 *  @param[in]  size  ���д�С
 *  @param[out] ��
 *  @return ����ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
Queue *ul_queue_init(int size);

/**
 *  ���ٶ���
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[out] ��
 *  @return ��
 */
void ul_queue_destroy(Queue *queue);

/**
 *  �ַ������
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[in]  value  �ַ�ֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_queue_in_char(Queue *queue, char value);


/**
 *  �ַ��ͳ�����
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  �ַ��ʹ�ŵ�ָ��
 *  @param[out] value  �ַ�ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ����п�
 */
int ul_queue_out_char(Queue *queue, char *value);



/**
 *  �Ӷ�����ȡһ���ַ����������������仯
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  �ַ���ŵ�ָ��
 *  @param[out] value  �ַ�ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_char(Queue *queue, char *value);


/**
 *  short�������
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[in]  value  short��ֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_queue_in_short(Queue *queue, short value);

/**
 *  short�ͳ�����
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  short�ʹ�ŵ�ָ��
 *  @param[out] value  short��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ����п�
 */
int ul_queue_out_short(Queue *queue, short *value);


/**
 *  �Ӷ�����ȡһ��short�ͣ��������������仯
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  short�ʹ�ŵ�ָ��
 *  @param[out] value  short��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_short(Queue *queue, short *value);


/**
 *  int�������
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[in]  value  int��ֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_queue_in_int(Queue *queue, int value);


/**
 *  int�ͳ�����
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  int�ʹ�ŵ�ָ��
 *  @param[out] value  int��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ����п�
 */
int ul_queue_out_int(Queue *queue, int *value);


/**
 *  �Ӷ�����ȡһ��int�ͣ��������������仯
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  int�ʹ�ŵ�ָ��
 *  @param[out] value  int��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_int(Queue *queue, int *value);

/**
 *  long�������
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[in]  value  long��ֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_queue_in_long(Queue *queue, long value);


/**
 *  long�ͳ�����
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  long�ʹ�ŵ�ָ��
 *  @param[out] value  long��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ����п�
 */
int ul_queue_out_long(Queue *queue, long *value);


/**
 *  �Ӷ�����ȡһ��long�ͣ��������������仯
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  long�ʹ�ŵ�ָ��
 *  @param[out] value  long��ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_long(Queue *queue, long *value);


/**
 *  void *�����
 *  
 *  @param[in]  queue  ����ָ��
 *  @param[in]  value  ָ��ֵ
 *  @param[out] ��
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ��ռ���
 */
int ul_queue_in_void(Queue *queue, void *value);


/**
 *  void *�ͳ�����
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  ָ���ʹ�ŵ�ָ��
 *  @param[out] value  ָ����ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ����п�
 */
int ul_queue_out_void(Queue *queue, void **value);


/**
 *  �Ӷ�����ȡһ��ָ���ͣ��������������仯
 *  
 *  @param[in]  stack  ����ָ��
 *  @param[in]  value  ָ���ʹ�ŵ�ָ��
 *  @param[out] value  ָ����ֵ
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_void(Queue *queue, void **value);


/**
 *  ȡ����ͷԪ�ص����ͣ����������״̬����
 *  
 *  @param[in]  stack  ջָ��
 *  @param[in]  type   ������͵�ָ��
 *  @param[out] type   �������
 *  @return ��������ֵ
 * - 1 �ɹ�
 * - 0 ʧ�ܣ�ջ��
 */
int ul_queue_peek_type(Queue *queue, QueueItemType *type);



/**
 *  ��ȡ���д�С
 *  
 *  @param[in]  stack  ���нṹָ��
 *  @param[out] ��
 *  @return ��С
 */
int ul_queue_get_size(Queue *queue);



/**
 *  ��ȡ����ʣ��ռ�Ĵ�С
 *  
 *  @param[in]  stack  ���нṹָ��
 *  @param[out] ��
 *  @return �ռ��С
 */
int ul_queue_get_space(Queue *queue);


/**
 *  �ж϶����Ƿ�Ϊ��
 *  
 *  @param[in]  stack  ���нṹָ��
 *  @param[out] ��
 *  @return �Ƿ�Ϊ��
 * - true  ��
 * - false ����
 */
bool ul_queue_is_empty(Queue *queue);


/**
 *  �ж϶����Ƿ�����
 *  
 *  @param[in]  stack  ���нṹָ��
 *  @param[out] ��
 *  @return �Ƿ�Ϊ��
 * - true  ��
 * - false ����
 */
bool ul_queue_is_full(Queue *queue);

#endif
