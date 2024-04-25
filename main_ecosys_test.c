#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

//plot "Evol_Pop.txt" using 1:2 with lines title "proies"
//replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
int main(void) {
 
	/* A completer. Part 2:
	* exercice 4, questions 2 et 4 */
	/*INITIALISATION*/
	Animal *liste_proie = NULL;
 	Animal *liste_predateur = NULL;
 	int i;
 	int energie = 10;
 	int monde[SIZE_X][SIZE_Y];
    for(i=0; i<SIZE_X; i++){
        for(int j=0; j<SIZE_Y;j++){
            monde[i][j]=0;
        }
    }

 	/*TEST DEPLACEMENT*/
 	/*
 	for (int i = 0; i < 1000; ++i)
 	{
	 	bouger_animaux(liste_proie);
		printf("x = %d y = %d dir[0] = %d dir[1] = %d\n",liste_proie->x,liste_proie->y,liste_proie->dir[0],liste_proie->dir[1]);
		afficher_ecosys(liste_proie,liste_predateur);
 	}
	*/
	/*TEST REPRODUCTION*/
	/*
	reproduce(&liste_proie,p_reproduce_proie);
	bouger_animaux(liste_proie);
	afficher_ecosys(liste_proie,liste_predateur);
	reproduce(&liste_proie,p_reproduce_proie);
	bouger_animaux(liste_proie);
	afficher_ecosys(liste_proie,liste_predateur);
	*/
	/*
	while(i < 200 && compte_animal_it(liste_proie) > 0)
	{
		rafraichir_proies(&liste_proie,monde);
		afficher_ecosys(liste_proie,liste_predateur);
		usleep(500000);
		i++;
	}
	*/
	/*TEST RAFRAICHIR PREDATEURS*/

	for (i = compte_animal_it(liste_predateur); i < 108; ++i)
	{
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
	}
	
	/*TEST RAFRAICHIR PROIES*/
	for (i = compte_animal_it(liste_proie); i < 36; ++i)
	{
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
	}
	i = 0;
	//on ouvre le fichier en mode ecriture/write
    FILE *f = fopen("Evol_Pop.txt", "w");
	// on vérifier que f existe
    if (f == NULL)
    {
        printf("fichier %s manquant\n", "Evol_Pop.txt");
        return 0;
    }
    printf(">Voulez-vous ecraser la simulation precedente ?(y/n)\n");
    char dlt = ' ';
    scanf("%c",&dlt);
	while((i < 300) && ((compte_animal_it(liste_proie) > 0) && (compte_animal_it(liste_predateur) > 0)))
	{
		clear_screen();
		afficher_ecosys(liste_proie,liste_predateur);
		if (dlt == 'y')
		{
			fprintf(f,"%d %d %d\n",i,compte_animal_it(liste_proie),compte_animal_it(liste_predateur));
		}
		rafraichir_proies(&liste_proie,monde);
		rafraichir_predateurs(&liste_predateur,&liste_proie);
		usleep(100000);
		i++;
	}
	liberer_liste_animaux(liste_proie);
	liberer_liste_animaux(liste_predateur);
	return 0;
}