#include "test-main.h"
#include "uUTF8_FI.h"
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv){
	const char filename[] = "test-file.txt";
	char *data = readFile(filename);
	if(data == NULL){
		fprintf(stderr,"Failed to read the file, aborting\n");
		return 1;
	}


	struct uUTF8_FI ds;
	if(!uUTF8_Initialize_FI(data,&ds)){
		fprintf(stderr,"Failed to initialize uUTF8_FI data structure, aborting\n");
		return 2;
	}
	
	uint8_t *decoder = uUTF8_Decode_FI(&ds);
	if(!decoder){
		fprintf(stderr,"Failed to decode to UTF8, aborting\n");
		return 3;
	}

	bool matched = true;
	for(size_t itr = 0; decoder[itr] != 0x0; itr++){
		if((uint8_t)data[itr] != decoder[itr]){
			fprintf(stderr,"Decoding didn't match at %lu, decoder said - 0x%x, data said - 0x%x\n",itr, decoder[itr],(uint8_t)(data[itr]));
			matched = false;
			break;
		}
	}

	if(matched){
		fprintf(stderr,"Decoding matched, success");
	}

	fputc('\n',stdout);

	free(decoder);
	uUTF8_Destroy_FI(&ds);
	return (matched == true ? 0 : 4);
}
