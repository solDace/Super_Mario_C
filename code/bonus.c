#include "bonus.h"

void countBonus(int **map)
{
    numberMushroom = 0;
    for (int j = 0; j < map_height; j++)
    {
        for (int i = 0; i < map_width; i++)
        {
            if (map[j][i] == MUSHROOM_RED || map[j][i] == MUSHROOM_GREEN || map[j][i] == STAR)
            {
                numberMushroom++;
            }
        }
    }
}

void initRedChampi(bonus *powerUp, int x, int y)
{
    powerUp->width = BLOCK_SIZE_RES * 0.9;
    powerUp->height = BLOCK_SIZE_RES * 0.9;
    powerUp->x = x;
    powerUp->y = y - 1;
    powerUp->dvx = 3;
    powerUp->dvy = 1;
    powerUp->facon_mouv = 1;
    powerUp->lequel = 1;
    powerUp->path = "AlgoS4/resources/sprites/mushroom-red.png";
    powerUp->actif = 1; //0: NON    1:OUI
    powerUp->state = NORMAL;
    powerUp->jump = 0;
    powerUp->yMax = 0;
    powerUp->image = al_load_bitmap(powerUp->path);
}

void initGreenChampi(bonus *powerUp, int x, int y)
{
    powerUp->width = BLOCK_SIZE_RES * 0.9;
    powerUp->height = BLOCK_SIZE_RES * 0.9;
    powerUp->x = x;
    powerUp->y = y - 1;
    powerUp->dvx = 3;
    powerUp->dvy = 1;
    powerUp->facon_mouv = 1;
    powerUp->lequel = 2;
    powerUp->path = "AlgoS4/resources/sprites/mushroom-green.png";
    powerUp->actif = 1; //0: NON    1:OUI
    powerUp->state = NORMAL;
    powerUp->jump = 0;
    powerUp->yMax = 0;
    powerUp->image = al_load_bitmap(powerUp->path);
}

void initStar(bonus *powerUp, int x, int y)
{
    powerUp->width = BLOCK_SIZE_RES;
    powerUp->height = BLOCK_SIZE_RES;
    powerUp->x = x;
    powerUp->y = y - 1;
    powerUp->dvx = 5;
    powerUp->dvy = 3;
    powerUp->facon_mouv = 2;
    powerUp->lequel = 3;
    powerUp->path = "AlgoS4/resources/sprites/star.png";
    powerUp->actif = 1; //0: NON    1:OUI
    powerUp->state = NORMAL;
    powerUp->jump = 0;
    powerUp->yMax = 0;
    powerUp->image = al_load_bitmap(powerUp->path);
}

void initBonus(int **map)
{
    countBonus(map);
    powerUp = malloc(numberMushroom * sizeof(bonus));

    for (int i = 0; i < numberMushroom; i++)
    {
        powerUp[i].actif = 0;
    }
}

void displayBonus(camera cam)
{

    for (int i = 0; i < numberMushroom; i++)
    {
        if (powerUp[i].actif == 1)
        {
            al_draw_scaled_bitmap(powerUp[i].image, 0, 0, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, powerUp[i].x - cam.x, powerUp[i].y - cam.y, powerUp[i].width, powerUp[i].height, 0);
        }
    }
}

void deplaceBonus(int **map, camera cam)
{

    for (int i = 0; i < numberMushroom; i++)
    {
        if (powerUp[i].actif == 1)
        {
            if (mapEndBonus(&powerUp[i], map, ((powerUp[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT))
            {
                mortBonus(&powerUp[i]);
            }

            else
            {
                if (!isBlockBonus(&powerUp[i], map, ((powerUp[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT))
                {
                    if (powerUp[i].facon_mouv == 1)
                    {
                        powerUp[i].x += powerUp[i].dvx;
                    }
                    else if (powerUp[i].facon_mouv == 2)
                    {
                        powerUp[i].x += powerUp[i].dvx;
                        sautBonus(&powerUp[i], map);
                    }
                }
                else
                {
                    if (powerUp[i].facon_mouv == 1)
                    {
                        powerUp[i].dvx = -powerUp[i].dvx;
                    }
                    else if (powerUp[i].facon_mouv == 2)
                    {
                        powerUp[i].dvx = -powerUp[i].dvx;
                        sautBonus(&powerUp[i], map);
                    }
                }
            }
        }
    }
}

bool isBlockBonus(bonus *powerUp, int **map, int direction, int vitesse)
{
    int y = 0, x = 0;
    int deplacement = 0;

    switch (direction)
    {
    case DROITE:
        deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
        y = (powerUp->y + powerUp->height) / BLOCK_SIZE_RES;
        x = (powerUp->x + powerUp->width + deplacement) / BLOCK_SIZE_RES;
        break;
    case BAS:
        deplacement = (vitesse == MOUVEMENT) ? powerUp->dvy : 1;
        y = (powerUp->y + deplacement + powerUp->height) / BLOCK_SIZE_RES;
        x = powerUp->x / BLOCK_SIZE_RES;
        break;
    case GAUCHE:
        deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
        y = (powerUp->y + powerUp->height) / BLOCK_SIZE_RES;
        x = (powerUp->x - deplacement) / BLOCK_SIZE_RES;
        break;
    }

    switch (map[y][x])
    {
    case WALL:
    case BRICK:
    case BLOCK:
    case STAR:
    case MUSHROOM_RED:
    case PIPETOPL:
    case PIPETOPR:
    case PIPEBIG:
    case PIPEMED:
    case PIPESMALL:
    case PIPEBIG_RIGHT:
    case PIPEMED_RIGHT:
    case PIPESMALL_RIGHT:
    case SECRET:
    case SOLID:

        return true;

        break;
    default:

        switch (direction)
        {
        case DROITE:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
            y = (powerUp->y) / BLOCK_SIZE_RES;
            x = (powerUp->x + powerUp->width + deplacement) / BLOCK_SIZE_RES;
            break;
        case BAS:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvy : 1;
            y = (powerUp->y + deplacement + powerUp->height) / BLOCK_SIZE_RES;
            x = (powerUp->x + powerUp->width) / BLOCK_SIZE_RES;
            break;
        case GAUCHE:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
            y = (powerUp->y) / BLOCK_SIZE_RES;
            x = (powerUp->x - deplacement) / BLOCK_SIZE_RES;
            break;
        }

        switch (map[y][x])
        {
        case WALL:
        case BRICK:
        case BLOCK:
        case SOLID:
        case STAR:
        case MUSHROOM_RED:
        case PIPETOPL:
        case PIPETOPR:
        case PIPEBIG:
        case PIPEMED:
        case PIPESMALL:
        case PIPEBIG_RIGHT:
        case PIPEMED_RIGHT:
        case PIPESMALL_RIGHT:
        case SECRET:

            return true;

            break;
        default:

            return false;
            break;
        }
        break;
    }
}

bool mapEndBonus(bonus *powerUp, int **map, int direction, int vitesse)
{
    int y = 0, x = 0;
    int deplacement = 0;

    if (powerUp->actif == 1)
    {
        switch (direction)
        {
        case DROITE:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
            y = (powerUp->y + powerUp->height) / BLOCK_SIZE_RES;
            x = (powerUp->x + powerUp->width + deplacement) / BLOCK_SIZE_RES;
            break;
        case BAS:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvy : 1;
            y = (powerUp->y + deplacement + powerUp->height) / BLOCK_SIZE_RES;
            x = powerUp->x / BLOCK_SIZE_RES;

            break;
        case GAUCHE:
            deplacement = (vitesse == MOUVEMENT) ? powerUp->dvx : 1;
            y = (powerUp->y + powerUp->height) / BLOCK_SIZE_RES;
            x = (powerUp->x - deplacement) / BLOCK_SIZE_RES;
            break;
        }

        return (x < 0 || x > map_width || y < 0 || y >= map_height) ? true : false;
    }
    else
        return false;
}

void mortBonus(bonus *powerUp)
{
    powerUp->height = 0;
    powerUp->width = 0;
    powerUp->x = 0;
    powerUp->y = 0;
    powerUp->dvx = 0;
    powerUp->dvy = 0;
    powerUp->path = "";
    powerUp->actif = 0;
    powerUp->image = NULL;
    powerUp->state = 0;
    powerUp->lequel = 0;
    powerUp->facon_mouv = 0;
}

void BonusMouvement(int **map, camera cam, joueur *perso, sound soundEffect)
{
    deplaceBonus(map, cam);
    bonusDescente(map);
    for (int i = 0; i < numberMushroom; i++)
    {
        if (bonusToucheCote(&powerUp[i], perso))
        {
            if (powerUp[i].lequel == 1)
            {
                if (perso->state == 0)
                {
                    perso->state = 1;
                    al_play_sample_instance(soundEffect.powerup);
                    ChangementSpritePersonnage(perso);
                }
            }
            else if (powerUp[i].lequel == 2)
            {
                al_play_sample_instance(soundEffect.up);
                user.try_remaining++;
            }
            else if (powerUp[i].lequel == 3)
            {
                perso->etoile = 1;
                perso->invinsible = 1;
                //effet etoile
                al_play_sample_instance(soundEffect.powerup);
                al_stop_sample_instance(soundEffect.songInstance);
                al_play_sample_instance(soundEffect.star);
            }
            mortBonus(&powerUp[i]);
        }
    }
}

void bonusDescente(int **map)
{
    for (int i = 0; i < numberMushroom; i++)
    {
        if (powerUp[i].jump == 0)
        {
            if (powerUp[i].actif == 1)
            {
                if (mapEndBonus(&powerUp[i], map, BAS, MOUVEMENT))
                {
                    if (mapEndBonus(&powerUp[i], map, BAS, MOUVEMENT))
                    {
                        while (!mapEndBonus(&powerUp[i], map, BAS, PIXEL))
                        {
                            powerUp[i].y++;
                        }
                        mortBonus(&powerUp[i]);
                        return;
                    }
                    powerUp[i].y += powerUp[i].dvy;
                }

                if (!isBlockBonus(&powerUp[i], map, BAS, MOUVEMENT))
                {
                    powerUp[i].y += powerUp[i].dvy;
                    if (powerUp[i].lequel == 1 || powerUp[i].lequel == 2)
                    {
                        powerUp[i].dvy++;
                    }
                }
                else
                {
                    while (!isBlockBonus(&powerUp[i], map, BAS, PIXEL))
                    {
                        powerUp[i].y++;
                    }
                    if (powerUp[i].lequel == 1 || powerUp[i].lequel == 2)
                    {
                        powerUp[i].dvy = 1;
                    }
                    else if (powerUp[i].lequel == 3)
                    {
                        powerUp[i].jump = 3;
                        powerUp[i].dvy = 3;
                        powerUp[i].yMax = powerUp[i].y - (1 * BLOCK_SIZE_RES) + 1;
                    }
                }
            }
        }
    }
}

bool bonusToucheCote(bonus *powerUp, joueur *perso)
{

    if (powerUp->lequel != 0)
    {
        if (perso->x >= powerUp->x && perso->x <= (powerUp->x + powerUp->width / 2) &&
            ((perso->y >= powerUp->y && perso->y <= (powerUp->y + powerUp->height)) || (perso->y + perso->height >= powerUp->y && perso->y + perso->height <= powerUp->y + powerUp->height)))
        {

            return true;
        }
        else if ((perso->x + perso->width / 2) >= powerUp->x && (perso->x + perso->width) <= (powerUp->x + powerUp->width) &&
                 ((perso->y >= powerUp->y && perso->y <= (powerUp->y + powerUp->height)) || (perso->y + perso->height >= powerUp->y && perso->y + perso->height <= powerUp->y + powerUp->height)))
        {

            return true;
        }
        else if (perso->y <= (powerUp->y + powerUp->height) && perso->y >= (powerUp->y) &&
                 ((perso->x >= powerUp->x && perso->x <= (powerUp->x + powerUp->width)) || ((perso->x + perso->width) >= powerUp->x && (perso->x + perso->width) <= (powerUp->x + powerUp->width))))
        {

            return true;
        }
    }
    return false;
}

void BonusMonte(int **map)
{
    for (int i = 0; i < numberMushroom; i++)
    {
        if (powerUp[i].lequel == 3)
        {
            if (!mapEndBonus(&powerUp[i], map, HAUT, MOUVEMENT))
            {
                if (!isBlockBonus(&powerUp[i], map, HAUT, MOUVEMENT))
                {
                    if (powerUp[i].y > powerUp[i].yMax)
                    {
                        powerUp[i].y += (-1) * powerUp[i].dvy;
                    }
                    else
                    {
                        powerUp[i].jump = 0;
                    }
                }
                else
                {
                    while (!isBlockBonus(&powerUp[i], map, HAUT, PIXEL))
                    {
                        powerUp[i].y--;
                    }

                    powerUp[i].jump = 0;
                }
            }
            else
            {
                if (powerUp[i].y > powerUp[i].yMax)
                {
                    powerUp[i].y += (-1) * powerUp[i].dvy;
                }
                else
                {
                    powerUp[i].jump = 0;
                }
            }
        }
    }
}

void sautBonus(bonus *powerUp, int **map)
{

    switch (powerUp->jump)
    {
    case 0:
        if (!mapEndBonus(powerUp, map, BAS, MOUVEMENT) || powerUp->y < map_height - 2 * BLOCK_SIZE_RES)
        {
            bonusDescente(map);
        }

        break;
    case 1:
    case 3:
        BonusMonte(map);

        break;
    }
}
