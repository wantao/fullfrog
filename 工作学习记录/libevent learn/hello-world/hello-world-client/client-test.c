#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static unsigned int g_thread_counts = 10;
static unsigned int g_one_thread_loop_connect_count = 100;
static char* g_server_ip = "192.168.238.129";
static unsigned int g_server_port = 9995;
static unsigned int g_data_size = 1024;
static char* g_sendData = NULL;
static unsigned int g_sleep_time = 1000;
static unsigned int g_sendData_count = 10000;
static unsigned int g_client_per_thread = 1000;
static int g_test_flag = 0;//0:tun tu test,1:bing fa test

#define MAX_BUFF_SIZE 1024


int tcp_connect(char* server_ip, unsigned int server_port)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    struct hostent *host;
    if ((host = gethostbyname(server_ip)) == NULL)
    {
        printf("get host by name error,server_ip:%s\n",server_ip);
        return sockfd;
    }
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("create_socketfd error\n");
    }
    else
    {
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        if (connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) == -1)
        {
            printf("cannot connect server,server_ip:%s,port:%d\n",server_ip,server_port);
            close(sockfd);
            return -1;
        }
    }
    return sockfd;

}

bool recvData(pthread_t id,int fd,char* pData,int pDataLen)
{
    
    int nbytes = 0,nRecvByte = 0;
    while (nRecvByte < pDataLen) {
        nbytes = recv(fd,pData+nRecvByte,pDataLen-nRecvByte,0);
        if (nbytes > 0) {
            nRecvByte += nbytes;
            //printf("nbytes=%d\n",nbytes);
            //printf("pData+%d:%s\n",nRecvByte,pData);
            continue;
        }
        printf("threadid:%d,recvData error,nbyte:%d,sterror:%s\n",id,nbytes,strerror(errno));
        return false;
        
    }
    return true;
}

bool sendData(pthread_t id,int fd,char* pData,int pDataLen)
{
    int nSendbyte = 0,nbyte = 0;
    while (nSendbyte < pDataLen) {
        nbyte = send(fd,pData+nSendbyte,pDataLen-nSendbyte,0);
        if (nbyte > 0) {
            nSendbyte += nbyte;
        } else {
            printf("threadid:%d,sendData error,nbyte:%d,sterror:%s\n",id,nbyte,strerror(errno));
            return false;
        }
    }
    return true;
}

void* tcp_connect_func(void* pArg)
{
    int client_count = 0;
    while (client_count < g_client_per_thread) {

    int j = 0;
    int fd = 0;
    pthread_t id = *(pthread_t*)pArg;
    fd = tcp_connect(g_server_ip,g_server_port);
    if (fd <= 0){
        printf("threadid:%d,tcp_connect failure\n",id);
        pthread_exit((void*)-1);
    }
    char *recvBuf = (char*)malloc(g_data_size*sizeof(char)+1);
    if (NULL == recvBuf) {
        printf("threadid:%d,malloc recvBuf failure\n",id);
        pthread_exit((void*)-1);
    }
    char *recvBufTmp = recvBuf;
    unsigned int sendData_has_send_count = 0,recvData_has_recv_count = 0;
    unsigned int has_send_count = 0;
    if (g_test_flag == 0) {

    while (1) {
        if (g_data_size <= 0) {
            usleep(1000*1000);
            continue;
        }
        memset(recvBufTmp,0,g_data_size);
        char* pData = g_sendData;
	if (has_send_count < g_sendData_count) {
        	if (sendData(id,fd,pData,g_data_size)) { 
			sendData_has_send_count +=1;
    			printf("threadid:%d,Send Success,sendData_has_send_count:%d\n",id,sendData_has_send_count);
			if (recvData(id,fd,recvBufTmp,g_data_size)) {
				recvData_has_recv_count += 1;
    				printf("threadid :%d,recve Sucssess,recvData_has_recv_count:%d\n",id,recvData_has_recv_count);
			}
        	}
		has_send_count += 1;
	} /*else {
		printf("pthread_id id:%d,has_send_count:%d\n",id,has_send_count);
	}*/
        usleep(g_sleep_time);

    }
	
    } else if (g_test_flag == 1) {
	
        if (g_data_size <= 0) {
            usleep(1000*1000);
            continue;
        }
        memset(recvBufTmp,0,g_data_size);
        char* pData = g_sendData;
	if (has_send_count < g_sendData_count) {
        	if (sendData(id,fd,pData,g_data_size)) { 
			sendData_has_send_count +=1;
    			printf("threadid:%d,Send Success,sendData_has_send_count:%d\n",id,sendData_has_send_count);
			if (recvData(id,fd,recvBufTmp,g_data_size)) {
				recvData_has_recv_count += 1;
    				printf("threadid :%d,recve Sucssess,recvData_has_recv_count:%d\n",id,recvData_has_recv_count);
			}
        	}
		has_send_count += 1;
	} /*else {
		printf("pthread_id id:%d,has_send_count:%d\n",id,has_send_count);
	}*/
        usleep(g_sleep_time);
    }
    if (NULL != recvBuf) {
        free(recvBuf);
        recvBuf = NULL;
    }
   	client_count +=1;
    }
    
    
   pthread_exit((void*)0);
}

void create_thread()
{
    pthread_t id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    
    int nret = pthread_create(&id,&attr,tcp_connect_func,&id);
    if (nret != 0)
    {
        printf("pthread_create failure\n");
    }
    pthread_attr_destroy(&attr);
}

int main(int argc, char** argv)
{
    printf("argc:%d\n",argc);
    if (argc != 9)
    {
        return -1;
    }
    g_server_ip = argv[1];
    g_server_port = atoi(argv[2]);
    g_thread_counts = atoi(argv[3]);
    g_data_size = atoi(argv[4]);
    g_sleep_time = atoi(argv[5]);
    g_sendData_count = atoi(argv[6]);
    g_client_per_thread = atoi(argv[7]);
    g_test_flag = atoi(argv[8]);
    printf("g_data_size:%d\n",g_data_size);
    if(g_data_size > 0) {
        g_sendData = (char*)malloc(g_data_size*sizeof(char) + 1);
        if (NULL != g_sendData) {
            memset(g_sendData,'1',g_data_size);
        }
    }
    int i = 0;
    for (; i < g_thread_counts; i++)
    {
        create_thread();
    }
    while (1)
    {
        sleep(2);
    }
    return 0;
}
