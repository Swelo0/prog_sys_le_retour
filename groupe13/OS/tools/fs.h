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

// Filesystem constants
#define SECTOR_SIZE       512
#define SIGNATURE_SIZE    8
#define FILENAME_SIZE	  32
#define FILE_ENTRY_SIZE   256
#define MAX_BLOCKS	 	  110	// 256 - (32 + 4) = 220 bytes for blocks indexing = 110 indexes

// General error constants
#define NO_ERROR          0
#define SYNTAX_ERROR      1
#define IO_ERROR	      2
#define RANGE_ERROR       3
// Specific error constants
#define FULL_FE_ERROR     4
#define FULL_BITMAP_ERROR 5

// Zero constant (1 byte)
const char zero = 0;

typedef struct file_entry {

		char  name[FILENAME_SIZE];
		int   size;
		short blocks[MAX_BLOCKS];

} file_entry __attribute__((packed));

typedef struct superblock {

		char signature[SIGNATURE_SIZE]; 
		int  sectors_per_block;
		int  bitmap_size;
		int  file_entry_nb;
		int  file_entry_size;
		int  data_blocks;

} superblock __attribute__((packed));

#endif