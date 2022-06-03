#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  


typedef struct{
	char* title;
	char* writer; 
	int number;
	char* category;
}Book;

void flushScanf(){
	int res;
	char c;
	do{
		res = scanf("%c", &c);
	} while( res==1 && c!='\n' );
}	


Book* readBook(){
	char tmp[256];
	char top[256];
	char tkp[256];
	Book* struc = NULL;
	FILE* paper = NULL;
	paper = fopen("Booklist.txt", "r+");
	if(paper == NULL){
		puts("Erreur d'allocation");
		printf("%d : %s", errno, strerror(errno));
		exit(1);
	}
	struc = malloc(5 * sizeof(Book));
	if(struc == NULL){
		exit(2);
	}
	for(int i = 0; i < 5; i++){
		fscanf(paper, "%s", tmp);
		int N = strlen(tmp);
		struc[i].title = malloc( (N+1) * sizeof(char) );
		if(struc[i].title == NULL){
			puts("Erreur d'allocation");
			exit(3);
		}
	    strcpy(struc[i].title , tmp);
	    
		fscanf(paper, "%s", top);
		int M = strlen(top);
		struc[i].writer = malloc( (M+1) * sizeof(char) );
		if(struc[i].writer == NULL){
			puts("Erreur d'allocation");
			exit(4);
		}
	    strcpy(struc[i].writer , top);
	    
	    fscanf(paper, "%s", tkp);
		int K = strlen(tkp);
		struc[i].category = malloc( (K+1) * sizeof(char) );
		if(struc[i].category == NULL){
			puts("Erreur d'allocation");
			exit(5);
		}
	    strcpy(struc[i].category , tkp);
	    
		fscanf(paper, "%d", &(struc[i].number));
	}
	
	fclose(paper);
	return struc;
}

void newbooks(){
	FILE * news = NULL;
	news = fopen("Booklist.txt", "a");
	if(news == NULL){
		puts("Erreur d'allocation");
		exit(1);
	}
	char tit[50]; 
	char wri[50]; 
	int nmb = 0;
	char cat[50];
	
	puts("Quel est votre livre?");
	scanf("%s", tit);
	flushScanf();
	//scanf("%s", log);
	fprintf(news, "%s\t", tit);
	
	
	puts("Quel est l'auteur?");
	scanf("%s", wri);
	flushScanf();
	fprintf(news, "%s\t", wri);
	
	puts("Quel est la catégorie?");
	scanf("%s", cat);
	flushScanf();
	fprintf(news, "%s\t", cat);
	
	do{
		puts("Quel est le numéro?");
		scanf("%d", &nmb);
		flushScanf();
	}while(nmb <= 0);
	fprintf(news, "%d\n", nmb);
	

	fclose(news);
}

void searchCategory(){
	Book* tab;
	tab = readBook();
	char category[50];
	puts("Quelle catégorie voulez-vous rechercher?");
	scanf("%s", category);
	for(int i = 0; i< 5; i++){
		if(strcmp(category, tab[i].category) == 0){
			printf("%s %s \n", tab[i].title, tab[i].writer);
		}
	}
}

			
				

int main()
{
	Book* tab; 
	tab = readBook();
	for(int i; i<5; i++){
		printf("Livre %d : %s de %s \n", i+1 , tab[i].title, tab[i].writer); 
		
	}
	newbooks();
	searchCategory();
	return 0;
}

