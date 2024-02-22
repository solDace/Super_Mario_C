/**
 * @file bonus.h
 * @brief Fonctions realtives aux bonus
 */
#include "main.h"
#include "commons.h"

/**
* @brief Compte le nombre de bonus sur la map et le stock dans numberMushroom (variable globale)
 * 
 * @param map
 */
void countBonus(int **map);

/**
 * @brief Initialisation d'un champi rouge
 * 
 * @param powerUp 
 * @param x
 * @param y
 */
void initRedChampi(bonus *powerUp,int x,int y);

/**
 * @brief Initialisation d'un champi vert
 * 
 * @param powerUp 
 * @param x
 * @param y
 */
void initGreenChampi(bonus *powerUp,int x,int y);

/**
 * @brief Initialisation d'un champi vert
 * 
 * @param powerUp 
 * @param x
 * @param y
 */
void initStar(bonus *powerUp, int x, int y);

/**
 * @brief Créer et initilise le tableau contenant tous les bonus
 * 
 * @param map
 */
void initBonus( int **map);

/**
 * @brief Affichage de tout les bonus contenu dans le tableau
 * 
 * @param cam
 */
void displayBonus( camera cam);

/**
 * @brief Active les champignon apres avoir taper un bloc myster
 * 
 * @param x
 * @param y
 *
 */
void actifchampi(int x,int y);

/**
 * @brief Fait faire un déplacement à chaque bonus
 * 
 * @param map
 * @param cam
 */
void deplaceBonus( int **map, camera cam);

/**
 * @brief Test de collision entre un bunus et la map
 * 
 * @param powerUp 
 * @param map 
 * @param direction 
 * @param vitesse 
 * @return true
 * @return false
 */
bool isBlockBonus(bonus *powerUp, int **map, int direction, int vitesse);

/**
 * @brief Test pour savoir si un bonus va sortir de la map
 * 
 * @param powerUp
 * @param map 
 * @param direction 
 * @param vitesse 
 * @return true 
 * @return false
 */
bool mapEndBonus(bonus *powerUp, int **map, int direction, int vitesse);

/**
 * @brief Vide la case correspondant au bonus (a faire quand il est définitivement mort)
 * 
 * @param powerUp
 */
void mortBonus(bonus *powerUp);

/**
 * @brief Foncton regrouppant tout les mouvements des bonus (a appeler dans le main)
 *  
 * @param map 
 * @param cam 
 * @param perso 
 * @param soundEffect
 */
void BonusMouvement( int **map, camera cam, joueur *perso,sound soundEffect);
/**
 * @brief Gestion de la gravité pour tout les bonus
 *  
 * @param map 
 */
void bonusDescente( int **map);

/**
 * @brief Test de contact latéral entre un bonus et mario
 * 
 * @param powerUp
 * @param perso 
 * @return true 
 * @return false 
 */
bool bonusToucheCote(bonus *powerUp, joueur *perso);

/**
 * @brief fait monter l'etoile a une sertaine hauteur
 *  
 * @param map 
 */
void BonusMonte(int **map);

/**
 * @brief Gestion du mouvement de l'etoile
 *  
 * @param powerUp
 * @param map 
 */
void sautBonus(bonus *powerUp, int **map);