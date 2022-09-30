#include <libssh/libssh.h>
#include <stdio.h>
#include <stdlib.h>

char *host = NULL;
int port = 22;
char *username = NULL;
char *password = NULL;
ssh_session this_session = NULL;

void exit_hook(void) {
	if (this_session != NULL) {
		ssh_disconnect(this_session);
		ssh_free(this_session);
	}
}

int main(void) {
	atexit(exit_hook);
	host = getenv("host");
	char *temp = NULL;
	temp = getenv("port");
	if (temp != NULL) {
		port = atoi(temp);
	}
	username = getenv("username");
	password = getenv("password");

	this_session = ssh_new();
	if (this_session == NULL)
		exit(EXIT_FAILURE);

	int verbosity = SSH_LOG_PROTOCOL;

	ssh_options_set(this_session, SSH_OPTIONS_HOST, host);
	ssh_options_set(this_session, SSH_OPTIONS_PORT, &port);
	ssh_options_set(this_session, SSH_OPTIONS_LOG_VERBOSITY,
			&verbosity);

	int ret;
	ret = ssh_connect(this_session);
	if (ret != SSH_OK) {
		fprintf(stderr,"can't connect to %s:%d, REASON: %s\n",
			host,port,
			ssh_get_error(this_session));
		exit(EXIT_FAILURE);
	}

	ret = ssh_userauth_password(this_session, username, password);
	if (ret != SSH_AUTH_SUCCESS) {
		fprintf(stderr,"can't login %s:%d use %s:%s, REASON: %s\n",
			host,port,username,password,
			ssh_get_error(this_session));
		exit(EXIT_FAILURE);
	}
	if (ret == SSH_AUTH_SUCCESS) {
		printf("PASSWORD FOUND: %s:%d %s:%s\n",
		       host,port,username,password);
	}

	ssh_disconnect(this_session);
	ssh_free(this_session);
	return 0;
}
