/**
 * @file map.h
 * @brief Fonctions relatives aux maps
 *
 */

#include <stdio.h>
#include "main.h"
#include "commons.h"

/**
 * @brief récupère les informations écrite dans le fichier en question
 *
 * @param level chaine de caractère correspondant au nom du niveau
 * @return int** Tableau correspondant a la map (mémoire allouée dynamiquement)
 */
int **loadMap(char *level, ennemi *rep);

/**
 * @brief détruit le tableau deux dimansions correspondant a la map
 *
 * @param map
 */
void destructMap(int **map);

/**
 * @brief affiche les blocks selon où la caméra est placé
 *
 * @param map int** |correspondant à l'emplacement des blocks de la map
 * @param cam camera | structure qui garde en mémoire la partie de la map a afficher
 * @param blocks cases | structure gardant les bitmap précédement chargés
 */
void displayMap(int **map, camera cam, cases *blocks);

/**
 * @brief Chargement des bitmap des blocs
 *
 * @param blocks cases | structure gardant les bitmap précédement chargés
 */
void initCases(cases *blocks);
