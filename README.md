# NF16-TP3

- Langage : C
- IDE : codeBlock

## Enoncé

Une matrice est dite creuse lorsque le nombre d'éléments nuls y figurant est très supérieur à celui des éléments non nuls. Par souci d'économie, on peut représenter une telle matrice en ne tenant compte que des éléments non nuls : une matrice 𝑁 × 𝑀 est représentée par un tableau de 𝑁 listes chaînées qui contiennent les éléments non nuls d'une ligne de la matrice coordonnés selon le rang de leur colonne. Chaque élément d'une liste contient l'indice de la colonne et la valeur de l'élément.

## Présentation

L'objectif de ce TP est de modéliser des matrices creuses à l'aide des listes chainés en C. Nous effectuons des opérations simple sur celle-ci comme la recherche d'une valeur, l'addition de deux matrices ou encore leur affichage.

## Fonction supplémentaire

Nous avons décider d'ajouter deux fonctions supplémentaires : une pour l'initialisation d'une matrice creuse et une autre pour libération de l'espace mémoire d'une matrice creuse. Cela n'était pas obligatoire car nous les utilisions qu'une seule fois dans le code mais par soucis de maintenabilité nous avons décidé dans faire des fonctions.

## Compléxité

- void remplirMatrice(matrice_creuse *m, int N, int M) : fonction qui remplie une matrice creuse selon les saisies utilisateurs




