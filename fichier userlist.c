#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

	

typedef struct{
	char* login;
	char* password;
	int type;
	char* borrow[20];
}Username;

	
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
	puts("2.Rendre un livre");
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
	puts("2.Rendre un livre");
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
	for(int i = 0; i < 2; i++){
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

	
	
void newusers(){
	FILE * new = NULL;
	new = fopen("userslist.txt", "a");
	if(new == NULL){
		puts("Erreur d'allocation");
		exit(1);
	}
	char log[20]; 
	char pw[20]; 
	int trk = 0;
	
	//SEGMENTATION FAULT
	
	puts("Quel est votre login?");
	scanf("%s", log);
	flushScanf();
	//scanf("%s", log);
	fprintf(new, "%s\t", log);
	
	
	puts("Quel est votre mot de passe?");
	scanf("%s", pw);
	flushScanf();
	fprintf(new, "%s\t", pw);
	if(new == NULL){
			puts("Erreur d'allocation");
			exit(74);
	}
	do{
		puts("Quel est votre profession ? (1 = élèves, 2 = professeur)");
		scanf("%d", &trk);
		flushScanf();
	}while(trk > 2 || trk <= 0);
	fprintf(new, "%d\n", trk);
	fclose(new);
}

	
int main()
{
	Username* tab;
	tab = readFile();
	printf("%d \n", tab[1].type);
	int choice = connection();
	if(choice == 2){	
		newusers();
	}	
	return 0;
}

//Faire un systeme de connexion
//Si la personne est professeur, il peut ajouter un livre 
//Faire un système d'emprunt de livre et pour rendre le lire 
