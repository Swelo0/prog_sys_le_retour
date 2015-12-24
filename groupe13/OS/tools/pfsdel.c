#include "fs.h"

// Suppression fichier
void pfsdel(filesystem *fs, char file[]) {

	// Parcourir File Entries jusqu'à trouver le fichier correspondant 
	int index = -1;

	while ((index < FILE_CONTENTS) && (strcmp((*fs).fe[++index].name, file) != 0));
	if (index < 0) return;

	// Changer le premier caractère du nom du fichier et sa taille
	(*fs).fe[index].name[0] = '\0';
	(*fs).fe[index].size    =  0 ;

	// Pour chaque bloc du File Entry :
	// 	Récupérer son index
	//	Mettre le bit correspondant dans Bitmap à 0
	int i;
	int64*  ptBitmap =(int64*)(&(*fs).bitmap);
	for (i = 0; i < MAX_BLOCKS; i++) 
		if ((*fs).fe[index].blocks[i] != 0) {
			*ptBitmap ^= 1 << ((*fs).fe[index].blocks[i]-1); 
		}
}