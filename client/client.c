#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

char file1[100];
char file2[100];
const char *filename="default.txt";
const char *freqdef="file.txt";
int main(int argc, char *argv[])
{
int skt1,skt2, p_no_1,p_no_2, n;
struct sockaddr_in serv_addr1, serv_addr2;
struct hostent *server;
int rec_byt1 = 0;
int rec_byt2 =0;
char buf_recv1[256];
char buf_recv2[256];
memset(buf_recv1, '0', sizeof(buf_recv1));
memset(buf_recv2, '0', sizeof(buf_recv2));

int flg =0;
char buffer1[256];
char buffer2[256];
if (argc < 3)
{
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0);
}

p_no_1 = atoi(argv[1]);
p_no_2 = atoi(argv[2]);
skt1 = socket(AF_INET, SOCK_STREAM, 0);
if(skt1<0)
{
	printf("error in the opening of socket");
	//exit(0);
}
server =  gethostbyname("localhost");
if(server == NULL)
{
	fprintf(stderr, "there is no such host \n");
	exit(0);
}
bzero((char *)&serv_addr1, sizeof(serv_addr1));

serv_addr1.sin_family = AF_INET;

//server = (struct hostent *)malloc(sizeof(struct hostent));
bcopy((char *) server->h_addr,(char *)&serv_addr1.sin_addr.s_addr,server->h_length);


//if (skt h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

serv_addr1.sin_port = htons(p_no_1);



if (connect(skt1,&serv_addr1,sizeof(serv_addr1))  < 0) 
        printf("errro in connecting too server!\n");

//if (connect(skt,&serv_addr1,sizeof(serv_addr1)) > 0)
else {
printf("connected to server1\n");
printf("Please enter the filename to check to server1: \n");
bzero(buffer1,256);
fgets(buffer1,255,stdin);
n = write(skt1,buffer1,strlen(buffer1));
freqdef =buffer1;
if (n < 0)
{
printf("error in writing to socket");
}
bzero(buffer1,256);
n = read(skt1,buffer1,255);
if (n < 0)
{
printf("error in reading from socket");
}
printf("%s\n",buffer1 );
	FILE *fp;
	printf("please enter the local file name in which you want to save the data\n");
	scanf("%s ",file1);
    //fp = fopen(filename, "ab"); 
    filename =file1;
    fp = fopen(filename,"ab");
    if(NULL == fp)
    {
        printf("error in  opening the file\n");
        return 1;
    }
    while((rec_byt1 = read(skt1, buf_recv1, 256)) > 0)
    {
        fwrite(buf_recv1, 1,rec_byt1,fp);
        flg = 1;
    }

    if(rec_byt1 < 0)
    {
        printf("\n error in reading the file \n");
    }
}

close(skt1);
bzero((char *)&serv_addr2, sizeof(serv_addr2));
serv_addr2.sin_family = AF_INET;
bcopy((char *) server->h_addr,(char *)&serv_addr2.sin_addr.s_addr,server->h_length);
serv_addr2.sin_port = htons(p_no_2);
skt2 = socket(AF_INET, SOCK_STREAM, 0);
//if (flg==0 && connect(skt,&serv_addr2,sizeof(serv_addr2)) > 0)
if (connect(skt2,&serv_addr2,sizeof(serv_addr2))  < 0) 
        printf("errro in connecting to server\n");
else
{
if(flg==0)
{
//printf("Please enter the filename: ");
//printf("connected to server2\n");
//printf("Please enter the filename to check to server2: \n");
//fflush(stdout);
bzero(buffer2,256);
fgets(buffer2,255,stdin);
n = write(skt2,buffer2,strlen(buffer2));
freqdef =buffer2;
if (n < 0)
{
printf("error in writing to socket\n");
}
bzero(buffer2,256);
n = read(skt2,buffer2,255);
if (n < 0)
{
printf("error in reading from socket\n");
}
printf("%s\n",buffer2 );

	FILE *fp;
    //fp = fopen(filename, "ab"); 
    filename =file2;

	//	filename = file2;
    //fp = fopen(filename, "ab"); 
    
    fp = fopen("tempfi.txt","ab");
    if(fp==NULL)
    {
        printf("error in opening file!");
        return 1;
    }
    while((rec_byt2 = read(skt2, buf_recv2, 256)) > 0)
    {
        fwrite(buf_recv2, 1,rec_byt2,fp);
    }

    if(rec_byt2 < 0)
    {
        printf("\n error in reading to fsa \n");
    }

}
}
    return 0;
}