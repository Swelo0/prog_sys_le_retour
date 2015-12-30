//////////////////////////////////////////////////////////////////////////////////////////
/// \file fs.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 27 décembre 2015
/// \brief Implementation of the kernel file system handling functions
//////////////////////////////////////////////////////////////////////////////////////////

#include "pfs.h"

int strcmp (const char* s1, const char* s2) {
    while(*s1 && (*s1==*s2)) s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
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

int file_remove(char* filename) {
	
	int offset = 0;
	char* current_filename = NULL;
	file_iterator_t it = file_iterator();
	char sector_bitmap[SECTOR_SIZE*it.size_block];
	char sector_fe[SECTOR_SIZE];
	
	// Iterate
	while (file_next(current_filename, &it)) {
		// Compare
		if (!strcmp(current_filename, filename)) {
			//On test si notre file entry est dans la première
			//ou deuxième partie du secteur [256|256] = 1 secteur de 512
			if (it.index % 2)
				offset = 256;
			//on met le premier caractère de la FE à \0
			read_sector(it.first + (it.index / 2), sector_fe);
			sector_fe[offset] = '\0';
			write_sector(it.first + (it.index / 2), sector_fe);
			//Parcrous du bitmap et réecriture.
			for (int i = 0; i < it.size_block; i++)
				read_sector(it.size_block,sector_bitmap + SECTOR_SIZE * i);
			
			int j = 0;
			//les 36 premiers bytes sont filename + data size
			while (sector_fe[36+j]) {
				sector_bitmap[(uint16_t)sector_fe[36+j]] = '\0';
				j+=2; //data index = 2 bytes
			}
			for (int i = 0;i < it.size_block; i++)
				write_sector(it.size_block, sector_bitmap + SECTOR_SIZE * i);
		}	
	}
	
	return -1;
	
}

/*
 * Vérifie qu'un fichier existe et renvoie l'équivalent d'un booléen
 */
int file_exists(char* filename) {
	
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
	
	char sb[SECTOR_SIZE];
	
	file_iterator_t it;
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
	it.index             = -1;
	it.first             = sizeblock + (sizebitmap * sizeblock);
	
	return it;
	
}

/*
 * Cette fonction permet d'itérer sur les fichiers du système de fichiers. L'appel à file_next
 * renvoie 1 si l'itérateur it pointe sur le fichier courant. Dans ce cas, le nom du fichier
 * courant est copié dans filename. Si l'itérateur a déjà itéré sur tous les fichiers, alors la
 * fonction renvoie 0 et rien n'est copié dans filename. A noter qu'il est obligatoire
 * d'initialiser l'itérateur it avec la fonction file_iterator avant d'appeler la fonction
 * file_next.
 */
int file_next(char *filename, file_iterator_t *it){
	
	char sector[SECTOR_SIZE];
	int offset = 0;
	// tant qu on a pas d'entrée fichier
	while(1) {
		
		if (++(*it).index >= (*it).nb_file_entries)
			return 0;
		
		read_sector((*it).first + ((*it).index / 2), sector);
		if ((*it).index % 2)
			offset = 256;
		if (sector[offset])
			break;
	}
	//maj de l'entrée courante
	memcpy(&(*it).current, sector + offset, 256);
 	//copie du nom
	int i = 0;
	while (sector[offset + i]) {
		*(filename + i) = sector[offset + i];
		i++;
	}
	*(filename+i) = '\0';
	
	return 1;
	
}