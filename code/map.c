#include "map.h"

int **loadMap(char *level, ennemi *rep)
{

    FILE *fichier = NULL;
    char path[50];
    strcat(strcat(strcpy(path, "AlgoS4/resources/map/"), level), ".txt");
    fichier = fopen(path, "r");
    int row = 0, col = 0;
    char a = 0;
    do
    {
        fscanf(fichier, "%c", &a);
    } while (a != '[');
    a = 0;
    fscanf(fichier, "%d][%d] = { ", &row, &col);

    int **map = malloc(row * sizeof(int));
    for (int i = 0; i < row; i++)
    {
        map[i] = malloc(col * sizeof(int));
    }
    int tmp = 0;
    map_height = row;
    map_width = col;

    for (int i = 0; i < row; i++)
    {
        do
        {
            fscanf(fichier, "%c", &a);
        } while (a != '{');
        a = 0;

        for (int j = 0; j < col - 1; j++)
        {
            fscanf(fichier, " %d,", &tmp);
            map[i][j] = tmp;
        }
        fscanf(fichier, " %d", &tmp);
        map[i][col - 1] = tmp;
    }

    tpsNiveau = 400;
    fclose(fichier);
    return map;
}

void destructMap(int **map)
{
    for (int i = 0; i < map_height; i++)
    {
        free(map[i]);
    }
    free(map);
}

void displayMap(int **map, camera cam, cases *blocks)
{

    int marge = (WINDOW_HEIGHT / BLOCK_SIZE_RES) - map_height;

    al_clear_to_color(al_map_rgb(161, 173, 255));

    for (int j = 0; j < map_height; j++)
    {
        for (int i = 0; i < map_width; i++)
        {
            if (j <= ((cam.y + WINDOW_HEIGHT) / BLOCK_SIZE_RES + 2) && j >= (cam.y / BLOCK_SIZE_RES - 2) &&
                i <= ((cam.x + WINDOW_WIDTH) / BLOCK_SIZE_RES + 2) && i >= (cam.x / BLOCK_SIZE_RES - 2))
            {
                switch (map[j][i])
                {
                case 0:

                    break;
                case WALL:

                    al_draw_scaled_bitmap(
                        blocks->wall,                                                     // image source
                        0, 0,                                                             // coin haut gauche
                        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                                   // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        BLOCK_SIZE_RES,                                                   // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation

                    break;

                case BRICK:
                case STAR:
                    al_draw_scaled_bitmap(
                        blocks->brick,                                                    // image source
                        0, 0,                                                             // coin haut gauche
                        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                                   // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        BLOCK_SIZE_RES,                                                   // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;

                case BLOCK:
                    al_draw_scaled_bitmap(
                        blocks->block,                                                    // image source
                        0, 0,                                                             // coin haut gauche
                        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                                   // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        BLOCK_SIZE_RES,                                                   // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case SOLID:
                    al_draw_scaled_bitmap(
                        blocks->solid,                                                    // image source
                        0, 0,                                                             // coin haut gauche
                        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                                   // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        BLOCK_SIZE_RES,                                                   // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;

                case SECRET:
                case MUSHROOM_RED:
                    al_draw_scaled_bitmap(
                        blocks->secret,                                                   // image source
                        0, 0,                                                             // coin haut gauche
                        BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                                   // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        BLOCK_SIZE_RES,                                                   // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case BUSHSMALL:
                    al_draw_scaled_bitmap(
                        blocks->bushSmall,                                                // image source
                        0, 0,                                                             // coin haut gauche
                        2 * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                               // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        2 * BLOCK_SIZE_RES,                                               // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case BUSHMED:
                    al_draw_scaled_bitmap(
                        blocks->bushMed,                                                  // image source
                        0, 0,                                                             // coin haut gauche
                        3 * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                               // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        3 * BLOCK_SIZE_RES,                                               // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case BUSHBIG:
                    al_draw_scaled_bitmap(
                        blocks->bushBig,                                                  // image source
                        0, 0,                                                             // coin haut gauche
                        4 * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,                               // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        4 * BLOCK_SIZE_RES,                                               // taille destination
                        BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case CLOUDSMALL:
                    al_draw_scaled_bitmap(
                        blocks->cloudSmall,                                                   // image source
                        0, 0,                                                                 // coin haut gauche
                        2 * BLOCK_SIZE_SRC, 1.5 * BLOCK_SIZE_SRC,                             // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge - 1) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        2 * BLOCK_SIZE_RES,                                                   // taille destination
                        1.5 * BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case CLOUDMED:
                    al_draw_scaled_bitmap(
                        blocks->cloudMed,                                                     // image source
                        0, 0,                                                                 // coin haut gauche
                        3 * BLOCK_SIZE_SRC, 1.5 * BLOCK_SIZE_SRC,                             // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge - 1) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        3 * BLOCK_SIZE_RES,                                                   // taille destination
                        1.5 * BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case CLOUDBIG:
                    al_draw_scaled_bitmap(
                        blocks->cloudBig,                                                     // image source
                        0, 0,                                                                 // coin haut gauche
                        4 * BLOCK_SIZE_SRC, 1.5 * BLOCK_SIZE_SRC,                             // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j + marge - 1) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        4 * BLOCK_SIZE_RES,                                                   // taille destination
                        1.5 * BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case PIPESMALL:
                    if (map[j + 1][i] == 1 || map[j + 1][i] == BLOCK)
                    {
                        al_draw_scaled_bitmap(
                            blocks->pipeSmall,                                                    // image source
                            0, 0,                                                                 // coin haut gauche
                            2 * BLOCK_SIZE_SRC, 2 * BLOCK_SIZE_SRC,                               // taille source
                            i * BLOCK_SIZE_RES - cam.x, (j - 1 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                            2 * BLOCK_SIZE_RES,                                                   // taille destination
                            2 * BLOCK_SIZE_RES,
                            0); // permutation
                    }
                    break;
                case PIPEMED:
                    if (map[j + 1][i] == 1 || map[j + 1][i] == BLOCK)
                    {
                        al_draw_scaled_bitmap(
                            blocks->pipeMed,                                                      // image source
                            0, 0,                                                                 // coin haut gauche
                            2 * BLOCK_SIZE_SRC, 3 * BLOCK_SIZE_SRC,                               // taille source
                            i * BLOCK_SIZE_RES - cam.x, (j - 2 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                            2 * BLOCK_SIZE_RES,                                                   // taille destination
                            3 * BLOCK_SIZE_RES,
                            0); // permutation
                    }
                    break;
                case PIPEBIG:
                    if (map[j + 1][i] == 1 || map[j + 1][i] == BLOCK)
                    {
                        al_draw_scaled_bitmap(
                            blocks->pipeBig,                                                      // image source
                            0, 0,                                                                 // coin haut gauche
                            2 * BLOCK_SIZE_SRC, 4 * BLOCK_SIZE_SRC,                               // taille source
                            i * BLOCK_SIZE_RES - cam.x, (j - 3 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                            2 * BLOCK_SIZE_RES,                                                   // taille destination
                            4 * BLOCK_SIZE_RES,
                            0); // permutation
                    }
                    break;
                case HILLSMALL:
                    if (map[j + 1][i] == 1)
                    {
                        al_draw_scaled_bitmap(
                            blocks->hillSmall,                                                // image source
                            0, 0,                                                             // coin haut gauche
                            3 * BLOCK_SIZE_SRC, 1.1875 * BLOCK_SIZE_SRC,                      // taille source
                            i * BLOCK_SIZE_RES - cam.x, (j + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                            3 * BLOCK_SIZE_RES,                                               // taille destination
                            1.1875 * BLOCK_SIZE_RES,
                            0); // permutation
                    }
                    break;
                case HILLBIG:
                    if (map[j + 1][i] == 1)
                    {
                        al_draw_scaled_bitmap(
                            blocks->hillBig,                                                      // image source
                            0, 0,                                                                 // coin haut gauche
                            5 * BLOCK_SIZE_SRC, 2.1875 * BLOCK_SIZE_SRC,                          // taille source
                            i * BLOCK_SIZE_RES - cam.x, (j - 1 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                            5 * BLOCK_SIZE_RES,                                                   // taille destination
                            2.1875 * BLOCK_SIZE_RES,
                            0); // permutation
                    }
                    break;

                case FLAG:
                    al_draw_scaled_bitmap(
                        blocks->flag,                                                                 // image source
                        0, 0,                                                                         // coin haut gauche
                        1.5 * BLOCK_SIZE_SRC, 10 * BLOCK_SIZE_SRC,                                    // taille source
                        (i - 0.5) * BLOCK_SIZE_RES - cam.x, (j - 8 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        1.5 * BLOCK_SIZE_RES,                                                         // taille destination
                        10 * BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case CASTLE:
                    al_draw_scaled_bitmap(
                        blocks->castle,                                                       // image source
                        0, 0,                                                                 // coin haut gauche
                        5 * BLOCK_SIZE_SRC, 5 * BLOCK_SIZE_SRC,                               // taille source
                        i * BLOCK_SIZE_RES - cam.x, (j - 4 + marge) * BLOCK_SIZE_RES + cam.y, // coin haut gauche destination
                        5 * BLOCK_SIZE_RES,                                                   // taille destination
                        5 * BLOCK_SIZE_RES,
                        0); // permutation
                    break;
                case PIECE:

                    /* fonction d'affichage d'une piece à ajouter */
                    affichagePiece(&modelPiece, i, j, cam);

                    break;

                default:
                    break;
                }
            }
        }
    }
}

void initCases(cases *blocks)
{

    blocks->wall = al_load_bitmap("AlgoS4/resources/sprites/wall.png");
    if (!blocks->wall)
        printf("al_load_bitmap( wall )");

    blocks->brick = al_load_bitmap("AlgoS4/resources/sprites/brick.png");
    if (!blocks->brick)
        printf("al_load_bitmap( brick )");

    blocks->block = al_load_bitmap("AlgoS4/resources/sprites/block.png");
    if (!blocks->block)
        printf("al_load_bitmap( block )");

    blocks->secret = al_load_bitmap("AlgoS4/resources/sprites/secret-box.png");
    if (!blocks->secret)
        printf("al_load_bitmap( secret )");
    blocks->solid = al_load_bitmap("AlgoS4/resources/sprites/solid.png");
    if (!blocks->secret)
        printf("al_load_bitmap( secret )");

    blocks->bushBig = al_load_bitmap("AlgoS4/resources/sprites/bush-big.png");
    if (!blocks->wall)
        printf("al_load_bitmap( wall )");

    blocks->bushMed = al_load_bitmap("AlgoS4/resources/sprites/bush-med.png");
    if (!blocks->brick)
        printf("al_load_bitmap( brick )");

    blocks->bushSmall = al_load_bitmap("AlgoS4/resources/sprites/bush-small.png");
    if (!blocks->block)
        printf("al_load_bitmap( block )");

    blocks->castle = al_load_bitmap("AlgoS4/resources/sprites/castle.png");
    if (!blocks->secret)
        printf("al_load_bitmap( secret )");

    blocks->cloudBig = al_load_bitmap("AlgoS4/resources/sprites/cloud-big.png");
    if (!blocks->wall)
        printf("al_load_bitmap( wall )");

    blocks->cloudMed = al_load_bitmap("AlgoS4/resources/sprites/cloud-med.png");
    if (!blocks->brick)
        printf("al_load_bitmap( brick )");

    blocks->cloudSmall = al_load_bitmap("AlgoS4/resources/sprites/cloud-small.png");
    if (!blocks->block)
        printf("al_load_bitmap( block )");

    blocks->flag = al_load_bitmap("AlgoS4/resources/sprites/flag.png");
    if (!blocks->secret)
        printf("al_load_bitmap( secret )");

    blocks->hillBig = al_load_bitmap("AlgoS4/resources/sprites/hill-big.png");
    if (!blocks->block)
        printf("al_load_bitmap( block )");

    blocks->hillSmall = al_load_bitmap("AlgoS4/resources/sprites/hill-small.png");
    if (!blocks->secret)
        printf("al_load_bitmap( secret )");

    blocks->pipeBig = al_load_bitmap("AlgoS4/resources/sprites/pipe-big.png");
    if (!blocks->wall)
        printf("al_load_bitmap( wall )");

    blocks->pipeMed = al_load_bitmap("AlgoS4/resources/sprites/pipe-med.png");
    if (!blocks->brick)
        printf("al_load_bitmap( brick )");

    blocks->pipeSmall = al_load_bitmap("AlgoS4/resources/sprites/pipe-small.png");
    if (!blocks->block)
        printf("al_load_bitmap( block )");
}
