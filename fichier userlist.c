#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

typedef struct{
	char* login;
	char* password;
	int type;
}Username;



//menu d'utilisation et choix
int menu(){
	puts("Quelle action voulez vous faire?");
	puts("1.Emprunter un livre");
	puts("2.Rendre un livre");
	puts("3.Se déconnecter");
	int res = 0;
	do{
		scanf("%d", &res);
	}while(res > 3 || res <= 0);
	return res;
}

//menu de connexion
int connection(){
	puts("****************************************************** \n  		Application CY-BiblioTECH			 \n ******************************************************");
	puts(" 1.Se connecter \n 2.Nouvel utilisateur");
	int res = 0;
	do{
		scanf("%d", &res);
	}while(res > 2 || res <= 0);
	printf("%d", res);
	return res;
}

/*
 declaration tableau 'tmp' 256 char
 recuperation "%s" du fscanf dans le tableau 'tmp' 
 recuperation longueur 'L' de la chaine avec strlen(tmp)
 allocation chaine de caracteres avec 'L'+1 (\0) et stockage adresse dans structure (login, password)
 copy 'tmp' dans 'malloc' (login, password)
	
*/  



Username* readFile(){
	char tmp[256];
	char top[256];
	Username* struc = NULL;
	FILE* user = NULL;
	user = fopen("userslist.txt", "r+");
	if(user == NULL){
		puts("Erreur d'allocation");
		printf("%d : %s", errno, strerror(errno));
		exit(1);
	}
	struc = malloc(5 * sizeof(Username));
	if(struc == NULL){
		exit(2);
	}
	for(int i = 0; i < 5; i++){
//		fscanf(user, "%s", struc[i].login);
		fscanf(user, "%s", tmp);
		int N = strlen(tmp);
		struc[i].login = malloc( (N+1) * sizeof(char) );
		if(struc[i].login == NULL){
			puts("Erreur d'allocation");
			exit(3);
		}
	    strcpy(struc[i].login , tmp);
//		fscanf(user, "%s", struc[i].password);
		fscanf(user, "%s", top);
		int M = strlen(top);
		struc[i].password = malloc( (M+1) * sizeof(char) );
		if(struc[i].password == NULL){
			puts("Erreur d'allocation");
			exit(4);
		}
	    strcpy(struc[i].password , top);
		fscanf(user, "%d", &(struc[i].type));
	}
	
	fclose(user);
	return struc;
}
	
int main()
{
	Username* tab;
	tab = readFile();
	for(int i = 0; i < 5; i++){
		printf("%s, %s, %d \n", tab[i].login, tab[i].password, tab[i].type);
	}
	return 0;
}

