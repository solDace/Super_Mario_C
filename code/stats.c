#include "stats.h"

void initStats(playerStats *user, char *name)
{
    user->scoreLv1 = 0;
    user->scoreLv2 = 0;
    user->scoreLv3 = 0;
    user->scoreLv4 = 0;
    user->scoreLv5 = 0;
    user->nb_coins = 0;
    user->try_remaining = 3;
    char *niv = "1-1";
    tpsNiveau = 400;
    user->stopwatch = 0;
    strcpy(user->level, niv);
    strcpy(user->lvl_max, niv);
    strcpy(user->name, name);
    user->son = 1;
}

void resetStats(playerStats *user)
{

    switch (user->level[2])
    {
    case '1':
        user->scoreLv1 = 0;
        break;
    case '2':
        user->scoreLv2 = 0;
        break;
    case '3':
        user->scoreLv3 = 0;
        break;
    case '4':
        user->scoreLv4 = 0;
        break;
    case '5':
        user->scoreLv5 = 0;
        break;
    }
    user->nb_coins = 0;
    user->stopwatch = 0;
}

/*void modifyStats(playerStats *user, char *event)
{
    switch (event[0])
    {
    case 'e':
        user->score += 20;
        break;
    case 'c':
        user->nb_coins++;
        user->score += 10;
        //ajouter ici les fonctions pour les pieces (tester +100,...)
        break;
    case 'p':
        user->score += 50;
        break;
    case 'd':
        user->score -= (user->score - 200 < 0) ? user->score : 200;
        user->try_remaining -= (user->try_remaining - 1 < 0) ? 0 : 1;
    default:
        break;
    }
}*/

void saveStats(playerStats *user, char *fileName)
{
    int lv1 = 0, lv2 = 0, lv3 = 0, lv4 = 0, lv5 = 0;
    FILE *fic;
    char fileNamev2[LENGTH_NAME];
    strcpy(fileNamev2, fileName);
    char File[LENGTH_NAME];
    strcpy(File, "./AlgoS4/resources/Save/");
    strcat(fileNamev2, ".txt");
    strcat(File, fileNamev2);

    fic = fopen(File, "r");
    if (fic != NULL)
    {
        fscanf(fic, "Lv1 = %d\n", &lv1);
        fscanf(fic, "Lv2 = %d\n", &lv2);
        fscanf(fic, "Lv3 = %d\n", &lv3);
        fscanf(fic, "Lv4 = %d\n", &lv4);
        fscanf(fic, "Lv5 = %d\n", &lv5);
    }

    fclose(fic);

    fic = fopen(File, "w+");
    if (fic != NULL)
    {
        if (user->scoreLv1 > lv1)
            fprintf(fic, "Lv1 = %d\n", user->scoreLv1);
        else
            fprintf(fic, "Lv1 = %d\n", lv1);

        if (user->scoreLv2 > lv2)
            fprintf(fic, "Lv2 = %d\n", user->scoreLv2);
        else
            fprintf(fic, "Lv2 = %d\n", lv2);

        if (user->scoreLv3 > lv3)
            fprintf(fic, "Lv3 = %d\n", user->scoreLv3);
        else
            fprintf(fic, "Lv3 = %d\n", lv3);

        if (user->scoreLv4 > lv4)
            fprintf(fic, "Lv4 = %d\n", user->scoreLv4);
        else
            fprintf(fic, "Lv4 = %d\n", lv4);

        if (user->scoreLv5 > lv5)
            fprintf(fic, "Lv5 = %d\n", user->scoreLv5);
        else
            fprintf(fic, "Lv5 = %d\n", lv5);

        fprintf(fic, "Name = %s\n", user->name);
        fprintf(fic, "nb_coins = %d\n", user->nb_coins);
        fprintf(fic, "try_remaining = %d\n", user->try_remaining);
        fprintf(fic, "level = %s\n", user->lvl_max);
        saveHS(user);
    }
    else
    {
        printf("Erreur ouverture fichier. \n");
    }
    fclose(fic);
}

bool saveHS(playerStats *user)
{
    FILE *fichier;
    int a = 0, b = 0, c = 0, d = 0, scoreTot = user->scoreLv1 + user->scoreLv2 + user->scoreLv3 + user->scoreLv4 + user->scoreLv5;
    char name1[LENGTH_NAME], name2[LENGTH_NAME], name3[LENGTH_NAME], name4[LENGTH_NAME];
    memset(name1, 0, LENGTH_NAME);
    memset(name2, 0, LENGTH_NAME);
    memset(name3, 0, LENGTH_NAME);
    memset(name4, 0, LENGTH_NAME);

    fichier = fopen("./AlgoS4/resources/Save/HS.txt", "r+");
    if (fichier != NULL)
    {
        fscanf(fichier, "1 = %s | %d\n", name1, &a);
        fscanf(fichier, "2 = %s | %d\n", name2, &b);
        fscanf(fichier, "3 = %s | %d\n", name3, &c);
        fscanf(fichier, "4 = %s | %d\n", name4, &d);
        if (scoreTot >= a)
        {

            if (strcmp(user->name, name1) != 0 && strcmp(user->name, name2) != 0 && strcmp(user->name, name3) != 0)
            {
                d = c;
                c = b;
                b = a;
                strcpy(name4, name3);
                strcpy(name3, name2);
                strcpy(name2, name1);
                strcpy(name1, user->name);
            }

            else if (strcmp(user->name, name3) == 0)
            {
                c = b;
                b = a;
                strcpy(name3, name2);
                strcpy(name2, name1);
                strcpy(name1, user->name);
            }

            else if (strcmp(user->name, name2) == 0)
            {
                b = a;
                strcpy(name2, name1);
                strcpy(name1, user->name);
            }

            a = scoreTot;
        }
        else if (scoreTot >= b)
        {
            if (strcmp(user->name, name1) == 0)
            {
                return false;
            }
            else if (strcmp(name3, user->name) == 0)
            {
                c = b;
                strcpy(name3, name2);
                strcpy(name2, user->name);
            }
            else if (strcmp(name2, user->name) != 0)
            {
                d = c;
                c = b;
                strcpy(name4, name3);
                strcpy(name3, name2);
                strcpy(name2, user->name);
            }
            b = scoreTot;
        }
        else if (scoreTot >= c)
        {
            if (strcmp(name1, user->name) == 0 || strcmp(name2, user->name) == 0)
                return false;
            else
            {
                d = c;
                c = scoreTot;
                strcpy(name4, name3);
                strcpy(name3, user->name);
            }
        }
        else if (scoreTot >= d)
        {
            if (strcmp(name1, user->name) == 0 || strcmp(name2, user->name) == 0 || strcmp(name3, user->name) == 0)
                return false;
            else
            {
                d = scoreTot;
                strcpy(name4, user->name);
                return false;
            }
        }
        else
        {
            return false;
            fclose(fichier);
        }

        fseek(fichier, 0, SEEK_SET);
        fprintf(fichier, "1 = %s | %d\n", name1, a);
        fprintf(fichier, "2 = %s | %d\n", name2, b);
        fprintf(fichier, "3 = %s | %d\n", name3, c);
        fprintf(fichier, "4 = %s | %d\n", name4, d);
    }
    else
    {
        printf("Erreur ouverture fichier. \n");
        return false;
    }
    fclose(fichier);
    return true;
}

void loadSave(playerStats *user, char *fileName)
{
    FILE *fic;
    char fileNamev2[LENGTH_NAME];
    strcpy(fileNamev2, fileName);
    char File[LENGTH_NAME];
    strcpy(File, "./AlgoS4/resources/Save/");
    strcat(fileNamev2, ".txt");
    strcat(File, fileNamev2);

    fic = fopen(File, "r");
    if (fic != NULL)
    {
        fscanf(fic, "Lv1 = %d\n", &user->scoreLv1);
        fscanf(fic, "Lv2 = %d\n", &user->scoreLv2);
        fscanf(fic, "Lv3 = %d\n", &user->scoreLv3);
        fscanf(fic, "Lv4 = %d\n", &user->scoreLv4);
        fscanf(fic, "Lv5 = %d\n", &user->scoreLv5);
        fscanf(fic, "Name = %s\n", user->name);
        fscanf(fic, "nb_coins = %d\n", &user->nb_coins);
        fscanf(fic, "try_remaining = %d\n", &user->try_remaining);
        fscanf(fic, "level = %s\n", user->lvl_max);
    }
    else
    {
        // printf("Erreur ouverture fichier. \n");
        initStats(user, fileName);
    }
    user->son = 1;
    fclose(fic);
}

void loadHS(int HS[3], char nameHS1[LENGTH_NAME], char nameHS2[LENGTH_NAME], char nameHS3[LENGTH_NAME])
{
    FILE *fic;
    fic = fopen("./AlgoS4/resources/Save/HS.txt", "r");
    if (fic != NULL)
    {
        fscanf(fic, "1 = %s | %d\n", nameHS1, &HS[0]);
        fscanf(fic, "2 = %s | %d\n", nameHS2, &HS[1]);
        fscanf(fic, "3 = %s | %d\n", nameHS3, &HS[2]);
    }
    else
    {
        printf("Erreur ouverture fichier. \n");
    }
    fclose(fic);
}

void DisplayHS(int x, int y, int method, ALLEGRO_FONT *font)
{

    int HS[3];
    // char nameHS[LENGTH_NAME];
    char nameHS1[LENGTH_NAME], nameHS2[LENGTH_NAME], nameHS3[LENGTH_NAME];
    loadHS(HS, nameHS1, nameHS2, nameHS3);
    switch (method)
    {
    case 1:
        al_draw_textf(font, al_map_rgb(255, 255, 255), x, y, 0, "%s : %d", nameHS1, HS[0]);
        break;

    case 2:
        al_draw_textf(font, al_map_rgb(255, 255, 255), x, y, 0, " %s - %d", nameHS1, HS[0]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), x + 8, y + 47, 0, " %s - %d", nameHS2, HS[1]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), x + 8, y + 94, 0, " %s - %d", nameHS3, HS[2]);

        break;
    }
}
