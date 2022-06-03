#include "projet.h"
#include "username.h"
#include "menu.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  


/*
 declaration tableau 'tmp' 256 char
 recuperation "%s" du fscanf dans le tableau 'tmp' 
 recuperation longueur 'L' de la chaine avec strlen(tmp)
 allocation chaine de caracteres avec 'L'+1 (\0) et stockage adresse dans structure (login, password)
 copy 'tmp' dans 'malloc' (login, password)
	
*/  


int main()
{
	Username* tab;
	int choice = connection();
	Book* bat; 
	bat = readBook();
	if(choice == 2){	
		newusers();
	}
	tab = readFile();
	char login[20];	
	char pw[20];
	int session = -1;
	puts("Entrer votre login :");
	scanf("%s", login);
	puts("Entrez votre mot de passe :");			
	scanf("%s", pw);
	for(int i = 0; i < 5; i++){
		if((strcmp(login, tab[i].login)) == 0){
			puts("Login bon");
			if((strcmp(pw, tab[i].password)) == 0){
				session = i;
				puts("Vous êtes connecté");
			}
		}
	}
	if(session == -1){
		printf("Login introuvable, fermeture de la session \n");
		exit(75);
	}
	
	
	int ch = 0;
	if(tab[session].type == 1){
		do{
			ch = menuStudent();	
			if(ch == 1){
		// faire fonction emprunter un livre
				listBook();
			}
			else if(ch == 2){
				puts("Pas encore codé");
			}
			puts("");
		}while(ch != 3);
	}
	else{
		do{
			ch = menuTeacher();
			if(ch == 4){
				newbooks();
			}
			else if(ch == 1){
		// faire fonction emprunter un livre
				listBook();
			}
			else if(ch == 2){
				puts("Pas encore codé");
			}
			puts("");
		}while(ch != 3);
	}
	return 0;
}

