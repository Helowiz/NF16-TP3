#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

#define MAX_MATRICES 100

int main() {

    matrice_creuse* matrices[MAX_MATRICES];
    int nombreMatrices = 0;

    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '8') {
        printf("\n======================================");
        printf("\n1. Remplir une matrice creuse");
        printf("\n2. Afficher une matrice creuse sous forme de tableau");
        printf("\n3. Afficher une matrice creuse sous forme de listes");
        printf("\n4. Donner la valeur d'un element d'une matrice creuse");
        printf("\n5. Affecter une valeur a un element d'une matrice creuse");
        printf("\n6. Additionner deux matrices creuses");
        printf("\n7. Calculer le gain");
        printf("\n8. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        switch (choix) {
            case '1' :
            {
                printf("\n### Remplir une nouvelle matrice creuse ###\n");
                int nbLigne, nbColonne;

                printf("Veuillez entrer le nombre de lignes de la matrice : ");
                if (!scanf("%d", &nbLigne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Veuillez entrer le nombre de colonnes de la matrice : ");
                if (!scanf("%d", &nbColonne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (nombreMatrices >= MAX_MATRICES) {
                    printf("ERREUR : Nombre maximum de matrices atteint\n");
                    break;
                }

                matrice_creuse* m = constructeurMatriceCreuse(nbLigne, nbColonne);
                remplirMatrice(m, nbLigne, nbColonne);
                matrices[nombreMatrices++] = m;
                break;
            }
            case '2' :
            {
                printf("\n### Afficher une matrice creuse sous forme de tableau ###\n");
                int index;

                printf("Choisissez la matrice à afficher [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                } else {
                    afficherMatrice(*matrices[index]);
                }
                break;
            }
            case '3':
            {
                printf("\n### Afficher une matrice creuse sous forme de listes ###\n");
                int index;

                printf("Choisissez la matrice à afficher [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                } else {
                    afficherMatriceListes(*matrices[index]);
                }
                break;
            }
            case '4':
            {
                printf("\n### Donner la valeur d'un élément d'une matrice creuse ###\n");
                int index, nLigne, nColonne;

                printf("Choisissez la matrice [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                    break;
                }

                matrice_creuse* m = matrices[index];
                if (m->Ncolonnes == 0 && m->Nlignes == 0){
                    printf("La matrice est vide");
                    break;
                }

                printf("Veuillez entrer la ligne : ");
                if (!scanf("%d", &nLigne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Veuillez entrer la colonne : ");
                if (!scanf("%d", &nColonne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                if (nColonne < m->Ncolonnes && nLigne < m->Nlignes && nColonne >= 0 && nLigne >= 0){
                    printf("\n    Ligne : %d ;\n    Colonne : %d ;\n    Valeur : %d ;", nLigne, nColonne, rechercherValeur(*matrices[index], nLigne, nColonne));
                } else {
                    printf("    Les valeurs colonnes ou lignes entree sont trop grande pour la matrice définit");
                }
                break;
            }
            case '5':
            {
                printf("\n### Affecter une valeur à un élément d'une matrice creuse ###\n");
                int index, nLigne, nColonne, valeur;

                printf("Choisissez la matrice [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                    break;
                }

                matrice_creuse* m = matrices[index];
                if (m->Ncolonnes == 0 && m->Nlignes == 0){
                    printf("La matrice est vide");
                    break;
                }

                printf("Veuillez entrer la ligne : ");
                if (!scanf("%d", &nLigne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Veuillez entrer la colonne : ");
                if (!scanf("%d", &nColonne)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }

                printf("Veuillez entrer la valeur : ");
                if (!scanf("%d", &valeur)){
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (nLigne >= m->Nlignes || nColonne >= m->Ncolonnes || nLigne < 0 || nColonne < 0){
                    printf("Les valeurs du numéro de ligne ou de colonne est incorrect");
                } else {
                    affecterValeur(*matrices[index], nLigne, nColonne, valeur);
                    printf("La valeur à bien été affecté");
                }
                break;
            }
            case '6':
            {
                printf("\n### Additionner deux matrices creuses ###\n");
                if (nombreMatrices < 2) {
                    printf("Il faut au moins deux matrices pour cette opération.\n");
                    break;
                }
                int index1, index2;
                printf("Choisissez la premiere matrice [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index1)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                printf("Choisissez la deuxieme matrice [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index2)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (index1 < 0 || index1 >= nombreMatrices || index2 < 0 || index2 >= nombreMatrices) {
                    printf("Indices de matrices invalides.\n");
                    break;
                }
                additionerMatrices(*matrices[index1], *matrices[index2]);
                break;
            }
            case '7':
            {
                printf("\n### Calcul du gain de mémoire ###\n");
                int index;

                printf("Choisissez la matrice [0...%d] : ", nombreMatrices - 1);
                if (!scanf("%d", &index)) {
                    printf("ERREUR : Le nombre saisi doit être un entier");
                    break;
                }
                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                    break;
                }

                printf("Gain de mémoire : %d octets\n", nombreOctetsGagnes(*matrices[index]));
                break;
            }
            case '8' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                for (int i = 0; i < nombreMatrices; i++) {
                    deconstructeurMatriceCreuse(*matrices[i]);
                    free(matrices[i]);
                }
                break;
            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
        viderBuffer();
    }
    return 0;
}
