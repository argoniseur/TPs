#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char * argv[])
{
	int i;
	struct stat fich;

	if (argc == 1)
	{
		DIR* dir=malloc(sizeof(DIR*));
		struct dirent *pdir;
		if((dir = opendir(".")) == NULL)
		{
			printf("Erreur lors de l'ouverture du repertoire");
		}
		else
		{
			while ((pdir = readdir(dir)) != NULL)
			{
				if(stat(pdir->d_name, &fich) == -1)
				{
					printf("Erreur lors de la recuperation des informations\n");
				}
				if (S_ISDIR(fich.st_mode))
				{
					printf("%-20s :repertoire %8d octets %s", pdir->d_name, (int)fich.st_size, ctime(&fich.st_mtime));	
				}
				else
				{
					printf("%-20s :fichier %11d octets %s", pdir->d_name, (int)fich.st_size, ctime(&fich.st_mtime));
				}
			}
		}
		free(dir);
	}
	else
	{
		for (i=1;i<argc;i++)
		{
			if(stat(argv[i], &fich) == -1)
			{
				printf("%d", i);
				printf("Erreur lors de la recuperation des informations\n");
			}
			if (S_ISDIR(fich.st_mode))
			{
				printf("%-20s :repertoire %8d octets %s", argv[i], (int)fich.st_size, ctime(&fich.st_mtime));
			}
			else
			{
				printf("%-20s :fichier %11d octets %s", argv[i], (int)fich.st_size, ctime(&fich.st_mtime));
			}
		}
	}	
	return 0;
}
