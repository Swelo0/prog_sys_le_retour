/*------------------------------------------------------------------------------
 *  Remarque : 	Le data block 0 n'est pas utilisé, car les bloc
 *				référencés dans les file entries sont initialisés à zéro
 *				et servent de valeur de test pour vérifier si un bloc
 *				est défini ou pas. Par conséquent, si le paramètre 
 *				data block passé à la création de l'image vaut n, il y
 *				aura en fait (n - 1) blocs utilisables pour les file contents.
 * ----------------------------------------------------------------------------*/

#ifndef H_FS_
#define H_FS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Filesystem constants
#define SECTOR_SIZE          512
#define SIGNATURE_SIZE       8
#define FILENAME_SIZE	     32
#define FILE_ENTRY_SIZE      256
#define MAX_BLOCKS	     110	// 256 - (32 + 4) = 220 bytes for blocks indexing = 110 indexes

// General error constants
#define NO_ERROR             0
#define SYNTAX_ERROR         1
#define IO_ERROR	     2
#define RANGE_ERROR          3
// Specific error constants
#define FULL_FE_ERROR        4
#define FULL_BITMAP_ERROR    5
#define FILE_NOT_FOUND_ERROR 6

// Zero constant (1 byte)
const char zero = 0;

typedef struct file_entry {

		char  name[FILENAME_SIZE];
		int   size;
		short blocks[MAX_BLOCKS];

} __attribute__((packed)) file_entry ;

typedef struct superblock {

		char signature[SIGNATURE_SIZE]; 
		int  sectors_per_block;
		int  bitmap_size;
		int  file_entry_nb;
		int  file_entry_size;
		int  data_blocks;

} __attribute__((packed)) superblock;

#endif
