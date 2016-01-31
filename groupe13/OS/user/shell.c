

char* buffer;
char* cmdArg[]

void main(int argc, char **argv) {
	printf(" ---- Shell le coquillage de l'espace V0.1 \n");
	
	while(1){
		Prompt();
		GetCmd();
		ExecCmd();
	}
}

void Prompt(){
	printf("> ");
}

void resetCmd() {
	buffer = '';
	
}

int GetCmd(){
	resetCmd();
}

void ExecCmd(){
	if (strcmp("ls", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("cat", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("rm", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("run", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("ticks", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("sleep", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("exit", commandArgv[0]) == 0) {
		();
		return 1;
	}
	if (strcmp("help", commandArgv[0]) == 0) {
		();
		return 1;
	}
	return 0;
}