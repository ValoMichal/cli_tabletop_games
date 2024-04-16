#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "monopoly.h"
int main(int argc, char *argv[]) {
	int opt;
	int flag=0;
	int players=2;
	while((opt=getopt(argc,argv,":n:spg"))!=-1){
		switch(opt){
			case 'n':
				players=atoi(optarg);
				break;
			case 's':
				flag=1;
				break;
			case 'p':
				flag=2;
				break;
			case 'g':
				flag=3;
				break;
		}
	}
	PLAYER hrac[4];
	hrac[0].number=1;
	hrac[1].number=2;
	hrac[2].number=3;
	hrac[3].number=4;
	hrac[0].space_number=0;
	hrac[1].space_number=0;
	hrac[2].space_number=0;
	hrac[3].space_number=0;
	hrac[0].num_jail_pass=0;
	hrac[1].num_jail_pass=0;
	hrac[2].num_jail_pass=0;
	hrac[3].num_jail_pass=0;
	hrac[0].is_in_jail=0;
	hrac[1].is_in_jail=0;
	hrac[2].is_in_jail=0;
	hrac[3].is_in_jail=0;
	hrac[0].num_properties=0;
	hrac[1].num_properties=0;
	hrac[2].num_properties=0;
	hrac[3].num_properties=0;
	switch(players){
		case 2:
			hrac[0].cash=20;
			hrac[1].cash=20;
			hrac[2].cash=0;
			hrac[3].cash=0;
			break;
		case 3:
			hrac[0].cash=18;
			hrac[1].cash=18;
			hrac[2].cash=18;
			hrac[3].cash=0;
			break;
		case 4:
			hrac[0].cash=16;
			hrac[1].cash=16;
			hrac[2].cash=16;
			hrac[3].cash=16;
			break;
	}
	int hod=0;
	for(int i=0;hrac[0].cash>=0&&hrac[1].cash>=0&&hrac[2].cash>=0&&hrac[3].cash>=0;i++){
		if((flag==2||flag==3)&&i>0){
			printf("Game board:\n");
			for(int x=0;x<NUM_SPACES;x++){
				printf("%d. ",1+x);
				if(game_board[x].property==NULL){
					printf("%s\n",space_types[(int)game_board[x].type]);
				}else{
					printf("%s %d %s",game_board[x].property->name,game_board[x].property->price,property_colors[(int)game_board[x].property->color]);
					int owned=0;
					for(int y=0;y<players;y++){
						for(int z=0;z<hrac[y].num_properties;z++){
							if(game_board[x].property->name==hrac[y].owned_properties[z]->name&&owned==0){
								printf(" P%d",z+1);
								owned=1;
								z=0;
							}
							if(game_board[x].property->color==hrac[y].owned_properties[z]->color&&game_board[x].property->name!=hrac[y].owned_properties[z]->name&&owned==1){
								owned=2;
							}
						}
					}
					if(owned==2){
						printf(" yes");
					}else if(owned==1){
						printf(" no");
					}
					owned=0;
					printf("\n");
				}
			}
		}
		if((flag==1||flag==3)&&i>0){
			printf("Players:\n");
			for(int x=0;x<players;x++){
				printf("%d. S: %d, C: %d, JP: %d, IJ: %s\n",hrac[x].number,hrac[x].space_number,hrac[x].cash,hrac[x].num_jail_pass,hrac[x].is_in_jail?"yes":"no");
				for(int y=0;y<hrac[x].num_properties;y++){
					for(int z=0;z<NUM_SPACES;z++){
						if(game_board[z].type==Property&&game_board[z].property->name==hrac[x].owned_properties[y]->name){
							printf(" %s %d %s S%d\n",hrac[x].owned_properties[y]->name,hrac[x].owned_properties[y]->price,property_colors[(int)hrac[x].owned_properties[y]->color],z);
						}
					}
				}
			}
		}
		if(flag==3&&i>0){
			printf("WINNER: -\n");
		}
		if(scanf("%d",&hod)!=1){
			return 1;
		}
		printf("R: %d\nTurn: %d\nPlayer on turn: P%d\n",hod,i+1,hrac[i%players].number);
		hrac[i%players].space_number+=hod;
		if(hrac[i%players].space_number>=NUM_SPACES){
			hrac[i%players].space_number-=NUM_SPACES;
			hrac[i%players].cash+=2;
		}
		if(hrac[i%players].is_in_jail==1){
			hrac[i%players].is_in_jail=0;	
			hrac[i%players].cash-=1;
		}
		switch(game_board[hrac[i%players].space_number].type){
			case Jail_pass:
				hrac[i%players].num_jail_pass++;
				break;
			case Go_to_jail:
				if(hrac[i%players].num_jail_pass>0){
					hrac[i%players].num_jail_pass--;
				}else{
					hrac[i%players].space_number-=12;
					hrac[i%players].is_in_jail=1;
				}
				break;
			case Property:
				int owned=0;
				for(int a=0;a<players;a++){
					for(int b=0;b<hrac[a].num_properties;b++){
						if(game_board[hrac[i%players].space_number].property->name==hrac[a].owned_properties[b]->name&&owned==0){
							hrac[i%players].cash-=hrac[a].owned_properties[b]->price;
							hrac[a].cash+=hrac[a].owned_properties[b]->price;
							owned=1;
							b=0;
						}
						if(game_board[hrac[i%players].space_number].property->color==hrac[a].owned_properties[b]->color&&game_board[hrac[i%players].space_number].property->name!=hrac[a].owned_properties[b]->name&&owned==1){
							hrac[i%players].cash-=hrac[a].owned_properties[b]->price;
							hrac[a].cash+=hrac[a].owned_properties[b]->price;
							owned=2;
							break;
						}
					}
					if(owned!=0){
						break;
					}
				}
				if(owned==0){
							hrac[i%players].owned_properties[hrac[i%players].num_properties]=game_board[hrac[i%players].space_number].property;
							hrac[i%players].num_properties++;
							hrac[i%players].cash-=game_board[hrac[i%players].space_number].property->price;
				}
				owned=0;
				break;
		}
	}
	int winner=0;
	int draw=-1;
	int compare=0;
	for(int i=1;i<4;i++){
		if(hrac[winner].cash==hrac[i].cash){
			draw=i;
		}else if(hrac[winner].cash<hrac[i].cash){
			winner=i;
			draw=-1;
		}
	}
	if(draw<0){
		if(flag==3){
			printf("WINNER: P%d\n",hrac[winner].number);
		}
		printf("player %d is the winner\n",hrac[winner].number);
	}else{
		for(int x=0;x<hrac[winner].num_properties;x++){
			compare+=hrac[winner].owned_properties[x]->price;
		}
		for(int x=0;x<hrac[draw].num_properties;x++){
			compare-=hrac[draw].owned_properties[x]->price;	
		}
		if(compare<0){
			if(flag==3){
				printf("WINNER: P%d\n",hrac[draw].number);
			}
			printf("player %d is the winner\n",hrac[draw].number);
		}else if(compare>0){
			if(flag==3){
				printf("WINNER: P%d\n",hrac[winner].number);
			}
			printf("player %d is the winner\n",hrac[winner].number);
		}else{
			if(flag==3){
				printf("WINNER: ?\n");
			}
			printf("draw between %d and %d\n",hrac[winner].number,hrac[draw].number);
		}
	}
	return 0;
}
