#pragma once
/**
 * @file piece.h
 * @brief Ensemble des fonctions relatives aux pièces
 *
 * (entièrement gérées par le groupe sous traitant)
 *
 */

#include <string.h>

#include "main.h"
#include "commons.h"

#define VITESSE_ROTATION_PIECE 180 //inverse de la vitesse de rotation (plus ce nombre est grand, plus la vitesse est petite)

/**
 * @brief Structure rassemblant toutes les caractéristiques d'une pièces
 *
 */
//#include "map.h"   // Pour la structure camera

/**
 * @brief Affiche une pièce au bonne endroit sur l'écran
 *
 * appel :
 *
 * map.c (l.280)
 *
 *
 *
 * @param model Piece servant de modèle pour savoir où en est la pièce de la ratation, et aussi avoir l'image de la pièce
 * @param x Abscisse du coin en haut à gauche de la pièce, en block (à multiplier par BLOCK_SIZE_RES dans la fonction)
 * @param y ordonnée du coin en haut à gauche de la pièce, en block (à multiplier par BLOCK_SIZE_RES dans la fonction)
 * @param cam Camera pour savoir où est la partie visible de l'écran
 */
void affichagePiece(piece *model, int x, int y, camera cam);

/**
 * @brief initialise toutes les variable de la structure
 *
 * appel :
 * main.c (l.46)
 *
 * @param model Piece servant de modèle pour savoir où en est la pièce de la ratation, et aussi avoir l'image de la pièce
 */
void initPiece(piece *model);

/**
 * @brief Effectue un ajout de pièce ou  de vie s'il y a >= 100 pièces
 *
 * appels :
 *
 *  - touchePiece()
 *  - joueur.c (l.334   l.374   l.463)
 *
 * @param player Informations regroupant les statsdu joueur actuel
 */
void ramassePiece(playerStats *player);

/**
 * @brief Ajout de la pièce dans les stats du joueur et enlève la pièce de la map
 *
 * Appels :
 *
 *   - joueur.c (l.407 et l.486)
 *
 *
 * @param player Informations regroupant les statsdu joueur actuel
 * @param map tableau deux dimensions (map[ligne][colonne]), qui dit où chaque block est placé
 * @param x Abscisse du coin en haut à gauche de la pièce, en block (à multiplier par BLOCK_SIZE_RES dans la fonction)
 * @param y ordonnée du coin en haut à gauche de la pièce, en block (à multiplier par BLOCK_SIZE_RES dans la fonction)
 */
void touchePiece(playerStats *player, int **map, int x, int y);
