#include "config.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int tl_read() {
	FILE *f = fopen(PATH, "r");
	int i = fgetc(f);
	fclose(f);
	return i != '0';
}

void tl_write(int b) {
        char *c = b ? "255\n" : "0\n";
        uid_t uid = getuid();
        int j = setuid(0); //root
        int en = errno;
        FILE *f = fopen(PATH, "w");
        if(!f) {
                printf("No privileges");
                if(j) printf(", setting the UID failed: %s\n", strerror(en));
                else printf("...I don't know, can't open, errno: %s\n", strerror(errno));
        	return;
	}
	fwrite(c, 1, b ? 4 : 2, f);
	fclose(f);
	setuid(uid);
}

void tl_help() {
	puts("Usage: thinklight [command]");
	puts("(thinklight is equal to thinklight t)");
	printf("\nt[oggle] - turns on the light if it's off and ");
	puts("turn it off if it's on");
	puts("on - turn on the light");
	puts("of[f] - turn off the light");
}

int main(int argc, char **argv) {
	char *cmd = argc > 1 ? argv[1] : "t";
	if(cmd[0] == 't') tl_write(!tl_read());
	else if(cmd[0] == 'o') {
		if(cmd[1] == 'n') tl_write(1);
		else if(cmd[1] == 'f') tl_write(0);
		else tl_help();
	}
	else tl_help();
}
