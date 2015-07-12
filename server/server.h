#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/stat.h>        
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/vfs.h>        
#include <dirent.h>          
#include <netinet/in.h>
#include <sys/file.h>
#include <netdb.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

struct FilePackage
{
	char cmd;
	int  filesize;
	int  ack;
	char username[50];
	char filename[125];
	char buf[1024];  
};


/*´ò°üº¯Êý*/
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


