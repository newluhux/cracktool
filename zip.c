#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#define MAXPASSWORDLEN 1024

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr,"usage: %s zipfile fileinzip < wordlist\n"
			,argv[0]);
		exit(EXIT_FAILURE);
	}
	char *zipfilename = argv[1];
	char *openfilename = argv[2];

	int err;
	zip_t *za = zip_open(zipfilename,ZIP_RDONLY,&err);
	if (err != ZIP_ER_OK) {
		fprintf(stderr,"can't open zip file %s, REASON:%d\n",
			zipfilename,err);
		exit(EXIT_FAILURE);
	}

	zip_file_t *zf = NULL;

	char pass[MAXPASSWORDLEN];
	while(fgets(pass,MAXPASSWORDLEN,stdin) != NULL) {
		if (pass[strlen(pass)-1] == '\n')
			pass[strlen(pass)-1] = '\0';
		zf = zip_fopen_encrypted(za, openfilename, ZIP_RDONLY,
					 pass);
		if (zf == NULL) {
			printf("try open file: %s ,use pass: %s\n",
			       openfilename,pass);
		} else {
			printf("PASSWORD FOUND: %s %s %s\n",
			       zipfilename,openfilename,
			       pass);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_FAILURE);
}
