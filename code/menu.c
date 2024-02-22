/**
 * @file menu.c
 * @brief fonctions d'affichage et de gestion du menu du jeu
 */
#include "menu.h"
#include "allegro.h"
#include "affichage.h"

int displayBackground(cases blocks)
{
    int dx = 0;
    float scale = 3;

    ALLEGRO_BITMAP *mario = NULL;
    ALLEGRO_BITMAP *title = NULL;
    ALLEGRO_BITMAP *goomba = NULL;

    //chargement des sprites
    goomba = al_load_bitmap("./AlgoS4/resources/sprites/owl.png");
    if (!goomba)
        printf("al_load_bitmap(goomba)");

    mario = al_load_bitmap("./AlgoS4/resources/sprites/mario-small.png");
    if (!mario)
        printf("al_load_bitmap(mario-small)");

    title = al_load_bitmap("./AlgoS4/resources/sprites/title_mario.png");
    if (!title)
        printf("al_load_bitmap(title_mario)");

    //affichage du ciel
    al_clear_to_color(al_map_rgb(161, 173, 255));
    int width_cloud_big = al_get_bitmap_width(blocks.cloudBig);
    int height_cloud_big = al_get_bitmap_height(blocks.cloudBig);
    al_draw_scaled_bitmap(blocks.cloudBig, 0, 0, width_cloud_big, height_cloud_big, 60, 50, width_cloud_big * scale, height_cloud_big * scale, 0);
    int width_cloud_small = al_get_bitmap_width(blocks.cloudSmall);
    int height_cloud_small = al_get_bitmap_height(blocks.cloudSmall);
    al_draw_scaled_bitmap(blocks.cloudSmall, 0, 0, width_cloud_small, height_cloud_small, 150, 275, width_cloud_small * scale, height_cloud_small * scale, 0);
    al_draw_scaled_bitmap(blocks.cloudSmall, 0, 0, width_cloud_small, height_cloud_small, 1160, 20, width_cloud_small * scale, height_cloud_small * scale, 0);

    //affichage colline et buissons
    int width_bush_big = al_get_bitmap_width(blocks.bushBig);
    int height_bush_big = al_get_bitmap_height(blocks.bushBig);
    al_draw_scaled_bitmap(blocks.bushBig, 0, 0, width_bush_big, height_bush_big, 500, 576, width_bush_big * scale, height_bush_big * scale, 0);
    int width_bush_small = al_get_bitmap_width(blocks.bushSmall);
    int height_bush_small = al_get_bitmap_height(blocks.bushSmall);
    al_draw_scaled_bitmap(blocks.bushSmall, 0, 0, width_bush_small, height_bush_small, 1150, 576, width_bush_small * scale, height_bush_small * scale, 0);
    int width_hill_big = al_get_bitmap_width(blocks.hillBig);
    int height_hill_big = al_get_bitmap_height(blocks.hillBig);
    al_draw_scaled_bitmap(blocks.hillBig, 0, 0, width_hill_big, height_hill_big, -30, 519, width_hill_big * scale, height_hill_big * scale, 0);
    int width_hill_small = al_get_bitmap_width(blocks.hillSmall);
    int height_hill_small = al_get_bitmap_height(blocks.hillSmall);
    al_draw_scaled_bitmap(blocks.hillSmall, 0, 0, width_hill_small, height_hill_small, 710, 567, width_hill_small * scale, height_hill_small * scale, 0);

    //affichage briques
    int width_secret_box = al_get_bitmap_width(blocks.secret);
    int height_secret_box = al_get_bitmap_height(blocks.secret);
    al_draw_scaled_bitmap(blocks.secret, 0, 0, width_secret_box, height_secret_box, 530, 436, width_secret_box * scale, height_secret_box * scale, 0);
    al_draw_scaled_bitmap(blocks.secret, 0, 0, width_secret_box, height_secret_box, 922, 436, width_secret_box * scale, height_secret_box * scale, 0);
    al_draw_scaled_bitmap(blocks.secret, 0, 0, width_secret_box, height_secret_box, 1018, 436, width_secret_box * scale, height_secret_box * scale, 0);
    al_draw_scaled_bitmap(blocks.secret, 0, 0, width_secret_box, height_secret_box, 970, 248, width_secret_box * scale, height_secret_box * scale, 0);
    int width_brick = al_get_bitmap_width(blocks.brick);
    int height_brick = al_get_bitmap_height(blocks.brick);
    al_draw_scaled_bitmap(blocks.brick, 0, 0, width_brick, height_brick, 874, 436, width_brick * scale, height_brick * scale, 0);
    al_draw_scaled_bitmap(blocks.brick, 0, 0, width_brick, height_brick, 970, 436, width_brick * scale, height_brick * scale, 0);
    al_draw_scaled_bitmap(blocks.brick, 0, 0, width_brick, height_brick, 1066, 436, width_brick * scale, height_brick * scale, 0);

    //affichage mario
    al_draw_scaled_bitmap(mario, 32, 16, 16, 16, 300, 576, 16 * scale, 16 * scale, 0);

    //affichage du goomba
    int height_goomba = al_get_bitmap_height(goomba);
    al_draw_scaled_bitmap(goomba, 0, 0, 16, height_goomba, 890, 576, 16 * scale, 16 * scale, 0);

    //affichage du titre
    int width_title = al_get_bitmap_width(title);
    int height_title = al_get_bitmap_height(title);
    al_draw_scaled_bitmap(title, 0, 0, width_title, height_title, 400, 50, width_title / 2.5, height_title / 2.5, 0);

    //affichage du sol
    int width_wall = al_get_bitmap_width(blocks.wall);
    int height_wall = al_get_bitmap_height(blocks.wall);
    for (int i = 0; i < 27; i++)
    {
        al_draw_scaled_bitmap(blocks.wall, 0, 0, width_wall, height_wall, dx, 672, width_wall * scale, height_wall * scale, 0);
        al_draw_scaled_bitmap(blocks.wall, 0, 0, width_wall, height_wall, dx, 624, width_wall * scale, height_wall * scale, 0);
        dx += 48;
    }

    return ATTENTE_PSEUDO;
}

void displayScoreTab(fonts police)
{
    al_draw_filled_rounded_rectangle(430, 340, 850, 472, 10, 10, al_map_rgb(0, 0, 0));

    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 435, 345, 0, "TOP 1 :");
    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 435, 392, 0, "TOP 2 :");
    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 435, 439, 0, "TOP 3 :");
}

void initName(char player_name[LENGTH_NAME])
{
    memset(player_name, 0, LENGTH_NAME);
}

int recupName(int caractere, char player_name[LENGTH_NAME])
{
    char tampon[5];
    memset(tampon, 0, 5);

    if (caractere >= 'a' && caractere <= 'z')
    {
        sprintf(tampon, "%c", caractere);
        strcat(player_name, tampon);
        return ATTENTE_PSEUDO;
    }
    else if (caractere >= 'A' && caractere <= 'Z')
    {
        sprintf(tampon, "%c", caractere);
        strcat(player_name, tampon);
        return ATTENTE_PSEUDO;
    }
    else if ((/*caractere == 32  ||*/ caractere == 13) && player_name[0] != 0)
    {
        return REGISTER_PLAYER;
    }
    else
    {
        return 0;
    }
}

void dispName(char player_name[LENGTH_NAME], int start, fonts police)
{
    int text_width = al_get_text_width(police.gameplay, player_name);

    al_draw_filled_rounded_rectangle(start, start, start + 10 + text_width, start + 40, 10, 10, al_map_rgb(0, 0, 0));

    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), start + 5, start + 5, 0, player_name);
}

void userDraw(playerStats user, fonts police)
{
    switch (user.lvl_max[2])
    {
    case '5':
        button_maps(police, 70, 550, "MAP 1 - 5");
    case '4':
        button_maps(police, 70, 450, "MAP 1 - 4");
    case '3':
        button_maps(police, 70, 350, "MAP 1 - 3");
    case '2':
        button_maps(police, 70, 250, "MAP 1 - 2");
    case '1':
        button_maps(police, 70, 150, "MAP 1 - 1");
        break;

    default:
        button_maps(police, 70, 150, "MAP 1 - 1");
        break;
    }
}

int waiting_start(playerStats *user, joueur *personnage)
{
    ALLEGRO_MOUSE_STATE mouse;

    al_get_mouse_state(&mouse);
    if (mouse.x >= 70 && mouse.x <= 214 && mouse.buttons & 1)
    {
        if (mouse.y >= 150 && mouse.y <= 198)
        {
            strcpy(user->level, "1-1");
            return PLAYING_MAP;
        }
        else if (mouse.y >= 250 && mouse.y <= 298 && user->lvl_max[2] >= '2')
        {
            strcpy(user->level, "1-2");
            return PLAYING_MAP;
        }
        else if (mouse.y >= 350 && mouse.y <= 398 && user->lvl_max[2] >= '3')
        {
            strcpy(user->level, "1-3");
            return PLAYING_MAP;
        }
        else if (mouse.y >= 450 && mouse.y <= 498 && user->lvl_max[2] >= '4')
        {
            strcpy(user->level, "1-4");
            return PLAYING_MAP;
        }
        else if (mouse.y >= 550 && mouse.y <= 598 && user->lvl_max[2] == '5')
        {
            strcpy(user->level, "1-5");
            return PLAYING_MAP;
        }
        else
            return WAITING_START;
    }
    else if (mouse.x >= 1041 && mouse.x <= 1105 && mouse.y >= 90 && mouse.y <= 205 && mouse.buttons & 1)
    {
        if (personnage->character == 0)
        {
            personnage->character = 1;
            return PLAYER_MENU;
        }
        else if (personnage->character == 1)
        {
            personnage->character = 0;
            return PLAYER_MENU;
        }
        else
            return WAITING_START;
    }
    else
        return WAITING_START;
}

void display_notif_name(fonts police)
{
    char *text = "Entrer un pseudo et valider avec 'ENTRER'";

    int text_w = al_get_text_width(police.gameplay, text);

    al_draw_filled_rounded_rectangle(640 - (text_w / 2), 650, (650 - (text_w / 2)) + text_w, 690, 10, 10, al_map_rgb(0, 0, 0));

    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 645 - (text_w / 2), 655, 0, text);
}

int menu_pause(fonts police, cases blocks, playerStats *user)
{
    float scale = 3;
    int dx = 0;

    al_clear_to_color(al_map_rgb(161, 173, 255));

    int width_cloud_big = al_get_bitmap_width(blocks.cloudBig);
    int height_cloud_big = al_get_bitmap_height(blocks.cloudBig);
    al_draw_scaled_bitmap(blocks.cloudBig, 0, 0, width_cloud_big, height_cloud_big, 60, 50, width_cloud_big * scale, height_cloud_big * scale, 0);
    int width_cloud_small = al_get_bitmap_width(blocks.cloudSmall);
    int height_cloud_small = al_get_bitmap_height(blocks.cloudSmall);
    al_draw_scaled_bitmap(blocks.cloudSmall, 0, 0, width_cloud_small, height_cloud_small, 150, 275, width_cloud_small * scale, height_cloud_small * scale, 0);
    al_draw_scaled_bitmap(blocks.cloudSmall, 0, 0, width_cloud_small, height_cloud_small, 1160, 20, width_cloud_small * scale, height_cloud_small * scale, 0);

    int width_bush_big = al_get_bitmap_width(blocks.bushBig);
    int height_bush_big = al_get_bitmap_height(blocks.bushBig);
    al_draw_scaled_bitmap(blocks.bushBig, 0, 0, width_bush_big, height_bush_big, 500, 576, width_bush_big * scale, height_bush_big * scale, 0);
    int width_bush_small = al_get_bitmap_width(blocks.bushSmall);
    int height_bush_small = al_get_bitmap_height(blocks.bushSmall);
    al_draw_scaled_bitmap(blocks.bushSmall, 0, 0, width_bush_small, height_bush_small, 1150, 576, width_bush_small * scale, height_bush_small * scale, 0);
    int width_hill_big = al_get_bitmap_width(blocks.hillBig);
    int height_hill_big = al_get_bitmap_height(blocks.hillBig);
    al_draw_scaled_bitmap(blocks.hillBig, 0, 0, width_hill_big, height_hill_big, -30, 519, width_hill_big * scale, height_hill_big * scale, 0);
    int width_hill_small = al_get_bitmap_width(blocks.hillSmall);
    int height_hill_small = al_get_bitmap_height(blocks.hillSmall);
    al_draw_scaled_bitmap(blocks.hillSmall, 0, 0, width_hill_small, height_hill_small, 710, 567, width_hill_small * scale, height_hill_small * scale, 0);

    int width_wall = al_get_bitmap_width(blocks.wall);
    int height_wall = al_get_bitmap_height(blocks.wall);
    for (int i = 0; i < 27; i++)
    {
        al_draw_scaled_bitmap(blocks.wall, 0, 0, width_wall, height_wall, dx, 672, width_wall * scale, height_wall * scale, 0);
        al_draw_scaled_bitmap(blocks.wall, 0, 0, width_wall, height_wall, dx, 624, width_wall * scale, height_wall * scale, 0);
        dx += 48;
    }

    button_maps(police, 537, 100, "REPRENDRE");
    button_maps(police, 582, 200, "MENU");
    button_maps(police, 565, 400, "LOG OUT");
    button_maps(police, 565, 500, "QUITTER");

    if (user->son == 1)
    {
        button_maps(police, 564, 300, "SON : ON");
    }
    else if (user->son == 0)
    {
        button_maps(police, 557, 300, "SON : OFF");
    }

    return PAUSE;
}

int pause(playerStats *user, settings *system, sound sound, joueur personnage)
{
    ALLEGRO_MOUSE_STATE mouse;

    al_get_mouse_state(&mouse);
    if (mouse.buttons & 1)
    {
        if (user->son == 0)
        {
            if (mouse.x >= 557 && mouse.x <= 843 && mouse.y >= 300 && mouse.y <= 393)
            {
                user->son = 1;
                al_set_mixer_gain(sound.master_mixer, user->son);
                return DRAW_PAUSE;
            }
        }
        else
        {
            if (mouse.x >= 564 && mouse.x <= 814 && mouse.y >= 300 && mouse.y <= 393)
            {
                user->son = 0;
                al_set_mixer_gain(sound.master_mixer, user->son);
                return DRAW_PAUSE;
            }
        }

        if (mouse.x >= 537 && mouse.x <= 894 && mouse.y >= 100 && mouse.y <= 193)
        {
            system->mode = PLAYING_MAP;
            al_stop_sample_instance(sound.pause);
            if (personnage.etoile == 1)
            {
                al_play_sample_instance(sound.star);
            }
            else
            {
                al_play_sample_instance(sound.songInstance);
            }
            return PLAYING_MAP;
        }
        else if (mouse.x >= 582 && mouse.x <= 754 && mouse.y >= 200 && mouse.y <= 293)
        {
            al_stop_sample_instance(sound.pause);

            return PLAYER_MENU;
        }
        else if (mouse.x >= 565 && mouse.x <= 815 && mouse.y >= 400 && mouse.y <= 493)
        {
            al_stop_sample_instance(sound.pause);

            return STARTING_SCREEN;
        }
        else if (mouse.x >= 565 && mouse.x <= 815 && mouse.y >= 500 && mouse.y <= 593)
        {
            system->done = true;
            al_stop_sample_instance(sound.pause);

            return STARTING_SCREEN;
        }
        else
        {
            return DRAW_PAUSE;
        }
    }
    else
    {
        return PAUSE;
    }
}

void display_register_name(fonts police, char *player_name)
{
    if (player_name[0] != '\0')
    {
        char *text = player_name;

        int text_w = al_get_text_width(police.gameplay, text);

        al_draw_filled_rounded_rectangle(640 - (text_w / 2), 550, (650 - (text_w / 2)) + text_w, 590, 10, 10, al_map_rgb(0, 0, 0));

        al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 645 - (text_w / 2), 555, 0, text);
    }
}

void display_select_luigi(joueur *personnage)
{

    ALLEGRO_BITMAP *mario = NULL;
    ALLEGRO_BITMAP *luigi = NULL;

    mario = al_load_bitmap("./AlgoS4/resources/sprites/mario-big.png");
    if (!mario)
        printf("al_load_bitmap(mario-big)");

    luigi = al_load_bitmap("./AlgoS4/resources/sprites/luigi-big.png");
    if (!luigi)
        printf("al_load_bitmap(luigi-big)");

    al_draw_filled_rounded_rectangle(1041, 90, 1105, 205, 10, 10, al_map_rgb(0, 0, 0));

    if (personnage->character == MARIO)
    {
        al_draw_scaled_bitmap(mario, 32, 32, 16, 32, 1050, 100, 16 * 3, 32 * 3, 0);
    }
    else if (personnage->character == LUIGI)
    {
        al_draw_scaled_bitmap(luigi, 32, 32, 16, 32, 1050, 100, 16 * 3, 32 * 3, 0);
    }
}

void display_text_persoChangement(fonts police)
{
    char *text = "changer personnage";

    int text_w = al_get_text_width(police.gameplay, text);

    al_draw_filled_rounded_rectangle(1060 - (text_w / 2), 30, (1080 - (text_w / 2)) + text_w, 79, 10, 10, al_map_rgb(0, 0, 0));

    al_draw_text(police.gameplay, al_map_rgb(255, 255, 255), 1070 - (text_w / 2), 40, 0, text);
}