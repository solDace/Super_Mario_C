/*!
* @file menu.h
* @brief prototypes de fonctions d'affichage et de gestion du menu du jeu
*/

/*! Importation of librairies*/
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include "commons.h"

/**
 * @brief fonction d'affichage du fond d'écran du menu
 *
 * @param disp pointeur de la fenêtre
 */
int displayBackground();

/**
 * @brief fonction d'affichage du tableau des scores, l'affichage du score n'est pas géré par cette fonction
 *
 * @param disp pointeur de la fenêtre
 */
void displayScoreTab(fonts police);

/**
 * @brief fonction qui initialise le tableau de char servant à récuperer le nom
 *
 * @param player_name tableau de char contenant le nom du joueur
 */
void initName(char player_name[LENGTH_NAME]);

/**
 * @brief fonction qui récupère chaque caractère du nom entré par le joueur et renvoi le system.mode en fonction
 *
 * @param caractere le caractère entré par le joueur
 * @param player_name tableau de char contenant le nom du joueur
 * @return int mets à jour le system.mode en fonction de l'action du joueur
 */
int recupName(int caractere, char player_name[LENGTH_NAME]);

/**
 * @brief affiche le pseudo entré par le joueur dans un cadre responsive
 *
 * @param disp pointeur de la fenêtre
 * @param player_name tableau de char contenant le nom
 * @param start coordonnée en fonction de laquelle est calculée la  taille/position du cadre
 */
void dispName(char player_name[LENGTH_NAME], int start, fonts police);

/**
 * @brief fonction qui dessine les boutons correspondants aux niveaux débloqués par le joueur courant
 * 
 * @param user structure du joueur courant
 * @param police structure contenant les polices initialisées
 */
void userDraw(playerStats user, fonts police);

/**
 * @brief fonction vérifiant l'état et la position de la souris pour l'utilisation des boutons de sélection de niveaux
 * 
 * @param user structure du joueur courant
 * @return int retourne le numéro de la map sélectionnée par le joueur
 */
int waiting_start(playerStats *user, joueur *personnage);

/**
 * @brief affiche le panneau notifiant le joueur d'entrée un pseudo
 * 
 * @param police structure contenant les polices initialisées
 */
void display_notif_name(fonts police);

/**
 * @brief affichage du menu pause
 * 
 * @param police 
 * @param blocks 
 * @param user 
 * @param soundEffect
 * @return int 
 */
int menu_pause(fonts police, cases blocks, playerStats *user);

/**
 * @brief fonctionnement du menu pause
 * 
 * @param police 
 * @param blocks 
 * @param user 
 * @param personnage
 * @return int 
 */
int pause(playerStats *user, settings *system, sound sound, joueur personnage);

/**
 * @brief Afffiche le nom qui est entrain d'être écrit
 * 
 * @param police structure contenant les polices initialisées
 * @param player_name Nom entrain d'être tapé
 */
void display_register_name(fonts police, char *player_name);

/**
 * @brief affichage du bouton de sélection du personnage jouable
 * 
 * @param personnage 
 */
void display_select_luigi(joueur *personnage);

/**
 * @brief affiche texte pour dire comment changer de sprite
 * 
 * @param police 
 */
void display_text_persoChangement(fonts police);
