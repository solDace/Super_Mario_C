/**
 * @file allegro.c
 * @brief Ensemble des fonctions reltives au deplacement et a l'affichage du personnage
 * @version 0.1
 * @date 2021-01-20
 *
 *
 */

#include "joueur.h"
#include "ennemi.h"
#include "bonus.h"

void initImage(char *path, joueur *personnage)
{
    ALLEGRO_BITMAP *bitmap = al_load_bitmap(path);

    personnage->path = path;

    personnage->image = bitmap;
}

void initPersonnage(joueur *personnage)
{
    personnage->x = 6 * BLOCK_SIZE_RES;
    personnage->dvx = 0;
    personnage->rdvx = 0;
    personnage->dvy = 0;
    personnage->width = 0.9 * BLOCK_SIZE_RES;
    personnage->height = 1 * BLOCK_SIZE_RES - 1;
    personnage->y = 12 * BLOCK_SIZE_RES - 1 - personnage->height;
    personnage->state = 0;
    personnage->invinsible = 0;
    personnage->jump = 0;
    personnage->mouv = 1;
    personnage->yMax = 0;
    personnage->cptrun = 0;
    personnage->etoile = 0;
    personnage->cptEtoile = 0;
    personnage->display = 0;
}

void personnageMonte(joueur *personnage, int **map, sound soundEffect)
{
    if (!mapEndJoueur(personnage, map, HAUT, MOUVEMENT))
    {
        if (!isBlock(personnage, map, HAUT, MOUVEMENT, soundEffect))
        {
            if (personnage->y > personnage->yMax)
            {

                personnage->y += (-1) * personnage->dvy;
                personnage->dvy--;
            }
            else
            {

                personnage->dvy += personnage->dvy * 0.05 + 1;
                personnage->jump = 0;
            }
        }
        else
        {
            while (!isBlock(personnage, map, HAUT, PIXEL, soundEffect))
            {
                personnage->y--;
            }

            personnage->jump = 0;
        }
    }
    else
    {
        if (personnage->y > personnage->yMax)
        {

            personnage->y += (-1) * personnage->dvy;
            personnage->dvy--;
        }
        else
        {

            personnage->dvy += personnage->dvy * 0.05 + 1;
            personnage->jump = 0;
        }
    }
}

void personnageDescente(joueur *personnage, int **map, ennemi *rep, sound soundEffect)
{
    if (!mapEndJoueur(personnage, map, HAUT, PIXEL))
    {
        if (!isBlock(personnage, map, BAS, MOUVEMENT, soundEffect))
        {
            personnage->y += personnage->dvy;
            personnage->dvy += personnage->dvy * 0.05 + 1;

            for (int i = 0; i < numberEnnemis; i++)
            {
                if (isEnnemi(personnage, rep[i]))
                {

                    if (rep[i].type == GOOMBA)
                    {
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

                        if (personnage->etoile == 0)
                        {
                            personnage->invinsible = 0;
                        }
                        personnage->jump = 3;
                        personnage->dvy = 14;

                        al_play_sample_instance(soundEffect.stomp);
                        personnage->yMax = personnage->y - (JUMP_HEIGHT / 2 * BLOCK_SIZE_RES); // Hauteur Max 210px au-dessus du personnage

                        //ajouter des points au score
                    }
                    else if (rep[i].type == KOOPA)
                    {
                        switch (rep[i].state)
                        {

                        case NORMAL:
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
                            rep[i].height = 0.8 * BLOCK_SIZE_RES;
                            rep[i].width = 0.8 * BLOCK_SIZE_RES;
                            al_play_sample_instance(soundEffect.stomp);
                        case CARAPACE_MOUV:
                            rep[i].state = CARAPACE_FIXE;
                            rep[i].dvx = 0;
                            al_play_sample_instance(soundEffect.kick);
                            break;
                        case CARAPACE_FIXE:
                            rep[i].state = CARAPACE_MOUV;
                            rep[i].dvx = KOOPA_SPEED;
                            rep[i].animation = 1;
                            al_play_sample_instance(soundEffect.kick);
                            break;

                        default:
                            break;
                        }
                        personnage->invinsible = 49;
                        personnage->jump = 3;
                        personnage->dvy = 14;
                        personnage->yMax = personnage->y - (JUMP_HEIGHT / 2 * BLOCK_SIZE_RES); // Hauteur Max 210px au-dessus du personnage

                        //ajouter des points au score
                    }
                }
            }
        }
        else
        {
            while (!isBlock(personnage, map, BAS, PIXEL, soundEffect))
            {
                personnage->y++;
            }
            personnage->jump = 0;
            personnage->dvy = 5;
        }
    }
    else
    {
        personnage->y += personnage->dvy;
        personnage->dvy += personnage->dvy * 0.05 + 1;

        for (int i = 0; i < numberEnnemis; i++)
        {
            if (isEnnemi(personnage, rep[i]))
            {

                if (rep[i].type == GOOMBA)
                {

                    mortEnnemi(&rep[i]);

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
                    //ajouter des points au score
                }
            }
        }
    }
}

void sautpersonnage(joueur *personnage, int **map, ennemi *rep, sound soundEffect)
{

    switch (personnage->jump)
    {
    case 0:
        if (!mapEndJoueur(personnage, map, BAS, MOUVEMENT) || personnage->y < map_height - 2 * BLOCK_SIZE_RES)
        {
            personnageDescente(personnage, map, rep, soundEffect);
        }
        else
        {
            personnage->state = -1;
        }
        break;
    case 1:
    case 3:

        personnageMonte(personnage, map, soundEffect);

        break;
    }
}

void afficheImageJump(joueur *personnage, camera *cam, int **map, sound soundEffect)
{
    if (!mapEndJoueur(personnage, map, HAUT, PIXEL))
    {
        if (personnage->mouv != 9)
        {
            /* code */
            if ((personnage->jump == 1 || personnage->jump == 0 || personnage->jump == 3) && (!isBlock(personnage, map, BAS, PIXEL, soundEffect)))
            {
                if (personnage->mouv == 8 || personnage->mouv == 7 || personnage->mouv == 6 || personnage->mouv == 5)
                {
                    if (personnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(personnage->image, 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(personnage->image, couleurFiltre(personnage->cptEtoile), 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        personnage->cptEtoile++;
                    }
                }
                else
                {
                    if (personnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(personnage->image, 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(personnage->image, couleurFiltre(personnage->cptEtoile), 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                        personnage->cptEtoile++;
                    }
                }
            }
            else if (personnage->jump == 0 && isBlock(personnage, map, BAS, PIXEL, soundEffect))
            {
                if (personnage->etoile == 0)
                {
                    al_draw_scaled_bitmap(personnage->image, 2 * BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                }
                else
                {
                    al_draw_tinted_scaled_bitmap(personnage->image, couleurFiltre(personnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                    personnage->cptEtoile++;
                }
            }
        }
    }
    else
    {
        if (personnage->mouv != 9)
        {
            /* code */
            if ((personnage->jump == 1 || personnage->jump == 0 || personnage->jump == 3))
            {
                if (personnage->mouv == 8 || personnage->mouv == 7 || personnage->mouv == 6 || personnage->mouv == 5)
                {

                    if (personnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(personnage->image, 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(personnage->image, couleurFiltre(personnage->cptEtoile), 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        personnage->cptEtoile++;
                    }
                }
                else
                {
                    if (personnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(personnage->image, 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(personnage->image, couleurFiltre(personnage->cptEtoile), 0, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((personnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
                        personnage->cptEtoile++;
                    }
                }
            }
            /* else if (personnage->jump == 0 && isBlock(personnage, map, BAS, PIXEL))
            {
                al_draw_scaled_bitmap(personnage->image, 2 * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, personnage->x - cam->x, personnage->y - cam->y, personnage->width, personnage->height, 0);
            } */
        }
    }
}

void ChangementSpritePersonnage(joueur *personnage)
{
    switch (personnage->state)
    {
    case 0:
        if(personnage->character == 0){
            initImage("./AlgoS4/resources/sprites/mario-small.png", personnage);
            personnage->height = 1 * BLOCK_SIZE_RES - 1;
            personnage->y = personnage->y + BLOCK_SIZE_RES;
        }
        else{
            initImage("./AlgoS4/resources/sprites/luigi-small.png", personnage);
            personnage->height = 1 * BLOCK_SIZE_RES - 1;
            personnage->y = personnage->y + BLOCK_SIZE_RES;
        }
        break;

    case 1:
        if(personnage->character == 0){
            initImage("./AlgoS4/resources/sprites/mario-big.png", personnage);
            personnage->height = 2 * BLOCK_SIZE_RES - 1;
            personnage->y -= BLOCK_SIZE_RES;
        }
        else{
            initImage("./AlgoS4/resources/sprites/luigi-big.png", personnage);
            personnage->height = 2 * BLOCK_SIZE_RES - 1;
            personnage->y -= BLOCK_SIZE_RES;
        }
        break;
    }
}

void avancer(joueur *personnage, camera *cam, int **map, ennemi *rep, sound soundEffect)
{
    int approche = 0;
    if (!mapEndJoueur(personnage, map, HAUT, PIXEL))
    {
        if (!isBlock(personnage, map, DROITE, MOUVEMENT, soundEffect))
        {
            personnage->x += personnage->dvx;
            for (int i = 0; i < numberEnnemis; i++)
            {
                if (ennemiToucheCote(rep[i], personnage))
                {
                    if (rep[i].type == KOOPA && rep[i].state == CARAPACE_FIXE)
                    {

                        rep[i].state = CARAPACE_MOUV;
                        rep[i].dvx = KOOPA_SPEED;
                        rep[i].animation = 1;
                        personnage->invinsible = 49;
                        al_play_sample_instance(soundEffect.kick);
                    }
                    else if (rep[i].type == GOOMBA || (rep[i].type == KOOPA /*&& rep[i].state == NORMAL*/))
                    {
                        if (personnage->etoile == 0)
                        {
                            personnage->state--;
                            if (personnage->state < 0)
                            {
                                personnage->dvx = 0;
                                personnage->rdvx = 0;
                                personnage->dvy = 0;
                                personnage->jump = 0;
                                user.stopwatch = 0;
                            }
                            else
                            {
                                al_play_sample_instance(soundEffect.powerdown);
                            }
                            personnage->invinsible = 1;
                            ChangementSpritePersonnage(personnage);
                        }
                        else
                        {
                            mortEnnemi(&rep[i]);
                        }
                    }
                }
            }
            if ((personnage->x - cam->x) >= 13 * BLOCK_SIZE_RES && (cam->x + WINDOW_WIDTH + personnage->dvx) / BLOCK_SIZE_RES < map_width)
            {
                cam->x += personnage->dvx;
            }
        }
        else
        {

            while (approche == 0)
            {
                if (isBlock(personnage, map, DROITE, PIXEL, soundEffect))
                {
                    approche++;
                }
                else
                {
                    personnage->x++;
                }
            }
        }
    }
    else
    {
        personnage->x += personnage->dvx;

        if ((personnage->x - cam->x) >= 13 * BLOCK_SIZE_RES && (cam->x + WINDOW_WIDTH + personnage->dvx) / BLOCK_SIZE_RES < map_width)
        {
            cam->x += personnage->dvx;
        }
    }
}

void avanceEvent(joueur *ptpersonnage, camera *cam, int **map, ennemi *rep, sound soundEffect)
{

    if (ptpersonnage->mouv == 2 || ptpersonnage->mouv == 3 || ptpersonnage->mouv == 4)
    {
        if (!mapEndJoueur(ptpersonnage, map, HAUT, PIXEL))
        {
            if (mapEndJoueur(ptpersonnage, map, DROITE, PIXEL))
            {
                /* code */
            }
            else if (mapEndJoueur(ptpersonnage, map, DROITE, MOUVEMENT))
            {
                while (!mapEndJoueur(ptpersonnage, map, DROITE, PIXEL))
                {
                    ptpersonnage->x++;
                }
            }
            else
            {
                avancer(ptpersonnage, cam, map, rep, soundEffect);
            }
        }
        else
        {
            avancer(ptpersonnage, cam, map, rep, soundEffect);
        }
    }
}

void afficheAnime(joueur *ptpersonnage, camera *cam, int **map, sound soundEffect)
{
    if (!mapEndJoueur(ptpersonnage, map, BAS, MOUVEMENT))
    {
        /* code */
        if (ptpersonnage->state == -1)
        {
            al_draw_scaled_bitmap(ptpersonnage->image, 0, 0, BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
        }
        else if (ptpersonnage->invinsible % 4 == 1 && ptpersonnage->state != 2 && ptpersonnage->etoile == 0)
        {
            al_draw_scaled_bitmap(ptpersonnage->image, 0, 0, 0, 0, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
        }
        else if (ptpersonnage->invinsible % 4 == 1 && ptpersonnage->state == 2 && ptpersonnage->etoile == 0)
        {
            al_draw_scaled_bitmap(ptpersonnage->image, 0, 0, 0, 0, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
        }
        else
        {

            if (mapEndJoueur(ptpersonnage, map, HAUT, PIXEL))
            {
                {
                    switch (ptpersonnage->mouv)
                    {
                    case 0:

                        break;
                    case 1:

                        switch (ptpersonnage->display)
                        {
                        case 0:
                            if (ptpersonnage->etoile == 0)
                            {
                                al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            }
                            else
                            {
                                al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                                ptpersonnage->cptEtoile++;
                            }
                            break;
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                            ptpersonnage->display++;
                            break;
                        case 15:
                            break;
                        default:
                            if (ptpersonnage->etoile == 0)
                            {
                                al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            }
                            else
                            {
                                al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                                ptpersonnage->cptEtoile++;
                            }
                            ptpersonnage->display++;
                            break;
                        }

                        break;

                    case 2:

                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 4;
                            ptpersonnage->cptrun = 0;
                        }

                        break;
                    case 3:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 2;
                            ptpersonnage->cptrun = 0;
                        }

                        break;
                    case 4:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 3;
                            ptpersonnage->cptrun = 0;
                        }

                        break;
                    case 5:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                            ptpersonnage->cptEtoile++;
                        }

                        break;
                    case 6:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 8;
                            ptpersonnage->cptrun = 0;
                        }

                        break;
                    case 7:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 6;
                            ptpersonnage->cptrun = 0;
                        }

                        break;

                    case 8:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->cptrun++;
                        if (ptpersonnage->cptrun == 6)
                        {
                            ptpersonnage->mouv = 7;
                            ptpersonnage->cptrun = 0;
                        }

                        break;
                    case 9:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 0, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 0, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        break;
                    }
                }
            }
            else if ((ptpersonnage->jump == 1 || ptpersonnage->jump == 0 || ptpersonnage->jump == 3) && (!isBlock(ptpersonnage, map, BAS, MOUVEMENT, soundEffect)) && ptpersonnage->mouv != 9)
            {
                afficheImageJump(ptpersonnage, cam, map, soundEffect);
            }
            else

            {

                switch (ptpersonnage->mouv)
                {
                case 0:

                    break;
                case 1:

                    switch (ptpersonnage->display)
                    {
                    case 0:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        break;
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        ptpersonnage->display++;
                        break;
                    case 15:
                        break;
                    default:
                        if (ptpersonnage->etoile == 0)
                        {
                            al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        }
                        else
                        {
                            al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                            ptpersonnage->cptEtoile++;
                        }

                        ptpersonnage->display++;
                        break;
                    }

                    break;

                    break;

                case 2:

                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 4;
                        ptpersonnage->cptrun = 0;
                    }

                    break;
                case 3:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 2;
                        ptpersonnage->cptrun = 0;
                    }

                    break;
                case 4:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y, ptpersonnage->width, ptpersonnage->height, 0);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 3;
                        ptpersonnage->cptrun = 0;
                    }

                    break;
                case 5:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        ptpersonnage->cptEtoile++;
                    }

                    break;
                case 6:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 8;
                        ptpersonnage->cptrun = 0;
                    }

                    break;
                case 7:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), BLOCK_SIZE_SRC, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 6;
                        ptpersonnage->cptrun = 0;
                    }

                    break;

                case 8:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 0, 2 * ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, ALLEGRO_FLIP_HORIZONTAL);
                        ptpersonnage->cptEtoile++;
                    }

                    ptpersonnage->cptrun++;
                    if (ptpersonnage->cptrun == 6)
                    {
                        ptpersonnage->mouv = 7;
                        ptpersonnage->cptrun = 0;
                    }

                    break;
                case 9:
                    if (ptpersonnage->etoile == 0)
                    {
                        al_draw_scaled_bitmap(ptpersonnage->image, 2 * BLOCK_SIZE_SRC, 0, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                    }
                    else
                    {
                        al_draw_tinted_scaled_bitmap(ptpersonnage->image, couleurFiltre(ptpersonnage->cptEtoile), 2 * BLOCK_SIZE_SRC, 0, BLOCK_SIZE_SRC, ((ptpersonnage->height + 1) / BLOCK_SIZE_RES) * BLOCK_SIZE_SRC, ptpersonnage->x - cam->x, ptpersonnage->y - cam->y, ptpersonnage->width, ptpersonnage->height, 0);
                        ptpersonnage->cptEtoile++;
                    }

                    break;
                }
            }
        }
    }
}

void reculer(joueur *personnage, camera *cam, int **map, ennemi *rep, sound soundEffect)
{
    int approche = 0;
    if (!mapEndJoueur(personnage, map, HAUT, PIXEL))
    {

        if (!isBlock(personnage, map, GAUCHE, MOUVEMENT, soundEffect))
        {
            personnage->x -= personnage->rdvx;
            for (int i = 0; i < numberEnnemis; i++)
            {
                if (ennemiToucheCote(rep[i], personnage))
                {
                    if (rep[i].type == KOOPA && rep[i].state == CARAPACE_FIXE)
                    {

                        rep[i].state = CARAPACE_MOUV;
                        rep[i].dvx = -KOOPA_SPEED;
                        rep[i].animation = 1;
                        personnage->invinsible = 49;
                        al_play_sample_instance(soundEffect.kick);
                    }
                    else if (rep[i].type == GOOMBA || (rep[i].type == KOOPA /*&& rep[i].state == NORMAL*/))
                    {
                        if (personnage->etoile == 0)
                        {
                            personnage->state--;
                            personnage->invinsible = 1;
                            ChangementSpritePersonnage(personnage);
                            if (personnage->state < 0)
                            {
                                personnage->dvx = 0;
                                personnage->rdvx = 0;
                                personnage->dvy = 0;
                                personnage->jump = 0;
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

            if ((personnage->x - cam->x) <= 10 * BLOCK_SIZE_RES && (cam->x - personnage->rdvx) > 0)
            {

                cam->x -= personnage->rdvx;
            }
        }
        else
        {
            while (approche == 0)
            {
                if (isBlock(personnage, map, GAUCHE, PIXEL, soundEffect))
                {
                    approche++;
                }
                else
                {
                    personnage->x--;
                }
            }
        }
    }
    else
    {
        personnage->x -= personnage->rdvx;

        if ((personnage->x - cam->x) <= 10 * BLOCK_SIZE_RES && (cam->x - personnage->rdvx) > 0)
        {

            cam->x -= personnage->rdvx;
        }
    }
}

void reculerEvent(joueur *ptpersonnage, camera *cam, int **map, ennemi *rep, sound soundEffect)
{
    if (ptpersonnage->mouv == 6 || ptpersonnage->mouv == 7 || ptpersonnage->mouv == 8)
    {
        if (!mapEndJoueur(ptpersonnage, map, HAUT, PIXEL))
        {
            if (mapEndJoueur(ptpersonnage, map, GAUCHE, PIXEL))
            {
                /* code */
            }
            else if (mapEndJoueur(ptpersonnage, map, GAUCHE, MOUVEMENT))
            {
                while (!mapEndJoueur(ptpersonnage, map, GAUCHE, PIXEL))
                {
                    ptpersonnage->x--;
                }
            }
            else
            {
                reculer(ptpersonnage, cam, map, rep, soundEffect);
            }
        }
        else
        {
            reculer(ptpersonnage, cam, map, rep, soundEffect);
        }
    }
}

int isBlock(joueur *personnage, int **map, int direction, int vitesse, sound soundEffect)
{

    int y = 0, x = 0;
    int deplacement = 0;
    bool end = false;
    for (int i = 0; i <= (personnage->height + 1) / BLOCK_SIZE_RES; i++)
    {
        for (int j = 0; j <= (int)((int)(personnage->width) / (int)(0.9 * BLOCK_SIZE_RES)); j++)
        {

            switch (direction)
            {
            case HAUT:
                deplacement = (vitesse == MOUVEMENT) ? (-1) * personnage->dvy : 1;
                y = (personnage->y + deplacement) / BLOCK_SIZE_RES;
                x = (personnage->x + ((j != 0) ? -0.1 * BLOCK_SIZE_RES : 0.1 * BLOCK_SIZE_RES)) / BLOCK_SIZE_RES + j;
                break;
            case DROITE:
                deplacement = (vitesse == MOUVEMENT) ? personnage->dvx : 1;
                y = (personnage->y + ((i != 0) ? 1 : -1) + personnage->height) / BLOCK_SIZE_RES - i;
                x = (personnage->x + personnage->width + deplacement) / BLOCK_SIZE_RES;
                break;
            case BAS:
                deplacement = (vitesse == MOUVEMENT) ? personnage->dvy : 1;
                y = (personnage->y + deplacement + personnage->height) / BLOCK_SIZE_RES;
                x = (personnage->x + ((j != 0) ? -0.1 * BLOCK_SIZE_RES : 0.1 * BLOCK_SIZE_RES)) / BLOCK_SIZE_RES + j;
                break;
            case GAUCHE:
                deplacement = (vitesse == MOUVEMENT) ? personnage->rdvx : 1;
                y = (personnage->y + ((i != 0) ? 1 : -1) + personnage->height) / BLOCK_SIZE_RES - i;
                x = (personnage->x - deplacement) / BLOCK_SIZE_RES;
                break;
            }

            if (y < 0)
            {
                return false;
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
                if (direction == HAUT && vitesse == PIXEL /* && mario = GRAND */)
                {
                    changeBlock(map, x, y, personnage, soundEffect);
                }

                end = true;

                break;
            case SECRET:
                if (direction == HAUT && vitesse == PIXEL /* && mario = GRAND */)
                {
                    changeBlock(map, x, y, personnage, soundEffect);
                    al_stop_sample_instance(soundEffect.coin);
                    al_play_sample_instance(soundEffect.coin);
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
                    /* fonction d'ajout de pièce à rajouter */
                    ramassePiece(&user);
                }
                end = true;

                break;
            case SOLID:
                if (direction == HAUT && vitesse == PIXEL /* && mario = GRAND */)
                {
                    deplacement = (vitesse == MOUVEMENT) ? (-1) * personnage->dvy : 1;
                    y = (personnage->y + deplacement) / BLOCK_SIZE_RES;
                    x = (personnage->x + personnage->width) / BLOCK_SIZE_RES;

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
                        if (direction == HAUT && vitesse == PIXEL /* && mario = GRAND */)
                        {
                            changeBlock(map, x, y, personnage, soundEffect);
                        }

                        end = true;
                        break;
                    case SECRET:
                        if (direction == HAUT && vitesse == PIXEL /* && mario = GRAND */)
                        {
                            changeBlock(map, x, y, personnage, soundEffect);
                            al_stop_sample_instance(soundEffect.coin);

                            al_play_sample_instance(soundEffect.coin);
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

                            /* fonction d'ajout de pièce à rajouter */
                            ramassePiece(&user);
                        }

                        end = true;

                        break;
                    default:

                        break;
                    }
                }
                end = true;

                break;
            default:
                if (map[y][x] == MUSHROOM_GREEN && direction == HAUT)
                {
                    if (vitesse == MOUVEMENT)
                    {
                        while (!isBlock(personnage, map, direction, PIXEL, soundEffect))
                        {
                            personnage->y--;
                        }
                        changeBlock(map, x, y, personnage, soundEffect);
                    }

                    end = true;
                }
                if (map[y][x] == PIECE)
                {
                    al_stop_sample_instance(soundEffect.coin);
                    al_play_sample_instance(soundEffect.coin);
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

                    /*Fonction de gestion quand collision avec une piece */
                    touchePiece(&user, map, x, y);
                }
                break;
            }
        }
    }

    return end;
}

void changeBlock(int **map, int x, int y, joueur *personnage, sound soundEffect)
{

    switch (map[y][x])
    {
    case SECRET:
        map[y][x] = SOLID;
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

        /* ajout d'une pi�ce */
        break;
    case MUSHROOM_RED:
        map[y][x] = SOLID;
        al_play_sample_instance(soundEffect.powerup_appears);

        for (int i = 0; i < numberMushroom; i++)
        {
            if (powerUp[i].actif == 0)
            {
                initRedChampi(&powerUp[i], x * BLOCK_SIZE_RES, (y - 1) * BLOCK_SIZE_RES);
                break;
            }
        }

        break;
    case MUSHROOM_GREEN:
        map[y][x] = SOLID;
        al_play_sample_instance(soundEffect.powerup_appears);
        for (int i = 0; i < numberMushroom; i++)
        {
            if (powerUp[i].actif == 0)
            {
                initGreenChampi(&powerUp[i], x * BLOCK_SIZE_RES, (y - 1) * BLOCK_SIZE_RES);
                break;
            }
        }

        break;
    case BRICK:
        if (personnage->state == 1)
        {
            map[y][x] = 0;
            switch (user.level[2])
            {
            case '1':
                user.scoreLv1 += 50;
                break;
            case '2':
                user.scoreLv2 += 50;
                break;
            case '3':
                user.scoreLv3 += 50;
                break;
            case '4':
                user.scoreLv4 += 50;
                break;
            case '5':
                user.scoreLv5 += 50;
                break;
            }
            al_play_sample_instance(soundEffect.breakBlock);
        }
        else
        {
            al_play_sample_instance(soundEffect.bump);
            map[y][x] = BRICK;
        }
        /* ajout de score */
        break;
    case STAR:
        map[y][x] = SOLID;
        al_play_sample_instance(soundEffect.powerup_appears);
        for (int i = 0; i < numberMushroom; i++)
        {
            if (powerUp[i].actif == 0)
            {
                initStar(&powerUp[i], x * BLOCK_SIZE_RES, (y - 1) * BLOCK_SIZE_RES);
                break;
            }
        }

        break;

    default:
        break;
    }
}

bool isEnnemi(joueur *perso, ennemi mechant)
{
    if (perso->state >= 0)
    {

        if (mechant.state != MORT &&
            ((perso->y + perso->height) <= (mechant.y + mechant.height) && (perso->y + perso->height) >= (mechant.y) &&
             ((perso->x >= mechant.x && perso->x <= (mechant.x + mechant.width)) || ((perso->x + perso->width) >= mechant.x && (perso->x + perso->width) <= (mechant.x + mechant.width)))))
        {
            return true;
        }
    }
    return false;
}

bool mapEndJoueur(joueur *perso, int **map, int direction, int vitesse)
{
    int y = 0, x = 0;
    int deplacement = 0;

    switch (direction)
    {
    case DROITE:
        deplacement = (vitesse == MOUVEMENT) ? perso->dvx : 1;
        y = (perso->y + perso->height) / BLOCK_SIZE_RES;
        x = (perso->x + perso->width + deplacement) / BLOCK_SIZE_RES;
        break;
    case BAS:
        deplacement = (vitesse == MOUVEMENT) ? perso->dvy : 1;
        y = (perso->y + deplacement + perso->height) / BLOCK_SIZE_RES;
        x = perso->x / BLOCK_SIZE_RES;
        break;
    case HAUT:
        deplacement = (vitesse == MOUVEMENT) ? (-1) * perso->dvy : 1;
        y = (perso->y + deplacement) / BLOCK_SIZE_RES;
        x = perso->x / BLOCK_SIZE_RES;

        break;
    case GAUCHE:
        deplacement = (vitesse == MOUVEMENT) ? perso->rdvx : 1;
        y = (perso->y + perso->height) / BLOCK_SIZE_RES;
        x = (perso->x - deplacement - BLOCK_SIZE_RES) / BLOCK_SIZE_RES;
        break;
    }

    return (x < 0 || x > map_width || y < 0 || y >= map_height) ? true : false;
}

bool isFlag(joueur *perso, int **map)
{
    for (int i = 0; i < map_height; i++)
    {
        if (map[i][(perso->x + 20) / BLOCK_SIZE_RES] == FLAG)
        {

            return true;
        }
    }
    return false;
}

void endLevelAnimtion(joueur *ptpersonnage, settings *system, int **map, int timer, sound soundEffect)
{
    /* Descente du drapeau */
    if (!mapEndJoueur(ptpersonnage, map, HAUT, PIXEL))
    {
        if (isFlag(ptpersonnage, map) && system->load != 1 && system->mode == PLAYING_MAP)
        {
            ptpersonnage->etoile = 0;
            system->mode = END_LEVEL;
            switch (user.level[2])
            {
            case '1':
                user.scoreLv1 += (tpsNiveau - timer / REFRESH_RATE) * 50;
                break;
            case '2':
                user.scoreLv2 += (tpsNiveau - timer / REFRESH_RATE) * 50;
                break;
            case '3':
                user.scoreLv3 += (tpsNiveau - timer / REFRESH_RATE) * 50;
                break;
            case '4':
                user.scoreLv4 += (tpsNiveau - timer / REFRESH_RATE) * 50;
                break;
            case '5':
                user.scoreLv5 += (tpsNiveau - timer / REFRESH_RATE) * 50;
                break;
            }
            al_stop_sample_instance(soundEffect.songInstance);
            al_stop_sample_instance(soundEffect.star);
            al_play_sample_instance(soundEffect.flagpole);

            switch (map_height - (ptpersonnage->y / BLOCK_SIZE_RES))
            {
            case 5:
                switch (user.level[2])
                {
                case '1':
                    user.scoreLv1 += 100;
                    break;
                case '2':
                    user.scoreLv2 += 100;
                    break;
                case '3':
                    user.scoreLv3 += 100;
                    break;
                case '4':
                    user.scoreLv4 += 100;
                    break;
                case '5':
                    user.scoreLv5 += 100;
                    break;
                }
                break;
            case 7:
            case 6:
                switch (user.level[2])
                {
                case '1':
                    user.scoreLv1 += 400;
                    break;
                case '2':
                    user.scoreLv2 += 400;
                    break;
                case '3':
                    user.scoreLv3 += 400;
                    break;
                case '4':
                    user.scoreLv4 += 400;
                    break;
                case '5':
                    user.scoreLv5 += 400;
                    break;
                }
                break;
            case 8:
                switch (user.level[2])
                {
                case '1':
                    user.scoreLv1 += 800;
                    break;
                case '2':
                    user.scoreLv2 += 800;
                    break;
                case '3':
                    user.scoreLv3 += 800;
                    break;
                case '4':
                    user.scoreLv4 += 800;
                    break;
                case '5':
                    user.scoreLv5 += 800;
                    break;
                }
                break;
            case 11:
            case 9:
            case 10:
                switch (user.level[2])
                {
                case '1':
                    user.scoreLv1 += 1600;
                    break;
                case '2':
                    user.scoreLv2 += 1600;
                    break;
                case '3':
                    user.scoreLv3 += 1600;
                    break;
                case '4':
                    user.scoreLv4 += 1600;
                    break;
                case '5':
                    user.scoreLv5 += 1600;
                    break;
                }
                break;
            case 12:
                switch (user.level[2])
                {
                case '1':
                    user.scoreLv1 += 3200;
                    break;
                case '2':
                    user.scoreLv2 += 3200;
                    break;
                case '3':
                    user.scoreLv3 += 3200;
                    break;
                case '4':
                    user.scoreLv4 += 3200;
                    break;
                case '5':
                    user.scoreLv5 += 3200;
                    break;
                }
                break;

            default:
                break;
            }
        }

        if (isFlag(ptpersonnage, map) && system->load != 1)
        {
            ptpersonnage->mouv = 9;
            ptpersonnage->jump = 0;
            ptpersonnage->dvx = 0;

            ptpersonnage->rdvx = 0;

            if (isBlock(ptpersonnage, map, BAS, MOUVEMENT, soundEffect))
            {

                ptpersonnage->mouv = 4;
                ptpersonnage->dvx = 4;
                al_play_sample_instance(soundEffect.stage_clear);
                //    ptpersonnage->mouv = 1;
            }
        }

        /* arret au château */

        if (map[(ptpersonnage->y + ptpersonnage->height - 5) / BLOCK_SIZE_RES][ptpersonnage->x / BLOCK_SIZE_RES] == 183 && ptpersonnage->dvx != 0)
        {

            ptpersonnage->dvx = 0;
            ptpersonnage->mouv = 1;
            ptpersonnage->display++;
        }

        if (ptpersonnage->display == 15)
        {
            system->mode = PLAYER_MENU;
            if (user.lvl_max[2] == user.level[2] && user.lvl_max[2] < '5')
            {
                user.lvl_max[2]++;
            }
            ptpersonnage->display = 0;
            saveStats(&user, user.name);
        }
    }
}

ALLEGRO_COLOR couleurFiltre(int cpt)
{
    if (cpt % 6 == 1 || cpt % 6 == 2)
    {
        float r = 250;
        float g = 1;
        float b = 1;
        float a = 1;
        ALLEGRO_COLOR filtre = al_map_rgba_f(r, g, b, a);
        return (filtre);
    }
    else if (cpt % 6 == 3 || cpt % 6 == 4)
    {
        float r = 1;
        float g = 100;
        float b = 1;
        float a = 1;
        ALLEGRO_COLOR filtre = al_map_rgba_f(r, g, b, a);
        return (filtre);
    }
    else if (cpt % 6 == 5 || cpt % 6 == 0)
    {
        float r = 1;
        float g = 1;
        float b = 250;
        float a = 1;
        ALLEGRO_COLOR filtre = al_map_rgba_f(r, g, b, a);
        return (filtre);
    }
}
