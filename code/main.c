/**
 * @file main.c
 * @brief Document principal
 * @version 0.1
 * @date 2021-01-10
 *
 * @copyright Copyright (c) 2021
 */

#include "main.h"
#include "allegro.h"
#include "joueur.h"
#include "map.h"
#include "system.h"
#include "menu.h"
#include "stats.h"
#include "ennemi.h"
#include "bonus.h"
#include "affichage.h"
#include "piece.h"

char player_name[LENGTH_NAME];

int main()
{

    /* Initialisation de la bibliothéque */

    init result = initLib();
    sound sound = initSound();
    if (result.success != 0)
    {
        return 0;
    }

    ALLEGRO_TIMER *timer = result.timer;
    ALLEGRO_EVENT_QUEUE *queue = result.queue;
    ALLEGRO_DISPLAY *disp = result.disp;
    ALLEGRO_FONT *font = result.font;

    ALLEGRO_EVENT event;

    /* Initialisation les variables du systéme */
    settings system;
    initSettings(&system);

    /* Initialisation de la map et de la camera*/
    int **map = NULL;
    camera cam;
    ennemi *ennemis = NULL;

    /* Initialisation des bitmap des blocks */
    cases blocks;
    initCases(&blocks);
    initPiece(&modelPiece);

    /*Inititalisation du nom et des variables nécessaires à la recup*/
    initName(player_name);
    int lemode;

    al_start_timer(timer);

    joueur personnage;
    joueur *ptpersonnage = &personnage;
    personnage.character = 0;

    fonts police;
    police = initFonts();

    /* D�marrage de la boucle d'�v�nement */

    while (!system.done)
    {

        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
        {
            // game logic goes here.
            switch (system.mode)
            {
            case STARTING_SCREEN:
                break;

            case ATTENTE_PSEUDO:
                break;

            case REGISTER_PLAYER:
                loadSave(&user, player_name);
                memset(player_name, '\0', LENGTH_NAME);

                system.mode = PLAYER_MENU;
                break;

            case PLAYER_MENU:
                system.mode = WAITING_START;
                system.load = 1;
                break;

            case WAITING_START:
                system.mode = waiting_start(&user, ptpersonnage);
                break;

            case PAUSE:
                al_stop_sample_instance(sound.songInstance);
                al_stop_sample_instance(sound.star);
                al_play_sample_instance(sound.pause);

                system.mode = pause(&user, &system, sound, personnage);
                break;

            case PLAYING_MAP:
                user.stopwatch++;
            case END_LEVEL:
                if (system.load == 1)
                {
                    system.load = 0;
                    map = loadMap(user.level, ennemis);

                    cam = initCam();
                    initPersonnage(ptpersonnage);
                    ennemis = initEnnemis(ennemis, map);
                    ChangementSpritePersonnage(ptpersonnage);
                    initBonus(map);
                    al_stop_sample_instance(sound.stage_clear);
                    al_play_sample_instance(sound.songInstance);
                    resetStats(&user);
                }
                modelPiece.cpt++;
                if (modelPiece.cpt >= 10)
                {
                    modelPiece.rotation = (modelPiece.rotation + 1) % 4;
                    modelPiece.cpt = 0;
                }

                ennemiMouvement(ennemis, map, cam, ptpersonnage, sound);
                avanceEvent(ptpersonnage, &cam, map, ennemis, sound);
                sautpersonnage(ptpersonnage, map, ennemis, sound);
                BonusMouvement(map, cam, ptpersonnage, sound);
                reculerEvent(ptpersonnage, &cam, map, ennemis, sound);
                sonTimer(user.stopwatch, sound, ptpersonnage, &system);

                if (ptpersonnage->etoile == 0)
                {
                    if (ptpersonnage->invinsible > 0 && ptpersonnage->invinsible <= 50)
                    {
                        ptpersonnage->invinsible++;
                    }
                    else
                    {
                        ptpersonnage->invinsible = 0;
                    }
                }
                else if (ptpersonnage->etoile == 1)
                {
                    if (ptpersonnage->invinsible > 0 && ptpersonnage->invinsible <= 400)
                    {
                        ptpersonnage->invinsible++;
                    }
                    else
                    {
                        al_stop_sample_instance(sound.star);
                        al_play_sample_instance(sound.songInstance);
                        ptpersonnage->invinsible = 0;
                        ptpersonnage->etoile = 0;
                    }
                }

                endLevelAnimtion(ptpersonnage, &system, map, user.stopwatch, sound);
                if (user.stopwatch >= 30 && personnage.state == -1)
                {
                    personnage.state--;
                }
                else if (personnage.state == -1)
                {
                    user.stopwatch++;
                    system.mode = END_LEVEL;
                }
                if (ptpersonnage->state < -1 || tpsNiveau - (user.stopwatch / REFRESH_RATE) <= 0)
                {
                    user.try_remaining--;
                    system.mode = DIE;
                    user.stopwatch = 0;
                }

                system.redraw = true;
                break;

            case DIE:
                if (user.try_remaining <= 0)
                {
                    system.mode = GAME_OVER;

                    break;
                }
                if (user.stopwatch < 105)
                {
                    al_stop_sample_instance(sound.songInstance);
                    al_stop_sample_instance(sound.star);
                    al_play_sample_instance(sound.die);

                    user.stopwatch++;
                }
                else
                {
                    system.load = 1;
                    system.mode = PLAYING_MAP;
                    user.stopwatch = 0;
                    resetStats(&user);
                }
                break;

            case GAME_OVER:
                if (user.stopwatch < 135)
                {
                    user.stopwatch++;
                    al_stop_sample_instance(sound.songInstance);
                    al_stop_sample_instance(sound.star);
                    al_play_sample_instance(sound.gameOver);
                }
                else
                {
                    system.mode = PLAYER_MENU;
                    user.try_remaining = 3;
                    user.stopwatch = 0;
                    resetStats(&user);
                }
                break;
            default:
                break;
            }
            break;
        }
        /* ALLEGRO_EVENT_DISPLAY_CLOSE - the window is closed. */
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
            system.done = true;
            break;
        }

        case ALLEGRO_EVENT_KEY_CHAR:
        {

            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                if (system.mode == PLAYING_MAP)
                {
                    /* code */

                    system.mode = DRAW_PAUSE;
                }
                break;

            case ALLEGRO_KEY_ENTER:

                break;
            }

            break;
        }
        }

        switch (system.mode)
        {
        case STARTING_SCREEN:
            break;

        case ATTENTE_PSEUDO:
            lemode = recupName(event.keyboard.unichar, player_name);
            if (lemode != 0)
            {
                system.mode = lemode;
            }
            break;

        case PLAYING_MAP:
            switch (event.type)
            {
            /* ALLEGRO_EVENT_KEY_DOWN - a keyboard key was pressed.*/
            case ALLEGRO_EVENT_KEY_DOWN:
            {
                switch (event.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:

                    if (!mapEndJoueur(ptpersonnage, map, BAS, PIXEL))
                    {
                        if (isBlock(ptpersonnage, map, BAS, PIXEL, sound))
                        {

                            ptpersonnage->jump = 1;
                            ptpersonnage->dvy = 20;
                            ptpersonnage->yMax = ptpersonnage->y - (JUMP_HEIGHT * BLOCK_SIZE_RES); // Hauteur Max 210px au-dessus du personnage
                            if (ptpersonnage->state == 1 && ptpersonnage->jump == 1)
                            {
                                sound.jump = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_jump-super.wav"));
                            }
                            else if (ptpersonnage->state == 0 && ptpersonnage->jump == 1)
                            {
                                sound.jump = al_create_sample_instance(al_load_sample("./AlgoS4/resources/audios/smb_jump-small.wav"));
                            }
                            al_attach_sample_instance_to_mixer(sound.jump, sound.sound_mixer);
                            al_set_sample_instance_playmode(sound.jump, ALLEGRO_PLAYMODE_ONCE);
                            al_play_sample_instance(sound.jump);
                        }
                        else
                        {
                            //personnage déjà dans les airs
                        }
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                    ptpersonnage->dvx = 15;
                    ptpersonnage->mouv = 4;
                    break;
                case ALLEGRO_KEY_LEFT:
                    ptpersonnage->rdvx = 15;
                    ptpersonnage->mouv = 8;
                    break;
                }

                break;
            }
            case ALLEGRO_EVENT_KEY_UP:
            {
                switch (event.keyboard.keycode)
                {
                case ALLEGRO_KEY_RIGHT:
                {
                    ptpersonnage->dvx = 0;
                    ptpersonnage->mouv = 1;
                    break;
                }
                case ALLEGRO_KEY_LEFT:
                    ptpersonnage->rdvx = 0;
                    ptpersonnage->mouv = 5;
                    break;
                case ALLEGRO_KEY_UP: //On a relacher le bouton de saut

                    if (ptpersonnage->jump == 1)
                    {
                        ptpersonnage->dvy = 5;
                        ptpersonnage->jump = 0;
                    }

                    break;
                case ALLEGRO_KEY_ESCAPE:

                    break;
                }
                break;
            case ALLEGRO_KEY_DOWN:
                ptpersonnage->y = 3 * BLOCK_SIZE_RES;
                break;
            }
            break;
            }
        case ALLEGRO_EVENT_KEY_CHAR:
        {
            //Sert � �viter l'appui long sur une m�me touche
            switch (event.keyboard.unichar)
            {
            default:
            { //Si la touche à tester n'est pas une lettre
                switch (event.keyboard.keycode)
                {
                case ALLEGRO_KEY_RIGHT:
                    //Déplacement provisoire de la camera
                    break;

                case ALLEGRO_KEY_LEFT:
                    //Déplacement provisoire de la camera
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    if (system.mode == PLAYING_MAP)
                    {
                        /* code */

                        system.mode = DRAW_PAUSE;
                        al_play_sample_instance(sound.click_pause);
                    }
                    break;
                }
                break;
            }
            }
            break;
        }
        break;

        case END_LEVEL:
            break;

        default:
            break;
        }
        switch (system.mode)
        {
        case STARTING_SCREEN:
            system.mode = displayBackground(blocks);
            displayScoreTab(police);
            DisplayHS(525, 345, 2, font);
            display_notif_name(police);
            break;
        case ATTENTE_PSEUDO:
            display_register_name(police, player_name);
            break;
        case PLAYER_MENU:
            displayBackground(blocks);
            displayScoreTab(police);
            DisplayHS(525, 345, 2, font);
            dispName(user.name, 70, police);
            userDraw(user, police);
            display_text_persoChangement(police);
            display_select_luigi(ptpersonnage);
            break;

        case PLAYING_MAP:
        case END_LEVEL:
            if (system.load == 0)
            {
                displayMap(map, cam, &blocks);
                displayEnnemi(ennemis, cam);
                displayBonus(cam);

                afficheAnime(ptpersonnage, &cam, map, sound);
                switch (user.level[2])
                {
                case '1':
                    afficheScore(user.name, user.scoreLv1, police);
                    break;
                case '2':
                    afficheScore(user.name, user.scoreLv2, police);
                    break;
                case '3':
                    afficheScore(user.name, user.scoreLv3, police);
                    break;
                case '4':
                    afficheScore(user.name, user.scoreLv4, police);
                    break;
                case '5':
                    afficheScore(user.name, user.scoreLv5, police);
                    break;
                }

                afficheNombrePiece(user.nb_coins, police);
                afficheNiveau(user.level, police);
                afficheTimer(user.stopwatch, police);
            }

            afficheAnime(ptpersonnage, &cam, map, sound);
            break;

        case GAME_OVER:
            gameOverScreen(police);
            break;

        case DIE:
            dieScreen(user.try_remaining, police);
            break;

        case DRAW_PAUSE:
            system.mode = menu_pause(police, blocks, &user);
            if (system.mode != PAUSE)
            {
                al_stop_sample_instance(sound.star);
            }

            break;
        }

        al_flip_display();
        system.redraw = false;
    }
    destructLib(timer, queue, disp, font, sound);
    destructMap(map);

    free(ennemis);
    free(powerUp);
    return 0;
}
