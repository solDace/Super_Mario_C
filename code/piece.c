/**
 * @file Ensemble des fonctions relatives aux pièces
 * @brief
 *
 */

#include "piece.h"

void initPiece(piece *model)
{
    char path[] = "AlgoS4/resources/sprites/coin.png";
    model->image = al_load_bitmap(path);
    if (!model->image)
    {
        printf("al_load_bitmap( piece )");
    }
    else
    {
        model->width = al_get_bitmap_width(model->image);
        model->width = al_get_bitmap_height(model->image);
    }
    model->rotation = 0;
    model->cpt = 0;
}

void affichagePiece(piece *model, int x, int y, camera cam)
{
    int marge = (WINDOW_HEIGHT / BLOCK_SIZE_RES) - map_height;
    /*  int etat = 0;
    model->rotation++;
    if (model->rotation < VITESSE_ROTATION_PIECE)
    {
    }
    else if (model->rotation < 2 * VITESSE_ROTATION_PIECE)
    {
        etat = 1;
    }
    else if (model->rotation < 3 * VITESSE_ROTATION_PIECE)
    {
        etat = 2;
    }
    else if (model->rotation < 4 * VITESSE_ROTATION_PIECE)
    {
        etat = 3;
    }
    else
    {
        model->rotation = 0;
    } */
    al_draw_scaled_bitmap(
        model->image,
        (model->rotation % 4) * BLOCK_SIZE_SRC, 0,
        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,
        x * BLOCK_SIZE_RES - cam.x, (y + marge) * BLOCK_SIZE_RES + cam.y,
        BLOCK_SIZE_RES, BLOCK_SIZE_RES,
        0);
}

void ramassePiece(playerStats *player)
{
    player->nb_coins++;
    if (player->nb_coins == 100)
    {
        player->nb_coins = 0;
        player->try_remaining++;
    }
}

void touchePiece(playerStats *player, int **map, int x, int y)
{
    map[y][x] = 0;
    ramassePiece(player);
}
