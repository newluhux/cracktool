#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

#define MAXPASSWORDLEN 1024

int main(void) {
	char *zipfilename = getenv("zipfilename");
	char *openfilename = getenv("openfilename");

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
		if (zf != NULL) {
			printf("PASSWORD FOUND: %s %s %s\n",
			       zipfilename,openfilename,
			       pass);
			exit(EXIT_SUCCESS);
		}
		printf("try %s %s use %s\n",
		       zipfilename,openfilename,
		       pass);
	}
	return 0;
}
