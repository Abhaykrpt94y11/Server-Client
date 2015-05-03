Aim: 
To build a simple network involving three nodes with following instructions.
1. One of the nodes will be a client and the other two nodes will be servers.

2. The client can request for a file from the servers and any server having the file will send the
file, also flag an error message if the server does not have the file. If both servers have the
file, send the file from any of the servers.


Compilation instruction
1) client server is hard coded in file itself
2) only port are provided as command line for each file
3) 2 port are provided corresponding to each server for client.c file.

----------------server1.c-------------------------------
abhaykrpt@ubuntu:~/Desktop/Server1$ gcc server1.c -o server1.out
abhaykrpt@ubuntu:~/Desktop/Server1$ ./server1.out 9092
file requested is s1_f1.txt

File  s1_f1.txt is found  in server1
 error in  openning the file
abhaykrpt@ubuntu:~/Desktop/Server1$ 


---------------------server2.c-------------------------
abhaykrpt@ubuntu:~/Desktop/Server2$ gcc server2.c -o server2.out
abhaykrpt@ubuntu:~/Desktop/Server2$ ./server2.out 9090
file requested is s2_f3.txt

File  s2_f3.txt is found  in server2
 error in opening of file!abhaykrpt@ubuntu:~/Desktop/Server2$ 



----------------client.c-----------------------------------
abhaykrpt@ubuntu:~/Desktop/client$ ./client.out 9092 9090
connected to server1
Please enter the filename to check to server1: 
s1_f1.txt
File is found at server1
please enter the local file name in which you want to save the data
localfile.txt
s2_f3.txt
File is found at server2
abhaykrpt@ubuntu:~/Desktop/client$ 

