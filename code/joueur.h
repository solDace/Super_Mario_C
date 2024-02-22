/**
 * @file joueur.h
 * @brief Ensemble des fonctions relatives au personnage
 *
 */

#include "main.h"
#include "stats.h"
#include "commons.h"
#include "ennemi.h"

/**
 * @brief Initialisation de l'image du personnage
 *
 * @param path chemin de l'image du personnage
 * @param personnage
 */
void initImage(char *path, joueur *personnage);

/**
 * @brief Initialisation du personnage
 *
 * @param personnage
 *
 */
void initPersonnage(joueur *personnage);

/**
 * @brief Permet de faire sauter le personnage
 *
 * @param personnage
 * @param map
 * @param soundEffect
 */
void personnageMonte(joueur *personnage, int **map, sound soundEffect);

/**
 * @brief Permet de faire descendre le personnage
 *
 * @param personnage
 * @param map
 * @param rep
 * @param soundEffect
 */

void personnageDescente(joueur *personnage, int **map, ennemi *rep, sound soundEffect);

/**
 * @brief Permet de regrouper les différentes fonctions du saut avec les collisions des blocks
 *
 * @param personnage
 * @param map
 * @param rep
 * @param soundEffect
 */

void sautpersonnage(joueur *personnage, int **map, ennemi *rep, sound soundEffect);

/**
 * @brief Permet d'afficher le perssonage lors du saut
 *
 * @param personnage
 * @param cam
 * @param map
 * @param soundEffect
 */
void afficheImageJump(joueur *personnage, camera *cam, int **map, sound soundEffect);

/**
 * @brief Permet de donner une nouvelle abscissee au personnage dans le sens positif
 *
 * @param personnage
 * @param cam
 * @param map
 * @param soundEffect
 *
 */
void avancer(joueur *personnage, camera *cam, int **map, ennemi *rep,sound soundEffect);

/**
 * @brief Permet de faire avancer le personnage d'une distance voulue en appelant la fonction avancer
 *
 * @param ptpersonnage
 * @param cam
 * @param map
 * @param soundEffect
 *
 */
void avanceEvent(joueur *ptpersonnage, camera *cam, int **map, ennemi *rep,sound soundEffect);

/**
 * @brief Permet de creer un mouvement en faisant defiler les sprites
 *
 * @param personnage
 * @param cam
 * @param map
 * @param soundEffect
 *
 */
void afficheAnime(joueur *personnage, camera *cam, int **map, sound soundEffect);

/**
 * @brief Permet de donner une nouvelle abscissee au personnage dans le sens negatif
 *
 * @param personnage
 * @param cam
 * @param map
 * @param soundEffect
 *
 */
void reculer(joueur *personnage, camera *cam, int **map, ennemi *rep,sound soundEffect);

/**
 * @brief Permet de faire reculer le personnage d'une distance voulue en appelant la fonction avancer
 *
 * @param ptpersonnage
 * @param cam
 * @param map
 * @param soundEffect
 *
 */
void reculerEvent(joueur *ptpersonnage, camera *cam, int **map, ennemi *rep,sound soundEffect);

/**
 * @brief Savoir s'il y a un bloque dans la continuité du déplacement de mario
 *
 * @param personnage
 * @param map
 * @param direction
 * @param vitesse MOUVEMENT: Prend en compte le mouvement du joueur | PIXEL: Test au pixel à côté
 * @param user stats correspondant au joueur actuel
 * @param soundEffect
 * @return true Il y a un bloc
 * @return false Il n'y a pas de block
 */
int isBlock(joueur *personnage, int **map, int direction, int vitesse, sound soundEffect);

/**
 * @brief Gestion des réactions particulière d'un block suite à une collision
 * 
 * @param map 
 * @param x 
 * @param y 
 * @param personnage 
 * @param soundEffect
 */
void changeBlock(int **map, int x, int y, joueur *personnage, sound soundEffect);

/**
 * @brief Détection de s'il y a un ennemi en dessou de mario
 *
 * @param perso
 * @param mechant
 * @return true il y en a un
 * @return false il n'y en a pas
 */
bool isEnnemi(joueur *perso, ennemi mechant);

/**
 * @brief savoir si le joueur sort de la map
 *
 * @param perso
 * @param map
 * @param direction
 * @param vitesse
 * @return true il est en dehors
 * @return false il est dans la map
 */
bool mapEndJoueur(joueur *perso, int **map, int direction, int vitesse);

/**
 * @brief savoir si le joueur est sur le ligne du drapeau
 *
 * @param perso
 * @param map
 * @return true il l'est
 * @return false il ne l'est pas
 */
bool isFlag(joueur *perso, int **map);

/**
 * @brief gestion des mouvements de mario une fois le drapeau touché
 *
 * @param ptpersonnage
 * @param system
 * @param map
 * @param soundEffect
 * @return true
 * @return false
 */
void endLevelAnimtion(joueur *ptpersonnage, settings *system, int **map, int timer, sound soundEffect);

/**
 * @brief Changement du sprite du personnage
 * 
 * @param personnage 
 */
void ChangementSpritePersonnage(joueur *personnage);

/**
 * @brief filtre la couleur des sprite
 * 
 * @param un entier 
 */
ALLEGRO_COLOR couleurFiltre(int cpt);