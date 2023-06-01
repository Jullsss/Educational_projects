#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char **argv) {
int mod=atoi(argv[2]);
int fd=open(argv[1],O_CREAT | O_EXCL | O_TRUNC | O_RDWR, 0751);
const char *buf1="#!/usr/bin/env python3\n";
write(fd,buf1,sizeof(buf1));
const char *buf2="count = int(input())\n";
write(fd,buf2,sizeof(buf2));
const char *buf6="count = (count + 1) * count / 2\n";
write(fd,buf6,sizeof(buf6));
const char *buf7 = "mod=";
write(fd,buf7,sizeof(buf7));
write(fd, &mod, sizeof(mod));
const char *buf8 = "\n";
write(fd,buf8,sizeof(buf8));
const char *buf9 = "print (count % mod)\n";
write(fd,buf9,sizeof(buf9));
close(fd);
return 0;
}
