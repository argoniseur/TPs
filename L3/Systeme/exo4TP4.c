#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

#define TMAX 100
#define Consommateur 0
#define Producteur 1


sem_t CritiqueL;
sem_t tab[2];
sem_t depot[2];


typedef struct Message_s { 
	char infoChar[50];
	int type;
} Message;

typedef struct Info_s {
	int id;
	Message msg;
} Info;

Message Buffer[TMAX];

int ICV,ICP;
int N;
int nbDepot, nbRetrait;


int init()
{
	ICV=0;
	ICP=0;
	if (sem_init(&tab[Consommateur],0,0)!=0)
	{
		perror("Consommateur");
		return (-1);
	}
	if (sem_init(&tab[Producteur],0,N))
	{
		perror("Producteur");
		return(-1);
	}

	if (sem_init(&depot[0],0,1)!=0)
	{
		perror("Dépot de type 0");
		return(-1);
	}
	if (sem_init(&depot[1],0,0)!=0)
	{
		perror("Dépot de type 1");
		return(-1);
	}

	if (sem_init(&CritiqueL,0,1)!=0)
	{
		perror("critiqueL");
		return(-1);
	}

	return 0;
}

void ecrireMessage(Message *m, int id, int nb)
{

	Buffer[ICV].type=m->type;
	sprintf(m->infoChar,"Bonjour %d de %d",nb,id);
	strcpy(Buffer[ICV].infoChar,m->infoChar);
	ICV=(ICV+1)%N;
}

void * produire(void *arg)
{
	Info *info=(Info *)arg;
	for (int i=0;i<nbDepot;i++)
	{
		if (sem_wait(&depot[info->msg.type])==-1)
		{
		printf("erreur sem_wait\n");
		exit(99);
		}
		if(sem_wait(&tab[Producteur])==-1)
		{
			printf("erreur sem_wait\n");
			exit(99);
		}
		printf("Prod %d : Demande depot %d\n",info->id,i);
		ecrireMessage(&info->msg,info->id,i);
		printf("Prod %d : Message depose = [%s] de type %d\n",info->id,info->msg.infoChar,info->msg.type);
		if (sem_post(&tab[Consommateur])==-1)
		{
			printf("erreur sem_post\n");
			exit(99);
		}
		if (sem_post(&depot[(info->msg.type+1)%2])==-1)
		{
			printf("erreur sem_post\n");
			exit(99);
		}
	}

	pthread_exit(0);
}

void lireMessage (Message *m)
{
	m->type=Buffer[ICP].type;
	strcpy(m->infoChar,Buffer[ICP].infoChar);
	ICP=(ICP+1)%N;
}

void * consommer (void *arg)
{
	Info *info=(Info *)arg;
	for (int i=0;i<nbRetrait;i++)
	{
		if (sem_wait(&tab[Consommateur])==-1)
		{
			printf("erreur sem_wait\n");
			exit(99);
		}
		if (sem_wait(&CritiqueL)==-1)
		{
			printf("erreur sem_wait\n");
			exit(99);
		}
		printf("Conso %d : Demande retrait %d\n",info->id,i);
		lireMessage(&info->msg);
		printf("Conso %d : Message lu = [%s] de type %d\n",info->id,info->msg.infoChar,info->msg.type);
		if (sem_post(&CritiqueL)==-1)
		{
			printf("erreur sem_post\n");
			exit(99);
		}
		if (sem_post(&tab[Producteur])==-1)
		{
			printf("erreur sem_post\n");
			exit(99);
		}
	}	

	pthread_exit(0);
}



int main (int argc, char * argv[])
{

	if (argc!=6)
	{
		printf("Erreur sur les paramètres."
			"\nUsage : nbProducteurs nbMessagesDéposés nbConsommateurs nbMessagesRetirés nbCaseBuffer");
		exit(99);
	}

	N=atoi(argv[5]);

	if (init()!=0)
	{
		printf("Erreur sur l'initialisation des semaphores\n");
		exit(99);
	}

	nbRetrait=atoi(argv[4]);
	nbDepot=atoi(argv[2]);

	Info rangProd[TMAX];
	Info rangConso[TMAX];

    pthread_attr_t attribut;
	int nbProd=atoi(argv[1]);
	pthread_t threadProd[nbProd];
    //Créationd des threads Producteurs
	for (int i=0;i<nbProd;i++)
	{
		rangProd[i].id=i;
		rangProd[i].msg.type=i%2;
		pthread_attr_init(&attribut);
		pthread_attr_setscope(&attribut, PTHREAD_SCOPE_SYSTEM);
		if (pthread_create(&threadProd[i],&attribut,produire,&rangProd[i])!=0)
		{
			perror("creation thread");
			exit(1);
		}
	}


	int nbConso=atoi(argv[2]);
	pthread_t threadConso[nbConso];
	//Créationd des threads Consommateurs
	for (int i=0;i<nbConso;i++)
	{
		rangConso[i].id=i;
		pthread_attr_init(&attribut);
		pthread_attr_setscope(&attribut, PTHREAD_SCOPE_SYSTEM);
		if (pthread_create(&threadConso[i],&attribut,consommer,&rangConso[i])!=0)
		{
			perror("creation thread");
			exit(1);
		}
	}

	//fin des threadProd
	for (int i=0;i<nbProd;i++)
	{
		if (pthread_join(threadProd[i],NULL)!=0)
		{
			perror("pthread_joind erreur");
			exit(2);
		}
	}

	//fin des threadConso
	for (int i=0;i<nbConso;i++)
	{
		if (pthread_join(threadConso[i],NULL)!=0)
		{
			perror("pthread_joind erreur");
			exit(2);
		}
	}
	sem_destroy(&tab[Consommateur]);
	sem_destroy(&tab[Producteur]);
	sem_destroy(&CritiqueL);
	sem_destroy(&depot[0]);
	sem_destroy(&depot[1]);

	return 0;
}