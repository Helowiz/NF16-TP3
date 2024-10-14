#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
#define OCTET_INT 4

/*==============  FONCTIONS DEMANDEES ===============*/

// 1.	Ecrire une fonction qui permet de remplir une matrice creuse
void remplirMatrice(matrice_creuse *m, int N, int M) { //avant demander le nombre de ligne est de colonnes de la matrice
    int i, j, val;
    liste_ligne current_element;

    for(i = 0; i < N; ++i){
        current_element = m->tab_lignes[i];
        for(j = 0;j < M; ++j){
            printf("    Veuillez entrer la valeur de la %d lignes, colonnes %d : ", i, j);
            scanf("%d", &val); // TO DO traiter les erreurs utilisateurs ?
            if(val != 0){
                ajouterElement(&m->tab_lignes[i], j, val);
            }
        }
    }
}


// 2.	Ecrire une fonction qui permet d�afficher une matrice creuse sous forme de tableau
void afficherMatrice(matrice_creuse m){
    int i, j, val = 0;
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
    element* current_element = m.tab_lignes[i];
    while (current_element){
        if (current_element->col == j) return current_element->val;
        if (current_element->col > j) return result;
        current_element = current_element->suivant;
    }
    return result;
}



// 5.	Ecrire une fonction qui affecte une valeur donn�e � l'�l�ment de la ligne i et la colonne j
void affecterValeur(matrice_creuse m, int i, int j, int val) {
    if (val == 0) return;
    element* current_element = m.tab_lignes[i];
    while (current_element){
        if (current_element->col == j) current_element->val = val;
        if (current_element->col > j) return;
        current_element = current_element->suivant;
    }
    return;
}



// 6.	Ecrire une fonction qui r�alise la somme de deux matrices
void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {
    /*
    * TO DO : Ecrire ici votre code
    */
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
