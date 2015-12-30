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
	char* current_filename = NULL;
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
	char current_filename[32] = "";
	int offset = 0;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			printf("\nLecture du fichier: %s", current_filename);
			for (uint i = 0; i < MAX_BLOCKS; i++){
				if(it.current.blocks[i] == 0){
					break;
				}
				else{
					printf("\nNum. du Data Bloc en cours de lecture: %d", it.current.blocks[i]);
					printf("\nContenu du fichier: ");
					//Nos blocs font 2048 de taille, les secteurs 512, il faut lire 4 secteurs pour avoir un bloc
					for (uint j = 0; j < 4; j++){
						//(it.size_size_entries*it.nb_files_entries)/512 = nombres de secteurs pour les file entries
						//it.first = nombre de secteur pour sauter le superblock
						//la boucle for permet de lire 4 secteurs et le buffer les enregistre les un après les autres
						printf("\n%d", (it.size_file_entries*it.nb_file_entries)/512 + it.first + it.current.blocks[i] + 8 + j);
						read_sector((it.size_file_entries*it.nb_file_entries)/512 + it.first + it.current.blocks[i] + 8 + j, buf); //+ j *  SECTOR_SIZE);
					}
					printf("\n%s", buf);
				}
			}
			return 0;
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

int file_exists(char *filename){
	char* current_filename = NULL;
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
	int32_t sizebitmap;
	int32_t nbfileentries;
	int32_t sizefileentries;
	int32_t sizedatablocks;
	
	memcpy(&sizeblock,sb+8,sizeof(int32_t));
	memcpy(&sizebitmap,sb+12,sizeof(int32_t));
	memcpy(&nbfileentries,sb+16,sizeof(int32_t));
	memcpy(&sizefileentries,sb+20,sizeof(int32_t));
	memcpy(&sizedatablocks,sb+24,sizeof(int32_t));
	
	it.size_block 		 = sizeblock;
	it.size_bitmap 	 	 = sizebitmap;
	it.size_file_entries = nbfileentries;
	it.size_data_blocks  = sizefileentries;
	it.nb_file_entries   = nbfileentries;
	it.index = -1;
	it.first = sizeblock+(sizebitmap*sizeblock);
	
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
int file_next(char *filename, file_iterator_t *it){
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
