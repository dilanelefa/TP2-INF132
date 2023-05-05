#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magasin.h"
#include "commande.h"
#include "aide.h"

int affichage_liste_article_disponible(){
	int n,i;
	Article *art = lecture_article(&n);
	for(i = 0 ; i < n; i++){
		if( art[i].qute_seuil_article < art[i].qute_stock_article){
			printf("%-15s %-20s %-10d %f\n", art[i].code_article , art[i].nom_article ,art[i].qute_stock_article , art[i].prix_unitaire_article);
		}
	}
	free(art);
}

int modifier_cmd(char *num){
	int i , n,m , k, pos,option;
	char temp[5];
	Article *art;
	Commande *cmd;
	FILE *f;
	cmd = lecture_cmd(&n);
	i = rechercher_cmd(num);
	if(cmd == NULL || i == -1)
		return 0;
	printf("numero commande: %s, numero du client: %d\n", cmd[i].numero_cmd, cmd[i].numero_client);
	printf("Que voulez vous modifier?\n");
	printf("0. annuler\n1. Ajouter des articles dans le panier\n2. Diminuer la quantite d'un article.\n3. Supprimer un article\n");
	scanf("%d",&option);
	int taille = sizeof(cmd[k].qute_article)/(int)sizeof(int);
	switch(option){
		case 0:
			return 1;
		case 1:
			taille++;
			if( cmd[i].code_article)
				return 0;
			affichage_liste_article_disponible();
			printf("\nEntrer le code de l'article que vous voulez: ");
			scanf("%s", cmd[i].code_article[taille-1]);
			printf(" la quantite: ");
			scanf("%d", &cmd[i].qute_article[taille-1]);
			
			
			f = fopen(commande, "w");
			if(f == NULL)
				return 0;
			fprintf(f, "%s, %d,\"", cmd[i].numero_cmd , cmd[k].numero_client);
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%s," , cmd[i].code_article[k]);
			fprintf(f, "\",\"");
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%d," , cmd[i].qute_article[k]);
			fprintf(f, "\", %s\n" , cmd[i].matricule);
			fclose(f);
			break;
		case 2: 
			art = lecture_article(&m);
			printf("%-8s %-15s %-4s\n", "Code" , "Designation", "quantite"); 
			for( k = 0 ; k < taille ; k++){
				pos = rechercher_article(cmd[i].code_article[k]);
				if( art[pos].qute_stock_article < cmd[i].qute_article[k])
					printf("%-8s %-15s pas en stock\n" , cmd[i].code_article[k] , art[pos].nom_article);
				else
					printf("%-8s %-15s %d\n", cmd[i].code_article[k] , art[pos].nom_article, cmd[i].qute_article[k]);
			}
			
			printf("\n\nEntrer le code de l'article a diminuer la quantite ");
			scanf("%s", temp);
			for(k = 0 ; k < taille ; k++){
				if(strcmp(toLowerCase(cmd[i].code_article[k]), toLowerCase(temp)) == 0){
					printf("Entrer la nouvelle quantite: ");
					scanf("%d", &cmd[i].qute_article[k]);
				}
			}
			
			
			f = fopen(commande, "w");
			if(f == NULL)
				return 0;
			fprintf(f, "%s, %d,\"", cmd[i].numero_cmd , cmd[k].numero_client);
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%s," , cmd[i].code_article[k]);
			fprintf(f, "\",\"");
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%d," , cmd[i].qute_article[k]);
			fprintf(f, "\", %s\n" , cmd[i].matricule);
			fclose(f);
		case 3:
			art  = lecture_article(&m);
			printf("%-8s %-15s %-4s\n", "Code" , "Designation", "quantite"); 
			for( k = 0 ; k < taille ; k++){
				pos = rechercher_article(cmd[i].code_article[k]);
				if( art[pos].qute_stock_article < cmd[i].qute_article[k])
					printf("%-8s %-15s pas en stock\n" , cmd[i].code_article[k] , art[pos].nom_article);
				else
					printf("%-8s %-15s %d\n", cmd[i].code_article[k] , art[pos].nom_article, cmd[i].qute_article[k]);
			}
			
			printf("\n\nEntrer le code de l'article a supprimer: ");
			scanf("%s", temp);
			for(k = 0 ; k < taille ; k++){
				if(strcmp(toLowerCase(cmd[i].code_article[k]), toLowerCase(temp)) == 0){
					printf("Entrer la nouvelle quantite: ");
					scanf("%d", &cmd[i].qute_article[k]);
				}
			}
			
			f = fopen(commande, "w");
			if(f == NULL)
				return 0;
			fprintf(f, "%s, %d,\"", cmd[i].numero_cmd , cmd[k].numero_client);
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%s," , cmd[i].code_article[k]);
			fprintf(f, "\",\"");
			for(k = 0 ; k < taille; k++) 
				fprintf(f, "%d," , cmd[i].qute_article[k]);
			fprintf(f, "\", %s\n" , cmd[i].matricule);
			fclose(f);
	}
	return 0;
}	
	

