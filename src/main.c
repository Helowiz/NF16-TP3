#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main() {
    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (choix != '8') {
        printf("\n======================================");
        printf("\n1. Remplir une matrice creuse");
        printf("\n2. Afficher une matrice creuse sous forme de tableau");
        printf("\n3. Afficher une matrice creuse sous forme de listes");
        printf("\n4. Donner la valeur d'un element d'une matrice creuse");
        printf("\n5. Affecter une valeur à un élément d’une matrice creuse");
        printf("\n6. Additionner deux matrices creuses");
        printf("\n7. Calculer le gain");
        printf("\n8. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        matrice_creuse* m;
        switch (choix) {
            case '1' :
                {
                    int nbLigne, nbColonne;

                    printf("\n### Remplir une matrice creuse ###\n\n");
                    printf("    Veuillez entrer le nombre de ligne de la matrice ? ");
                    scanf("%d", &nbLigne);
                    printf("    Veuillez entrer le nombre de colonnes de la matrice ? ");
                    scanf("%d", &nbColonne);
                    if (nbLigne < 0 || nbColonne < 0) {
                        printf("Une matrice ne peut pas avoir un nombre de lignes ou de colonne negatif. ");
                        break;
                    }
                    m = constructeurMatriceCreuse(nbLigne, nbColonne);
                    afficherMatrice(*m);
                    remplirMatrice(m, m->Nlignes, m->Ncolonnes);
                    afficherMatrice(*m);
                    break;
                }
            case '2' :
                {
                    printf("\n### Afficher une matrice creuse sous forme de tableau ###\n\n");
                    afficherMatrice(*m);
                    break;
                }

            case '3' :
                {
                    printf("\n### Afficher une matrice creuse sous forme de listes ###\n\n");
                    afficherMatriceListes(*m);
                    break;
                }

            case '4' :
                {
                    printf("\n### Donner la valeur d'un element d'une matrice creuse ###\n\n");

                    if (m->Ncolonnes == 0 && m->Nlignes == 0){
                        printf("    La matrice est vide");
                        break;
                    }
                    int nLigne, nColonne;
                    printf("    Veuillez entrer la ligne ? ");
                    scanf("%d", &nLigne);
                    printf("    Veuillez entrer la colonne ? ");
                    scanf("%d", &nColonne);
                    if (nColonne <= m->Ncolonnes && nLigne <= m->Nlignes ){
                        printf("\n    Ligne : %d ;\n    Colonne : %d ;\n    Valeur : %d ;", nLigne, nColonne, rechercherValeur(*m, nLigne, nColonne));
                    } else {
                        printf("    Les valeurs colonnes ou lignes entree sont trop grande pour la matrice définit");
                    }
                    break;

                }
            case '5' :
                {
                    printf("\n### Affecter une valeur à un élément d’une matrice creuse ###\n\n");

                    if (m->Ncolonnes == 0 && m->Nlignes == 0){
                        printf("    La matrice est vide");
                        break;
                    }
                    int nLigne, nColonne, valeur;
                    printf("    Veuillez entrer la ligne ? ");
                    scanf("%d", &nLigne);
                    printf("    Veuillez entrer la colonne ? ");
                    scanf("%d", &nColonne);
                    printf("    Veuillez entrer la valeur ? ");
                    scanf("%d", &valeur);
                    if (nColonne <= m->Ncolonnes && nLigne <= m->Nlignes && valeur != 0){
                        affecterValeur(*m, nLigne, nColonne, valeur);
                        printf("La valeur a ete affectee");
                    } else {
                        printf("    Les valeurs colonnes ou lignes entree sont trop grande pour la matrice définit");
                    }
                    break;
                }


            case '6' :
                // Ecrire ici le code pour ce choix utlisateur
                break;

            case '7' :
               {
                 printf("%d", nombreOctetsGagnes(*m));
                 break;
               }

            case '8' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
        viderBuffer();
    }

    return 0;
}
