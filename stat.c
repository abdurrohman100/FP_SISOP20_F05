#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"


void help(){
    printf(1,"stat : Membersihkan layar terminal\n");
    printf(1,"clear [OPTION]\n");
    printf(1,"Option:\n");
    printf(1,"--help : Memperlihatkan bantuan lalu exit\n");
    printf(1,"--versi : Menunjukan informasi tentang versi lalu exit\n");
}

void prog(){
printf(1,"clear version 1.00\n");
printf(1,"Dibuat oleh Abdur\n");
}

void statnya(char * path,struct stat * ps){
    printf(1,"Name: %s\nevice: %d\nInode:%d\nLink:%d\nSize: %d\nType: %d\n",ps->dev,ps->ino,ps->nlink,ps->size,ps->type);

}
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int main(int argc,char *argv[])
{
    if(argv[1][0]=='-'){
        if(strcmp(argv[1],"--help")==0) help();
        else if(strcmp(argv[1],"--versi")==0) prog();
        else printf(1,"pwd: invalid opsi %s\nCoba ketik 'clear --help' untuk informasi lebih lanjut\n",argv[1]);
        exit();
    }
    else {
        
        // for ( i = 1; i < argc; i++)
        // {
        //     struct stat apa;
        //     //
        //     if(stat(argv[i],&apa)){
        //         //printf(1,"apa\n");
        //         //statnya(argv[i],&apa);
        //     }
        // }
        struct stat ps;
        stat(argv[1],&ps);
        printf(1,"Device: %d\nInode:%d\nLink:%d\nSize: %d\nType: %d\nGid: %d\nUid: %d",ps.dev,ps.ino,ps.nlink,ps.size,ps.type,ps.gid,ps.uid);
    }
    exit();
}