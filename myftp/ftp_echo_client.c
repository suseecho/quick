/*================================================================
*   Copyright (C) 2018  All rights reserved.
*   
*   文件名称：ftp_client.c
*   创 建 者：echo (echoxj233@gmail.com)
*   创建日期：2018年07月06日
*   描    述：
*
================================================================*/


#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUFFERSIZE 1024

int main(int argc , char ** argv)
{
	char buff[BUFFERSIZE];
	int client_fd;
	if( (client_fd = socket(AF_INET ,SOCK_STREAM , 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2333);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if( connect(client_fd , (struct sockaddr*)&server_addr , sizeof(server_addr)) < 0)
	{
		perror("connect");
		exit(2);
	}

    char operation[20];
    char src[50];
    char dest[50];
	int sin_len ;
	int len_file;
	int dest_fd;
	int src_fd;
	int temp_fd;

    sin_len = read( client_fd , buff ,sizeof(buff));
	printf("%s\n",buff);
    while(1)
    {
		printf(">");
//        memset(buff,0,sizeof(buff));
        scanf("%s",operation);
        if( strncmp(operation,"quit",4) == 0)
        {
			send(client_fd, operation, sizeof(buff) , 0);
			printf("disconnected\n");	
			break;
			
        }

        if( strncmp(operation,"list",4) == 0)
        {
			send(client_fd, operation, sizeof(buff) , 0);
			while((len_file=read(client_fd , buff , sizeof(buff))) > 0)
			{
				if(strncmp(buff,"finished",8) == 0)
					break;
				printf("%s",buff);
			}
        }


        if( strncmp(operation,"help",4) == 0)
        {
			printf("\tget <remote file> <locate file>\n");
			printf("\tput <local file> <remote file>\n");
			
        }
		if( strncmp(operation,"get",3) == 0)
		{
			send(client_fd, operation, sizeof(buff) , 0);
			scanf("%s %s",src,dest);
			send(client_fd,src , sizeof(src),0);
			recv (client_fd , buff , sizeof(buff),0);
			printf("%s\n",buff);

			if( (dest_fd = open(dest , O_WRONLY | O_CREAT, 0644)) < 0)
			{
				printf("can not create file\n");
			}

			memset(buff,0,BUFFERSIZE);


			while((len_file=read(client_fd , buff , sizeof(buff))) > 0)
			{
				write(dest_fd , buff , len_file);
			}

			printf("Transfer complete\n");
			memset(buff,0,BUFFERSIZE);
			break;

		}

		if( strncmp(operation,"put",3) == 0)
		{
			send(client_fd, operation, sizeof(buff) , 0);
			scanf("%s %s",src,dest);
			send(client_fd,dest, sizeof(dest),0);
			recv (client_fd , buff , sizeof(buff),0);
			printf("%s\n",buff);

			if( (src_fd= open(src, O_RDONLY)) < 0)
			{
				printf("no such file\n");
			}

			memset(buff,0,BUFFERSIZE);


			while((len_file=read(src_fd, buff , sizeof(buff))) > 0)
			{
				write(client_fd, buff , len_file);
			}

			printf("Upload complete\n");
			memset(buff,0,BUFFERSIZE);
			break;

		}
//	    printf("%s",buff);
		send(client_fd, buff , sizeof(buff) , 0);
//        memset(buff,0,sizeof(buff));
    }


	close(client_fd);
}

