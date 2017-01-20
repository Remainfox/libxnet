
#ifndef __XNET_EPOLL__
#define __XNET_EPOLL__


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <ifaddrs.h>
#include <pthread.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>

typedef void (*FUNC_CALLBACK)(int, int, void *);

/* ���������ļ������������Ϣ */
struct event_data_s 
{    
	int efd;
	int fd;                                                 //Ҫ�������ļ�������    
	int events;                                             //��Ӧ�ļ����¼�   
	void *arg;                                              //���Ͳ���    
	FUNC_CALLBACK read_callback;       						//���ص�����  
	FUNC_CALLBACK write_callback;       					//д�ص�����  
	int status;                                             //�Ƿ��ڼ���:1->�ں������(����), 0->����(������)    
	char *buf;    
	int len;    
	long last_active;                                       //��¼ÿ�μ������� g_efd ��ʱ��ֵ

	int live_statue;
	pthread_t pid;
	int thread_run_state;                                   //�߳�����״̬
};


#endif



