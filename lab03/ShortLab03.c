#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
fork() basically generates processes. if u call fork() one time then it will creat two process. one child and second called parent.

fork() returns 0 in child process and returns PID of child in parent process

*/

int i = 0;
int pid = 0; // it will store process id
int fd = 0;
int data = 19530;

int my_signal(void)
{

/*
This function will get called when child complete his task.
Basically in parent function.
it will read data from file. devide by 5 and write to a file

*/
fd = open("myfile",O_RDONLY);
read(fd,&data,sizeof(data));
data = (data /5) - 1;
printf("Parent: %d\n\n",data);
close(fd);
fd = open("myfile",O_WRONLY|O_TRUNC);
write(fd,&data,sizeof(data));
close(fd);
fflush(stdout);

}
int main()
{

fd = open("myfile.txt",O_WRONLY|O_CREAT);
write(fd,&data,sizeof(data));
close(fd);
signal(17,my_signal); // when child complete its task then it will call this ISR to user

for( i=0;i<5;i++) // loop will run 5 times
{
printf("Iteration %d \n",i);
pid = fork();

if(pid == 0)
{
/*child code */
sleep(2);
fd = open("myfile",O_RDONLY);
read(fd,&data,sizeof(data));
data = data -5;
printf("Chile: %d\n",data);

close(fd);
fd = open("myfile",O_WRONLY|O_TRUNC);
write(fd,&data,sizeof(data));
close(fd);
fflush(stdout);
exit(0);

/*
child will open afile, read a data and do operation.
again open a file, append it and write the data
*/
}
else
{
wait(0); // wait for complete child process
}
}
sleep(1);
}