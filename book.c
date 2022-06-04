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
		fscanf(paper, "%d", &(struc[i].available));
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
	fprintf(news, "%d\t", nmb);
	
	puts("Quel est votre livre?");
	scanf("%s", tit);
	flushScanf();
	fprintf(news, "%s\t", tit);
	
	
	puts("Quel est l'auteur?");
	scanf("%s", wri);
	flushScanf();
	fprintf(news, "%s\t", wri);
	
	puts("Quel est la catégorie?");
	scanf("%s", cat);
	flushScanf();
	fprintf(news, "%s\t", cat);
	
	nmb = numberbooks();
	fprintf(news, "%d\n", nmb+1);
	

	fclose(news);
}



void searchCategory(int nmb){
	Book* tab;
	tab = readBook();
	char category[50];
	puts("Quelle catégorie voulez-vous rechercher?");
	scanf("%s", category);
	printf("Livre en lien avec %s :\n", category);
	for(int i = 0; i< nmb; i++){
		if(strcmp(category, tab[i].category) == 0){
			printf("- %s de %s \n", tab[i].title, tab[i].writer);
		}
	}
}

void listBook(int nmb){
	Book* tab;
	tab = readBook();
	puts("Voici la liste des livres disponibles: ");
	for(int i = 0; i<nmb; i++){
		if(tab[i].available == 0){
			printf("%s de %s \n", tab[i].title, tab[i].writer);
		}
	}
}	

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
				FILE* paper = NULL;
				fopen = fopen("Booklist.txt", "a");
					if(paper == NULL){
						puts("Erreur d'allocation");
						exit(1);
					}
				tab[i].available == 1;
				
				
				
				
				
				
				
				fclose(paper);
				while(user->borrow[j] > 0){
					j++;
					if (j >= 5){
						puts("Vous avez déjà emprunté trop de livres ! Veuillez les rendre avant de vous resservir !");
						exit(22);
					}
				}
				user->borrow[j] = tab[i].number;
				puts("Livre emprunté");
			}
		}
	}
	
//	puts("Ce livre est déjà emprunté ou n'existe pas");
}		

void booking(){
	Book* tab;
	tab = readBook();
	int nmb = numberbooks();
	int choice;
	puts("1.Liste des livres disponibles \n2.Recherche de livre par catégorie \n3.Emprunt \n");
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
