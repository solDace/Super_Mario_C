/**
 * @file commons.h
 * @brief Ensemble définitions des structures, énumérations et variables globales
 */

#ifndef commons
#define commons

#include "main.h"

/**
 * @brief taille initiale des blocks
 */
#define BLOCK_SIZE_SRC 16

/**
 * @brief taille des blocks à l'écran
 *
 * diviseur entier de WINDOW_HEIGHT
 */
#define BLOCK_SIZE_RES 48

#define JUMP_HEIGHT 4.37
//------------------------------------ Allegro ------------------------------------//

/**
 * @struct init
 *
 * @brief Permet de manipuler tout les pointeurs relatifs à librairy d'un coup
 */
typedef struct Init
{
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_FONT *font;

    int success;
} init;

/**
 * @struct fonts
 * @brief structure pour regrouper toutes les polices utilisées
 */
typedef struct FONTS
{
    ALLEGRO_FONT *gameplay;
    ALLEGRO_FONT *fontScore;
} fonts;

/**
 * @struct sound
 * @brief structure pour regrouper toutes les mixers et les samples
 *
 */
typedef struct Sound
{
    ALLEGRO_MIXER *master_mixer;
    ALLEGRO_MIXER *music_mixer;
    ALLEGRO_MIXER *sound_mixer;
    ALLEGRO_VOICE *voice;

    ALLEGRO_SAMPLE_INSTANCE *songInstance;
    ALLEGRO_SAMPLE_INSTANCE *star;
    ALLEGRO_SAMPLE_INSTANCE *pause;
    ALLEGRO_SAMPLE_INSTANCE *click_pause;
    ALLEGRO_SAMPLE_INSTANCE *stomp;
    ALLEGRO_SAMPLE_INSTANCE *breakBlock;
    ALLEGRO_SAMPLE_INSTANCE *bump;
    ALLEGRO_SAMPLE_INSTANCE *powerup_appears;
    ALLEGRO_SAMPLE_INSTANCE *coin;
    ALLEGRO_SAMPLE_INSTANCE *powerup;
    ALLEGRO_SAMPLE_INSTANCE *up;
    ALLEGRO_SAMPLE_INSTANCE *jump;
    ALLEGRO_SAMPLE_INSTANCE *die;
    ALLEGRO_SAMPLE_INSTANCE *gameOver;
    ALLEGRO_SAMPLE_INSTANCE *powerdown;
    ALLEGRO_SAMPLE_INSTANCE *kick;
    ALLEGRO_SAMPLE_INSTANCE *stage_clear;
    ALLEGRO_SAMPLE_INSTANCE *world_clear;
    ALLEGRO_SAMPLE_INSTANCE *warning;
    ALLEGRO_SAMPLE_INSTANCE *flagpole;
} sound;

//------------------------------------ Ennemis ------------------------------------//

enum EnnemyType
{
    GOOMBA = 91,
    KOOPA = 109,
};

enum States
{
    NORMAL,
    CARAPACE_FIXE,
    CARAPACE_MOUV,
    MORT,
};

enum CHARACTER{
    MARIO,
    LUIGI,
};

#define KOOPA_SPEED 16

/**
 * @struct ennemi
 * @brief Ensemble des informations relatives à tous les ennemis
 */

typedef struct Ennemi
{
    int height;
    int width;
    int x;
    int y;
    int dvx;
    int dvy;
    int animation;
    int state; //vivant, mort ...
    int type;  //goomba ...
    int cpt;   // compteur pour animation
    int actif; //0: NON    1:OUI
    char *path;
    ALLEGRO_BITMAP *image;
} ennemi;

int numberEnnemis;

//------------------------------------ Joueur ------------------------------------//

/**
 * @struct joueur
 *
 * @brief Permet de manipuler tout les �lements du joueur
 */

typedef struct Joueur
{
    int width;
    int height;
    int x, y, yMax; // Cordonn�e du joueur selon chaque axe
    int dvx, dvy;   // Vitesse de d�placement du joueur sur chaque axe
    int rdvx;
    int state;
    int invinsible;
    int jump;
    int mouv;
    int cptrun;
    int display;
    int etoile;
    int cptEtoile;
    char *path;
    ALLEGRO_BITMAP *image;
    int character;
} joueur;

/**
 * @brief énumération pour les valeurs de direction
 *
 */
enum direction
{
    HAUT,
    DROITE,
    BAS,
    GAUCHE
};

/**
 * @brief énumération pour les valeurs de distance
 *
 */
enum distance
{
    PIXEL,
    MOUVEMENT
};

//------------------------------------ Sysytem ------------------------------------//

/**
 * @brief énumération des différents stades d'avancée dans le jeu
 */
enum Modes
{
    STARTING_SCREEN,
    ATTENTE_PSEUDO,
    REGISTER_PLAYER,
    PLAYER_MENU,
    WAITING_START,
    PLAYING_MAP,
    END_LEVEL,
    GAME_OVER,
    DIE,
    DRAW_PAUSE,
    PAUSE,
};

/**
 * @struct settings
 *
 * @brief ensemble des variables de paramètre
 *
 */
typedef struct Settings
{
    int load;    // 0 : Map chargée    |    1 : Il faut charger la map
    bool done;   // Variable correspondante à si le jeu est en cours d'utilisation (false) ou fini (true)
    bool redraw; // True :il faut redessiner la fenêtre | False : Pas besoin de redessiner       (le changement se fait suivant le timer)
    int mode;
} settings;

//------------------------------------ Stat ------------------------------------//

#define LENGTH_NAME 99

/**
 * @struct playerStats
 *
 * @brief Structure contenant toutes les informations associées à la partie en cours
 *
 */

typedef struct PLAYERSTAT
{
    int scoreLv1;
    int scoreLv2;
    int scoreLv3;
    int scoreLv4;
    int scoreLv5;
    int try_remaining;
    int nb_coins;
    char level[4];
    int stopwatch;
    char name[LENGTH_NAME];
    char lvl_max[4];
    int son;
} playerStats;

playerStats user;
int tpsNiveau;
//------------------------------------ Map ------------------------------------//

/**
 * @struct camera
 *
 * @brief Sauvegarde de l'emplacement de la fenêtre par rapport à la map (en px)
 *
 *
 */

typedef struct CAMERA
{
    int x; //abscisse de la camera (en px)
    int y; //ordonnée de la camera (en px)
} camera;

/**
 * @struct cases
 *
 * @brief Sauvegarde des bitmap correspondants aux blocks
 *
 */
typedef struct Cases
{
    ALLEGRO_BITMAP *wall;
    ALLEGRO_BITMAP *brick;
    ALLEGRO_BITMAP *block;
    ALLEGRO_BITMAP *secret;
    ALLEGRO_BITMAP *solid;
    ALLEGRO_BITMAP *bushBig;
    ALLEGRO_BITMAP *bushMed;
    ALLEGRO_BITMAP *bushSmall;
    ALLEGRO_BITMAP *castle;
    ALLEGRO_BITMAP *cloudBig;
    ALLEGRO_BITMAP *cloudMed;
    ALLEGRO_BITMAP *cloudSmall;
    ALLEGRO_BITMAP *flag;
    ALLEGRO_BITMAP *hillBig;
    ALLEGRO_BITMAP *hillSmall;
    ALLEGRO_BITMAP *pipeBig;
    ALLEGRO_BITMAP *pipeMed;
    ALLEGRO_BITMAP *pipeSmall;
} cases;

/**
 * @brief enumeration of the number in the map associated with each sprite
 *
 */
enum Block
{
    NOTHING = 0,

    WALL = 1,
    BRICK = 2,
    SECRET = 17,
    BLOCK = 16,
    SOLID = 20,

    PIECE = 108,

    BUSHSMALL = 22,
    BUSHMED = 7,
    BUSHBIG = 78,

    CLOUDSMALL = 18,
    CLOUDMED = 52,
    CLOUDBIG = 48,

    PIPESMALL = 46,
    PIPESMALL_RIGHT = 47,
    PIPEMED = 61,
    PIPEMED_RIGHT = 62,
    PIPEBIG = 76,
    PIPEBIG_RIGHT = 77,
    PIPETOPL = 31,
    PIPETOPR = 32,

    MUSHROOM_RED = 92,
    MUSHROOM_GREEN = 106,
    STAR = 107,

    HILLSMALL = 97,
    HILLBIG = 100,

    FLAG = 135,
    CASTLE = 181,
    DOOR = 183,
};

/**
 * @brief largeur de la map en block
 *
 */
int map_width;

/**
 * @brief hauteur de la map en block
 *
 */
int map_height;

//------------------------------------ Pieces ------------------------------------//

/**
 * @brief Structure rassemblant toutes les caractéristiques d'une pièces
 *
 */
typedef struct Piece
{
    int width;
    int height;
    int rotation;
    char *path;
    ALLEGRO_BITMAP *image;
    int cpt;
} piece;

piece modelPiece;

typedef struct Bonus
{
    int width;
    int height;
    int x;
    int y;
    int dvx;
    int dvy;
    int facon_mouv;
    int lequel;
    char *path;
    int actif; //0: NON    1:OUI
    int state;
    int jump;
    int yMax;
    ALLEGRO_BITMAP *image;

} bonus;

int numberMushroom;
bonus *powerUp;

#include "joueur.h"
#include "piece.h"
#include "affichage.h"
#endif
