#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"
#include "afficheur.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

//plot "Evol_Pop.txt" using 1:2 with lines title "proies"
//replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"
int main(void) {
	/*INITIALISATION*/
	//INITIALISATION MONDE
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
    //INITIALISATION PREDATEURS
    for (i = compte_animal_it(liste_predateur); i < 80; ++i)
	{
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
	}
	
	//INITIALISATION PROIES
	for (i = compte_animal_it(liste_proie); i < 40; ++i)
	{
		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
	}
	i = 0;
	//on ouvre le fichier en mode ecriture/write
    FILE *f = NULL;
    /*SIMULATION*/
    afficheur("SIMULATION ECOSYSTEME");
    printf(">Voulez-vous ecraser la simulation precedente ?(y/n)\n");
    char c = ' ';
    scanf("%c",&c);
    if (c == 'y')
	{
		f = fopen("Evol_Pop.txt", "w");
		// on vérifier que f existe
		if (f == NULL)
		{
			printf("fichier %s manquant\n", "Evol_Pop.txt");
			return 0;
		}
	}
	while((i < 1200) && (compte_animal_it(liste_proie) > 0) && (compte_animal_it(liste_predateur) > 0))
	{
		clear_screen();
		afficher_ecosys(liste_proie,liste_predateur);
		if (c == 'y')
		{
			fprintf(f,"%d %d %d\n",i,compte_animal_it(liste_proie),compte_animal_it(liste_predateur));
		}
		rafraichir_proies(&liste_proie,monde);
		rafraichir_predateurs(&liste_predateur,&liste_proie);
		usleep(T_WAIT);
		i++;
	}
	afficher_ecosys(liste_proie,liste_predateur);
	liberer_liste_animaux(liste_proie);
	liberer_liste_animaux(liste_predateur);
	return 0;
}