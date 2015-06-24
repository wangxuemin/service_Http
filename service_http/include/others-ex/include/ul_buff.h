/**
 * @file
 * @brief �ַ�������
 */
//***********************************************************************
//			Signature Utilities (SU) 1.0
//
//   programmed by Ming Lei, Jul, 2000
//***********************************************************************

/**
 * @brief ��������Ҫ��Ϊ��ĳһ�ռ���Ƶ����׷����Ϣ�ṩ�򻯵Ĳ�����ͬʱ���Է�ֹ����Խ�磬�����������ַ�ʽ�ṩ����\n
 * �ռ䣬һ�����û��Լ�����ռ䣬Ȼ��ͨ��ul_buff_bind()�������ռ��뻺�����󶨣����ַ�ʽ���ܶԿռ�����Զ�\n
 * ��չ����֮��Ӧ��Ҫͨ��ul_buff_unbind()�����������ռ�İ󶨣��ռ���Ҫ�û��Լ��ͷţ���һ�ַ�ʽ��ͨ��\n
 * ul_buff_alloc()�Զ�Ϊ����������ռ䣬ȱʡ�����пռ���Զ���չ�������Ҫ�ռ�����Զ���չ������ͨ��\n
 * ul_buff_set_realloc_size()����ÿ����չ�Ĵ�С����֮���Ӧ�ģ���ͨ��ul_buff_free()�ͷſռ䡣
 */



#ifndef __UL_BUFF__
#define __UL_BUFF__


#define F_REALLOC		0x01
#define F_BINDED		0x02

typedef struct {
	int  pos;		// current position
	int  len;		// buffer's length
	int  ralen;		// realloc size of increament
	char flag;		// internal flag
        char *buffer;		// start position
}Buff;


/**
 *  ��ʼ���������ṹ
 *  
 *  @param[in]   buff  Buff��ָ��
 *  @param[out]  buff  Buff��ʼ����Ľ��
 *  @return �������
 * - 0      �ɹ�
 * - -1     ʧ��
 */
int ul_buff_init(Buff *buff);


/**
 *  Ϊ�������󶨿ռ�
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  buffer  ���󶨵�buf
 *  @param[in]  len     buf����
 *  @param[out] buff    �󶨲�����Ľṹ
 *  @return �������
 * - 0      �ɹ�
 * - -1     ʧ��
 *  @note ��ģʽ��,��buf��ʱ,��֧���Զ�����ռ�,��Ҫ����Ӧ����ע���ⷽ����ж�
 */
int ul_buff_bind(Buff *buff, char *buffer, int len);



/**
 *  ȡ���������Ŀռ��
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[out] ��
 *  @return �ռ�ָ��
 * - ��NULL      �ɹ�
 * - NULL        ʧ��
 *  @note �˺�����::ul_buff_bind�������ʹ��
 */
char *ul_buff_unbind(Buff *buff);




/**
 *  Ϊ����������ռ�
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  len     ��������С
 *  @param[out] ��
 *  @return �������
 * - 0      �ɹ�
 * - -1     ʧ��
 *  @note �˺����������ڰ󶨵�ģʽ
 */
int ul_buff_alloc(Buff *buff, int len);


/**
 *  �ͷŻ������ռ�
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[out] ��
 *  @return �������
 * - 0      �ɹ�
 * - -1     ʧ��
 *  @note �˺����������ڰ󶨵�ģʽ
 */
int ul_buff_free(Buff *buff);



/**
 *  ���ÿռ���չ��������С
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  size    ������С
 *  @param[out] ��
 *  @return �������
 * - 0      �ɹ�
 * - -1     ʧ��
 *  @note �󶨵Ŀռ䲻�ܽ�����չ,�����󶨵Ŀռ䲻�����·���
 */
int ul_buff_set_realloc_size(Buff *buff, int size);


/**
 *  ���һ���ַ���������
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  ch      ������ַ�
 *  @param[out] ��
 *  @return �������
 * - 1      �ɹ�
 * - 0      �ռ䲻��
 * - -1     ʧ��
 */
int ul_buff_putc(Buff *buff, char ch);

/**
 *  ���һ���ַ�����������
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  str     ������ַ�
 *  @param[out] ��
 *  @return �������
 * - 1      �ɹ�
 * - 0      �ռ䲻��
 * - -1     ʧ��
 */
int ul_buff_puts(Buff *buff, char *str);


/**
 *  ���һ��N���ֽڵ�������
 *  
 *  @param[in]  buff    Buff��ָ��
 *  @param[in]  src     ָ������������
 *  @param[in]  len     ��������ݵĳ���
 *  @param[out] ��
 *  @return �������
 * - >0     �ɹ�,ʵ��������ֽ���
 * - 0      �ռ䲻��
 * - -1     ʧ��
 */
int ul_buff_copy(Buff *buff, void *src, int len);



/**
 *  ��ʽ�������������
 *  
 *  @param[in]  buff     Buff��ָ��
 *  @param[in]  fmt, ... ��μ�C����printf
 *  @param[out] ��
 *  @return �������
 * - >0     �ɹ�,ʵ��������ֽ���
 * - 0      �ռ䲻��
 * - -1     ʧ��
 */
int ul_buff_printf(Buff *buff, char *fmt, ...);



/**
 *  ��ȡ��������ǰ�ռ�Ĵ�С
 *  
 *  @param[in]  buff     Buff��ָ��
 *  @param[out] ��
 *  @return �������
 * - >0     �ɹ�,�������ռ�Ĵ�С
 * - -1     �ռ�δ���󶨻�δ����
 */
int ul_buff_get_buffer_size(Buff *buff);


/**
 *  ��ȡ��������ǰ���ݳ���
 *  
 *  @param[in]  buff     Buff��ָ��
 *  @param[out] ��
 *  @return �������
 * - >0     �ɹ�,�������ռ�����ݳ���
 * - -1     �ռ�δ���󶨻�δ����
 */
int ul_buff_get_data_len(Buff *buff);


/**
 *  ��ȡ�������Ŀռ��ַ
 *  
 *  @param[in]  buff     Buff��ָ��
 *  @param[out] ��
 *  @return ָ��ռ��ָ��
 * - ��NULL      �ɹ�
 * - NULL        ʧ��,�ռ�δ���󶨻�δ����
 */
char *ul_buff_get_buffer(Buff *buff);

#endif
