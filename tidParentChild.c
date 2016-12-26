/* mod 5 8 99 for shuffled start compile with -lm flag */
#include	<sys/types.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<stdio.h>
#include	<unistd.h>
#include 	<stdlib.h>
#include	<pthread.h>
#define	KEY 75
#define KFOUR  4096
int 		shmid; 	/*for external cleanup routine*/
int		matsize;
int 		*pint;
typedef struct arguments {
	char thisStart[10];
	char thisWalkno[10];
	char thisMatsize[10]; 
	char thisShmkey[10];
}arguments;

arguments tid_arg;

void *tidchild(void *child);

main(int argc, char *argv[])
{	
	int i, j, k, m, n, shmkey, offset;
	int status = 0;
	char *addr;
	int  walkers, walktid, next, start;
	pthread_t tid;
	
	pthread_attr_t attr;

	/* start processing with test of args*/
	if (argc < 3)
	{
		perror("Not enough parameters:  basename, matsize, start");
		exit(1);
	}
	
	/* get parms*/
	matsize = atoi(argv[1]);
	start   = atoi(argv[2]);
	shmkey  = KEY;

	/*set up shared memory*/
	shmid = shmget(shmkey, KFOUR, 0777| IPC_CREAT);
	addr  = shmat(shmid,0,0);
	printf("start of memory 0x%x\n", addr);
	pint  = (int *)addr;
	printf("loading  shm \n");
	for(i=0; i < matsize; i++)
	{
		pint++;
		*pint = 0;
	}

	pint = (int *)addr;
        printf("verifying  shm \n");
        for (i = 0; i < matsize; i++) 
	{	
                pint++;
		printf("%d\t %d\t\n", pint, *pint);
	}
	
	/* Putting values in tid_arg*/
	sprintf(tid_arg.thisWalkno,  "%d", (m + 1));  
	sprintf(tid_arg.thisStart,   "%d", start);  
	sprintf(tid_arg.thisMatsize, "%d", matsize);  
	sprintf(tid_arg.thisShmkey,  "%d", shmkey);

	/* now create walkers*/
	int tid_child[matsize];
	for(m = 0; m < matsize; ++m)
	{	
		printf("started walker %d\t\n", m);

		pthread_attr_init(&attr);
		tid_child[m] = m;
		/* create the thread */
		if (pthread_create(&tid, &attr, tidchild, (void *)(tid_child + m)) != 0) {
			printf("Could not execute child program\n");
			exit(1);
		}


	}/* end create walkers loop*/

	/* now signal to start*/
	sleep(5); /* let them get started*/
	pint=(int *)addr;
	*pint=atoi(argv[2]); /* restore true start*/
	printf( "Unblocking\n");

	/*wait for children to complete then terminate*/
 	pthread_join(tid,NULL);
        printf("all children completed\n");
	printf("Bryan Cantos ID: %d\n", 23023992);
} /* end of main*/

void *tidchild(void *child) {

	int* walkno = (int*)child;
	int i;
	char *addr;
	srand(time(NULL));
	int start, shmid, matsize, shmkey;
	pthread_mutex_t mutex;

	/*creates the mutex lock*/
	pthread_mutex_init(&mutex, NULL);

	/* get parms*/ 
	start   = atoi(tid_arg.thisStart);
	matsize = atoi(tid_arg.thisMatsize);
	shmkey  = atoi(tid_arg.thisShmkey); 

	printf("walkno = %d\n", *walkno);
	printf("start = %d\n", start);
	printf("matsize = %d\n", matsize);
	printf("shmkey = %d\n", shmkey);

	/*debug*/
	printf("child %d start %d size of list %d memory key %d \n", *walkno, start, matsize,shmkey);

	/*set up shared memory*/
	shmid = shmget(shmkey, KFOUR, 0777);
	addr = shmat(shmid,0,0);

	/*wait for block on the first memory location to be cleared*/
	pint    = (int *)addr;
        while(*pint > start)
		pint=(int *)addr;

	/*acquires the mutext lock*/
	pthread_mutex_lock(&mutex);
	printf("Child %d acquires the mutex lock and is entering critcal section\n", *walkno);

	/*enters the critical section*/

	/* Writes into Array*/
	printf("Child %d is looking for free slot\n", *walkno);
	if(*pint != 0)
	{
		printf("Slot is taken, Child %d looking for a new slot\n", *walkno);
		pint++;
		while(*pint != 0)
		{
			printf("Child %d is still looking for a free slot\n", *walkno);
			pint++;
		}
	}
	/*Child takes array*/
	printf("Child %d found free slot\n", *walkno);
	printf("Child %d is putting his ID in slot\n", *walkno);
	*pint = pthread_self();
	printf("Child %d ID is %d\n", *walkno, *pint);
	printf("Child %d is now letting go of lock and leaving critcal section\n", *walkno);

	/* release the mutex lock*/
	pthread_mutex_unlock(&mutex);

	/*Child sleeps for a random period of time*/
	printf("Child %d is now sleeping\n", *walkno);
	sleep(rand() % 10);

	printf ("Child %d is now exiting. Putting 0 in slot\n", *walkno);	
	*pint = 0;

	/*print out state of array*/
	pint=(int *)addr;
	printf( "child %d pint %d *pint %d\n",*walkno, pint, *pint);
	for(i= 0; i < matsize; i++)
	{
		pint++;
		printf("%d\t", *pint);
	}
	printf("\n");
	pthread_exit(0);
}

