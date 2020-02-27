#include "NanoIO.h"


string IO_ReadFile(string path) {

	FILE* infile;
	char* buffer;
	long    numbytes;

	fopen_s(&infile, path, "r");

	if (!infile) {
		printf("ERROR LOAD %s\n", path);
		return 0;
	}

	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);
	fseek(infile, 0L, SEEK_SET);
	buffer = (char*)calloc(numbytes, sizeof(char));

	if (!buffer) {
		printf("ERROR MEMORY %s\n", path);
		return 0;
	}

	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);
	return (string)buffer;
}

