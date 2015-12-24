#include "fs.h"

// Ajout
void pfsadd(filesystem *fs, char fileName[]) {

	FILE* fp;
	block blockTemp;
	int   ptByte = 0;
	int64*  ptBitmap =(int64*)(&(*fs).bitmap);
	char  ch;
	int	  fileLen, numEntry, currentBlock = 0, numBlock = 0;
	
	// Mode lecture
	fp = fopen(fileName,"r"); 
	
	if( fp == NULL ) perror("Error while opening the file.\n");
	
	// On trouve une entrée libre.
	numEntry = -1;
	while ((*fs).fe[++numEntry].name[0] != '\0');
	strcpy((*fs).fe[numEntry].name, fileName);
	
	// Longueur du fichier
	fseek(fp, 0, SEEK_END);
	// Nombre de bytes dans le fichier	
	fileLen=ftell(fp); 
	fseek(fp, 0, SEEK_SET);
	
	(*fs).fe[numEntry].size = fileLen;
	
	int i=0;
	// On parcourt le fichier par block (1024o) 
	for (i=0;i<(fileLen/BLOCK_SIZE);i++) {
		fread( blockTemp , BLOCK_SIZE , 1 , fp );
		// On met a jour le Bitmap et écrit les données, writeBlock(...)
		// On trouve un block libre
		while ((*ptBitmap)&1<<(numBlock++)); 
		// Mise à jour de Bitmap
		(*ptBitmap) |= 1<<(numBlock-1); 
		// Ecrit 2
		(*fs).fe[numEntry].blocks[currentBlock++] = numBlock; 
		// Si le deuxième block est libre (donc réellement le bloc[1])
		memmove((*fs).fc[numBlock], blockTemp, BLOCK_SIZE);
	}
	
	// Quand il reste moins de 1024o de données à écrire. 
	while( ( ch = fgetc(fp) ) != EOF ) blockTemp[ptByte++] = ch;
	blockTemp[ptByte] = '\0'; //fin du fichier
	
	// On met a jour le Bitmap et écrit les données, writeBlock(...)
	numBlock = 0;
	// On trouve un block libre
	while ((*ptBitmap)&1<<(numBlock++)); 
	// Mise à jour de bitmap
	(*ptBitmap) |= 1<<(numBlock-1); 
	// Ecrit 2
	(*fs).fe[numEntry].blocks[currentBlock++] = numBlock; 
	// Si le deuxième block est libre (donc réellement le bloc[1])
	memmove((*fs).fc[numBlock], blockTemp, BLOCK_SIZE);
	
        fclose(fp);
    
}
