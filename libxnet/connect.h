
#ifndef __XNET_CONNECT__
#define __XNET_CONNECT__


#include "queue.h"

#define   READ_BUFFER_SIZE    4096
#define   WRITE_BUFFER_SIZE   4096



struct client_conn_s {
	queue_t head;

	int sockfd;						//��HTTP���ӵ�socket
	struct sockaddr_in address;		//�Է���socket��ַ

	char read_buf[READ_BUFFER_SIZE];//��������
	int read_index;					//��ʶ���������Ѿ�����Ŀͻ������ݵ����һ���ֽڵ���һ��λ��


	char write_buf[WRITE_BUFFER_SIZE];				//��д������
	int write_index;				//д�����������͵��ֽ���

	
	char* file_address;				//�ͻ������Ŀ���ļ���mmap���ڴ��е���ʼλ��
	struct stat file_stat;			//Ŀ���ļ���״̬��ͨ���������ж��ļ��Ƿ���ڣ��Ƿ�ΪĿ¼���Ƿ�ɶ�������ȡ�ļ���С����Ϣ
	struct iovec iv[2];				//ʹ��writev��ִ��д���������Զ�������������Ա������iv_count��ʾ��д�ڴ�������
	int iv_count;
};

typedef struct client_conn_s client_conn_t;


#endif


