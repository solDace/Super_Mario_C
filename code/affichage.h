/**
 * @file affichage.h
 * @brief Ensemble des fonctions relatives au personnage
 */

#include "main.h"
#include "commons.h"

/**
 * @brief initialisation des polices
 *
 * @return fonts ensemble des polices utlisées dans le jeu
 */
fonts initFonts();

sound initSound();
/**
 * @brief affiche le score actuel du joueur et son nom
 *
 * @param nom
 * @param score
 * @param police
 */
void afficheScore(char *nom, int score, fonts police);

/**
 * @brief affiche le nombre de pieces du joueur
 *
 * @param pieces
 * @param police
 */
void afficheNombrePiece(int pieces, fonts police);

/**
 * @brief affiche le niveau actuel
 *
 * @param niveau
 * @param police
 */
void afficheNiveau(char *niveau, fonts police);

/**
 * @brief affiche le nombre de seconde écoulées depuis le début du niveau
 *
 * @param timer
 * @param police
 */
void afficheTimer(int timer, fonts police);

/**
 * @brief écran suite a la mort de la dernière vie
 */
void gameOverScreen(fonts police);

/**
 * @brief ecran affiche le nombre de vie qui restent
 */
void dieScreen(int life, fonts police);

/**
 * @brief affiche un bouton png avec le texte de notre choix à l'intérieur
 *
 * @param police structure contenant les polices initialisées
 * @param posx abscisse du point de départ du bouton
 * @param posy ordonnée du poitn de départ du bouton
 * @param title texte à afficher dans le bouton
 */
void button_maps(fonts police, int posx, int posy, char* title);
