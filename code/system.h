/**
 * @file system.h
 * @brief  Gestion de l'ensemble des variables de paramètre du jeu
 */

#include "main.h"
#include "map.h"
#include "commons.h"

/**
 * @brief Initialisation des parametres
 *
 * @param param la structure a initialiser
 */

void initSettings(settings *param);

/**
 * @brief initialisation de la camera
 *
 * @return camera camera a initialiser
 */
camera initCam(void);
