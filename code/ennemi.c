#include "ennemi.h"

void countEnnemis(int **map)
{
    numberEnnemis = 0;
    for (int j = 0; j < map_height; j++)
    {
        for (int i = 0; i < map_width; i++)
        {
            if (map[j][i] == GOOMBA || map[j][i] == KOOPA)
            {
                numberEnnemis++;
            }
        }
    }
}

void initGoomba(ennemi *goomba, int x, int y)
{
    goomba->type = GOOMBA;
    goomba->height = 0.9 * BLOCK_SIZE_RES;
    goomba->width = 0.9 * BLOCK_SIZE_RES;
    goomba->x = x;
    goomba->y = y - 1;
    goomba->path = "AlgoS4/resources/sprites/owl.png";
    goomba->dvx = -3;
    goomba->dvy = 1;
    goomba->state = NORMAL;
    goomba->animation = 0;
    goomba->cpt = 0;
    goomba->actif = 0;
    goomba->image = al_load_bitmap(goomba->path);
}

void initKoopa(ennemi *koopa, int x, int y)
{
    koopa->type = KOOPA;
    koopa->height = 1.7 * BLOCK_SIZE_RES;
    koopa->width = 0.9 * BLOCK_SIZE_RES;
    koopa->x = x;
    koopa->y = y - 0.7 * BLOCK_SIZE_RES;
    koopa->path = "AlgoS4/resources/sprites/koopa.png";
    koopa->dvx = -3;
    koopa->dvy = 1;
    koopa->state = NORMAL;
    koopa->animation = 0;
    koopa->cpt = 0;
    koopa->actif = 0;
    koopa->image = al_load_bitmap(koopa->path);
}

ennemi *initEnnemis(ennemi *rep, int **map)
{
    countEnnemis(map);
    rep = malloc(numberEnnemis * sizeof(ennemi));
    int number = 0;

    for (int j = 0; j < map_height - 1; j++)
    {
        for (int i = 0; i < map_width - 1; i++)
        {

            if (map[j][i] == GOOMBA)
            {

                initGoomba(&rep[number], i * BLOCK_SIZE_RES, j * BLOCK_SIZE_RES);
                number++;
            }
            if (map[j][i] == KOOPA)
            {

                initKoopa(&rep[number], i * BLOCK_SIZE_RES, j * BLOCK_SIZE_RES);
                number++;
            }
        }
    }
    return rep;
}

void displayEnnemi(ennemi *rep, camera cam)
{
    ennemi mechant;
    for (int i = 0; i < numberEnnemis; i++)
    {
        if (rep[i].type == GOOMBA)
        {
            mechant = rep[i];

            al_draw_scaled_bitmap(mechant.image,
                                  mechant.animation * BLOCK_SIZE_SRC, 0,
                                  BLOCK_SIZE_SRC, BLOCK_SIZE_SRC,
                                  mechant.x - cam.x, mechant.y - cam.y,
                                  mechant.width, mechant.height,
                                  0);
        }
        else if (rep[i].type == KOOPA)
        {
            mechant = rep[i];
            if (mechant.state == NORMAL)
            {
                al_draw_scaled_bitmap(mechant.image,
                                      mechant.animation * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC - 1,
                                      BLOCK_SIZE_SRC, 23,
                                      mechant.x - cam.x, mechant.y - cam.y,
                                      mechant.width, mechant.height,
                                      (mechant.dvx < 0) ? 0 : ALLEGRO_FLIP_HORIZONTAL);
            }
            else if (mechant.state == CARAPACE_FIXE || mechant.state == CARAPACE_MOUV)
            {
                al_draw_scaled_bitmap(mechant.image,
                                      mechant.animation * BLOCK_SIZE_SRC, 0,
                                      BLOCK_SIZE_SRC, BLOCK_SIZE_SRC - 1,
                                      mechant.x - cam.x, mechant.y - cam.y,
                                      mechant.width, mechant.height,
                                      0);
            }
            else if (mechant.state == MORT)
            {
                al_draw_scaled_bitmap(mechant.image,
                                      BLOCK_SIZE_SRC, 0,
                                      BLOCK_SIZE_SRC, BLOCK_SIZE_SRC - 1,
                                      mechant.x - cam.x, mechant.y - cam.y,
                                      mechant.width, mechant.height,
                                      ALLEGRO_FLIP_VERTICAL);
            }
        }
    }
}

void deplaceEnnemi(ennemi *rep, int **map, camera cam, sound soundEffect)
{

    int cptMax = 0;
    int nbAnimation = 0;
    for (int i = 0; i < numberEnnemis; i++)
    {
        if (rep[i].state == MORT)
        {
            rep[i].cpt++;
            if (rep[i].cpt == 25)
            {
                mortEnnemi(&rep[i]);
            }
        }
        else
        {
            if (rep[i].type != 0)
            {
                if (rep[i].actif == 0)
                {
                    if (cam.x + WINDOW_WIDTH >= rep[i].x)
                    {
                        rep[i].actif = 1;
                    }
                }
                else if (mapEndEnnemi(rep[i], map, ((rep[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT))
                {
                    mortEnnemi(&rep[i]);
                }
                else
                {
                    if (!isBlockEnnemi(rep[i], map, ((rep[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT) && !ennemiToucheEnnemi(&rep[i], i, rep, ((rep[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT, soundEffect))
                    {
                        if (rep[i].state != CARAPACE_FIXE)
                        {
                            ennemi test = rep[i];
                            test.x += (test.dvx >= 0) ? test.width : -test.width;
                            if (rep[i].type == KOOPA && rep[i].state == NORMAL && !isBlockEnnemi(test, map, BAS, PIXEL) && isBlockEnnemi(rep[i], map, BAS, PIXEL))
                            {
                                rep[i].dvx = -rep[i].dvx;
                            }
                            else
                                rep[i].x += rep[i].dvx;
                            if (rep[i].type == GOOMBA || rep[i].type == KOOPA)
                            {
                                cptMax = 3;
                                nbAnimation = 1;
                            }

                            if (rep[i].cpt == cptMax)
                            {
                                if (rep[i].animation < nbAnimation)
                                {
                                    rep[i].animation++;
                                }
                                else
                                {
                                    rep[i].animation = 0;
                                }
                                rep[i].cpt = 0;
                            }
                            else
                            {
                                rep[i].cpt++;
                            }
                        }
                    }
                    else
                    {
                        if (isBlockEnnemi(rep[i], map, ((rep[i].dvx > 0) ? DROITE : GAUCHE), MOUVEMENT))
                        {
                            while (!isBlockEnnemi(rep[i], map, ((rep[i].dvx > 0) ? DROITE : GAUCHE), PIXEL))
                            {
                                rep[i].x += ((rep[i].dvx > 0) ? 1 : -1);
                            }
                        }

                        rep[i].dvx = -rep[i].dvx;
                    }
                }
            }
        }
    }
}

bool isBlockEnnemi(ennemi mechant, int **map, int direction, int vitesse)
{
    int y = 0, x = 0;
    int deplacement = 0;

    switch (direction)
    {
    case DROITE:
        deplacement = (vitesse == MOUVEMENT) ? mechant.dvx : 1;
        y = (mechant.y + mechant.height) / BLOCK_SIZE_RES;
        x = (mechant.x + mechant.width + deplacement) / BLOCK_SIZE_RES;
        break;
    case BAS:
        deplacement = (vitesse == MOUVEMENT) ? mechant.dvy : 1;
        y = (mechant.y + deplacement + mechant.height) / BLOCK_SIZE_RES;
        x = mechant.x / BLOCK_SIZE_RES;
        break;
    case GAUCHE:
        deplacement = (vitesse == MOUVEMENT) ? mechant.dvx : 1;
        y = (mechant.y + mechant.height) / BLOCK_SIZE_RES;
        x = (mechant.x + deplacement) / BLOCK_SIZE_RES;
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
            deplacement = (vitesse == MOUVEMENT) ? mechant.dvx : 1;
            y = (mechant.y) / BLOCK_SIZE_RES;
            x = (mechant.x + mechant.width + deplacement) / BLOCK_SIZE_RES;
            break;
        case BAS:
            deplacement = (vitesse == MOUVEMENT) ? mechant.dvy : 1;
            y = (mechant.y + deplacement + mechant.height) / BLOCK_SIZE_RES;
            x = (mechant.x + mechant.width) / BLOCK_SIZE_RES;
            break;
        case GAUCHE:
            deplacement = (vitesse == MOUVEMENT) ? mechant.dvx : 1;
            y = (mechant.y) / BLOCK_SIZE_RES;
            x = (mechant.x + deplacement) / BLOCK_SIZE_RES;
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

void ennemiDescente(ennemi *rep, int **map)
{
    for (int i = 0; i < numberEnnemis; i++)
    {
        if (rep[i].type != 0 && rep[i].actif != 0)
        {
            if (mapEndEnnemi(rep[i], map, BAS, MOUVEMENT))
            {
                if (mapEndEnnemi(rep[i], map, BAS, MOUVEMENT))
                {
                    while (!mapEndEnnemi(rep[i], map, BAS, PIXEL))
                    {
                        rep[i].y++;
                    }

                    mortEnnemi(&rep[i]);
                    return;
                }

                rep[i].y += rep[i].dvy;
                rep[i].dvy++;
            }

            if (!isBlockEnnemi(rep[i], map, BAS, MOUVEMENT))
            {
                rep[i].y += rep[i].dvy;
                rep[i].dvy++;
            }
            else
            {
                while (!isBlockEnnemi(rep[i], map, BAS, PIXEL))
                {
                    rep[i].y++;
                }
                rep[i].dvy = 1;
            }
        }
    }
}

void ennemiMouvement(ennemi *rep, int **map, camera cam, joueur *perso, sound soundEffect)
{
    deplaceEnnemi(rep, map, cam, soundEffect);
    ennemiDescente(rep, map);
    for (int i = 0; i < numberEnnemis; i++)
    {
        if (ennemiToucheCote(rep[i], perso))
        {
            if (perso->etoile == 0)
            {
                perso->state--;
                ChangementSpritePersonnage(perso);
                if (perso->state < 0)
                {
                    perso->dvx = 0;
                    perso->rdvx = 0;
                    perso->dvy = 0;
                    perso->jump = 0;
                    user.stopwatch = 0;
                }
                else
                {
                    al_play_sample_instance(soundEffect.powerdown);
                }
            }
            else
            {
                mortEnnemi(&rep[i]);
            }
        }
    }
}

bool mapEndEnnemi(ennemi sujet, int **map, int direction, int vitesse)
{
    int y = 0, x = 0;
    int deplacement = 0;

    switch (direction)
    {
    case DROITE:
        deplacement = (vitesse == MOUVEMENT) ? sujet.dvx : 1;
        y = (sujet.y + sujet.height) / BLOCK_SIZE_RES;
        x = (sujet.x + sujet.width + deplacement) / BLOCK_SIZE_RES;
        break;
    case BAS:
        deplacement = (vitesse == MOUVEMENT) ? sujet.dvy : 1;
        y = (sujet.y + deplacement + sujet.height) / BLOCK_SIZE_RES;
        x = sujet.x / BLOCK_SIZE_RES;

        break;
    case GAUCHE:
        deplacement = (vitesse == MOUVEMENT) ? sujet.dvx : 1;
        y = (sujet.y + sujet.height) / BLOCK_SIZE_RES;
        x = (sujet.x - deplacement) / BLOCK_SIZE_RES;
        break;
    }

    return (x < 0 || x > map_width || y < 0 || y >= map_height) ? true : false;
}

void mortGoomba(ennemi *goomba)
{
    goomba->state = MORT;
    goomba->cpt = 0;
    goomba->dvx = 0;
    goomba->dvy = 0;
    goomba->path = "AlgoS4/resources/sprites/owl-dead.png";
    goomba->animation = 0;
    goomba->y += goomba->height / 2;
    goomba->image = al_load_bitmap(goomba->path);
}

void mortKoopa(ennemi *koopa)
{
    koopa->state = MORT;
    koopa->cpt = 0;
    koopa->dvx = 0;
    koopa->dvy = 0;
    koopa->height = 0.8 * BLOCK_SIZE_RES;
    koopa->width = 0.8 * BLOCK_SIZE_RES;
    koopa->animation = 0;
}

void mortEnnemi(ennemi *mechant)
{
    mechant->type = 0;
    mechant->height = 0;
    mechant->width = 0;
    mechant->x = 0;
    mechant->y = 0;
    mechant->path = "";
    mechant->dvx = 0;
    mechant->dvy = 0;
    mechant->state = 0;
    mechant->animation = 0;
    mechant->cpt = 0;
    mechant->actif = 0;
    mechant->image = NULL;
}

bool ennemiToucheCote(ennemi mechant, joueur *perso)
{
    if (perso->state != MORT)
    {
        if (mechant.state == NORMAL || mechant.state == CARAPACE_MOUV || mechant.state == CARAPACE_FIXE)
        {
            if (mechant.type == GOOMBA || (mechant.type == KOOPA))
            {
                if (perso->x >= mechant.x && perso->x <= (mechant.x + mechant.width) &&
                    ((perso->y >= mechant.y && perso->y <= (mechant.y + mechant.height)) || (perso->y + perso->height >= mechant.y && perso->y + perso->height <= mechant.y + mechant.height)))
                {
                    if (perso->invinsible == 0)
                    {
                        perso->invinsible = 1;

                        return true;
                    }
                    else if (perso->invinsible != 0 && perso->etoile == 1)
                    {
                        return true;
                    }
                }
                else if ((perso->x + perso->width) >= mechant.x && (perso->x + perso->width) <= (mechant.x + mechant.width) &&
                         ((perso->y >= mechant.y && perso->y <= (mechant.y + mechant.height)) || (perso->y + perso->height >= mechant.y && perso->y + perso->height <= mechant.y + mechant.height)))
                {

                    if (perso->invinsible == 0)
                    {
                        perso->invinsible = 1;

                        return true;
                    }
                    else if (perso->invinsible != 0 && perso->etoile == 1)
                    {
                        return true;
                    }
                }
                else if (perso->y <= (mechant.y + mechant.height) && perso->y >= (mechant.y) &&
                         ((perso->x >= mechant.x && perso->x <= (mechant.x + mechant.width)) || ((perso->x + perso->width) >= mechant.x && (perso->x + perso->width) <= (mechant.x + mechant.width))))
                {

                    if (perso->invinsible == 0)
                    {
                        perso->invinsible = 1;

                        return true;
                    }
                    else if (perso->invinsible != 0 && perso->etoile == 1)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ennemiToucheEnnemi(ennemi *mechant, int numero, ennemi *rep, int direction, int vitesse, sound soundEffect)
{
    // int y = 0, x = 0;
    int deplacement = 0;

    switch (direction)
    {

    case BAS:
        deplacement = (vitesse == MOUVEMENT) ? mechant->dvy : 1;
        break;
    case DROITE:
    case GAUCHE:
        deplacement = (vitesse == MOUVEMENT) ? mechant->dvx : 1;

        break;
    }
    for (int i = 0; i < numberEnnemis; i++)
    {
        if (i != numero && rep[i].actif != 0)
        {
            if (mechant->state != MORT)
            {

                if (mechant->type == GOOMBA || mechant->type == KOOPA)
                {
                    switch (direction)
                    {

                    case DROITE:

                        if (mechant->x + mechant->width + deplacement >= rep[i].x && mechant->x <= rep[i].x + rep[i].width && ((mechant->y + mechant->height >= rep[i].y && mechant->y <= rep[i].height + rep[i].y)))
                        {
                            if (mechant->state == CARAPACE_MOUV)
                            {
                                if (rep[i].state != MORT)
                                {
                                    switch (rep[i].type)
                                    {
                                    case GOOMBA:
                                        mortGoomba(&rep[i]);
                                        switch (user.level[2])
                                        {
                                        case '1':
                                            user.scoreLv1 += 200;
                                            break;
                                        case '2':
                                            user.scoreLv2 += 200;
                                            break;
                                        case '3':
                                            user.scoreLv3 += 200;
                                            break;
                                        case '4':
                                            user.scoreLv4 += 200;
                                            break;
                                        case '5':
                                            user.scoreLv5 += 200;
                                            break;
                                        }
                                        al_stop_sample_instance(soundEffect.kick);
                                        al_play_sample_instance(soundEffect.kick);
                                        break;
                                    case KOOPA:
                                        if (rep[i].state == NORMAL || rep[i].state == CARAPACE_FIXE)
                                        {
                                            mortKoopa(&rep[i]);
                                            switch (user.level[2])
                                            {
                                            case '1':
                                                user.scoreLv1 += 200;
                                                break;
                                            case '2':
                                                user.scoreLv2 += 200;
                                                break;
                                            case '3':
                                                user.scoreLv3 += 200;
                                                break;
                                            case '4':
                                                user.scoreLv4 += 200;
                                                break;
                                            case '5':
                                                user.scoreLv5 += 200;
                                                break;
                                            }
                                            al_stop_sample_instance(soundEffect.kick);
                                            al_play_sample_instance(soundEffect.kick);
                                        }
                                        else if (rep[i].state == CARAPACE_MOUV)
                                        {
                                            return true;
                                        }

                                        break;

                                    default:
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if (rep[i].state != MORT)
                                {

                                    return true;
                                }
                            }
                        }

                        break;
                    case BAS:

                        break;
                    case GAUCHE:
                        if (mechant->x + deplacement <= rep[i].x + rep[i].width && mechant->x + mechant->width >= rep[i].x && ((mechant->y + mechant->height >= rep[i].y && mechant->y <= rep[i].height + rep[i].y)))
                        {
                            if (mechant->state == CARAPACE_MOUV)
                            {
                                switch (rep[i].type)
                                {
                                case GOOMBA:
                                    mortGoomba(&rep[i]);
                                    switch (user.level[2])
                                    {
                                    case '1':
                                        user.scoreLv1 += 200;
                                        break;
                                    case '2':
                                        user.scoreLv2 += 200;
                                        break;
                                    case '3':
                                        user.scoreLv3 += 200;
                                        break;
                                    case '4':
                                        user.scoreLv4 += 200;
                                        break;
                                    case '5':
                                        user.scoreLv5 += 200;
                                        break;
                                    }
                                    al_stop_sample_instance(soundEffect.kick);
                                    al_play_sample_instance(soundEffect.kick);
                                    break;
                                case KOOPA:
                                    if (rep[i].state == NORMAL || rep[i].state == CARAPACE_FIXE)
                                    {
                                        switch (user.level[2])
                                        {
                                        case '1':
                                            user.scoreLv1 += 200;
                                            break;
                                        case '2':
                                            user.scoreLv2 += 200;
                                            break;
                                        case '3':
                                            user.scoreLv3 += 200;
                                            break;
                                        case '4':
                                            user.scoreLv4 += 200;
                                            break;
                                        case '5':
                                            user.scoreLv5 += 200;
                                            break;
                                        }
                                        mortKoopa(&rep[i]);
                                        al_stop_sample_instance(soundEffect.kick);
                                        al_play_sample_instance(soundEffect.kick);
                                    }
                                    else if (rep[i].state == CARAPACE_MOUV)
                                    {
                                        return true;
                                    }

                                    break;

                                default:
                                    break;
                                }
                            }
                            else
                            {
                                if (rep[i].state != MORT)
                                {

                                    return true;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    return false;
}
