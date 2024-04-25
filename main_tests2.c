#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ecosys.h"

void ecrire_ecosys(const char *nom_fichier, Animal *liste_proie, Animal *liste_predateur)
{
    //on ouvre le fichier en mode ecriture/write
    FILE *f = fopen(nom_fichier, "w");
	// on vérifier que f existe
    if (f == NULL)
    {
        printf("fichier %s manquant\n", nom_fichier);
        return;
    }

    //on met les proies dans le fichier f
    //fprintf sert à écrire dans le fichier, elle ecrira la balise d'ouverture <proies>
    fprintf(f, "<proies>\n");
    //on cree une variable de parcourt tmp qui sert à parcourir la liste
    Animal *tmp = liste_proie;
    //tant que la liste n'est pas null/finit
    while (tmp)
    {
        //on copie les donnees des proies 
        printf("x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
        fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
        tmp = tmp->suivant;
    }
    //on ferme la balise
    fprintf(f, "</proies>\n");

    //on met les predateurs dans le fichier f
    //on reprend le même principe pour prédateur
    fprintf(f, "<predateurs>\n");
    tmp = liste_predateur;
    while (tmp)
    {
        fprintf(f, "x= %d y= %d dir=[%d %d] e= %f\n", tmp->x, tmp->y, tmp->dir[0], tmp->dir[1], tmp->energie);
        tmp = tmp->suivant;
    }
    fprintf(f, "</predateurs>\n");
    printf("</predateurs>\n");
    //une fois que c'est fini on ferme le fichier
    fclose(f);
}
void lire_ecosys(char* nom_fichier,  Animal **liste_proie, Animal **liste_predateur){
    //on ouvre le fichier en mode lecture "r"
    FILE *f = fopen(nom_fichier, "r");
    // on vérifier que f existe
    if (f == NULL)
    {
        printf("fichier %s manquant\n", nom_fichier);
        return;
    }
    // reinitialisation des listes pour eviter toute fuite de memoire
    liberer_liste_animaux(*liste_proie);
    liberer_liste_animaux(*liste_predateur);
    //creation du tableau
    char buffer[255];
    //creation de la variable stockant la ligne
    char *ligne = (char*)malloc(256);
    //on cree les variables qui vont nous permettre de cree un animal
    int x, y;
    float e;
    int dir[2];
    //lecture proie
    //on check si la premiere ligne est bien la ligne proie
    assert(strncmp(fgets(buffer, 255, f), "<proies>", 8) == 0);
    //on récupère la deuxième ligne
    ligne = fgets(buffer, 255, f);
    //on parcourt le buffer tant qu'on n'a pas la balise de fin
    while(strncmp(buffer, "</proies>", 9) != 0)
    {
        //on récupère les valeurs de l'animal
        sscanf(ligne, "x= %d y= %d dir=[%d %d] e= %f\n",&x,&y,&dir[0],&dir[1],&e);
        Animal *a_lu = creer_animal(x, y, e);
        a_lu->dir[0] = dir[0];
        a_lu->dir[1] = dir[1];
        Animal *tmp = *liste_proie;
        //si c'est le premier animal de la liste
        if (*liste_proie == NULL)
        {
            a_lu->suivant = *liste_proie;
            *liste_proie = a_lu;
            printf("\nx= %d y= %d dir=[%d %d] e= %f\n", (*liste_proie)->x, (*liste_proie)->y, (*liste_proie)->dir[0], (*liste_proie)->dir[1], (*liste_proie)->energie);
        }else{
            //si il y a deja des animaux dans la liste on va au bout de la liste et on l'ajoute à la fin
            while(tmp->suivant != NULL){
                tmp = tmp->suivant;
            }
            tmp->suivant = a_lu;
        }
        fgets(buffer, 255, f);
    }
    //lecture predateurs
    //on check si la première ligne est bien la ligne predateurs
    assert(strncmp(fgets(buffer, 255, f), "<predateurs>", 8) == 0);
    //on récupère la deuxième ligne
    ligne = fgets(buffer, 255, f);
    //on parcourt le buffer tant qu'on n'a pas la balise de fin
    while(strncmp(buffer, "</predateurs>", 9) != 0)
    {
        //on récupère les valeurs de l'animal
        sscanf(ligne, "x= %d y= %d dir=[%d %d] e= %f\n",&x,&y,&dir[0],&dir[1],&e);
        Animal *a_lu = creer_animal(x, y, e);
        a_lu->dir[0] = dir[0];
        a_lu->dir[1] = dir[1];
        Animal *tmp = *liste_predateur;
        //si c'est le premier animal de la liste
        if (*liste_predateur == NULL)
        {
            a_lu->suivant = *liste_predateur;
            *liste_predateur = a_lu;
            printf("\nx= %d y= %d dir=[%d %d] e= %f\n", (*liste_predateur)->x, (*liste_predateur)->y, (*liste_predateur)->dir[0], (*liste_predateur)->dir[1], (*liste_predateur)->energie);
        }else{
            //si il y a deja des animaux dans la liste on va au bout de la liste et on l'ajoute à la fin
            while(tmp->suivant != NULL){
                tmp = tmp->suivant;
            }
            tmp->suivant = a_lu;
        }
        fgets(buffer, 255, f);
    }
    free(ligne);
    //on ferme le fichier
    fclose(f);
}

int main(int argc, char const *argv[])
{
    /*INITIALISATION*/
	Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
    Animal *liste_proie2 = NULL;
    Animal *liste_predateur2 = NULL;
	int energie=10;

    /*TEST DES FONCTIONS DE BASES*/
	for (int i = 0; i < 10; ++i)
	{
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
	}
	afficher_ecosys(liste_proie,liste_predateur);
	Animal *a1 = creer_animal(0,10, energie);
	liste_proie = ajouter_en_tete_animal(liste_proie, a1);
	Animal *a2 = creer_animal(15,35, energie);
	liste_predateur = ajouter_en_tete_animal(liste_predateur, a2);
	afficher_ecosys(liste_proie,liste_predateur);
	enlever_animal(&liste_proie,a1);
	enlever_animal(&liste_predateur,a2);
	afficher_ecosys(liste_proie,liste_predateur);

    /*TEST DES FONCTIONS LECTURE/ECRITURE*/

	ecrire_ecosys("ecosys.txt", liste_proie, liste_predateur);
    lire_ecosys("ecosys.txt", &liste_proie2, &liste_predateur2);  
    Animal *tmp = liste_proie;
    Animal *tmp2 = liste_proie2;
    while(tmp != NULL && tmp2 != NULL){
        tmp = tmp->suivant;
        tmp2 = tmp2->suivant;
    }
    if (tmp != tmp2)
    {
        printf("liste_proie differentes\n");
    }else{
        printf("proies identiques\n");
    }
    tmp = liste_predateur;
    tmp2 = liste_predateur2;
    while(tmp != NULL && tmp2 != NULL){
        tmp = tmp->suivant;
        tmp2 = tmp2->suivant;
    }
    if (tmp != tmp2)
    {
        printf("liste_predateur differentes\n");
    }else{
        printf("predateurs identiques\n");
    }

    /*LIBERATION MEMOIRE*/
    printf("on libere proie\n");
    liberer_liste_animaux(liste_proie);
    printf("on libere proie2\n");
    liberer_liste_animaux(liste_proie2);
    printf("on libere predateur\n");
    liberer_liste_animaux(liste_predateur);
    printf("on libere predateur2\n");
    liberer_liste_animaux(liste_predateur2);
	return 0;
}
