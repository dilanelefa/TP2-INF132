#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magasin.h"
#include "aide.h"

#define article "article.txt"

int ajout_article(){
	Article art;
	printf("Entrer le code: ");
	scanf("%d", &art.code_article);
	printf("Entrer le nom de l'article: ");
	scanf("%[^\n]", art.nom_article);
	getchar();
	printf("Entrer la quantite en stock: ");
	scanf("%d", &art.qute_stock_article);
	printf("Entrer la quantite seuil : ");
	scanf("%d", &art.qute_seuil_article);
	printf("Entrer le prix unitaire: ");
	scanf("%f", &art.prix_unitaire_article);
	
	//ouverture du fichier article.csv pour y stocker les donnees
	FILE *fp = fopen(article , "a");
	if(fp == NULL )
		return 0;
	fprintf(fp , "%d, %s, %d, %d, %f\n", art.code_article , art.nom_article , art.qute_stock_article, art.qute_seuil_article, art.prix_unitaire_article); 
	fclose(fp);
	return 1;	
}

//lecture des engeristrements contenue dans article
Article * lecture_article(int *n ){
	Article *art;
	int i = 0;
	FILE *fp = fopen(article , "r");
	if( fp == NULL)
		return NULL;
	
	do{
		if( i == 0) art = malloc(sizeof(*art));
		else art = realloc(art , (i+1)*sizeof(*art));
		if( art ==  NULL) return NULL;
		fscanf(fp , "%d, %[^,], %d, %d, %f\n", &art[i].code_article , art[i].nom_article , &art[i].qute_stock_article, &art[i].qute_seuil_article, &art[i].prix_unitaire_article);
		i++;
	}while(!feof(fp));
	fclose(fp);
	*n = i;
	return art;
}


//suppression d'un article par son code
int supprimer_article(int code){
	int k ,n ,i;
	k = rechercher_article(code);
	Article *art = lecture_article(&n);
	FILE *fp = fopen(article , "w");
	if( k == -1 || art == NULL || fp == NULL ) return 0;
	for(i = 0; i < n; i++){
		if( i != k){
			fprintf(fp , "%d, %s, %d, %d, %f\n", art[i].code_article , art[i].nom_article , art[i].qute_stock_article, art[i].qute_seuil_article, art[i].prix_unitaire_article);
		}
	}
	fclose(fp);
	return 1;
}


int rechercher_article(int code){
	int i, n ;
	Article *art = lecture_article(&n);
	for(i = 0; i < n; i++){
		if(art[i].code_article == code)
			return i;
	}
	return -1;
}
