#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*analogies:*/
#define Line 14
#define Row 9
#define BombCount 15
/*suggested analogies for testing:
Line 14
Row 9
BombCount 15
*/

int main() {
	/* map randomizer */
	/* variable defining */
	srand(time(NULL));
	char c;
	int z, NakedBoard[Line][Row]={0}, CoveredBoard[Line][Row], counter=1, i, j, i_rand, j_rand, flag, choice_i, choice_j, Bombs_found, interaction_choice;;
	/* bomb planting proceedure */
		while (counter<=BombCount){
		/* flag for processing optimization */
		flag=0;
		/* random coordinate generator */ 
		i_rand= rand()%Line+1;
		j_rand=rand()%Row+1;
		/* bomb planting */
		for(i=0; i<=Line-1; i++){
			for(j=0; j<=Row-1; j++){
				/* checking for duplicate bombs */
				if (i==i_rand && j==j_rand){		
					/* if yes turn back the clock */					
					if (NakedBoard[i][j]==9){
						counter= counter-1;
					}					
					/* if no plant and +1 nearby cells */					
					else{
						NakedBoard[i][j]=9;		
						if (NakedBoard[i-1][j]!=9) NakedBoard[i-1][j]=NakedBoard[i-1][j]+1;						
						if (NakedBoard[i][j-1]!=9) NakedBoard[i][j-1]=NakedBoard[i][j-1]+1;						
						if (NakedBoard[i-1][j-1]!=9) NakedBoard[i-1][j-1]=NakedBoard[i-1][j-1]+1;						
						if (NakedBoard[i-1][j+1]!=9) NakedBoard[i-1][j+1]=NakedBoard[i-1][j+1]+1;						
						if (NakedBoard[i+1][j-1]!=9) NakedBoard[i+1][j-1]=NakedBoard[i+1][j-1]+1;						
						if (NakedBoard[i+1][j]!=9) NakedBoard[i+1][j]=NakedBoard[i+1][j]+1;						
						if (NakedBoard[i][j+1]!=9) NakedBoard[i][j+1]=NakedBoard[i][j+1]+1;						
						if (NakedBoard[i+1][j+1]!=9) NakedBoard[i+1][j+1]=NakedBoard[i+1][j+1]+1;						
						flag=1;						
					}
				}
			/* flag for processing optimization */
			if (flag==1) break;	
			}
		if (flag==1) break;
		}
		counter= counter+1;
	}
	/* Naked Board printing
	Comment out in final build

	for(i=0; i<=Line-1; i++){
		for(j=0; j<=Row-1; j++){
			if(NakedBoard[i][j]==9){
				printf("[B]");
			}
			else{
				printf("[%d]", NakedBoard[i][j]);
			}
			
		}
		printf("\n");
	}
	printf("\n");
	*/

	/* Covered Board creation */
	for (i=0; i<=Line -1; i++){
		for (j=0; j<=Row -1; j++){
			CoveredBoard[i][j]=10;
		}
	}
	
	/* game process */
	flag=2;
	do{
		printf("\n\n     ");
		for(j=0; j<=Row-1; j++){
			printf("[%d]", j+1 );
		}
		printf("\n");
		for(i=0; i<=Line-1; i++){
			if(i+1<10) printf("\n[%d]  ", i+1);
			else  printf("\n[%d] ", i+1);
			for(j=0; j<=Row-1; j++){
				if (CoveredBoard[i][j]==10) printf("[#]");
				else if(CoveredBoard[i][j]==9){
					printf("[B]");
					flag=-1;
				}
				else if(CoveredBoard[i][j]==11) printf("[F]");
				else if(CoveredBoard[i][j]==0) printf("[ ]");
				else printf("[%d]", CoveredBoard[i][j]);
			}
		}

		/*win condition checking*/ 
		Bombs_found=0;
		for (i=0; i<=Line-1; i++){
			for (j=0; j<=Row-1; j++){
				if (NakedBoard[i][j]==10 && CoveredBoard[i][j]==9) Bombs_found=Bombs_found+1;
			}
		}
		if (Bombs_found== BombCount) flag=1;

		/* player interaction */
		if (flag==0||flag==2){
			printf("\n\nEnter coordinates to excavate (Line then Row):\n");
			scanf("%d %d", &choice_i, &choice_j);
			while(choice_i<1||choice_i>Line||choice_j<1||choice_j>Row){
				printf("\n\nPlease enter valid coordinates to excavate (Line then Row):\n");
				scanf("%d %d", &choice_i, &choice_j);
			}
			choice_i= choice_i-1;
			choice_j= choice_j-1;
			printf("\nChoose interaction:\n1: Excavate on coordinates\n2: Flag coordinates\n");
			scanf("%d", &interaction_choice);
			if (interaction_choice!=1 && interaction_choice!=2){
				do{
					printf("\nChoose valid interaction:\n1: Excavate on coordinates\n2: Flag coordinates\n");
					scanf("%d", &interaction_choice);
				}while (interaction_choice!=1 && interaction_choice!=2);
			}
			if(interaction_choice==1){ 
				CoveredBoard[choice_i][choice_j]=NakedBoard[choice_i][choice_j];
				if (flag==2){
					if (NakedBoard[choice_i-1][choice_j-1]!=9 && choice_i-1>=0 && choice_j-1>=0) CoveredBoard[choice_i-1][choice_j-1]=NakedBoard[choice_i-1][choice_j-1]; 
					if (NakedBoard[choice_i-1][choice_j]!=9 && choice_i-1>=0) CoveredBoard[choice_i-1][choice_j]=NakedBoard[choice_i-1][choice_j];
					if (NakedBoard[choice_i][choice_j-1]!=9 && choice_j-1>=0) CoveredBoard[choice_i][choice_j-1]=NakedBoard[choice_i][choice_j-1];
					if (NakedBoard[choice_i-1][choice_j+1]!=9 && choice_i-1>=0 && choice_j+1<Row) CoveredBoard[choice_i-1][choice_j+1]=NakedBoard[choice_i-1][choice_j+1];				 
					if (NakedBoard[choice_i+1][choice_j-1]!=9 && choice_i+1<Line && choice_j-1>=0) CoveredBoard[choice_i+1][choice_j-1]=NakedBoard[choice_i+1][choice_j-1];				
					if (NakedBoard[choice_i+1][choice_j+1]!=9 && choice_i+1<Line && choice_j+1<Row) CoveredBoard[choice_i+1][choice_j+1]=NakedBoard[choice_i+1][choice_j+1];				
					if (NakedBoard[choice_i+1][choice_j]!=9 && choice_i+1<Line) CoveredBoard[choice_i+1][choice_j]=NakedBoard[choice_i+1][choice_j];
					if (NakedBoard[choice_i][choice_j+1]!=9 && choice_j+1<Row) CoveredBoard[choice_i][choice_j+1]=NakedBoard[choice_i][choice_j+1];
					flag=0;
				}
			}
			else CoveredBoard[choice_i][choice_j]=11;
		}
		system("cls");
	}while(flag==0);

	if (flag==1) printf("\nCongratulations you won\n");
	else printf("\a\nYou lost\n");

	system("PAUSE");
			
	return 0;	
}