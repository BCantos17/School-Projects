#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define   BUF_SIZE   100
#define   MEM_SIZE   50


int main(int argc, char * argv[])
{

    int status; 
    int mem[50];
    pid_t pid[10], waitPid;
    char buf[BUF_SIZE];
    srand(time(NULL));

	int i;
	for(i = 0; i < 50; i++)
    	mem[i] = 1;

	// Creating Child
    int j;
    for(j = 0; j < 20; j++){

    	int rand_num =  rand() % 25;
 		// Fork failed
    	if((pid[j] = fork()) < 0)
    	{	
        	fprintf(stderr,"fork() failed!\n");
        	return 1;
    	}

    	// In Child
    	else if (pid[j] == 0)
    	{
			char test[10];
			sprintf(test, "%d", j);
    		fprintf(stderr,"Child process is accessing memory %d.\n", rand_num);
    		execl("helloworld", "helloworld", test, (char*)0);
    		if(execl("helloworld", "helloworld", mem, (char*)0) == -1)
    			printf("error\n");
    		exit(0);
    		/*if(mem[rand_num] == 0)
    		{
    			fprintf(stderr,"Memory slot is empty, child is now taking slot\n");
    			mem[rand_num] = getpid();
    			fprintf(stderr,"Memory = %d  Pid ID = %d\n", rand_num, &mem[rand_num]);
    			sleep(rand() % 5);
    			execlp("sleep", "sleep", "2", (char *)0);// Sleeps
    			fprintf(stderr, "Child is releasing pid and resetting memory %d to zero.\n", rand_num);
    			mem[rand_num] = 0; 
    			exit(1);
    		}
    		else if(mem[rand_num] != 0 )
    		{
    			fprintf(stderr,"Memory is taken\n");
    			exit(1);
    		}*/
    		
    	}

    	// In Parent, do nothing
    	else{} 
    	
    }

	// Waiting for Child process to finish
    while((waitPid=wait(&status))>0); 
    sprintf(buf, "Bryan Cantos ID: %d\n", 23023992);
    write(1, buf, strlen(buf));

    return 0;
}

void ChildGetsMem(int mem[]){

	/*// fork failed
        	printf("fork() failed!\n");
        	return 1;
    	}

    	else if (pid == 0)
    	{
			srand(time(NULL));
    		int rand_num =  rand() % 50;
    		printf("Child process is accessing memory %d.\n", rand_num);
    		if(mem[rand_num] == 0)
    		{
    			printf("Memory slot is empty, child is now taking slot\n");
    			mem[rand_num] = getpid();
    			printf("Memory = %d  Pid ID = %d\n", rand_num, mem[rand_num]);
    			execlp("sleep", "sleep", "2", (char *)0);//Load the program
    		}
    		else 
    			printf("mem is taken\n");
    		//execlp("sleep", "sleep", "2", (char *)0);//Load the program*/

}