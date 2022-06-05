#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

void flushScanf(){
	int res;
	char c;
	do{
		res = scanf("%c", &c);
	} while( res==1 && c!='\n' );
}	

//menu d'utilisation et choix
int menuStudent(){
	puts("Quelle action voulez vous faire?");
	puts("1.Emprunter un livre");
	puts("(2.Rendre un livre) - pas réussi");
	puts("3.Se déconnecter");
	int res = 0;
	do{
		scanf("%d", &res);
		flushScanf();
	}while(res > 3 || res <= 0);
	return res;
}

int menuTeacher(){
	puts("Quelle action voulez vous faire?");
	puts("1.Emprunter un livre");
	puts("(2.Rendre un livre) - pas réussi");
	puts("3.Se déconnecter");
	puts("4.Ajouter un livre");
	int res = 0;
	do{
		scanf("%d", &res);
		flushScanf();
	}while(res > 4 || res <= 0);
	return res;
}

//menu de connexion
int connection(){
	puts("****************************************************** \n  		Application CY-BiblioTECH			 \n ******************************************************");
	puts(" 1.Se connecter \n 2.Nouvel utilisateur");
	int res = 0;
	do{
		scanf("%d", &res);
		flushScanf();
	}while(res > 2 || res <= 0);
	return res;
}


