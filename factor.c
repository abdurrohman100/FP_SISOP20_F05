#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

	
void opsi(char *arg){
	   int flag=0;

	   
	   if(strcmp(arg, "--help")==0){
		flag=1;
	   }
	   else if(strcmp(arg,"--version")==0){
		flag=2;
	   }
	    
	    if(flag==1){
		printf(1,"factor : Perintah ini digunakan untuk menghasilkan faktor dari sebuah integer\n");
	    printf(1,"factor [NUMBER]\n");
		printf(1,"OPSI:\n");
		printf(1,"\t--help : Memperlihatkan bantuan\n");
		printf(1, "\t --version : Menunjukan informasi tentang versi\n");
	        exit();
	    }
	    else if(flag==2){
	        printf(1,"factor version 0.01\n");
		printf(1,"Dibuat oleh Sisop20-F05\n");
	        exit();
	    }
	    else if(flag==0){
	    printf(1,"factor: number tidak valid\n",arg);
	    exit();
	    }	
}

int sqrt(int n){
	double tmp = n/2;
	double tmp2=0;
	
	while(tmp!=tmp2){
		tmp2=tmp;
		tmp=(n/tmp2 + tmp2)/2;	
	}
	return tmp;
}
	
int main(int argc,char *argv[]){
	
	    int n=0;
	   
	
	for(int i=1;i<argc;i++){
	    if(argv[i][0]=='-'){
	        if(argv[i][1]=='-'){
			opsi(argv[i]);
		}
	        else {
	            printf(1,"factor: read error\n");
	        }
	    }
	}
	
	for(int i=1;i<argc;i++){
	    n = atoi(argv[i]);
	    if(n==0 && strcmp(argv[i],"0") ){
	        printf(1,"factor: read error\n",argv[i]);
	    }
	    else {
			printf(1,"%d:",n);
			if(n==1 || n==0){
				printf(1,"\n");
				exit();
			}
			while(n%2==0){
				printf(1,"2 ");
				n = n/2;
			}
		
			for(int i=3;i<=sqrt(n);i=i+2){
				while(n%i==0){
					printf(1,"%d ",i);
					n = n/i;
				}
			}
		
			if(n>2){
				printf(1,"%d ",n);		
			}
			printf(1,"\n");
		}
	}
	exit();
}
	
	

