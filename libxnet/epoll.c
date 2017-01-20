
#include <stdio.h>
#include "epoll.h"




/*���ṹ�� myevent_s ��Ա���� ��ʼ��*/
void eventset(struct event_data_s *ev, int efd,int fd, FUNC_CALLBACK read_callback,
				FUNC_CALLBACK write_callback, void *arg)
{    
	ev->efd = efd;
	ev->fd = fd;    
	ev->read_callback  = read_callback;   
	ev->write_callback = write_callback;
	ev->events = 0;    
	ev->arg = arg;   
	ev->status = 0; 
	ev->live_statue = 0;
	ev->last_active = time(NULL);                       
	//����eventset������ʱ��    
	return;
}


/* �� epoll�����ĺ���� ���һ�� �ļ������� */
void eventadd(int events, struct event_data_s *ev)
{
    struct epoll_event epv = {0, {0}};
    int op;
    epv.data.ptr = ev;
    epv.events = ev->events = events ;       //EPOLLIN �� EPOLLOUT

    if (ev->status == 1) {                                          //�Ѿ��ں���� g_efd ��
        op = EPOLL_CTL_MOD;                                         //�޸�������
    } else {                                						//���ں������
        op = EPOLL_CTL_ADD;                 						//����������� g_efd, ����status��1
        ev->status = 1;
    }
	
    if (epoll_ctl(ev->efd, op, ev->fd, &epv) < 0)  {
        //printf("event add failed [fd=%d], events[%d],errno:%d\n", ev->fd, events,errno);
	}
    else{
        //printf("event add OK [fd=%d]\n", ev->fd, op);
	}

    return ;
}


void eventdel(int efd, struct event_data_s *ev)
{
    struct epoll_event epv = {0, {0}};

    if (ev->status != 1)                                        //���ں������
        return ;

    epv.data.ptr = ev;
    ev->status = 0;                                             //�޸�״̬
    epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv);                //�Ӻ���� efd �Ͻ� ev->fd ժ��

    return ;
}



