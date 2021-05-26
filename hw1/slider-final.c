#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <ctype.h>
/*swap the address with the target address */
void swap(char *pos, char *tar){
	char temp;
	temp=*tar;
	*tar=*pos;
	*pos=temp;
}

void  STPsimulator2(FILE *f){ 
	/*set up all the variables*/	
	char board[25];/*initialize an empty board*/
	int i;
	char c;
	//int p;
	int q;
	int space;
	int j;
	char spiral[25]="RGGGGRYWWORYWWORYYOOBBBB "; /*for checking the spiral array*/
	int k;
	
	/*fill the empty board with color from the file stream*/
	for(i=0;i<25;i++){
		c=getc(f);
		if(c=='\n')
			c=getc(f);
		board[i]=c; 
		/*found where the space is*/
		if(board[i]==' ')
			space=i;	
	}
	/*take the move instructions from the file stream*/
	c=getc(f);
	while(c!=EOF){
		if(c==' '||c=='\0'||c=='\n'||c=='\t'){
			c=getc(f); /*ignore this one and get another one;*/
			continue;
		}else{
			/*move *lower case is impassable	*/
			switch(toupper(c)){
				case 'D':
					if(space>4&&isupper(board[space-5])) {
						swap(&board[space], &board[space-5]);
						space-=5;
					}	
					break;
				case 'U':
					if(space<20&&isupper(board[space+5])) {
						swap(&board[space], &board[space+5]);
						space+=5;
					}	
					break;
				case 'R':
					if(space%5!=0&&isupper(board[space-1])) {
						swap(&board[space], &board[space-1]);
						space-=1;
					}
					break;
				case 'L':
					if((space+1)%5!=0&&isupper(board[space+1])) {
						swap(&board[space], &board[space+1]);
						space+=1;
					}	
					break;
				default:
					printf("error instructions!");
				}
		}
		c=getc(f);
	}
	
	/*output the moved board;*/
	for(j=0;j<25;j++){
		if(j==0)
			printf("%s","+-+-+-+-+-+\n");
		if(j%5==0&&j!=0)
			printf("%s","|\n+-+-+-+-+-+\n");
		printf("|%c",board[j]);
	}
	printf("%s","|\n+-+-+-+-+-+\n");
	
	/*check with spiral;*/
	for(k=0;k<25;k++){
		if(tolower(board[k])!=tolower(spiral[k]))
			break;
	}
	if(k==25){
		printf("%s","Spiral!\n");
	}
	exit(1);
}
  
int main(int argc, char* argv[]){
	/*check the file*/
	FILE *f;

	if(argc<2)
		printf("no filename!");
	else{
		f= fopen(argv[1], "r");
		}
	if(f==NULL){
			printf("Could not openfile %s",argv[1]);
			return 1;
		}
		
	/*running the board.*/
	STPsimulator2(f);
	fclose(f);
	return 0;

}
