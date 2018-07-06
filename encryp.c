/*================================================================
*   Copyright (C) 2018  All rights reserved.
*   
*   文件名称：test11.c
*   创 建 者：echo
*   创建日期：2018年07月05日
*   描    述：
*
================================================================*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

void encryption(char * str , int len)
{
	int i = 0 ; 
	for(  ; i < len ; i++)
	{
		str[i] ^= 'X';
	}
}

int main(int argc , char ** argv)
{
	if(argc != 2)
	{
		printf("usage: copy src dest\n");
		exit(2);
	}
	int src_file;
	int temp = 0;
	char *src = argv[1];
	unsigned char buff[1024];
	src_file = open(src,O_RDWR);
	if(src_file < 0 )
	{
		printf("open file failed\n");
		exit(1);
	}
	lseek(src_file,0,SEEK_SET);
	while((temp=read(src_file,buff,sizeof(buff))) > 0)
	{
		encryption(buff,temp);
		lseek(src_file,0-temp,SEEK_CUR);
		write(src_file,buff,temp);
		//lseek(src_file,temp,SEEK_CUR);
	}
	close(src_file);
	return 0;
}

