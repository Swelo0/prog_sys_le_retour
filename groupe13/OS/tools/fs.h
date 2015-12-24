/*----------------------------------------------------------------------
 * 					Système de fichier (version linux)
 * 	Fonctionnalité :
 * 		-pfscreate: Initialise notre système de fichier.
 * 		-pfsadd   : Permet d'ajouter un fichier au système,
 * 					on chercher une entrée libre dans le file entry pour
 * 					notre fichier et on l'écris en blocks dans le file 
 * 					content, le bitmap est mis à jour en parrallèle.
 * 
 * 		-pfsdel   : Met simplement à 0 le premier caractère du file 
 * 					entry de notre fichier ainsi que les bitmap qui le
 * 					concerne
 * 
 *  Remarques :  /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ 
 * 
 * 				Le premier bloc du content (qui à la valeur 0 en c)
 * 				est considéré comme le 1 ici. Ainsi si dans notre file
 * 				entry, notre fichier est dans le block [1], en réalité
 * 				c'est le block [0] en mémoire.
 * 				exemple :
 * 						fileEntry[1].blocks[1] == fileContent[0]
 * 
 * -------------------------------------------------------------------*/

#ifndef H_FS_
#define H_FS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR_SIZE     512
#define SIGNATURE_SIZE  8
#define FILENAME_SIZE	32
#define FILE_ENTRY_SIZE 256	// Each entry takes 256 bytes
#define MAX_BLOCKS	 	110	// 256 - (32 + 4) = 220 bytes for blocks indexing

// Block size = sectors_per_block * SECTOR_SIZE
// File_entry_blocks = number of file entries
// File_content_size = number of data blocks

typedef struct file_entry {

		char  name[FILENAME_SIZE];
		int   size;
		short blocks[MAX_BLOCKS];

} file_entry;

// attribute(packed) pour empêcher le compilateur de faire du panning
typedef struct filesystem {

	// Superblock = 28 bytes
	struct superblock {

		char signature[SIGNATURE_SIZE]; 
		int  sectors_per_block;
		int  bitmap_size;
		int  file_entry_size;
		int  file_entry_blocks;
		int  file_content_size;

	} sb __attribute__((packed));

	int* bitmap;

	int* fe; //  __attribute__((packed));

	int* fc;
		
} filesystem;

int  pfscreate(char* img_p, int block_size, int file_entries_num, int data_blocks);
void pfslist(filesystem *fs);
void pfsadd (filesystem *fs, char file[]);
void pfsdel (filesystem *fs, char file[]);

#endif
