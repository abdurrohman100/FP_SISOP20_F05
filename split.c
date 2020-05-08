#include "types.h"
#include "fcntl.h"
#include "user.h"
#include "stat.h"
#include "fs.h"

#define CHUNK_SIZE	1024

int line_limit = 1000;
int fdfile;
char output_name[100];
char *suffix;
char delimiter='\n';

void split1 (void);
int newfile (void);


void split1()
{
  char buf[CHUNK_SIZE];
  register char *index, *base;
  register int n;
  int fd;
  long lines = 0L;

  fd = -1;
  while ((n = read(fdfile, buf, CHUNK_SIZE)) > 0) {
	base = index = buf;
	while (--n >= 0) {
		if (*index++ == delimiter)
			if (++lines % line_limit == 0) {
				if (fd == -1) fd = newfile();
				if (write(fd, base, (int) (index - base)) != (int) (index - base))
					exit();
				base = index;
				close(fd);
				fd = -1;
			}
	}
	if (index == base) continue;
	if (fd == -1) fd = newfile();
	if (write(fd, base, (int) (index - base)) != (int) (index - base))
		exit();
  }
  exit();
}

int newfile()
{
  int fd;

  if (++*suffix > 'z') {
	*suffix = 'a';		
	++*(suffix - 1);	

  }
  if ((fd = open(output_name,O_CREATE|O_RDWR)) < 0) {
	printf(2,"Cannot create new file.\n");
	exit();
  }
  return fd;
}



void help(){
    printf(1,"split : Membagi file menjadi beberapa file dimana secara default beberapa file tersebut tidak melebihi 1000 line\n");
    printf(1,"split [OPSI] [PARAMETER] [NAMAFILE]\n");
    printf(1,"OPSI:\n");
	printf(1,"\t-l : Membagi setiap file dengan batasan line yang ditentukan\n");
    printf(1,"\t--help : Memperlihatkan bantuan\n");
    printf(1,"\t--version : Menunjukan informasi tentang versi\n");
}

void versi(){
    printf(1,"clear version 0.01\n");
    printf(1,"Dibuat oleh Sisop20-F05\n");
}

int main(int argc,char **argv)
{
   
  output_name[0]='x';
  fdfile=-1;
  if(argc>4)printf(2,"Argumen terlalu banyak\n");
  

	if(argv[1][0]=='-'){
		if(strcmp(argv[1],"--help")==0) help();
		else if(strcmp(argv[1],"--versi")==0) versi();
		else if(strcmp(argv[1],"-l")==0){
			if(line_limit==1000){
				int flag=1,j;
				// printf(1,"%s",argv[2]);
				for(j=0;j<strlen(argv[2]);j++){
					if(argv[2][j] < '0' || argv[2][j] > '9' ){
						flag=0;
						// printf(1,"ciluk ba\n");
					}
				}
				if(!flag){
					printf(2,"%s bukan parameter yang valid\n",argv[2]);
					exit();
				}
				else{
					line_limit=atoi(argv[2]);
				}
			}
			strcpy(output_name, argv[3]);
			
		}
	}
	else{
		strcpy(output_name, argv[1]);
	}
	if ((fdfile = open(output_name, O_RDONLY)) < 0) {
		printf(2,"Tidak buka membuka file. Ketik split --help untuk bantuan\n");
		exit();
	}
	// if (infile == -1) infile = 0;
	strcat(output_name, ".aaa");

	for (suffix = output_name; *suffix; suffix++);
	suffix--;

	*suffix = 'a' - 1;
	split1();
	exit();
	return(0);

}