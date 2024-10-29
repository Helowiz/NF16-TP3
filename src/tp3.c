#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

/*==============  FONCTIONS DEMANDEES ===============*/

// 1.	Ecrire une fonction qui permet de remplir une matrice creuse
void remplirMatrice(matrice_creuse *m, int N, int M) {
    if (N < 0 || M < 0) {
        printf("    ERREUR : Les dimensions de la matrice doivent être positives\n");
        return;
    }

    int i = 0, j = 0, val;
    while (i < N) {
        j = 0;
        element *actuelElement = NULL;
        while (j < M) {
            printf("    Veuillez entrer la valeur de la %d lignes, colonnes %d : ", i, j);
            if (scanf("%d", &val) != 1) {
                printf("    ERREUR : Le nombre saisie doit être un entier\n");
                viderBuffer();
            } else {
                if (val != 0) {
                    element *nouveauElement = creerElement(j, val);
                    if (!actuelElement) {
                        m->tab_lignes[i] = nouveauElement;
                        actuelElement = nouveauElement;
                    } else {
                        actuelElement->suivant = nouveauElement;
                        actuelElement = nouveauElement;
                    }
                }
                ++j;
            }
        }
        ++i;
    }
    printf("Matrice créée et remplie avec succès\n");
}


// 2.	Ecrire une fonction qui permet d'afficher une matrice creuse sous forme de tableau
void afficherMatrice(matrice_creuse m){
    int i, j;
    liste_ligne actuelElement;

    printf("[");
    for (i = 0 ; i < m.Nlignes ; ++i) {
        printf("[");
        actuelElement = m.tab_lignes[i];
        for(j = 0 ; j < m.Ncolonnes ; ++j){
            if (actuelElement && actuelElement->col == j) {
                printf("%d", actuelElement->val);
                actuelElement = actuelElement->suivant;
            } else {
                printf("0");
            }
            if (j < m.Ncolonnes - 1) printf(", ");
        }
        printf("]");
        if (i < m.Nlignes - 1) printf(",\n");
    }
    printf("]");
}



// 3.	Ecrire une fonction qui permet d'afficher toutes les listes chaînées
void afficherMatriceListes(matrice_creuse m) {
    int i;
    liste_ligne actuelElement;

    for (i = 0 ; i < m.Nlignes ; ++i) {
        printf("[]");
        actuelElement = m.tab_lignes[i];
        while (actuelElement) {
            printf("-> (Colonne : %d ; Valeur : %d) ", actuelElement->col, actuelElement->val);
            actuelElement = actuelElement->suivant;
        }
        printf("\n");
    }
}



//  4.	Ecrire une fonction qui renvoie la valeur de l'élément de la ligne i et la colonne j
int rechercherValeur(matrice_creuse m, int i, int j) {
    int result = 0;
    element* actuelElement = m.tab_lignes[i];

    while (actuelElement){
        if (actuelElement->col == j) return actuelElement->val;
        if (actuelElement->col > j) return result;
        actuelElement = actuelElement->suivant;
    }
    return result;
}



// 5.	Ecrire une fonction qui affecte une valeur donnée à l'élément de la ligne i et la colonne j
void affecterValeur(matrice_creuse m, int i, int j, int val) {
    element* actuelElement = m.tab_lignes[i];
    element* precedent = NULL;
    element* tmp;

    while(actuelElement){
        if(actuelElement->col == j) {
            if (val == 0) {
                tmp = actuelElement;
                actuelElement = actuelElement->suivant;
                free(tmp);
                if (precedent) {
                    precedent->suivant = actuelElement;
                } else {
                    m.tab_lignes[i] = actuelElement;
                }
                return;
            }
            actuelElement->val = val;
            return;
        }
        if(actuelElement->col > j) {
            if (val == 0) return;
            element *nouvelElement = creerElement(j, val);
            nouvelElement->suivant = actuelElement;
            if (precedent) {
                precedent->suivant = nouvelElement;
            } else {
                m.tab_lignes[i] = nouvelElement;
            }
            return;
        }
        precedent = actuelElement;
        actuelElement = actuelElement->suivant;
    }
    if (val == 0) return;
    element *nouvelElement = creerElement(j, val);
    if (precedent) {
        precedent->suivant = nouvelElement;
    } else {
        m.tab_lignes[i] = nouvelElement;
    }
}



// 6.	Ecrire une fonction qui réalise la somme de deux matrices
void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    element* actuelElementM1;
    element* actuelElementM2;
    element* precedentM1;
    element* tmp;
    int i;

    for(i = 0; i < m1.Nlignes;++i){
        actuelElementM1 = m1.tab_lignes[i];
        actuelElementM2 = m2.tab_lignes[i];
        precedentM1 = NULL;

        while(actuelElementM2){
            if(!actuelElementM1 || actuelElementM2->col < actuelElementM1->col){
                element *nouvelElement = creerElement(actuelElementM2->col, actuelElementM2->val);
                nouvelElement->suivant = actuelElementM1;
                if (precedentM1) {
                    precedentM1->suivant = nouvelElement;
                } else {
                    m1.tab_lignes[i] = nouvelElement;
                }
                precedentM1 = nouvelElement;
                actuelElementM2 = actuelElementM2->suivant;
            } else if(actuelElementM1->col < actuelElementM2->col){
                precedentM1 = actuelElementM1;
                actuelElementM1 = actuelElementM1->suivant;
            } else if(actuelElementM1 && actuelElementM1->col == actuelElementM2->col){
                actuelElementM1->val += actuelElementM2->val;
                if (actuelElementM1->val == 0){
                    tmp = actuelElementM1;
                    actuelElementM1 = actuelElementM1->suivant;
                    free(tmp);
                    if (precedentM1) {
                        precedentM1->suivant = actuelElementM1;
                    } else {
                        m1.tab_lignes[i] = actuelElementM1;
                    }
                } else {
                    precedentM1 = actuelElementM1;
                    actuelElementM1 = actuelElementM1->suivant;
                    actuelElementM2 = actuelElementM2->suivant;
                }
            }
        }
    }
    printf("Matrice additionnees avec succes.");
}

// 7.	Ecrire une fonction qui retourne le nombre d�octets gagn�s
int nombreOctetsGagnes(matrice_creuse m) {
    int result = 0, i = 0;
    liste_ligne actuelElement = m.tab_lignes[i];
    result = sizeof(element)*m.Ncolonnes*m.Nlignes;

    for (i ; i < m.Nlignes ; ++i) {
        actuelElement = m.tab_lignes[i];
        while (actuelElement) {
            result -= sizeof(element);
            actuelElement = actuelElement->suivant;
        }
    }
    return result;
}




/*==============  FONCTIONS SUPPLEMENTAIRES ===============*/

// fonction qui renvoie un nouvel �l�ment de liste
element *creerElement(int colonne, int valeur) {
    element *nouvelElement = malloc(sizeof(element));
    nouvelElement->col = colonne;
    nouvelElement->val = valeur;
    nouvelElement->suivant = NULL;
    return nouvelElement;
}


// fonction qui permet de vider le buffer d'entr�e clavier
void viderBuffer (){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/*==============  FONCTIONS AJOUTEE ===============*/

// fonction qui initialise une matrice creuse
matrice_creuse* constructeurMatriceCreuse(int N, int M){
     int i;
     matrice_creuse* m = (matrice_creuse *)malloc(sizeof(matrice_creuse));
	 m->Ncolonnes = M;
	 m->Nlignes = N;
	 m->tab_lignes = (liste_ligne*)malloc(m->Nlignes*sizeof(liste_ligne));

	for (i = 0; i < m->Nlignes; ++i) {
        m->tab_lignes[i] = NULL;
    }
	return m;
}

//fonction qui libère une matrice creuse
void deconstructeurMatriceCreuse(matrice_creuse m){
    element* tmp;
    for (int i = 0; i < m.Nlignes; i++) {
        while (m.tab_lignes[i]) {
            tmp = m.tab_lignes[i];
            m.tab_lignes[i] = m.tab_lignes[i]->suivant;
            free(tmp);
        }
    }
    free(m.tab_lignes);
}
