#ifndef MAGASIN_H
#define MAGASIN_H

typedef struct Article{
	char code[10];
	char nom_article[20];
	int qute_stock_article;
	int qute_seuil_article;
	float prix_unitaire_article;
} Article;

typedef struct Client{
	int numero_client;
	char nom_client[20];
	char tel_client[20];
	char adresse_client[20];
} Client;

typedef struct Vendeur{
	char matricule[10];
	char nom_vendeur[20];
	float salaire;
}Vendeur;

typedef struct commande{
	int numero_cmd;
	int numero_client;
	char **code_article;
	int *qute_article;
	char matricule[10];
}

int ajout_article();
int supprimer_article(char *);
int modifier_artice(char *);
int rechercher_article(char *);
Article * lecture_article( int *);


int recherche_vendeur(char *);
vendeur * lecture_vendeur(int *);
int ajouter_vendeur();
int supprimer_vendeur(char *);
int modifier(char *);

int recherche_client(int *);
client * lecture_client(int *);
int ajouter_vendeur();
int supprimer_vendeur(char *);
int modifier(char *);

