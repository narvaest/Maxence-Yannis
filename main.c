#include "projet.h"
#include "username.h"
#include "menu.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  



int main()
{
	Username* tab;
	int choice = connection();
	if(choice == 2){	
		newusers();
	}
	tab = readFile();
	char login[20];	
	char pw[20];
	int session = -1;
	int res = 0;
	puts("Entrer votre login :");
	scanf("%s", login);
	puts("Entrez votre mot de passe :");			
	scanf("%s", pw);
	int number = numberusers();
	for(int i = 0; i < number; i++){
		if((strcmp(login, tab[i].login)) == 0){
			res = 1;
			if((strcmp(pw, tab[i].password)) == 0){
				session = i;
				puts("Vous êtes connecté ! \n");
			}
		}
	}
	if(session == -1){
		if(res == 0){
			puts("Login introuvable, fermeture de la session ");
			exit(75);
		}
		puts("Mauvais mot de passe associé au login, fermeture de la session");
		exit(76);
	}

	int ch = 0;
	printf("****************************************\nBienvenue %s dans votre session \n****************************************\n", tab[session].login);
	if(tab[session].type == 1){
		do{
			ch = menuStudent();	
			if(ch == 1){
				booking();
			}
			else if(ch == 2){
				giveback(session);
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
				booking();
			}
			else if(ch == 2){
				giveback(session);
			}
			puts("");
		}while(ch != 3);
	}
	return 0;
}

