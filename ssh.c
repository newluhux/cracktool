#include <libssh/libssh.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPASSWORDLEN 1024

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr,"usage: %s host port username password\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	char *host = argv[1];
	int port = atoi(argv[2]);
	char *username = argv[3];
	char *password = argv[4];

	ssh_session this_session = NULL;

	if (this_session != NULL) {
		ssh_disconnect(this_session);
		ssh_free(this_session);
	}

	this_session = NULL;
	this_session = ssh_new();
	if (this_session == NULL)
		exit(EXIT_FAILURE);

	int verbosity = SSH_LOG_PROTOCOL;

	ssh_options_set(this_session, SSH_OPTIONS_HOST, host);
	ssh_options_set(this_session, SSH_OPTIONS_PORT, &port);
	ssh_options_set(this_session, SSH_OPTIONS_LOG_VERBOSITY,
			&verbosity);

	int ret;
	if (ssh_connect(this_session) != SSH_OK) {
		fprintf(stderr,"can't connect to %s:%d, REASON: %s\n",
			host,port,
			ssh_get_error(this_session));
		exit(EXIT_FAILURE);
	}

	ret = ssh_userauth_password(this_session, username, password);
	if (ret != SSH_AUTH_SUCCESS) {
		fprintf(stderr,"try %s:%d ,use %s:%s, REASON: %s\n",
			host,port,username,password,
			ssh_get_error(this_session));
		exit(EXIT_FAILURE);
	}
	if (ret == SSH_AUTH_SUCCESS) {
		printf("PASSWORD FOUND: %s:%d %s:%s\n",
		       host,port,username,password);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
