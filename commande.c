#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "commande.h"
#include "magasin.h"
#include "aide.h"

void generateur_cmd(char num[8]){
	srand(time(NULL));
	int i = rand()%(100-0)+1;
	struct tm* t;
	time_t temp_actuel = time(NULL);
	t = localtime(&temp_actuel);
	sprintf(num , "%dC%d", t->tm_yday , i);
}

//les fonctions de gestion de commande
int ajout_cmd(int numero_client, char *code_article[], int *qute_article, int taille , char *matricule){
	char numero_cmd[8];
	generateur_cmd(numero_cmd);
	FILE *f = fopen(commande, "a");
	if( f == NULL ) 
		return 0;
	fprintf(f, "%s, %d,\"", numero_cmd , numero_client);
	for(int i = 0 ; i < taille; i++) 
		fprintf(f, "%s," , code_article[i]);
	fprintf(f, "\",\"");
	for(int i = 0 ; i < taille; i++) 
		fprintf(f, "%d," , qute_article[i]);
	fprintf(f, "\", %s\n" , matricule);
	fclose(f);
	
	return 1;
}

int commande_article(){
	int n, i;
	char opt;
	Article *art = lecture_article(&n);
	if(art == NULL){
		return 0;
	}
	 i = 0;
	 Commande cmd;
	 
	do{
		affichage_liste_article_disponible();
		printf("Entrer le code de l'article a commande: ");
		scanf("%s" , cmd.code_article[i]);
		getchar();
		printf("Entrer la quantite: ");
		scanf("%d" , &cmd.qute_article[i]);
		getchar();
		i++;
		printf("Voulez vous continuez la commande? [O/N] ");
		scanf("%c", &opt);
	}while(opt != 'N');
	
	printf("Entrer le numero du client ");
	scanf("%d", &cmd.numero_client);
	/*if(rechercher_client(cmd.numero_client) == -1){
		printf("Vous etes pas client? Veuillez vous inscrire");
		if(ajout_client());
			printf("inscription reussie, Veuillez recommencer votre commande.");
		}
		else{
			printf("inscription echoue, Veuillez recommencer inscription a partir de la page d'accueil.");
		}
		free(cmd.article);
		free(cmd.qute_article);
		return;
	}*/
	printf("Entrer le matricule du vendeur ");
	scanf("%s" , cmd.matricule);
		
	if( ajout_cmd(cmd.numero_client , cmd.code_article , cmd.qute_article , i , cmd.matricule))
	{
		printf("Commande reussie!!");
		return 1;
	}
	return 0;
}


Commande *lecture_cmd(int *n){
	Commande *cmd;
	int i = 0;
	FILE *f = fopen(commande, "r");
	if( f == NULL)
		return NULL;
	
	while(!feof(f)){
		if( i == 0) cmd = (Commande*)malloc(sizeof(Commande));
		else cmd = (Commande*)realloc(cmd , (i+1)*sizeof(Commande));
		if( cmd ==  NULL) 
			return NULL;
		fscanf(f, "%[^,], %d, \"", cmd[i].numero_cmd , &cmd[i].numero_client);
		int j = 0;
		do{
			fscanf(f, "%[^,],", cmd[i].code_article[j]);
			j++;
		}while(fgetc(f) != '"');
		fgetc(f);
		printf("%c\n", fgetc(f));
		j = 0;
		do{
			fscanf(f, "%d", &cmd[i].qute_article[j]);
			j++;
		}while(fgetc(f) != '"'); 
		fscanf(f , "\",%s" , cmd[i].matricule); 
		i++;
	}
	fclose(f);
	*n = i;
	return cmd;
}

int rechercher_cmd(char *num){
	Commande *cmd;
	int i,n;
	cmd = lecture_cmd(&n);
	if(cmd == NULL)
		return -1;
	for(i = 0; i < n; i++)
	{
		if(strcmp(toUpperCase(num) , toUpperCase(cmd[i].numero_cmd)) == 0)
			return i;
	}
	
	return -1;
}

int supprimer_cmd(char *num){
	Commande *cmd;
	int i,n;
	cmd = lecture_cmd(&n);
	i = rechercher_cmd(num);
	if(cmd == NULL || i == -1)
		return 0;
	//renitialisation du fichier commande.txt
	FILE *f = fopen(commande,  "w");
	if(f == NULL )
		return 0;
	for(int k = 0; k < n; k++){
		if(k != i ){
			int taille = sizeof(cmd[k].qute_article)/(int)sizeof(int);
			fprintf(f, "%s, %d,\"", cmd[k].numero_cmd , cmd[k].numero_client);
			for(i = 0 ; i < taille; i++) 
				fprintf(f, "%s," , cmd[k].code_article[i]);
			fprintf(f, "\",\"");
			for(i = 0 ; i < taille; i++) 
				fprintf(f, "%d," , cmd[k].qute_article[i]);
			fprintf(f, "\", %s\n" , cmd[k].matricule);			
		}
	}
	fclose(f);
	return 1;
}
