CFLAGS += -Wall -Wextra
LIBS   += -lssh

all: ssh

ssh:
	$(CC) $(CFLAGS) $(LIBS) ssh.c -o ssh

clean:
	rm -f a.out
	rm -f core
	rm -f ssh
