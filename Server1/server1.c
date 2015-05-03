#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <stdlib.h>

int alldata[10000][10000];
int flag = 50;
int  count=0;
char filename[1000];

const char *ms="Default returrning msg! Not Found";
void searchfile(char *dir, int depth, char fname[])
{
    DIR *dp;
    count = 0;
    struct dirent *s_e;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((s_e = readdir(dp)) != NULL) 
    {
        count = 0;
        lstat(s_e->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
         {
            if(strcmp(".",s_e->d_name) == 0 ||
                strcmp("..",s_e->d_name) == 0)
                continue;
    
           searchfile(s_e->d_name,depth+4,fname);
        }
        else 
        {
            int l1 = strlen(s_e->d_name);
            int l2 = strlen(fname);
            int i =0 ;
            int count=0;
            for(i=0;i<l1+1;i+=1)
            {
                if(s_e->d_name[i] == fname[i])
                {
                    count+=1;
                }
              
            }
            if(count==l1 && count>1)
            {
                printf("File  %s is found  in server1\n ", s_e->d_name);
                   // printf("filename is %s\n",s_e->d_name);

                    flag = 100;
                    ms = "File is found at server1";
                     }
    
        }
    }
    chdir("..");
    closedir(dp);

}

int main(int argc, char *argv[])
{
	//printf("sajdklsdlsd\n");
    
	
int skt;
			int newskt;
	   flag = 100;		int connfd;
			int p_no;
			int c_ln;
			char buffer[256];
			struct sockaddr_in serv_addr,cli_addr;
			int n;
			char sendBuff[1025];

	memset(sendBuff, '0', sizeof(sendBuff));
	if(argc<2)
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	skt = socket(AF_INET, SOCK_STREAM,0);
	if(skt<0)
	{
		printf("ERROR opening socket");	
	}

	bzero((char *)&serv_addr,sizeof(serv_addr));
	p_no = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	serv_addr.sin_port = htons(p_no);
	if(bind(skt, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("error in binding the socet\n");
	}
	listen(skt, 1);
	c_ln = sizeof(cli_addr);
	newskt = accept(skt, (struct sockaddr *)&cli_addr, &c_ln);
	if(newskt <0)
	{
	printf("error in accepting the client server\n");
	}	
	bzero(buffer, 256);
	n = read(newskt, buffer, 255);
	if(n<0)
	{
		printf("error in reading from socket!\n");
	}
	printf("file requested is %s\n", buffer);
	searchfile("/home/abhaykrpt/Desktop/Server1",0,buffer);

	/*
	if(flag == 50)
    {
              ms = "File is not found on server1!";
            //    break;
    }
    if(flag ==100)
    {
    	  ms = "File is found at server1 !";
    }
	*/
	n = write(newskt, ms, strlen(ms));
	if(n<0)
	{
		printf("error inwriting to socket");
	}

	//filename = (char *)malloc(100*sizeof(char));
	//foundfile = (char *)malloc(100*sizeof(char));
	
	strcpy(filename, buffer);
    int l1,l2;
   // l1 = strlen(filename);
    //l2 = strlen(buffer);
    //printf("l1 is %d  %s l2 is %d  %s", l1,filename, l2, buffer);
	

    while(1)
    {
     	 
            if(flag==50)
            {
            	printf("file is not found on server1\n");
            	break;
            }


        FILE *fp = fopen("file.txt","rb");
        if(fp==NULL)
        {
            printf("error in  openning the file\n");
            return 1;   
        }   
        while(1)
        {
            
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);      

            if(nread > 0)
            {
                printf("Sending data\n");
                write(newskt, buff, nread);
            }

        }

        close(newskt);
        sleep(1);
        break;
    }

	return 0;

}

