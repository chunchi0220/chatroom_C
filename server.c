// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#define PORT 8080

int serverfd;
int clientfd[100];
int size = 50;
int count=0;
char* IP = "127.0.0.1";
typedef struct sockaddr meng;
time_t nowtime;

void init(){
	serverfd =socket(AF_INET,SOCK_STREAM,0);
	if(serverfd==-1){
		perror("create socket fail");
		exit(-1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr=inet_addr(IP);
	if(bind(serverfd,(meng*)&addr,sizeof(addr))==-1){
		perror("bind fail");
		exit(-1);
	}
	if(listen(serverfd,100)==-1){
		perror("listen fail");
		exit(-1);
	}
}

void SendAll(char* msg){
	for(int i=0;i<size;i++){
		if(clientfd[i]!=0){
			printf("send to %d:%s\n",clientfd[i],msg);
			char buf[1024];
			FILE *logs = fopen("log.txt","a+");
			if(logs==NULL){
				printf("open file error:\n");
			}
			else{
				sprintf(buf,"join time:%s\tIP address:%s\n",ctime(&nowtime),IP);
				fputs(buf,logs);
				sprintf(buf,"message:%s\n",msg);
				fputs(buf,logs);
				fclose(logs);
			}
			send(clientfd[i],msg,strlen(msg),0);
		}
	}
}

void* server_thread(void* p){
	int fd=*(int*)p;
	printf("pthread=%d\n",fd);
	printf("There are %d people in the chatroom now\n",count);
	while(1){
		char buf[100]={};
		char buf2[100]={};
		if(recv(fd,buf,sizeof(buf),0) <= 0 || strstr(buf,"quit")!=NULL){
			int i;
			for(i=0;i<size;i++){
				if(clientfd[i]==fd){
					clientfd[i]=0;
					count-=1;
					break;
				}
			}
			recv(fd,buf2,sizeof(buf2),0);
			printf("%s\n",buf2);
			printf("There are %d people in the chatroom\n",count);
			SendAll(buf2);
			printf("<<exit:fd=%d exit>>\n",fd);
			char buf[1024];
			FILE *logs=fopen("log.txt","a");
			if(logs==NULL){
				printf("open file error:\n");
			}
			else{
				sprintf(buf,"exit time:%s\tIP address:%s\n",ctime(&nowtime),IP);
				fputs(buf,logs);
				fclose(logs);
			}
			//free(p);
			pthread_exit(0);
		}
		SendAll(buf);
	}
}
	void server(){
		printf("server start\n");
		while(1){
		struct sockaddr_in fromaddr;
		socklen_t len =sizeof(fromaddr);
		int fd=accept(serverfd,(meng*)&fromaddr,&len);
		if(fd==-1){
			printf("client connection fail\n");
			continue;
		}
		int i;
		for (i=0;i<size;i++){
			if(clientfd[i]==0){
				clientfd[i]=fd;
				count+=1;
				printf("pthread number = %d\n",fd);
				pthread_t tid;
				pthread_create(&tid,0,server_thread,&fd);
				break;
			}
			if(size==i){
				char* str = "sorry chatroom is full";
				send(fd,str,strlen(str),0);
				close(fd);
				
			}
		}
		}
	}

int main(){
	init();
	server();
	return 0;
}
