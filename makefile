CFLAGS += -Wall -Wextra -O3
LIBS   += -lssh -lzip

all: ssh zip

ssh:
	$(CC) $(CFLAGS) $(LIBS) ssh.c -o ssh

zip:
	$(CC) $(CFLAGS) $(LIBS) zip.c -o zip

clean:
	rm -f a.out
	rm -f core
	rm -f ssh
	rm -f zip
