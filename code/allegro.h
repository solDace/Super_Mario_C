/**
 * @file allegro.h
 * @brief Ensemble des fonctions reltives à la library
 * @version 0.1
 * @date 2021-01-10
 */

#include "main.h"
#include <allegro5\allegro_native_dialog.h>
#include "commons.h"
/**
 * @brief Initialise Allegro, le clavier, le timer, la file, les images, l'affichage et les polices d'écritures
 *
 * @return init Structure contenant les pointeur initialisés à récuperer dans le main
 */
init initLib(void);

/**
 * @brief Initialisation des mixers et sounds
 * 
 * @return sound Structure contenant les pointeurs initialisés à récuperer dans les différents code
 */
sound initSound(void);


/**
 * @brief Permet d'afficher le texte sous la forme d'un popup avec pour entête "Erreur"
 *
 * @param txt Contenu du popup (ecrire pourquoi cette erreur arrive)
 */
void erreur(const char *txt);

/**
 * @brief Pemet d'ajouter du son à un certain moment du timer 
 * 
 * @param timer 
 * @param soundEffect 
 * @param personnage
 * @param system 
 */
void sonTimer(int timer,sound soundEffect,joueur *personnage,settings *system);


/**
 * @brief Libère les pointeurs relatifs à la librairy
 *
 * @param timer
 * @param queue
 * @param disp
 * @param font
 * @param soundEffect
 */
void destructLib(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font,sound soundEffect);

