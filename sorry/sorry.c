#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n = 13,A=0,B=0,round=0,value=0;
    printf("Zadaj velkost hracej plochy [neparne cislo]: ");
    scanf("%d",&n);
    printf("\n");
	for(;A<=4*n-5&&B<=4*n-5;round++){
		printf("Round %d ",round);
        if(round%2){
            printf("B:\n");
            do{
                value=rand()%6+1;
                B+=value;
                printf("%d\n",value);
            }while(value==6);
        }else{
            printf("A:\n");
            do{
                value=rand()%6+1;
                A+=value;
                printf("%d\n",value);
            }while(value==6);
        }
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(
				A<n/2&&i==A&&j==n/2+1
				||A>=n/2&&A<n-2&&i==n/2-1&&j==A+2
				||A>=n-2&&A<n&&j==n-1&&i==A-n/2+1
				||A>=n&&A<n+n/2-1&&i==n/2+1&&j==n*2-A-2
				||A>=n+n/2-1&&A<2*n-3&&j==n/2+1&&i==A-n+3
				||A>=2*n-3&&A<2*n-1&&i==n-1&&j==n/2-A+2*n-3
				||A>=2*n-1&&A<2*n+n/2-2&&j==n/2-1&&i==n-3-A+2*n
				||A>=2*n+n/2-2&&A<3*n-4&&i==n/2+1&&j==n/2-A+2*n+n/2-4
				||A>=3*n-4&&A<3*n-2&&j==0&&i==n/2-A+3*n-4
				||A>=3*n-2&&A<3*n+n/2-3&&i==n/2-1&&j==A-3*n+3
				||A>=3*n+n/2-3&&A<4*n-5&&j==n/2-1&&i==n/2-A+3*n+n/2-5
				||A==4*n-5&&i==0&&j==n/2
			){
				printf("A");
			}else if(
				B<n/2&&i==n-B-1&&j==n/2-1
				||B>=n/2&&B<n-2&&i==n/2+1&&j==n-B-3
				||B>=n-2&&B<n&&j==0&&i==n+n/2-B-2
				||B>=n&&B<n+n/2-1&&i==n/2-1&&j==B-n+1
				||B>=n+n/2-1&&B<2*n-3&&j==n/2-1&&i==2*n-B-4
				||B>=2*n-3&&B<2*n-1&&i==0&&j==n/2+B-2*n+3
				||B>=2*n-1&&B<2*n+n/2-2&&j==n/2+1&&i==B-2*n+2
				||B>=2*n+n/2-2&&B<3*n-4&&i==n/2-1&&j==B-n/2-2*n+n/2+4
				||B>=3*n-4&&B<3*n-2&&j==n-1&&i==B+n/2-3*n+4
				||B>=3*n-2&&B<3*n+n/2-3&&i==n/2+1&&j==n-B+3*n-4
				||B>=3*n+n/2-3&&B<4*n-5&&j==n/2+1&&i==B-n/2-3*n+n/2+5
				||B==4*n-5&&i==n-1&&j==n/2
			){
				printf("B");
			}else if(i<n/2-1&&j<n/2-1||i<n/2-1&&j>n/2+1||i>n/2+1&&j>n/2+1||i>n/2+1&&j<n/2-1){
				printf(" ");
			}else if(i==n/2&&j==n/2){
				printf("X");
			}else if(i==n/2&&j!=n-1&&j!=0||j==n/2&&i!=n-1&&i!=0){
				printf("D");
			}else{
				printf("*");
			}
		}
		printf("\n");
	}
	}
	if(A<B){
		printf("\nHrac B vyhral\n");
	}else{
		printf("\nHrac A vyhral\n");
	}
}
