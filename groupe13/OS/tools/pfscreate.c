#include "fs.h"

// File system image
char* img;
// File system image handler
FILE* file;

// Writes a PFS structure into the specified image file
int pfscreate(char* img_p, int block_size, int file_entries_num, int data_blocks) {
	
		// Superblock init
		superblock sb;
		strcpy(sb.signature,   "PFSv0100");
		sb.sectors_per_block = (block_size / SECTOR_SIZE);
		sb.bitmap_size       = 1;
		sb.file_entry_size   = FILE_ENTRY_SIZE;
		sb.file_entry_nb     = file_entries_num;
		sb.data_blocks       = data_blocks;
		
		// Open image file
		if (!(file = fopen(img, "wb"))) {
			printf("I/O error ! File %s could not be accessed.\n", img);
			return IO_ERROR;
		}
		
		// Superblock (1 block)
		fwrite(&sb, sizeof(superblock), 1, file);
		for (int i = 0; i < (block_size - sizeof(superblock)); i++)
			fwrite(&zero, sizeof(char), 1, file);
		// Bitmap (1 block minimum)
		for (int i = 0; i < (data_blocks / 8); i++)
			fwrite(&zero, sizeof(char), 1, file);
		for (int i = (data_blocks / 8); i < block_size; i++)
			fwrite(&zero, sizeof(char), 1, file);
		// File entries
		for (int i = 0; i < (file_entries_num * sb.file_entry_size); i++)
			fwrite(&zero, sizeof(char), 1, file);
		// Data blocks
		for (int i = 0; i < (data_blocks * block_size); i++)
			fwrite(&zero, sizeof(char), 1, file);
		
		// End of routine
		fclose(file);
		return NO_ERROR;
		
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
	return pfscreate(img, block_size, file_entries, data_blocks);
	
}