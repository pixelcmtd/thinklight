#include "config.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int tl_read(const char *path) {
	FILE *f = fopen(path, "r");
	if(!f) {
		fprintf(stderr, "fopen(%s): %s\n", path, strerror(errno));
		return -1;
	}
	int i = fgetc(f);
	if(i == EOF) {
		fprintf(stderr, "fgetc(%s): %s\n", path, strerror(errno));
		fclose(f);
		return -1;
	}
	if(fclose(f))
		fprintf(stderr, "fclose(%s): %s\n", path, strerror(errno));
	return i != '0';
}

int tl_write(const char *path, int b) {
	uid_t uid = getuid();
	if(setuid(0)) {
		fprintf(stderr, "setuid(root): %s\n", strerror(errno));
		return 1;
	}
	FILE *f = fopen(path, "w");
	if(!f) {
		fprintf(stderr, "fopen(%s): %s\n", path, strerror(errno));
		setuid(uid);
		return 1;
	}
	fwrite(b ? "255\n" : "0\n", 1, b ? 4 : 2, f);
	if(fclose(f)) {
		fprintf(stderr, "fclose(%s): %s\n", path, strerror(errno));
		setuid(uid);
		return 1;
	}
	if(setuid(uid)) {
		fprintf(stderr, "setuid(%d): %s\n", uid, strerror(errno));
		return 1;
	}
	return 0;
}

inline int tl_main(const char *path, int argc, char **argv) {
	const char *cmd = argc > 1 ? argv[1] : "t";
	if(cmd[0] == 't') return tl_write(path, !tl_read(path));
	if(cmd[0] == 'o') {
		if(cmd[1] == 'n') return tl_write(path, 1);
		if(cmd[1] == 'f') return tl_write(path, 0);
	}
	printf("Usage: %s [<command>]\n", argv[0]);
	puts("(if no command is supplied, t[oggle] is assumed)");
	printf("\nt[oggle] - turns on the light if it's off and ");
	puts("turns it off if it's on");
	puts("on       - turn the light on");
	puts("of[f]    - turn the light off");
	return 1;
}

#define tl_genmain(path) \
	int main(int c, char **v) { return tl_main(path, c, v); }
