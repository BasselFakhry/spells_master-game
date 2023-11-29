
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int is_used(char *spell, char **used_spells, int num_used_spells)// Checks if the spell is already used
{
    for (int i = 0; i < num_used_spells; i++)
    {
        if (strcmp(spell, used_spells[i]) == 0)
            return 1;
    }
    return 0;
}

int negamax(char *previous_spell, char ***map, int color, int depth, int *frequency, int alpha, int beta)// returns a score for a spell
{
    if (depth == 6)
        return 0;
    char last = previous_spell[strlen(previous_spell) - 1];
    char **possible = map[last - 'a'];

    if (possible == NULL || possible[0] == NULL)
    {
        if (color == 1)
            return color * (4 - depth);
        else
            return color * (depth + 1);
    }

    int best = INT_MIN;
    for (int i = 0; i < frequency[last - 'a']; i++)
    {

        if (possible[i] != NULL)
        {
            char *choosed = possible[i];
            possible[i] = NULL;
            int score = -negamax(choosed, map, -color, depth + 1, frequency, -beta, -alpha);
            possible[i] = choosed;
            if (score > best)
                best = score;
            if (best >= beta)
                return best;
            if (best > alpha)
                alpha = best;
        }
    }
    // printf("%s : %d\n", previous_spell, best);
    return best;
}

int best(char **spells, char *previous_spell, int size, char **used_spells, int num_used_spells)//returns the index of the best spell 
{

    int result = -1;
    int frequency[26] = {0};
    char ***map = (char ***)malloc(sizeof(char **) * 26);
    for (int i = 0; i < 26; i++)
    {
        map[i] = NULL;
    }
    for (int i = 0; i < size; i++)
    {
        if (!is_used(spells[i], used_spells, num_used_spells))
        {
            int loc = spells[i][0] - 'a';
            frequency[loc]++;
            map[loc] = (char **)realloc(map[loc], frequency[loc] * sizeof(char *));
            map[loc][frequency[loc] - 1] = (char *)malloc(strlen(spells[i]) + 1);
            strcpy(map[loc][frequency[loc] - 1], spells[i]);
        }
    }
    char **p = (char **)malloc(sizeof(char *) * 26);
    int c = 0;
    if (strcmp(previous_spell, "") == 0)
    {
        int f[26] = {0};
        for (int i = 0; i < size; i++)
        {
            if (f[spells[i][strlen(spells[i]) - 1] - 'a'] == 0)
            {
                f[spells[i][strlen(spells[i]) - 1] - 'a']++;
                p[c] = spells[i];
                c++;
            }
            if (c == 26)
                break;
        }
        for (int i = 0; i < c; i++)
        {
            printf("  ,%s", p[i]);
        }
        printf("\n");
    }
    char last = previous_spell[strlen(previous_spell) - 1];
    int range = frequency[last - 'a'];
    char **possible = map[last - 'a'];
    if (strcmp(previous_spell, "") == 0)
    {
        possible = p;
        range = c;
    }
    char *bestSpell = NULL;
    int high_score = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (int i = 0; possible != NULL && possible[i] != NULL && i < range; i++)
    {
        char *current = possible[i];
        possible[i] = NULL;
        int score = negamax(current, map, 1, 0, frequency, alpha, beta);
        printf("%s: %d\n", current, scanf_s);
        possible[i] = current;
        if (score > high_score)
        {
            high_score = score;
            bestSpell = current;
        }
        if (score > alpha)
            alpha = score;
        if (alpha >= beta)
            break;
    }

    if (bestSpell != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (strcmp(spells[i], bestSpell) == 0)
            {
                result = i;
                break;
            }
        }
    }
    for (int i = 0; i < 26; i++)// freeing the memory
    {
        if (map[i] != NULL)
        {
            for (int j = 0; j < frequency[i]; j++)
            {
                free(map[i][j]);
            }
            free(map[i]);
        }
    }
    free(map);
    free(p);
    return result;
}

int main()
{
    char *spells[] = {"abracadabra",
                      "alakazam",
                      "bibbidi-bobbidi-boo",
                      "expelliarmus",
                      "wingardiumleviosa",
                      "alohomora",
                      "expectopatronum",
                      "avadakedavra",
                      "lumos",
                      "nox",
                      "accio",
                      "obliviate",
                      "aparecium",
                      "reparo",
                      "avis",
                      "aguamenti",
                      "araniaexumai",
                      "aquaeructo",
                      "aqualimpia",
                      "ascendio",
                      "bombarda",
                      "colloportus",
                      "confringo",
                      "defodio",
                      "deletrius",
                      "densaugeo",
                      "diffindo",
                      "engorgio",
                      "episkey",
                      "evanesco",
                      "expectopatronum",
                      "expulso",
                      "ferula",
                      "flagrate",
                      "flipendo",
                      "furnunculus",
                      "geminio",
                      "glacius",
                      "impedimenta",
                      "impervius",
                      "incarcerous",
                      "incendio",
                      "langlock",
                      "legilimens",
                      "levicorpus",
                      "liberacorpus",
                      "locomotor",
                      "lumosmaxima",
                      "metelojinx recanto",
                      "mobiliarbus",
                      "mobilicorpus",
                      "morsmordre",
                      "muffliato",
                      "nox",
                      "obliviate",
                      "obscuro",
                      "oppugno",
                      "periculum",
                      "petrificus totalus",
                      "pointme",
                      "portus",
                      "priorincantato",
                      "protego",
                      "quietus",
                      "reducio",
                      "reducto",
                      "rennervate",
                      "reparo",
                      "rictusempra",
                      "riddikulus",
                      "salviohexia",
                      "scourgify",
                      "sectumsempra",
                      "serpensortia",
                      "silencio",
                      "sonorus",
                      "stupefy",
                      "tarantallegra",
                      "tergeo",
                      "unbreakable vow",
                      "vermillious",
                      "viperaevanesca",
                      "vulnerasanentur",
                      "waddiwasi",
                      "wingardiumleviosa"};
    char *used_spells[] = {"defodio", "obliviate", "reducio",
                           "reducto",
                           "rennervate",
                           "reparo", "riddikulus"};
    clock_t start, end;

    int x = -1;
    start = clock();
    x = best(spells, "", 80, used_spells, 7);
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    if (x != -1)
    {
        printf("best spell: %s\n", spells[x]);
    }
    else
    {
        printf("No valid spell found.\n");
    }
    printf("%f", time);
    return 0;
}
