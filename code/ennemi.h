/**
 * @file ennemi.h
 * @brief Fonctions realtives aux ennemis
 *
 */

#include "main.h"
#include "commons.h"

/**
 * @brief Initialisation d'un goomba
 *
 * @param goomba
 * @param x
 * @param y
 */
void initGoomba(ennemi *goomba, int x, int y);

/**
 * @brief initialisation d'un koopa
 * 
 * @param koopa 
 * @param x 
 * @param y 
 */
void initKoopa(ennemi *koopa, int x, int y);

/**
 * @brief Compte le nombre d'ennemis sur la map et le stock dans numberEnnemis (variable globale)
 *
 * @param map
 */
void countEnnemis(int **map);

/**
 * @brief Créer et initilise le tableua contenant tous les ennemis
 *
 * @param rep
 * @param map
 * @return ennemi*
 */
ennemi *initEnnemis(ennemi *rep, int **map);

/**
 * @brief Affichage de tout les ennemis contenu dans le tableau
 *
 * @param rep
 * @param cam
 */
void displayEnnemi(ennemi *rep, camera cam);

/**
 * @brief Fait faire un déplacement à chaque ennemi
 *
 * @param rep
 * @param map
 * @param cam
 * @param soundEffect
 */
void deplaceEnnemi(ennemi *rep, int **map, camera cam,sound soundEffect);

/**
 * @brief Test de collision entre un ennemi et la map
 *
 * @param mechant
 * @param map
 * @param direction
 * @param vitesse
 * @return true
 * @return false
 */
bool isBlockEnnemi(ennemi mechant, int **map, int direction, int vitesse);

/**
 * @brief Gestion de la gravité pour tout les ennemis
 *
 * @param rep
 * @param map
 */
void ennemiDescente(ennemi *rep, int **map);

/**
 * @brief Foncton regrouppant tout les mouvements des ennemis (a appeler dans le main)
 *
 * @param rep
 * @param map
 * @param cam
 * @param perso
 * @param soundEffect
 */
void ennemiMouvement(ennemi *rep, int **map, camera cam, joueur *perso,sound soundEffect);

/**
 * @brief Test pour savoir si un ennemi va sortir de la map
 *
 * @param sujet
 * @param map
 * @param direction
 * @param vitesse
 * @return true
 * @return false
 */
bool mapEndEnnemi(ennemi sujet, int **map, int direction, int vitesse);

/**
 * @brief Vide la case correspondant à l'ennemi (a faire quand il est définitivement mort)
 *
 * @param mechant
 */
void mortEnnemi(ennemi *mechant);

/**
 * @brief etat transitoire de mort d'un goomba
 * 
 * @param goomba 
 */
void mortGoomba(ennemi *goomba);

/**
 * @brief etat transitoire de mort d'un koopa
 * 
 * @param koopa 
 */
void mortKoopa(ennemi *koopa);

/**
 * @brief Test de contact latéral entre un ennemi et mario
 *
 * @param mechant
 * @param perso
 * @return true
 * @return false
 */
bool ennemiToucheCote(ennemi mechant, joueur *perso);

/**
 * @brief contct entre deux ennemis
 *
 * @param mechant
 * @param numero le numero du gommba en question dans le repertoire d'ennemis
 * @param rep
 * @param direction
 * @param vitesse
 * @param soundEffect
 * @return true
 * @return false
 */
bool ennemiToucheEnnemi(ennemi *mechant, int numero, ennemi *rep, int direction, int vitesse,sound soundEffect);
