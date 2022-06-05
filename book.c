#include "projet.h"
#include "book.h"
#include "menu.h"
#include "username.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

int numberbooks(){
	FILE * news = NULL;
	news = fopen("Booklist.txt", "r+");
	if(news == NULL){
		puts("Erreur d'allocation");
		exit(1);
	}
	int number = 0;
	int c = 0;
	while((c = fgetc(news)) != EOF){
		if (c == '\n'){
			number++;
		}
	}
	fclose(news);
	return number;
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
	int nmb = numberbooks();
	struc = malloc(nmb * sizeof(Book));
	if(struc == NULL){
		exit(2);
	}
	for(int i = 0; i < nmb; i++){
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
	puts("****************************************");
	puts("Quel est votre livre?");
	scanf("%s", tit);
	flushScanf();
	fprintf(news, "%s\t", tit);
	
	puts("****************************************");
	puts("Quel est l'auteur?");
	scanf("%s", wri);
	flushScanf();
	fprintf(news, "%s\t", wri);
	
	puts("****************************************");
	puts("Quel est la catégorie?");
	scanf("%s", cat);
	flushScanf();
	fprintf(news, "%s\t", cat);
	puts("****************************************");
	
	nmb = numberbooks();
	fprintf(news, "%d\n", nmb+1);
	

	fclose(news);
}

//Emprunter un livre -> Recherche de livre par catégorie
void searchCategory(int nmb){
	Book* tab;
	tab = readBook();
	char category[50];
	puts("Quelle catégorie voulez-vous rechercher?");
	scanf("%s", category);
	puts("****************************************");
	printf("Livre en lien avec %s :\n", category);
	for(int i = 0; i< nmb; i++){
		if(strcmp(category, tab[i].category) == 0){
			printf("- %s de %s \n", tab[i].title, tab[i].writer);
		}
	}
	puts("****************************************");
}
//Emprunter un livre -> Liste des livres disponibles
void listBook(int nmb){
	Book* tab;
	tab = readBook();
	puts("****************************************\nVoici la liste des livres disponibles: \n");
	for(int i = 0; i<nmb; i++){
		if(tab[i].available == 0){
			printf("- %s de %s \n", tab[i].title, tab[i].writer);
		}
	}
	puts("****************************************");
}	

//Emprunter un livre -> Emprunt
void borrow(){
	Username* user;
	user = readFile();
	Book* tab;
	tab = readBook();
	char books[50];
	int j = 0;
	int nmb = numberusers();
	puts("Quel livre souhaitez-vous emprunter ?");
	scanf("%s", books);
	for(int i = 0; i < nmb; i++){
		if(strcmp(books, tab[i].title) == 0){
			if(tab[i].available == 0){
				int res = 0;
				while(user->borrow[j] > 0){
					if (j >= 5){
						puts("Vous avez déjà emprunté trop de livres ! Veuillez les rendre avant de vous resservir !");
						res = res + 1;
					}
					j++;
				}
				if(res == 0){
					user->borrow[j] = tab[i].number;
					puts("Livre emprunté");
					tab[i].available == 1;
				}
			}
		}
	}
}		


//MENU "Emprunter un livre"
void booking(){
	Book* tab;
	tab = readBook();
	int nmb = numberbooks();
	int choice;
	puts("****************************************");
	puts("1.Liste des livres disponibles \n2.Recherche de livre par catégorie \n(3.Emprunt) -pas réussi");
	do{
		scanf("%d", &choice);
		flushScanf();
	}while(choice > 3 || choice <= 0);
	if(choice == 2){
		searchCategory(nmb);
	}
	else if(choice == 1){
		listBook(nmb);
	}
	else{
		borrow();
	}
}

//Rendre un livre
void giveback(int session){
	Username* user;
	user = readFile();
	Book* tab;
	tab = readBook();
	puts("Lequel voulez-vous rendre ?");
	int res;
	scanf("%d", &res);
	int k = user[session].borrow[res];
	tab[k+1].available = 0;
	user[session].borrow[res] = 0;
	puts("Livre bien rendu ! \n"); 	
}		
