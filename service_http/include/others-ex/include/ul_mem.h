/**
 * @file
 * @brief �ṩ�̼߳����ڴ�����ܵ�memory�����壬��debugģʽ�¿���Ч����ڴ�й¶����releaseģʽ��Ϊϵͳ���õķ�װ
 */
#ifndef __UL_MEM__
#define __UL_MEM__

#include <stdio.h>

#ifdef __MEM_DEBUG__
#define ul_malloc(size) ul_debug_malloc(size, __FILE__, __LINE__)
#define ul_calloc(num, size) ul_debug_calloc(num, size, __FILE__, __LINE__)
#define ul_realloc(ptr, size) ul_debug_realloc(ptr, size, __FILE__, __LINE__)
#define ul_free(mem_ptr) ul_debug_free(mem_ptr)
#define ul_dump_mem_info(buff, buff_len) ul_debug_dump_mem_info(buff, buff_len)
#else
#define ul_malloc(size) ul_release_malloc(size)
#define ul_calloc(num, size) ul_release_calloc(num, size)
#define ul_realloc(ptr, size) ul_release_realloc(ptr, size)
#define ul_free(mem_ptr) ul_release_free(mem_ptr)
#define ul_dump_mem_info(buff, buff_len)	0
#endif


/**
 *  releaseģʽ�µ�malloc����malloc�÷���ͬ
 *  
 *  @param[in]  size  ���ٿռ��С
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_release_malloc(size_t size);

/**
 *  releaseģʽ�µ�calloc����calloc�÷���ͬ
 *  
 *  @param[in]  num   ���������ռ�Ŀ���
 *  @param[in]  size  ÿ���С
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_release_calloc(size_t num, size_t size);


/**
 *  releaseģʽ�µ�realloc����realloc�÷���ͬ
 *  
 *  @param[in]  ptr   ԭ��������
 *  @param[in]  size  ���·���Ĵ�С
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_release_realloc(void *ptr, size_t size);

/**
 *  releaseģʽ�µ�free����free�÷���ͬ
 *  
 *  @param[in]  ptr   ԭ��������ָ��
 *  @param[out] ��
 *  @return ��
 */
void ul_release_free(void *ptr);


/**
 *  debugģʽ�µ�malloc������ʱ���ڴ洮�����������ڴ��ع���
 *  
 *  @param[in]  size        ���ٿռ��С
 *  @param[in]  alloc_file  ��ǰ�ļ���
 *  @param[in]  alloc_line  ��ǰ��
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_debug_malloc(size_t size, char *alloc_file, int alloc_line);

/**
 *  debugģʽ�µ�calloc������ʱ���ڴ洮�����������ڴ��ع���
 *  
 *  @param[in]  num   ���������ռ�Ŀ���
 *  @param[in]  size  ÿ���С
 *  @param[in]  alloc_file  ��ǰ�ļ���
 *  @param[in]  alloc_line  ��ǰ��
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_debug_calloc(size_t num, size_t size, char *alloc_file, int alloc_line);


/**
 *  debugģʽ�µ�realloc������ʱ���ڴ洮�����������ڴ��ع���
 *  
 *  @param[in]  ptr   ԭ��������
 *  @param[in]  size  ���·���Ĵ�С
 *  @param[in]  alloc_file  ��ǰ�ļ���
 *  @param[in]  alloc_line  ��ǰ��
 *  @param[out] ��
 *  @return ���ٵ�ָ��
 * - ��NULL   �ɹ�
 * - NULL     ʧ��
 */
void *ul_debug_realloc(void *ptr, size_t size, char *alloc_file, int alloc_line);


/**
 *  debugģʽ�µ�free���ͷ���Դͬʱ�޸Ĺ������������ڴ��ع���
 *  
 *  @param[in]  ptr   ԭ��������
 *  @param[out] ��
 *  @return ��
 */
void ul_debug_free(void *ptr);

/**
 *  debugģʽ���Ӧ�ó�����ڴ�ʹ����Ϣ
 *  
 *  @param[in]  buff      bufָ��
 *  @param[in]  buff_len  buf����
 *  @param[out] buff      ����ڴ�ʹ����Ϣ
 *  @return ��
 */
int  ul_debug_dump_mem_info(char *buff, int buff_len);

#endif
