#include "projet.h"
#include "username.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  


int numberusers(){
	FILE * user = NULL;
	user = fopen("userslist.txt", "r+");
	if(user == NULL){
		puts("Erreur d'allocation");
		exit(1);
	}
	int number = 0;
	int c = 0;
	while((c = fgetc(user)) != EOF){
		if (c == '\n'){
			number++;
		}
	}
	fclose(user);
	return number;
}


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
	int nmb = numberusers();
	struc = malloc(nmb * sizeof(Username));
	if(struc == NULL){
		exit(2);
	}
	for(int i = 0; i < nmb; i++){
		fscanf(user, "%s", tmp);
		int N = strlen(tmp);
		struc[i].login = malloc( (N+1) * sizeof(char) );
		if(struc[i].login == NULL){
			puts("Erreur d'allocation");
			exit(3);
		}
	    strcpy(struc[i].login , tmp);
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
	
	puts("Quel est votre login?");
	scanf("%s", log);
	flushScanf();
	fprintf(new, "\n%s\t", log);
	
	
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
	fprintf(new, "%d", trk);
	fclose(new);
}
