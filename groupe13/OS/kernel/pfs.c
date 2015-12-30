//////////////////////////////////////////////////////////////////////////////////////////
/// \file fs.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 27 décembre 2015
/// \brief Implementation of the kernel file system handling functions
//////////////////////////////////////////////////////////////////////////////////////////

#include "pfs.h"

int strcmp (const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}

int file_stat(char *filename, stat_t *stat){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			//on utilise l'itérateur pour chopper et renvoyer la taille du fichier dans la structure
			//stat->size = it->file_entrie->size ou un truc du genre	
		}	
	}
	return -1;
}

int file_read(char *filename, void *buf){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_remove(char *filename){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			
		}	
	}
	return -1;
}

int file_exists(char *filename){
	char* current_filename;
	file_iterator_t it = file_iterator();
	while (file_next(current_filename, &it)) {
		//si strcmp renvoie 0, c'est que les chaines sont égales, donc if inversé
		if(!strcmp(current_filename, filename)){
			return 1;
		}	
	}
	return 0;
}

file_iterator_t file_iterator(){
	 char sb[512];
	 
	 read_sector(0,&sb);
	 
	 //int32_t sizeblock = (int32_t)(*(sb+8));
	 
	 printf("taille d'un block");
	 printf("%c",sb[1]);
	 //printf("%d",sizeblock);
	 /*
	 for(int i = 0;i<512;i++)
	  if(sb[i]=='P') {
	  
	   printf("position ");
	   printf("%d",i);
	   printf("\n");
	  }*/
	 printf("\ntest\n");
	 for(int i = 0;i<124;i++){
	  	printf("%d",i);
	  	printf(*(sb+i));
	 }
}

int file_next(char *filename, file_iterator_t *it){

}
