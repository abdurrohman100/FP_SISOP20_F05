#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void help(){
    printf(1,"clear : membersihkan layar terminal\n");
    printf(1,"clear [OPSI]\n");
    printf(1,"OPSI:\n");
    printf(1,"\t--help : Memperlihatkan bantuan\n");
    printf(1,"\t--version : Menunjukan informasi tentang versi\n");
}

void versi(){
    printf(1,"clear version 0.01\n");
    printf(1,"Dibuat oleh Sisop20-F05\n");
}

int main(int argc,char *argv[])
{
    if(argv[1][0]=='-'){
	if(strcmp(argv[1],"--help")==0) help();
	else if(strcmp(argv[1],"--version")==0) versi();
	else printf(1,"clear: invalid opsi %s\nKetik 'clear --help' untuk informasi lebih lanjut\n",argv[1]);
	exit();
    }
    else printf(1,"\033[2J\033[1;1H\n");
    exit();
}