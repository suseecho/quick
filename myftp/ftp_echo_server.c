/*================================================================
*   Copyright (C) 2018  All rights reserved.
*   
*   文件名称：ftp_server.c
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
#include<stdlib.h>
#include<arpa/inet.h>
#include<fcntl.h>

#define BUFFERSIZE 1024

int main(int argc , char ** argv)
{
    char buff[BUFFERSIZE];
    int server_fd;
    int client_fd;
    int sin_size;
    struct sockaddr_in server_addr , client_addr;
    if(( server_fd = socket(AF_INET, SOCK_STREAM , 0 )) < 0)
    {
        perror("socket");
        exit(2);
    }
    printf("socket create succuess\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(2333);

    if(bind(server_fd, (struct sockaddr *)&server_addr , sizeof(server_addr)) < 0 )
    {
        perror("bind");
        exit(3);
    }
    printf("bind success\n");

    if( listen(server_fd,5) < 0)
    {
        perror("listen");
        exit(4);
    }
    printf("listen success\n");
    sin_size = sizeof(client_addr);


    int len;
    int len_file;
    int src_fd;
    int dest_fd;
    int temp_fd;
    char operation[20];
    char src[50];
    char dest[50];
    char status[30];

    while(1)
    {
        if(( client_fd = accept(server_fd , ( struct sockaddr *)&client_addr , (socklen_t *)&sin_size)) < 0)
        {
            perror("accept");
            exit(5);
        }
    
        strcpy(status,"connected");
        printf("%s\n",status);
        send(client_fd,status, sizeof(status),0);
        while(len = recv(client_fd,operation,BUFFERSIZE,0) > 0)
        {
            printf("%s\n",operation);
            if(strncmp(operation,"quit",4) == 0)
            {
                memset(buff,0,BUFFERSIZE);
                printf("disconnected\n");
                break;
            }

            if( strncmp(operation,"list",4) == 0)
            {
			    system("ls -l > .temp.txt");
			    if( (temp_fd = open(".temp.txt", O_RDONLY)) < 0)
			    {
				    strcpy(buff,"something wrong happened , can not list\n");	
			    }
			    else
			    {
				    memset(buff,0,BUFFERSIZE);
				    while((len_file=read(temp_fd, buff , sizeof(buff))) > 0)
				    {
					    write(client_fd, buff , len_file);
				    }
                    memset(buff,0,BUFFERSIZE);
                    strcpy(status,"finished\n");
                    sleep(1);
                    write(client_fd,status,sizeof(status));
                    close(temp_fd);
			    }
            }

            if(strncmp(operation,"get",3) == 0)
            {
                printf("request get\n");
                recv (client_fd ,src , sizeof(src) , 0);
//            recv ( client_fd , dest , sizeof(dest) , 0);

                if( (src_fd = open( src ,O_RDONLY )) < 0)
                {
                    strcpy(status , "no such file\n");
                    send(client_fd , status , sizeof(status) , 0);
                }
                else
                {
                    strcpy(status,"downloading\n");
                    send(client_fd , status , sizeof(status) , 0);
                }
                memset(buff,0,BUFFERSIZE);
                while((len_file = read(src_fd , buff ,sizeof(buff))) > 0)
                {
//                printf("%s",buff);
                    write(client_fd , buff , len_file);
                }
                write(client_fd,0,0);
                shutdown(client_fd,SHUT_WR);
                close(src_fd);
//            recv(client_fd,buff,BUFFERSIZE,0);
            }
            if(strncmp(operation,"put",3) == 0)
            {
                printf("request put\n");
                recv (client_fd ,dest , sizeof(dest) , 0);
//            recv ( client_fd , dest , sizeof(dest) , 0);

                if( (dest_fd= open( dest,O_CREAT | O_WRONLY , 0644)) < 0)
                {
                    strcpy(status , "can not create file\n");
                    send(client_fd , status , sizeof(status) , 0);
                }
                else
                {
                    strcpy(status,"uploading\n");
                    send(client_fd , status , sizeof(status) , 0);
                }
                memset(buff,0,BUFFERSIZE);
                while((len_file = read(client_fd, buff ,sizeof(buff))) > 0)
                {
//                printf("%s",buff);
                    write(dest_fd, buff , len_file);
                }
                shutdown(client_fd,SHUT_RD);
                close(dest_fd);
//            recv(client_fd,buff,BUFFERSIZE,0);
            }
        }
    }
    close(client_fd);
    close(server_fd);
    return 0;
}
