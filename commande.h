#ifndef COMMMANDE_H
#define COMMANDE_H

#define commande "commande.txt" 
typedef struct Commande{
	char numero_cmd[5];
	int numero_client;
	char code_article[100][10];
	int qute_article[100];
	char matricule[10];
} Commande;
int commande_article();
int affichage_liste_article_disponible();
int ajout_cmd(int , char T[][], int *, int , char *);
int modifier_cmd(char *);
int supprimer_cmd(char *);
int rechercher_cmd(char *);
Commande *lecture_cmd(int *);

#endif
