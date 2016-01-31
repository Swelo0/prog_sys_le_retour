#include "shell.h"

char* buffer;
int buffSize = 0;
char* cmdArgv[10];
int cmdArgc;


void shell_handler() {
	printf(" ---- Shell le coquillage de l'espace V0.1 \n");
	
	while(1){
		Prompt();
		GetCmd();
		if (!ExecCmd())
			printf("Commande inconnu, tapez ''help'' pour voir la liste des commandes valides. \n");
	}
}

void Prompt(){
	printf("> ");
}

void resetCmd() {
	buffSize = 0;
	while(cmdArgc) {
		cmdArgv[cmdArgc] = NULL;
        cmdArgc--;       
	}
}

void GetCmd(){
	char input;
	resetCmd();
	while ((input != '\n') && (buffSize < INPUT_MAX_LENGTH)) {
		buffer[buffSize++] = input;
		input = getc();
	}
	buffer[buffSize] = '\0';     
	char* bufferTemp; //
	bufferTemp = strtok(buffer, " ");
	while (bufferTemp != NULL) {  
		cmdArgv[cmdArgc] = bufferTemp; //On stock les arguments
		bufferTemp = strtok(NULL, " ");
		cmdArgc++;
	}
}

int ExecCmd(){
	if (strncmp("ls", cmdArgv[0],2) == 0) {
		return 1;
	}
	if (strncmp("cat", cmdArgv[0],3) == 0) {
		if (cmdArgv[1] == NULL){
			printf("Utilisation : cat <name_file> \n");
			return 0;
		}
		read_file(cmdArgv[1],(uchar*)buffer);
		printf(buffer);
		return 1;
	}
	if (strncmp("rm", cmdArgv[0],2) == 0) {
		return 1;
	}
	if (strncmp("run", cmdArgv[0],3) == 0) {
		return 1;
	}
	if (strncmp("ticks", cmdArgv[0],5) == 0) {
		return 1;
	}
	if (strncmp("sleep", cmdArgv[0],5) == 0) {
		return 1;
	}
	if (strncmp("exit", cmdArgv[0],4) == 0) {
		return 1;
	}
	if (strncmp("help", cmdArgv[0],4) == 0) {
		return 1;
	}
	return 0;
}