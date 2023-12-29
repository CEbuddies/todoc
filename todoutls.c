#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Fileinfo{
	bool f_flag;
	int f_loc;
	bool config_flag;
	int m_loc;
} Fileinfo;

void print_cmdargs(int num_args, char* args[]){

	for(int i=0; i<num_args; i++){
		printf("%s\n", args[i]);
	}
}

// how do we handle if there is no argument after that?
int get_floc(int numargs, char* args[]){
	int loc=-1; // in case we do not find, returns -1
	
	for (int i=0; i<numargs; i++){
		if(strcmp("-f",args[i]) == 0){
			loc = i;
		}
	}
	// could also be <=, right?
	if(numargs == loc){
		return -1;
	}
	loc += 1;

	return loc;
}


// careful, partially returning int, fname should be a parameter
int read_config(char* filename){
	FILE* fptr;
	char fname[64];
	char cfg[64];
	char* value = (char*)malloc(64*sizeof(char));
	char* key = (char*)malloc(64*sizeof(char));
	char buffer[128];
	char* cfgname = "/home/nic/Desktop/cfg";

	printf("Attempting to read %s\n", cfgname);	
	fptr = fopen(cfgname,"r");
	if (fptr == NULL){
		perror("Error opening file: ");
		return -1;
	}

	while (fgets(buffer, sizeof(buffer), fptr) != NULL){
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len -1] == '\n'){
			buffer[len -1] = '\0'; // create 0 terminated str
		}

		char* key = strtok(buffer, ";");
		char* value = strtok(NULL, ";");

		if (key == NULL || value == NULL){
			break;
		}
		if (strcmp(key, "fname") == 0){
			strcpy(fname,value);
		}
		if (strcmp(key,"cfg") == 0){
			strcpy(cfg,value);
		}

	}
	fclose(fptr);
	
	if ( !(key == NULL || value == NULL)){
		free(key);
		free(value);
	}
	int len_fname = sizeof(fname)/sizeof(char);
	strcpy(filename, fname);
	return len_fname;
}
