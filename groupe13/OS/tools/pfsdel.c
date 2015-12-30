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
	int ok    = 0;
	for (int i = 0; i < sb.file_entry_nb; i++)
		if ((strcmp(fe[++entry].name, input)) == 0) {
			entry = i;
			ok = 1;
			break;
		}
	
	// Entry update
	int currentBlock = -1;
	int deleteBlock  = -1;
	int offset, blockNum;
	if ((ok) && (entry >= 0)) {
	
		printf("File entry id : %d\n", entry);
	
		while (fe[entry].blocks[++currentBlock] != 0) {
			
			deleteBlock = fe[entry].blocks[currentBlock];
			offset      = (deleteBlock / 8);
			blockNum    = (deleteBlock % 8);
			// Zero bit corresponding to entry in bitmap
			*(bitmap + offset) &= (!(1 << blockNum));
			// Zero corresponding block in file content
			memset(fc[offset * 8 + blockNum], 0, block_size);
			
			printf("Data Block[%d] : %d\n", currentBlock, deleteBlock);
			
		}
		
		// Zero corresponding file entry 
		memset(&fe[entry], 0, sb.file_entry_size);
			
	}
	else if (entry >= 0) {
		printf("Error ! File %s not found.\n", input);
		return FILE_NOT_FOUND_ERROR;
	}
	
	/* Display
	printf("Bitmap        :\n");
	for (int i = 0; i < (sb.data_blocks / 8); i++) {
		printf("%2d | ", i);
		for (int j = 0; j < 8; j++) {
			if (*(bitmap+i) & (1 << j)) printf("1 ");
			else printf("0 ");
		}
		printf("\n");
	}
	*/
	
	// Overwrite existing image with filesystem structure
	fclose(img_file);
	if (!(img_file = fopen(img, "w+"))) {
		printf("I/O error ! File %s could not be accessed.\n", img);
		return IO_ERROR;
	}
	fwrite(&sb,     sizeof(char),       block_size,       img_file);
	fwrite(&bitmap, sizeof(char),       block_size,       img_file);
	fwrite(&fe,     sb.file_entry_size, sb.file_entry_nb, img_file);
	fwrite(&fc,     block_size,         sb.data_blocks,   img_file);
	
	// Close files
	fclose(img_file);
	
	return NO_ERROR;
	
}

// Entry point
int main(int argc, char** argv) {
	
	// Arguments check
	if (argc < 3) {
		printf("Syntax Error ! Usage : %s <filesystem_image> <input_file>\n", argv[0]);
		return SYNTAX_ERROR;
	}
	
	// Delete file from filesystem
	return pfsdel(argv[1], argv[2]);
	
}