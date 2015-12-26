#include "fs.h"

// File handlers
FILE* img_file;

// Delete file from filesystem image
int pfsdel(char* img, char* input) {

	// Open files
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
	
	// Rest of the filesystem structure
	block bitmap, fc[sb.data_blocks];
	file_entry fe[sb.file_entry_nb];
	
	// Read the rest of the file
	fread(&sb + sizeof(superblock), sizeof(char),       block_size - sizeof(superblock), img_file); 
	fread(&bitmap,                  sizeof(char),       block_size,                      img_file);
	fread(&fe,                      sizeof(file_entry), sb.file_entry_nb,                img_file);
	fread(&fc,                      block_size,         sb.data_blocks,                  img_file);
	
	// Look for the specified file entry
	int entry = -1;
	for (int i = 0; i < sb.file_entry_nb; i++)
		if (!strcmp(fe[++entry].name, input)) {
			entry = i;
			break;
		}
		else printf("%s != %s\n", fe[entry].name, input);
	
	// Entry update
	int currentBlock = -1;
	int deleteBlock  = -1;
	int offset, blockNum;
	if (entry >= 0) {
	
		printf("File entry id : %d\n", entry);
	
		while (fe[entry].blocks[++currentBlock] != 0) {
			
			deleteBlock = fe[entry].blocks[currentBlock];
			offset      = (deleteBlock / 8);
			blockNum    = (deleteBlock % 8);
			// Zero bit corresponding to entry in bitmap
			*(bitmap + offset) &= (!(1 << blockNum));
			// Zero corresponding block in file content
			memset(fc[offset * 8 + blockNum], 0, block_size);
			// Zero corresponding file entry 
			memset(&fe[entry], 0, sb.file_entry_size);
			
			printf("Data Block[%d] : %d\n", currentBlock, deleteBlock);
			
		}
			
		memset(&fe[entry], 0, sizeof(char) * FILENAME_SIZE + sizeof(int));
		int b = -1;
		while ((fe[entry].blocks[++b] != 0) && (b < MAX_BLOCKS)) fe[entry].blocks[b] = 0;
		
	}
	else {
		printf("Error ! File %s not found.\n", input);
		return FILE_NOT_FOUND_ERROR;
	}
	
	// Display
	printf("Bitmap        :\n");
	for (int i = 0; i < (sb.data_blocks / 8); i++) {
		printf("%2d | ", i);
		for (int j = 0; j < 8; j++) {
			if (*(bitmap+i) & (1 << j)) printf("1 ");
			else printf("0 ");
		}
		printf("\n");
	}
	
	return NO_ERROR;
	
}

int main(int argc, char** argv) {
	
	return pfsdel(argv[1], argv[2]);
	
}