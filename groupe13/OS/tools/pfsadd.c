#include "fs.h"

// File handlers
FILE* img_file;
FILE* input_file;

// Add file to filesystem image
int pfsadd(char* img, char* input) {

	// Open files
	if (!(img_file = fopen(img, "r+"))) {
		printf("I/O error ! File %s could not be accessed.\n", img);
		return IO_ERROR;
	}
	if (!(input_file = fopen(input, "r"))) {
		printf("I/O error ! File %s could not be accessed.\n", input);
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
	
	// Look for a free file entry
	int entry = -1;
	for (int i = 0; i < sb.file_entry_nb; i++)
		if (!fe[i].name[0]) {
			entry = i;
			break;
		}
	// Entry check
	if (entry >= 0)
		strcpy(fe[entry].name, input);  
	else {
		printf("Error : no more available file entry.\n");
		return FULL_FE_ERROR;
	}
	printf("File entry id : %d\n", entry);
	
	// File size (bytes)
	fseek(input_file, 0, SEEK_END);
	int file_size = ftell(input_file); 
	fe[entry].size = file_size;
	
	// Reset file pointer
	fseek(input_file, 0, SEEK_SET);
	
	// Parse file block by block
	block tmp;
	int blockNum     = -1;
	int currentBlock = -1;
	for (int i = 0; i <= (file_size / block_size); i++) {
		
		// Read block
		memset(tmp, 0, block_size);
		if (i != (file_size / block_size))
			fread(tmp, block_size , 1, input_file);
		
		// Last portion is potentially not a whole block so we copy it byte per byte
		else {			
			char c;
			int b = 0;
			while ((c = fgetc(input_file)) != EOF) tmp[b++] = c;
		}
	
		// Look for a free block in the bitmap
		int offset = 0;
		int ok     = 0;
		while ((offset < (sb.data_blocks / 8)) && (!ok)) {
			
			blockNum = -1;
			for (int i = 0; i < 8; i++)
				// As soon as we find a 0 bit we stop (not the index 0 though)
				if (!(*(bitmap + offset) & (1 << (++blockNum))))
					if ((offset != 0) || (blockNum != 0)) {
						ok = 1;
						break;
					}
			if (!ok) offset++;
			
		}
		// If no free block found
		if (!ok) {
			printf("Error : no more available data block.\n");
			return FULL_BITMAP_ERROR;
		}
		
		// Update filesystem structure
		*(bitmap + offset) |= 1 << blockNum; 
		fe[entry].blocks[++currentBlock] = (offset * 8) + blockNum; 
		memcpy(fc[(offset * 8) + blockNum], &tmp, block_size);
		
		// Display
		printf("Data block[%d] : %d\n", currentBlock, (offset * 8) + blockNum);
		
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
	fclose(input_file);
	
	// End of routine
	return NO_ERROR;
    
}

// Entry point
int main(int argc, char** argv) {

	// Arguments check
	if (argc < 3) {
		printf("Syntax error ! Usage : %s <filesystem_image> <input_file>\n", argv[0]);
		return SYNTAX_ERROR;
	}
	
	// Add file to the filesystem
	return pfsadd(argv[1], argv[2]);
	
}