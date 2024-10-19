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
        printf("\n5. Affecter une valeur � un �l�ment d�une matrice creuse");
        printf("\n6. Additionner deux matrices creuses");
        printf("\n7. Calculer le gain");
        printf("\n8. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        switch (choix) {
            case '1' :
                {
                    int nbLigne, nbColonne;
                    printf("\n### Remplir une nouvelle matrice creuse ###\n");
                    printf("Veuillez entrer le nombre de lignes de la matrice : ");
                    scanf("%d", &nbLigne); 
                    printf("Veuillez entrer le nombre de colonnes de la matrice : ");
                    scanf("%d", &nbColonne);

                    if (nbLigne < 0 || nbColonne < 0) {
                        printf("Les dimensions de la matrice doivent être positives\n");
                        break;
                    }

                    if (nombreMatrices >= MAX_MATRICES) {
                        printf("Nombre maximum de matrices atteint\n");
                        break;
                    }

                    matrice_creuse* m = constructeurMatriceCreuse(nbLigne, nbColonne);
                    remplirMatrice(m, nbLigne, nbColonne);
                    matrices[nombreMatrices++] = m;
                    printf("Matrice créée et remplie avec succès\n");
                    break;
                }
            case '2' :
                {
                    printf("\n### Afficher une matrice creuse sous forme de tableau ###\n\n");
                    if (nombreMatrices == 0) {
                        printf("Aucune matrice à afficher.\n");
                        break;
                    }
                    int index;
                    printf("Choisissez la matrice à afficher (0-%d) : ", nombreMatrices - 1);
                    scanf("%d", &index);

                    if (index < 0 || index >= nombreMatrices) {
                        printf("Indice de matrice invalide.\n");
                    } else {
                        afficherMatrice(*matrices[index]);
                    }
                    break;
                }
            case '3': {
                printf("\n### Afficher une matrice creuse sous forme de listes ###\n\n");
                if (nombreMatrices == 0) {
                    printf("Aucune matrice à afficher.\n");
                    break;
                }
                int index;
                printf("Choisissez la matrice à afficher (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index);

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                } else {
                    afficherMatriceListes(*matrices[index]);
                }
                break;
            }

            case '4': {
                printf("\n### Donner la valeur d'un élément d'une matrice creuse ###\n\n");
                if (nombreMatrices == 0) {
                    printf("Aucune matrice disponible.\n");
                    break;
                }
                int index, nLigne, nColonne;
                printf("Choisissez la matrice (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index);
                matrice_creuse* m = matrices[index];

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                    break;
                }

                if (m->Ncolonnes == 0 && m->Nlignes == 0){
                    printf("    La matrice est vide");
                    break;
                }

                printf("Veuillez entrer la ligne : ");
                scanf("%d", &nLigne);
                printf("Veuillez entrer la colonne : ");
                scanf("%d", &nColonne);

                if (nColonne <= m->Ncolonnes && nLigne <= m->Nlignes ){
                    printf("\n    Ligne : %d ;\n    Colonne : %d ;\n    Valeur : %d ;", nLigne, nColonne, rechercherValeur(*matrices[index], nLigne, nColonne));
                }
                else {
                      printf("    Les valeurs colonnes ou lignes entree sont trop grande pour la matrice d�finit");
                }
                break;
            }


            case '5': {
                printf("\n### Affecter une valeur à un élément d'une matrice creuse ###\n\n");
                if (nombreMatrices == 0) {
                    printf("Aucune matrice disponible.\n");
                    break;
                }
                int index, nLigne, nColonne, valeur;
                printf("Choisissez la matrice (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index);
                matrice_creuse* m = matrices[index];

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                    break;
                }

                if (m->Ncolonnes == 0 && m->Nlignes == 0){
                    printf("    La matrice est vide");
                    break;
                }

                printf("Veuillez entrer la ligne : ");
                scanf("%d", &nLigne);
                printf("Veuillez entrer la colonne : ");
                scanf("%d", &nColonne);
                printf("Veuillez entrer la valeur : ");
                scanf("%d", &valeur);

                if (nColonne <= m->Ncolonnes && nLigne <= m->Nlignes && valeur != 0){
                    affecterValeur(*matrices[index], nLigne, nColonne, valeur);
                    printf("La valeur a ete affectee");
                } else {
                    printf("    Les valeurs colonnes ou lignes entree sont trop grande pour la matrice d�finit");
                }
                break;
            }

            case '6': {
                printf("\n### Additionner deux matrices creuses ###\n\n");
                if (nombreMatrices < 2) {
                    printf("Il faut au moins deux matrices pour cette opération.\n");
                    break;
                }
                int index1, index2;
                printf("Choisissez la première matrice (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index1);
                printf("Choisissez la deuxième matrice (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index2);

                if (index1 < 0 || index1 >= nombreMatrices || index2 < 0 || index2 >= nombreMatrices) {
                    printf("Indices de matrices invalides.\n");
                    break;
                }

                if (matrices[index1]->Nlignes != matrices[index2]->Nlignes ||
                    matrices[index1]->Ncolonnes != matrices[index2]->Ncolonnes) {
                    printf("Les matrices doivent avoir les mêmes dimensions.\n");
                    break;
                }

                additionerMatrices(*matrices[index1], *matrices[index2]);
                printf("Addition effectuée avec succès.\n");
                break;
            }

            case '7': {
                printf("\n### Calcul du gain de mémoire ###\n\n");
                if (nombreMatrices == 0) {
                    printf("Aucune matrice disponible.\n");
                    break;
                }
                int index;
                printf("Choisissez la matrice (0-%d) : ", nombreMatrices - 1);
                scanf("%d", &index);

                if (index < 0 || index >= nombreMatrices) {
                    printf("Indice de matrice invalide.\n");
                } else {
                    int gain = nombreOctetsGagnes(*matrices[index]);
                    printf("Gain de mémoire : %d octets\n", gain);
                }
                break;
            }
            case '8' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
        viderBuffer();
    }

    return 0;
}