#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/vfs.h>
#include <string.h>
#include <pthread.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define port 3333



struct FilePackage
{
	char cmd;
	int  filesize;
	int  ack;
	char username[50];
	char filename[125];
	char buf[1024];  
};


//~~~~~~~~~~~~~~~~~~~~~~~~打包数据~~~~~~~~~~~~~~~~~~~~~~~~~
struct FilePackage pack(char tCmd, char* tBuf, char* tFilename, int tFilesize, int tAck,int count,char *uname)
{
	struct FilePackage tPackage;
	tPackage.cmd = tCmd;
//	strcpy(tPackage.buf, tBuf);
//	strncpy(tPackage.buf, tBuf,1024);
	memcpy(tPackage.buf,tBuf,count);
	strcpy(tPackage.filename, tFilename);
	strcpy(tPackage.username, uname);
	tPackage.filesize = tFilesize;
	tPackage.ack = tAck; 
	return tPackage;
}

/*
请求：
Cmd：R
客服端发送数据包：0 请求连接

服务器发送数据包：1答应请求


登陆: 
Cmd:L    用户名与密码放在buf内以*号隔开如 admin*123
服务器发送数据包的ACK：0 用户名或密码错误
     	       	         1 登陆成功
     	                 2 客户端最大连接数

客服端发送数据包的ACK：9 登陆服务器  


下载：
Cmd：D
服务器发送数据包的ACK：0 接受下载，返回待下载文件大小
		       						 2 开始下载
											 4 下载完毕
											 		
客服端发送数据包的ACK：9 请求下载
		       						 1 本地磁盘空间不足
		       						 3 接受完毕


上传：
Cmd：U
服务器发送数据包的ACK：0 接受上传请求
		                   1 本地磁盘空间不足
		                   3 接收完毕

客服端发送数据包的ACK：9 请求上传，上传文件大小,文件名
		                   2 开始上传文件
		                   4 上传完毕
		       

显示文件列表
Cmd：S
服务器发送数据包的ACK: 0 第一个显示文件列表
		                  

客服端发送数据包的ACK：9 请求显示

退出
Cmd: Q
客服端发送数据包的ACK：0
*/
