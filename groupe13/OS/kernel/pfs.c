//////////////////////////////////////////////////////////////////////////////////////////
/// \file fs.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 27 décembre 2015
/// \brief Implementation of the kernel file system handling functions
//////////////////////////////////////////////////////////////////////////////////////////

#include "pfs.h"

int strcmp (const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}

int file_stat(char *filename, stat_t *stat){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			//on utilise l'itérateur pour chopper et renvoyer la taille du fichier dans la structure
			//stat->size = it->file_entrie->size ou un truc du genre	
		}	
	}
	return -1;
}

int file_read(char *filename, void *buf){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_remove(char *filename){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_exists(char *filename){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			return 1;
		}	
	}
	return 0;
}

/*
 Renvoie un itérateur permettant ensuite d'itérer sur tous les fic*hiers du système de fichiers
 grâce à la fonction file_next. Après appel à cette fonction, l'itérateur pointe sur le
 premier fichier (s'il y en a au moins un) du système de fichiers.
*/
file_iterator_t file_iterator(){
	char sb[512];
	char sector[512];
	/*
	for(int i = 0;i<512;i++)
		sb[i] = '\0';*/
	read_sector(0,sb);
	
	int32_t sizeblock;
	int32_t sizebitemap;
	int32_t nbfileentries;
	int32_t sizefileentries;
	int32_t sizedatablocks;
	
	memcpy(&sizeblock,sb+8,sizeof(int32_t));
	memcpy(&sizebitemap,sb+12,sizeof(int32_t));
	memcpy(&nbfileentries,sb+16,sizeof(int32_t));
	memcpy(&sizefileentries,sb+20,sizeof(int32_t));
	memcpy(&sizedatablocks,sb+24,sizeof(int32_t));
	
	read_sector(sizeblock,sector);
	
	printf("taille d'un block ");
	printf("%d",sizeblock);

	printf("\n sizebitemap ");
	printf("%d",sizebitemap);
	
	printf("\n nb file entries ");
	printf("%d",nbfileentries);
	
	printf("\n size file entries ");
	printf("%d",sizefileentries);
	
	printf("\n size data blocks ");
	printf("%d",sizedatablocks);
	/*
	for(int i = 8;i<12;i++){
		//printf("%d",i);
		printf("%d",sb[i]);
	}*/
}


/*
 Cette fonc*tion permet d'itérer sur les fichiers du système de fichiers. L'appel à file_next
 renvoie 1 si l'itérateur it pointe sur le fichier courant. Dans ce cas, le nom du fichier
 courant est copié dans filename. Si l'itérateur a déjà itéré sur tous les fichiers, alors la
 fonction renvoie 0 et rien n'est copié dans filename. A noter qu'il est obligatoire
 d'initialiser l'itérateur it avec la fonction file_iterator avant d'appeler la fonction
 file_next.
 */
int file_next(char *filename, file_iterator_t *it){

	return 0;
}