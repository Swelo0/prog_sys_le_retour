#include "fs.h"

// List files stored in the filesystem
int pfslist(char* img) {
	
	// Open filesystem image
	FILE* img_file;
	if (!(img_file = fopen(img, "r+"))) {
		printf("I/O error ! File %s could not be accessed.\n", img);
		return IO_ERROR;
	}

	// Read image and extract Superblock infos (28 bytes)
	superblock sb;
	fread(&sb, sizeof(char), sizeof(superblock), img_file);
	int block_size = sb.sectors_per_block * SECTOR_SIZE;
	
	// Block type definition
	typedef char block[block_size];
	
	// Rest of the read structure
	file_entry fe[sb.file_entry_nb];
	block bitmap;
	
	// Read the rest of the file until the file entries
	fread(&sb + sizeof(superblock), sizeof(char),       block_size - sizeof(superblock), img_file); 
	fread(&bitmap,                  sizeof(char),       block_size,                      img_file);
	fread(&fe,                      sizeof(file_entry), sb.file_entry_nb,                img_file);
	
	// Parse file entries
	printf("Entry  File                  Size\n");
	for (int i = 0; i < sb.file_entry_nb; i++)
		if (fe[i].name[0] != '\0')
			printf("[%3d]  %s           %4d\n", i, fe[i].name, fe[i].size);
	
	// Close file
	fclose(img_file);
	
	// End of routine
	return NO_ERROR;
	
}

int main(int argc, char** argv) {
	
	// Arguments check
	if (argc < 2) {
		printf("Syntax Error ! Usage : %s <filesystem_image>\n", argv[0]);
		return SYNTAX_ERROR;
	}
	
	// List files
	return pfslist(argv[1]);
	
}