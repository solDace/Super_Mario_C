/**
 * @file stats.h
 * @brief Ensemble des fonctions relatives a la manipulations des statistiques
 *
 */

#include "main.h"

#include <stdlib.h>
#include "commons.h"

/**
 * @brief Permet de sauvegarder, dans un fichier externe, le score s'il fait partit des meilleurs scores
 *
 * @param user pointeur vers la structure stat contenant les stats de la partie.
 *
 * @return bool permetant de savoir si le score a bien ete sauvegarde.
 */
bool saveHS(playerStats *user);

/**
 * @brief Permet de sauvegarder l'ensemble des stats liees a la partie dans un fichier externe
 *
 * @param struct pointeur contenant les stats de la partie.
 * @param txt avec le nom du fichier dans lequel on veut sauvegarder.
 *
 * @return void
 */
void saveStats(playerStats *user, char *fileName);

/**
 * @brief Permet de modifier les statistiques de la partie en fonction des evenements exterieurs
 *
 * @param user pointeur vers la struct stat contenant les stats de la partie.
 * @param event le nom de l'evenement qui s'est produit
 *
 * @return void
 */
void modifyStats(playerStats *user, char *event);

/**
 * @brief Permet d'initialiser la structure contenant les statistiques.
 *
 * @param user pointeur vers la struct stat contenant les stats de la partie.
 * @param name le nom du joueur en train de jouer.
 *
 * @return void
 */
void initStats(playerStats *user, char *name);

/**
 * @brief réinitialise les staistique pour recommencer le niveau
 * 
 * @param user 
 */
void resetStats(playerStats *user);

/**
 * @brief Permet de recuperer les statistiques sauvegardées dans un fichier externe ou d'initialiser une structure vierge pour un joueur courant
 *
 * @param user pointeur vers la struct stat contenant les stats de la partie.
 * @param fileName le nom du fichier dans lequel on veut recuperer la sauvegarde.
 *
 * @return void
 */
void loadSave(playerStats *user, char *fileName);

/**
 * @brief Permet de recuperer les meilleurs scores sauvegardes et le nom du joueur qu'il l'a fait
 *
 * @param HS tableau de int ou on rangera les meilleurs scores
 * @param nameHS1 avec le nom des personnes ayant eu ce score.
 * @param nameHS2 avec le nom des personnes ayant eu ce score.
 * @param nameHS3 avec le nom des personnes ayant eu ce score.
 *
 * @return void
 */
void loadHS(int HS[3], char nameHS1[LENGTH_NAME], char nameHS2[LENGTH_NAME], char nameHS3[LENGTH_NAME]);

/**
 * @brief Permet d'afficher les meilleurs score et le nom de ce qu'ils les ont fait.
 *
 * @param x coordonnee x de l'affichage du premier score
 * @param y coordonnee y de l'affichage du premier score
 * @param method variable pour choisir le mode d'affichage
 * @param font police/taille de l'ecriture.
 *
 * @return void
 */
void DisplayHS(int x, int y, int method, ALLEGRO_FONT *font);
