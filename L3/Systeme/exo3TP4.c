#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

sem_t mutex;
sem_t RDV;
int N;
int nb_present;
void * rendez_vous (void *arg)
{
	int *rang=(int*) arg;
	printf("Thread %d (id = %d), je fais un certain traitement\n",*rang,(int)pthread_self());

	if (sem_wait(&mutex)!=0)
	{
		perror("sem_wait mutex\n");
		exit(99);
	}

	nb_present--;
	
	printf("thread %d, j'arrive au point de rendez-vous\n",*rang);
	
	//Dernier à passer
	if (!nb_present)
	{
		for (int i=0;i<N;i++)
		{
			if (sem_post(&RDV)!=0)
			{
				perror("sem post rdv\n");
				exit(99);
			}
		}
	}

		if (sem_post(&mutex)!=0)
		{
			perror("sem_post mutex\n");
			exit(99);
		}
		if (sem_wait(&RDV)!=0)
		{
			perror("sem_wait RDV\n");
			exit(99);
		}
		printf("thread %d, j'ai passé le point de RDV\n",*rang);

		printf("thread %d, je continue\n",*rang);
	
	pthread_exit(0);
}


int main (int argc, char * argv[])
{

	if (argc!=2)
	{
		printf("erreur sur le nombre de paramètre \n Usage : ./exo4 Nombre de threads\n");
		exit(99);
	}

	if (sem_init(&mutex,0,1)!=0)
	{
		perror("mutex");
		return (-1);
	}
	if (sem_init(&RDV,0,0)!=0)
	{
		perror("RDV");
		return(-1);
	}

	N=atoi(argv[1]);
	nb_present=N;

	pthread_attr_t attribut;
	pthread_t thread[N];
	int rang[N];

	for (int i=0;i<N;i++)
	{
		rang[i]=i;
		pthread_attr_init(&attribut);
		pthread_attr_setscope(&attribut, PTHREAD_SCOPE_SYSTEM);
		if (pthread_create(&thread[i],&attribut,rendez_vous,&rang[i])!=0)
		{
			perror("creation thread");
			exit(-1);
		}
	}

	for (int i=0;i<N;i++)
	{
		if (pthread_join(thread[i],NULL)!=0)
		{
			perror("pthread_joind erreur");
			exit(2);
		}
	}

	sem_destroy(&RDV);
	sem_destroy(&mutex);

}