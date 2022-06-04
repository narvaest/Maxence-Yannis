#include "projet.h"
#include "book.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

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
	printf("Livre en lien avec %s :\n", category);
	for(int i = 0; i< 5; i++){
		if(strcmp(category, tab[i].category) == 0){
			printf("- %s de %s \n", tab[i].title, tab[i].writer);
		}
	}
}

void listBook(){
	Book* tab;
	tab = readBook();
	int choice;
	puts("Voici la liste des livres : ");
	for(int i = 0; i<5; i++){
		printf("%s de %s \n", tab[i].title, tab[i].writer);
	}
	puts("Voulez vous trier les livres ? (1 pour oui / 2 pour non)");
	scanf("%d", &choice);
	if(choice == 1){
		searchCategory();
	}
}	
	
void borrow(Username* user){
	Book* tab;
	tab = readBook();
	char borrow[50];
	int j = 0;
	puts("Quel livre souhaitez-vous emprunter ?");
	scanf("%s", borrow);
	for (int i = 0; i < 5; i++){
		if (strcmp(borrow, tab[i].title) != 0){
			puts("Ce livre n'esxiste pas dans la bibliothèque");
			exit(20);
		}
	}
	if (tab[i].available == 0){
		puts("Ce livre est déjà emprunté ! Vous ne pouvez pas le prendre !");
		exit(21);
	}
	tab[i].available == 0;
	while (user.borrow[j] > 0){
		j++;
		if (j >= 5){
			puts("Vous avez déjà emprunté trop de livres ! Veuillez les rendre avant de vous resservir !");
			exit(22);
		}
	}
	user.borrow[j] = number;
	puts("Livre emprunté");
}
			
			
	
