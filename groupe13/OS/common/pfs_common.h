#ifndef _PFS_COM_H_
#define _PFS_COM_H_

//////////////////////////////////////////////////////////////////////////////////////////
/// \file fs.h
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 27 décembre 2015
/// \brief Common part of the pfs syscalls
//////////////////////////////////////////////////////////////////////////////////////////
#include "types.h"

#define FILENAME_SIZE   32
#define MAX_BLOCKS	   	110
#define SECTOR_SIZE     512

typedef struct file_entry {

		char  name[FILENAME_SIZE];
		int   size;
		short blocks[MAX_BLOCKS];

} __attribute__((packed)) file_entry ;

typedef struct file_iterator_t {
	int32_t size_block;
	int32_t size_bitmap;
	int32_t size_file_entries;
	int32_t size_data_blocks;
	int nb_file_entries;
	file_entry current;
	int index;
	int first;
} __attribute__((packed)) file_iterator_t ;

typedef struct stat_t {
	char name[FILENAME_SIZE];
	int size;
} __attribute__((packed)) stat_t ;

#endif