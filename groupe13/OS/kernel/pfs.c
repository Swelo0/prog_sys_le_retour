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

int file_stat(char* filename, stat_t* stat) {
	
	char* current_filename = NULL;
	file_iterator_t it = file_iterator();
	
	// Iterate
	while (file_next(current_filename, &it))
		// Compare names
		if  (!strcmp(current_filename, filename)) {
			// Stat structure
			stat->size = it.current.size;
			for (int i = 0; i < FILENAME_SIZE; i++)
				if (stat->name[i]) stat->name[i] = it.current.name[i];
				else break;
				
			return 0;
			
		}	
		
	return -1;
	
}

int file_read(char *filename, void *buf){
	char* current_filename = NULL;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_remove(char *filename){
	char* current_filename = NULL;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_exists(char *filename) {
	
	char* current_filename = NULL;
	file_iterator_t it = file_iterator();
	
	// Iterate
	while (file_next(current_filename, &it))
		// Compare names
		if (!strcmp(current_filename, filename))
			return 1;
		
	return 0;
	
}

/*
 * Renvoie un itérateur permettant ensuite d'itérer sur tous les fic*hiers du système de fichiers
 * grâce à la fonction file_next. Après appel à cette fonction, l'itérateur pointe sur le
 * premier fichier (s'il y en a au moins un) du système de fichiers.
 */
file_iterator_t file_iterator(){
	char sb[512];
	//char sector[512];
	//int bitemap_sector;
	//int sector_fe;
	
	file_iterator_t it;
	/*
	 * for(int i = 0;i<512;i++)
	 *	sb[i] = '\0';*/
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
	
	it.nb_file_entries = nbfileentries;
	it.index = -1;
	it.first = sizeblock+(sizebitemap*sizeblock);
	
	return it;
}

/*
 * Cette fonc*tion permet d'itérer sur les fichiers du système de fichiers. L'appel à file_next
 * renvoie 1 si l'itérateur it pointe sur le fichier courant. Dans ce cas, le nom du fichier
 * courant est copié dans filename. Si l'itérateur a déjà itéré sur tous les fichiers, alors la
 * fonction renvoie 0 et rien n'est copié dans filename. A noter qu'il est obligatoire
 * d'initialiser l'itérateur it avec la fonction file_iterator avant d'appeler la fonction
 * file_next.
 */
int file_next(char* filename, file_iterator_t* it){
	char sector[512];
	int offset = 0;

	while(1) {
		if(++(*it).index >= (*it).nb_file_entries)
			return 0;
		read_sector((*it).first+((*it).index/2),sector);
		if ((*it).index%2)
			offset = 256;
		if(sector[offset] != '\0')
			break;
	}
	memcpy(&(*it).current,sector+offset,256);
	int i = 0;
	while(sector[offset+i] != '\0') {
		*(filename+i) = sector[offset+i];
		i++;
	}
	*(filename+i) = '\0';
	return 1;
}