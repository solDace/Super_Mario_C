#include "affichage.h"
#include "allegro.h"
#include "piece.h"

fonts initFonts()
{
    fonts polices;
    polices.fontScore = al_load_ttf_font("./AlgoS4/resources/fonts/gameplay.ttf", 32, 0);
    if (!polices.fontScore)
        printf("al_load_font()");

    polices.gameplay = al_load_ttf_font("./AlgoS4/resources/fonts/gameplay.ttf", 24, 0);
    if (!polices.gameplay)
        printf("al_load_font()");

    return polices;
}

void afficheScore(char *nom, int score, fonts police)
{
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 80, 10, 0, nom);

    char sScore[6];

    // convert 123 to string [buf]
    itoa(score, sScore, 10);
    int length = strlen(sScore);
    for (int i = length - 1; i >= 0; i--)
    {
        sScore[i + (6 - length)] = sScore[i];
    }
    for (int i = 0; i < 6 - length; i++)
    {
        sScore[i] = '0';
    }

    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 80, 55, 0, sScore);
}

void afficheNombrePiece(int pieces, fonts police)
{
    int x = 7 * BLOCK_SIZE_RES, y = 55;

    camera fixed;
    fixed.x = 0;
    fixed.y = 0;
    affichagePiece(&modelPiece, 7, 1, fixed);
    char sPieces[2];

    // convert 123 to string [buf]
    itoa(pieces, sPieces, 10);
    char tot[4] = "x ";
    strcat(tot, sPieces);
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), x + BLOCK_SIZE_RES, y, 0, tot);
}

void afficheNiveau(char *niveau, fonts police)
{
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 15 * BLOCK_SIZE_RES, 10, 0, "WORLD");

    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 15 * BLOCK_SIZE_RES + 37, 55, 0, niveau);
}

void afficheTimer(int timer, fonts police)
{
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 22 * BLOCK_SIZE_RES, 10, 0, "TIME");

    timer = tpsNiveau - timer / REFRESH_RATE;
    char sTimer[6];

    // convert 123 to string [buf]
    itoa(timer, sTimer, 10);
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), 22 * BLOCK_SIZE_RES, 55, 0, sTimer);
}

void gameOverScreen(fonts police)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 16, 0, "GAME OVER");
}

void dieScreen(int life, fonts police)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(al_load_bitmap("./AlgoS4/resources/sprites/mario-small.png"), 2 * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, WINDOW_WIDTH / 2 - BLOCK_SIZE_RES - 10, WINDOW_HEIGHT / 2 + 16, BLOCK_SIZE_RES, BLOCK_SIZE_RES, 0);

    char sLife[2];

    // convert 123 to string [buf]
    itoa(life, sLife, 10);
    char tot[4] = "x ";
    strcat(tot, sLife);

    al_draw_text(police.fontScore, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 16, 0, tot);
}

void button_maps(fonts police, int posx, int posy, char *title)
{
    int text_width = al_get_text_width(police.gameplay, title);

    ALLEGRO_BITMAP *button = NULL;

    button = al_load_bitmap("./AlgoS4/resources/sprites/back_button.png");
    if (!button)
        printf("al_load_bitmap(button)");

    int width_button = al_get_bitmap_width(button);
    int height_button = al_get_bitmap_height(button);
    al_draw_scaled_bitmap(button, 0, 0, width_button, height_button, posx, posy, text_width + 15, height_button * 0.08, 0);

    al_draw_text(police.gameplay, al_map_rgb(247, 215, 182), posx + 8, posy + 10, 0, title);
}
