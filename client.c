// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#define PORT 8080

int clientfd2;
char* IP = "127.0.0.1";
typedef struct sockaddr meng;
char name[30];  //the length of username
time_t nowtime;

void init(){
	clientfd2=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP);

	if (connect(clientfd2,(meng*)&addr,sizeof(addr))==-1){
		perror("cannot connect server");
		exit(-1);
	}
	printf("client connect success\n");
}

void start(){
	pthread_t id;
	void* recv_thread(void*);
	pthread_create(&id,0,recv_thread,0);
	char buf2[100]={};
	//char usr_buf[50]={};
	//strcpy(usr_buf,name);
	//send(clientfd2,usr_buf,strlen(usr_buf),0);
	sprintf(buf2,"\n================ %s join chatroom ====================\n",name);
	time(&nowtime);
	printf("join time:%s\n",ctime(&nowtime));
	send(clientfd2,buf2,strlen(buf2),0);
	while(1){
	char buf[100]={};
	gets(buf);
	//fgets(buf,100,stdin);
	//scanf("%s",buf);
	char msg[100]= {};
	if(buf[0] !='\0' && buf[0]!='\n'){
	sprintf(msg,"[%s]:%s",name,buf);
	send(clientfd2,msg,strlen(msg),0);
	if(strstr(buf,"quit")!=NULL){
		//memset(buf2,0,sizeof(buf2));
		sprintf(buf2,"\n=================== %s exit chatroom ====================\n",name);
		printf("Your already have left the chatroom , thanks for your using !!\n");
		send(clientfd2,buf2,strlen(buf2),0);
		memset(buf2,0,sizeof(buf2));
		break;
		}
	}
	}
	close(clientfd2);
}

void* recv_thread(void* p){
	while(1){
		char buf[100]={};
		if(recv(clientfd2,buf,sizeof(buf),0)<=0){
			break;
		}
	printf("%s\n",buf);
	}
}


int main(){
	init();
	printf("Please input username:");
	scanf("%s",name);
	printf("\n\n**************************************\n");
	printf("welcome %s join chatroom\n",name);
	printf("if you want to exit chatroom ,please input <quit>\n");
	printf("\n********************************************\n\n");
	start();
	return 0;
}

