// !!!
// 		Bitmap        : all bytess    != 0
// 		File entries  : bytes [0..11] != 0
//		File contents : nothing written in fs.img
// !!!

#include "fs.h"

#define SYNTAX_ERROR 1
#define IO_ERROR	 2
#define RANGE_ERROR  3

// File system structure
filesystem fs;
// File system image
char* img;

// Creates and inits a PFS structure 
int pfscreate(char* img_p, int block_size, int file_entries_num, int data_blocks) {
	
		int i, j;
	
		// Ouput image filename
		img = img_p;
	
		// Superblock init and copy
		strcpy(fs.sb.signature,    "PFSv0100");
		fs.sb.sectors_per_block  = (block_size / SECTOR_SIZE);
		fs.sb.bitmap_size        = 1;
		fs.sb.file_entry_size    = FILE_ENTRY_SIZE;
		fs.sb.file_entry_blocks  = file_entries_num;
		fs.sb.file_content_size  = data_blocks;
		
		// Bitmap init
		char* bitmap = malloc(sizeof(char) * (data_blocks / 8));
		memset(bitmap, 0, sizeof(char) * (data_blocks / 8));
		
		// File entries init
		file_entry* fe[file_entries_num];
		for (i = 0; i < file_entries_num; i++) {
			fe[i] = malloc(sizeof(file_entry));
			fe[i]->size = 0 ;
			for (j = 0; j < FILENAME_SIZE; j++) fe[i]->name[j]   = 0;
			for (j = 0; j < MAX_BLOCKS; j++)    fe[i]->blocks[j] = 0;
		}
		
		// File contents init
		char* fc = malloc(sizeof(char) * block_size * data_blocks);
		memset(fc, 0, (sizeof(char) * block_size * data_blocks));
		
		// Copy into structure
		fs.bitmap = (int*) &bitmap;
		fs.fc = (int*) &fc;
		fs.fe = (int*) &fe;

		return 0;
		
}

// Entry point
int main(int argc, char** argv) {
	
	// Syntax check
	if (argc < 5) {
		printf("Syntax error ! Usage : %s <output_image> <blocks_size> <file_entries> <data_blocks>\n", argv[0]);
		return SYNTAX_ERROR;	
	}
		
	// Image file creation
	img = argv[1];
	FILE * file = fopen(img, "wb");
	if (file == NULL) {
		printf("I/O error ! File %s could not be accessed.\n", img);
		return IO_ERROR;
	}
	
	// Arguments check
	int block_size = atoi(argv[2]);
	if ((block_size % SECTOR_SIZE) != 0) {
		printf("Range error ! Invalid block size (%d), must be a multiple of 512\n", block_size);
		return RANGE_ERROR;
	}
	int file_entries = atoi(argv[3]);
	if (file_entries <= 0) {
		printf("Range error ! Invalid file entries (%d), me be greater than 0.\n", file_entries);
		return RANGE_ERROR;
	}
	int data_blocks  = atoi(argv[4]);
	if (data_blocks <= 0) {
		printf("Range error ! Invalid data blocks (%d), me be greater than 0.\n", data_blocks);
		return RANGE_ERROR;
	}
	
	// Filesystem structure init
	pfscreate(img, block_size, file_entries, data_blocks);
	
	// Structure copy into image file
	fwrite(&fs.sb,     sizeof(struct superblock), 1,                          file);
	fwrite(&fs.bitmap, sizeof(char),              (data_blocks / 8),          file); 
	fwrite(&fs.fe,     sizeof(struct file_entry), file_entries,               file);
	fwrite(&fs.fc,     sizeof(char),              (data_blocks * block_size), file);
	
	// Close file
	fclose(file);
		
	// End of routine
	return 0;
	
}