#include
#include
#include
#include
#include
#include
#include
#include

int N;
void SigHndlr(int s){
    int c;
    int count = 0;
    while(count < N){
        c = fgetc(stdin);
        if (c == EOF)
            exit(0);
        fputc(c, stdout);
        if (c == '\n')
            count ++;
    }
}

int main(int argc, char **argv){
int f1 = open(argv[1], O_RDONLY);
dup2(f1,0);
close(f1);
N = (argv[2][0] - '0');

signal(SIGINT, SigHndlr);
while(1);
return 0;
}
