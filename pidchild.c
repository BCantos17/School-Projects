/* compile with -lm for rand*/

#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<sys/signal.h>        
#include	<stdio.h>
#include	<math.h>
#include        <time.h>
#include 	<pthread.h>
#define 	KFOUR 4096

main(int argc, char *argv[])
{
	int i, *pint, shmkey;
	char *addr;
	int walkno, start, shmid, matsize;
	pthread_mutex_t mutex;
	srand(time(NULL));

	/*creates the mutex lock*/
	pthread_mutex_init(&mutex, NULL);

	/* get parms*/
	walkno  = atoi(argv[1]);
	start   = atoi(argv[2]);
	matsize = atoi(argv[3]);
	shmkey  = atoi(argv[4]); 

	/*debug*/
	printf("child %d start %d size of list %d memory key %d \n", walkno, start, matsize,shmkey);

	/*set up shared memory*/
	shmid = shmget(shmkey, KFOUR, 0777);
	addr = shmat(shmid,0,0);

	/*wait for block on the first memory location to be cleared*/
	pint    = (int *)addr;
        while(*pint > start)
		pint=(int *)addr;

	/*acquires the mutext lock*/
	pthread_mutex_lock(&mutex);
	printf("Child %d acquires the mutex lock and is entering critcal section\n", walkno);

	/*enters the critical section*/

	/* Writes into Array*/
	printf("Child %d is looking for free slot\n", walkno);
	if(*pint != 0)
	{
		printf("Slot is taken, Child %d looking for a new slot\n", walkno);
		pint++;
		while(*pint != 0)
		{
			printf("Child %d is still looking for a free slot\n", walkno);
			pint++;
		}
	}
	/*Child takes array*/
	printf("Child %d found free slot\n", walkno);
	printf("Child %d is putting his ID in slot\n", walkno);
	*pint = getpid();
	printf("Child %d ID is %d\n", walkno, *pint);
	printf("Child %d is not letting go of lock and leaving critcal section\n", walkno);

	/* release the mutex lock*/
	pthread_mutex_unlock(&mutex);
	

	/*Child sleeps for a random period of time*/
	printf("Child %d is now sleeping\n", walkno);
	sleep(rand() % 3 + 3);

	printf ("Child %d is now exiting. Putting 0 in slot\n", walkno);	
	*pint = 0;

	/*print out state of array*/
	pint=(int *)addr;
	printf( "child %d pint %d *pint %d\n",walkno, pint, *pint);
	for(i= 0; i < matsize; i++)
	{
		pint++;
		printf("%d\t", *pint);
	}
	printf("\n");

	return(0);
	} /* end of main*/                  