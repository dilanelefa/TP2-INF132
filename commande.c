#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "commande.h"
#include "magasin.h"
#include "aide.h"

//liste des articles que l'on commande.
int affichage_liste_article_disponible(){
	int n,i;
	Article *art = lecture_article(&n);
	for(i = 0 ; i < n; i++){
		if( art[i].qute_seuil_article < art[i].qute_stock_article){
			printf("%6d %-20s %-10d %f\n", art[i].code_article , art[i].nom_article ,art[i].qute_stock_article , art[i].prix_unitaire_article);
		}
	}
	free(art);
}

void generateur_cmd(char num[8]){
	srand(time(NULL));
	int i = rand()%(100-0)+1;
	struct tm* t;
	time_t temp_actuel = time(NULL);
	t = localtime(&temp_actuel);
	sprintf(num , "%dC%d", t->tm_yday , i);
}

//les fonctions de gestion de commande

//ajouter une commande
int ajout_cmd(int numero_client, int *code_article, int *qute_article, int taille , char *matricule){
	char numero_cmd[8];
	int n, i;
	generateur_cmd(numero_cmd); // le numero de commande est genere aleatoirement pour eviter au maximun des doublons
	
	FILE *file = fopen(commande, "a");
	if(file == NULL)
		return 0;
		
	fprintf(file, "%s, %d, %s, qute: %d,", numero_cmd, numero_client, matricule, taille); // la quantite d'article commande est sauvegarde pour faciliter la manipulation dans la suite.
	for(i = 0; i < taille ; i++)
	{
		fprintf(file, "%d-%d,", code_article[i], qute_article[i]);
	}
	fprintf(file , "\n");
	fclose(file);
	return 1;
}

//fonction permettant a un client de commande des articles.
int commande_article(){
	int n, i;
	char opt;
	Article *art = lecture_article(&n); // recuperation des articles
	printf("1\n");
	if(art == NULL){
		return 0;
	}
	 i = 0;
	 Commande cmd;
	 cmd.code_article = malloc(4*sizeof(int));
	 cmd.qute_article = malloc(4*sizeof(int)); // allocation de l'espace memoire pour les articles
	 if( cmd.qute_article == NULL || cmd.code_article == NULL)
	 	return 0;
	affichage_liste_article_disponible();
	printf("---------------------------------------------------\n");
	for(i = 0; i < 4; i++){
		printf("\nEntrer le code de l'article[%d] a commande: " , i+1);
		scanf("%d" , &cmd.code_article[i]);
		printf("Entrer la quantite[%d]: " , i+1);
		scanf("%d" , &cmd.qute_article[i]);
	}
	do{
		cmd.code_article = realloc(cmd.code_article, (i+1)*sizeof(int));
	 	cmd.qute_article = realloc(cmd.qute_article ,(i+1)*sizeof(int));
	 	 if( cmd.qute_article == NULL || cmd.code_article == NULL)
	 	return 0;

	 	printf("Entrer le code de l'article[%d] a commande: " , i+1);
		scanf("%d" , &cmd.code_article[i]);
		printf("Entrer la quantite[%d]: " , i+1);
		scanf("%d" , &cmd.qute_article[i]);
		getchar();
		printf("Voulez vous continuer[O/N] ");
		scanf("%c", &opt);
		i++;
	}while(opt != 'N' && opt !='n');
	cmd.taille = i;
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
		free(cmd.code_article);
		free(cmd.qute_article);
		return;
	}*/
	printf("Entrer le matricule du vendeur ");
	scanf("%s" , cmd.matricule);
		
	if( ajout_cmd(cmd.numero_client , cmd.code_article , cmd.qute_article , cmd.taille, cmd.matricule))
	{
		printf("Commande reussie!!\n");
		return 1;
	}
	
	free(cmd.code_article); //liberation de l'espace memoire allouer pour les articles commande
	free(cmd.qute_article);
	return 0;
}


Commande *lecture_cmd(int *n){
	int i = 0 , j , taille;
	Commande *cmd; // l'utilisation du pointeur dans ce cas permet de generer un tableau de taille exacte pour tous les commandes
	FILE *f = fopen(commande, "r");
	if( f == NULL)
		return NULL;
	
	do{
		if( i == 0) cmd = malloc(sizeof(Commande)); // allocation de la taille pour la lecture d'une commande;
		else cmd = realloc(cmd , (i+1)*sizeof(Commande));
		if( cmd == NULL)
			return NULL; // le return NULL permet de connaitre si l'allocation s'est faite ou pas
		char *buffer = malloc(150*sizeof(char));
		fscanf(f, "%[^,], %d, %[^,], qute: %d,%s\n", cmd[i].numero_cmd , &cmd[i].numero_client, cmd[i].matricule, &cmd[i].taille , buffer );
		cmd[i].code_article = malloc(taille*sizeof(int));
		cmd[i].qute_article = malloc(taille*sizeof(int));
		if(cmd[i].code_article == NULL || cmd[i].qute_article == NULL)
			return NULL;
		char *tokens = strtok(buffer, ",");
		j = 0;
		while( tokens != NULL){
			sscanf(tokens, "%d-%d", &cmd[i].code_article[j], &cmd[i].qute_article[j]);
			tokens = strtok(NULL, ",");
			j++;
		}
		free(buffer);
		i++;
	}while(!feof(f));
	
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
		if(strcmp(toUpperCase(num) , toUpperCase(cmd[i].numero_cmd)) == 0)//la fonction  toUpperCase() renvoie une copie en la chaine en parametre en magiscule permettant de faciliter la recherche.
			return i;
	}
	
	return -1;
}

int supprimer_cmd(char *num){
	Commande *cmd;
	int i,n,j;
	cmd = lecture_cmd(&n);
	i = rechercher_cmd(num);
	if(cmd == NULL || i == -1)
		return 0;
	//renitialisation du fichier commande.txt
	FILE *file = fopen(commande,  "w");
	if(file == NULL )
		return 0;
	for(int k = 0; k < n; k++){
		if(k != i ){
			fprintf(file, "%s, %d, %s, qute: %d,", cmd[i].numero_cmd, cmd[i].numero_client,cmd[i].matricule, cmd[i].taille);
			for(i = 0; i < cmd[i].taille ; i++)
			{
				fprintf(file, "%d-%d,", cmd[i].code_article[i], cmd[i].qute_article[i]);
			}
			fprintf(file , "\n");		
		}
	}
	
	fclose(file);
	return 1;
}
