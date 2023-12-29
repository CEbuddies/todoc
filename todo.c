#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "todoutls.c"

/*
TODO:
- ommit the filename and write directly to a file
- check if " " might have been forgotten and connect the words
- maybe promt something to the user then
- add the possibility to init
- add some kind of a config file, that handles in which file to store
- config could for instance be overridden
*/
int main(int argc, char* argv[]){
	// check if there is f flag present, if is - no cfg reading at all
	// file is a local one/path provided
	// after this, see if there is message present and write to file
	// if there is no -f, read config, write to default file name
	Fileinfo f_info;
	
	
	// print_cmdargs(argc, argv);	

	// Hidden testcase
	if (argc == 2 && strcmp(argv[1], "-t") == 0){
		int numargs = 3;	
		char* arguments[] = {"suck","-f", "notes"};
		argc = numargs;
		argv = arguments;
	}
	// Hidden testcase

	// In general to be working, application needs at least 2 args
	if (argc < 2){
		printf("Not enough arguments provided!\n");
		exit(1);
	}
	FILE* fptr;
	int msg_loc, file_loc;
	msg_loc = -1;
	file_loc = -1;
	char* fname = (char*)malloc(128*sizeof(char));

	
	// obtain location of the filename
	file_loc = get_floc(argc, argv);
	if (file_loc == -1){
		f_info.f_flag = true;
		f_info.f_loc = -1;
	}
	if (file_loc > 1){
		fname = argv[file_loc];
	}
	if (argc >= file_loc+1){
		msg_loc = 3;	
	}	
	// if we end up here, user used cmdline args only	
	if(msg_loc == -1 || file_loc <= 1){
		msg_loc = 1; // can only be 1 if there is a message
		int cfg_success = read_config(fname); // get fname target
		if (cfg_success < 0) {
			free(fname);
			printf("No target provided via flag or cfg file!\n");
			
			return -1;
		}	
	}	

	printf("Writing to file from cfg %s ... \n",fname);
	fptr = fopen(fname, "a");
	if (fptr == NULL){
		perror("Error opening file: ");
		return -1;
	}
	
	// we could assume if there is f and is long enough there will be message
	
	if (msg_loc > 0){

		fprintf(fptr, "%s\n", argv[msg_loc]);
	}
	if (fptr != NULL){
		fclose(fptr);
	}
	
	return 0;
}
