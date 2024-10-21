#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

/*==============  FONCTIONS DEMANDEES ===============*/

// 1.	Ecrire une fonction qui permet de remplir une matrice creuse
void remplirMatrice(matrice_creuse *m, int N, int M) { //avant demander le nombre de ligne est de colonnes de la matrice
    int i = 0, j = 0, val;
    liste_ligne current_element;

    while(i < N){
        current_element = m->tab_lignes[i];
        j = 0;
        while(j < M){
            printf("    Veuillez entrer la valeur de la %d lignes, colonnes %d : ", i, j);
            if (scanf("%d", &val) != 1){
                printf("    ERREUR : Les char ne sont pas des int\n");
                viderBuffer();
            } else {
                if(val != 0) ajouterElement(&m->tab_lignes[i], j, val);   
                ++j;      
            } 
        }
        ++i;
    }
}


// 2.	Ecrire une fonction qui permet d�afficher une matrice creuse sous forme de tableau
void afficherMatrice(matrice_creuse m){
    int i, j;
    liste_ligne current_element;

    printf("[");
    for (i = 0 ; i < m.Nlignes ; ++i) {
        printf("[");
        current_element = m.tab_lignes[i];
        for(j = 0 ; j < m.Ncolonnes ; ++j){
            if (current_element != NULL && current_element->col == j) {
                printf("%d", current_element->val);
                current_element = current_element->suivant;
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



// 3.	Ecrire une fonction qui permet d�afficher toutes les listes cha�n�es
void afficherMatriceListes(matrice_creuse m) {
    int i;
    liste_ligne current_element;
    for (i = 0 ; i < m.Nlignes ; ++i) {
        current_element = m.tab_lignes[i];
        while (current_element != NULL) {
            printf("-> %d", current_element->val);
            current_element = current_element->suivant;
        }
        printf("\n");
    }
}



//  4.	Ecrire une fonction qui renvoie la valeur de l'�l�ment de la ligne i et la colonne j
int rechercherValeur(matrice_creuse m, int i, int j) {
    int result = 0;
    element* current = m.tab_lignes[i];
    while (current){
        if (current->col == j) return current->val;
        if (current->col > j) return result;
        current = current->suivant;
    }
    return result;
}



// 5.	Ecrire une fonction qui affecte une valeur donn�e � l'�l�ment de la ligne i et la colonne j
void affecterValeur(matrice_creuse m, int i, int j, int val) {
    if (val == 0) return;
    element* current = m.tab_lignes[i];
    element* prev = NULL;

    while (current) {
        if (current->col == j) {
            current->val = val; 
            return;
        }
        if (current->col > j) {
            element* nouv = creerElement(j, val);
            if (prev) {
                prev->suivant = nouv; 
            } else {
                m.tab_lignes[i] = nouv; 
            }
            nouv->suivant = current;
            return;
        }
        prev = current;
        current = current->suivant;
    }

    element* nouv = creerElement(j, val);
    if (prev) {
        prev->suivant = nouv;
    } else {
        m.tab_lignes[i] = nouv;
    }
}



// 6.	Ecrire une fonction qui r�alise la somme de deux matrices
void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    if (m1.Nlignes != m2.Nlignes || m1.Ncolonnes != m2.Ncolonnes) {
        printf("Les matrices doivent avoir les mêmes dimensions.\n");
        return;
    }
    for (int i = 0; i < m1.Nlignes; ++i) {
        element* current1 = m1.tab_lignes[i];
        element* current2 = m2.tab_lignes[i];
        element* prev1 = NULL;
        
        while (current2 != NULL) {
            if (current1 == NULL) {
                ajouterElement(&m1.tab_lignes[i], current2->col, current2->val);
                current2 = current2->suivant;
            }
            if (current1->col == current2->col) {
                current1->val += current2->val;
                if (current1->val == 0) {
                    if (prev1 == NULL) {
                        m1.tab_lignes[i] = current1->suivant;
                    } else {
                        prev1->suivant = current1->suivant;
                    }
                    element* temp = current1;
                    current1 = current1->suivant;
                    free(temp);
                } else {
                    prev1 = current1;
                    current1 = current1->suivant;
                }
                current2 = current2->suivant;
            } else if (current2->col < current1->col) {
                ajouterElement(&m1.tab_lignes[i], current2->col, current2->val);
                current2 = current2->suivant;
            } else {
                prev1 = current1;
                current1 = current1->suivant;
            }
        }
    }
}

// 7.	Ecrire une fonction qui retourne le nombre d�octets gagn�s
int nombreOctetsGagnes(matrice_creuse m) {
    int result = 0, i = 0;
    liste_ligne current_element = m.tab_lignes[i];
    result = sizeof(element)*m.Ncolonnes*m.Nlignes;

    for (i ; i < m.Nlignes ; ++i) {
        current_element = m.tab_lignes[i];
        while (current_element != NULL) {
            result -= sizeof(element);
            current_element = current_element->suivant;
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

	for (i = 0; i < m->Nlignes; ++i) { //initiqlisqtion de chqaue pointeur a NULL
        m->tab_lignes[i] = NULL;
    }
	 return m;
}

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

void ajouterElement(liste_ligne *ligne, int col, int val) {
    element *nouveau = creerElement(col, val);
    if (*ligne == NULL) {
        *ligne = nouveau;
    } else {
        element *actuel = *ligne;
        while (actuel->suivant != NULL) {
            actuel = actuel->suivant;
        }
        actuel->suivant = nouveau;
    }
}
