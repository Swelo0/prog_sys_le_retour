

char* buffer;
int buffSize = 0;
char* cmdArgv;
int cmdArgc;


void main(int argc, char **argv) {
	printf(" ---- Shell le coquillage de l'espace V0.1 \n");
	
	while(1){
		Prompt();
		GetCmd();
		if (!ExecCmd())
			printf("Commande inconnu, tapez ''help'' pour voir la liste des commandes valides. \n")
	}
	return 0;
}

void Prompt(){
	printf("> ");
}

void resetCmd() {
	bufferSize = 0;
	while(cmdArgc) {
		cmdArgv[cmdArgc] = NULL;
        cmdArgc--;       
	}
}

int GetCmd(){
	char input;
	resetCmd();
	while ((input != '\n') && (bufferSize < INPUT_MAX_LENGTH)) {
		buffer[bufferSize++] = input;
		input = getchar();
	}
	buffer[bufferSize] = '\0';     
	char* bufferTemp; //
	bufferTemp = strtok(buffer, " ");
	while (bufferTemp != NULL) {  
		cmdArgv[cmdArgc] = bufferTemp; //On stock les arguments
		bufferTemp = strtok(NULL, " ");
		cmdArgc++;
	}
}

void ExecCmd(){
	if (strcmp("ls", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("cat", cmdArgv[0]) == 0) {
		if (cmdArgv[1] == NULL){
			printf("Utilisation : cat <name_file> \n");
			return 0;
		}
		read_file(cmdArgv[1],buffer);
		printf(buffer);
		return 1;
	}
	if (strcmp("rm", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("run", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("ticks", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("sleep", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("exit", cmdArgv[0]) == 0) {
		return 1;
	}
	if (strcmp("help", cmdArgv[0]) == 0) {
		return 1;
	}
	return 0;
}