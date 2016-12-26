#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[])
{

    int counter = 0; 
    int arr[50];

	for(int i = 0; i < 50; i++)
    	arr[i] = 0;

    int j = 0;
    for(; j < 2; j++){

    	pid_t pid = fork();

    	if (pid == 0)
    	{
    		printf("Child process is accessing memory.\n");
    		sleep(2);
    		exit(0);
    	}
    	else if (pid > 0)
    	{
    		printf("In Parent Process, doing nothing.\n");
    	}
    	else
    	{
        	// fork failed
        	printf("fork() failed!\n");
        	return 1;
    	}
    }

    printf("Bryan Cantos ID: %d\n", 23023992);

    return 0;
}