#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record
{
    long long id;
    char name[32];
    char m_mod1;
    int m_mod2;
    char type[3];
    float value;
    int time;
    int date;
    struct record *next;
} RECORD;

void n_command(RECORD **first, int *n, int *record_count)
{
    if (*n)
    {
        RECORD *akt = *first;
        while (*first != NULL)
        {
            akt = *first;
            *first = (*first)->next;
            free(akt);
        }
    }
    *n = 1;

    FILE *fr;
    if ((fr = fopen("C:\\Users\\frede\\Desktop\\STU - FIIT\\Proceduralne programovanie\\Visual Studio Code\\Projekt 2\\test_dataloger.txt", "r")) == NULL)
    {
        printf("Zaznamy  neboli  nacitane!\n");
    }
    else
    {
        *record_count = 0;
        char sep[4];
        if (fgets(sep, 4, fr) != NULL)
        {
            RECORD *init = (RECORD *)malloc(sizeof(RECORD));
            RECORD *prev = init;
            fscanf(fr, "%lld\n", &(*init).id);
            fgets(init->name, 32, fr);
            init->name[strlen(init->name) - 1] = '\0';
            fscanf(fr, "%c%d", &(*init).m_mod1, &(*init).m_mod2);
            fscanf(fr, "%s", &(*init).type);
            fscanf(fr, "%f", &(*init).value);
            fscanf(fr, "%d", &(*init).time);
            fscanf(fr, "%d", &(*init).date);
            *first = init;
            init->next = NULL;
            (*record_count)++;

            while (fgets(sep, 4, fr) != NULL)
            {
                RECORD *new = (RECORD *)malloc(sizeof(RECORD));
                prev->next = new;

                fgets(sep, 4, fr);
                fscanf(fr, "%lld\n", &(*new).id);
                fgets(new->name, 32, fr);
                new->name[strlen(new->name) - 1] = '\0';
                fscanf(fr, "%c%d", &(*new).m_mod1, &(*new).m_mod2);
                fscanf(fr, "%s", &(*new).type);
                fscanf(fr, "%f", &(*new).value);
                fscanf(fr, "%d", &(*new).time);
                fscanf(fr, "%d", &(*new).date);
                new->next = NULL;
                prev = new;
                (*record_count)++;
            }
        }
        printf("Nacitalo sa %d zaznamov\n", *record_count);
    }
}

void print_data(long long id, char name[], char m_mod1, int m_mod2, char type[], double value, int time, int date)
{
    printf("ID cislo mer. osoby: %lld\n", id);
    printf("Meno osoby: %s\n", name);
    printf("Mer. modul: %c%d\n", m_mod1, m_mod2);
    printf("Typ  mer.  veliciny: %s\n", type);
    printf("Hodnota: %f\n", value);
    printf("Cas merania: %04d\n", time);
    printf("Datum: %d\n", date);
}

void v_command(RECORD *akt)
{
    int i = 1;
    while (akt != NULL)
    {
        printf("%d.\n", i);
        print_data(akt->id, akt->name, akt->m_mod1, akt->m_mod2, akt->type, akt->value, akt->time, akt->date);
        akt = akt->next;
        i++;
    }
}

void z_command(RECORD **first, int *record_count)
{
    long long id;
    scanf("%lld", &id);
    getchar();

    RECORD *akt = *first;
    RECORD *prev = NULL;
    RECORD *help = NULL;

    while (akt != NULL)
    {
        if (akt->id == id)
        {
            if (*first == akt)
            {
                printf("Zaznam pre ID: %lld pre modul %c%d bol vymazany.\n", akt->id, akt->m_mod1, akt->m_mod2);
                (*record_count)--;
                help = akt->next;
                *first = akt->next;
                free(akt);
                akt = help;
            }
            else
            {
                printf("Zaznam pre ID: %lld pre modul %c%d bol vymazany.\n", akt->id, akt->m_mod1, akt->m_mod2);
                (*record_count)--;
                help = akt->next;
                prev->next = akt->next;
                free(akt);
                akt = help;
            }
        }
        else
        {
            prev = akt;
            akt = akt->next;
        }
    }
}

int check_sort(RECORD *first)
{
    RECORD *akt = first;
    while (akt != NULL)
    {
        if (akt->next != NULL && akt->date > akt->next->date)
        {
            return 0;
        }
        akt = akt->next;
    }

    return 1;
}

void u_command(RECORD **first, int *record_count)
{
    for (int i = 0; i < *record_count; i++)
    {
        RECORD *akt = *first;
        RECORD *prev = NULL;
        RECORD *help = NULL;
        while (akt != NULL)
        {
            while (akt->next != NULL && (akt->date > akt->next->date || (akt->date == akt->next->date && akt->time > akt->next->time)))
            {
                if (akt == *first)
                {
                    help = akt->next;
                    prev = help;
                    akt->next = akt->next->next;
                    help->next = akt;
                    *first = help;
                }
                else
                {
                    help = akt->next;
                    akt->next = akt->next->next;
                    help->next = akt;
                    prev->next = help;
                    prev = help;
                }
            }

            prev = akt;
            akt = akt->next;
        }
    }
    if (check_sort(*first))
    {
        printf("Spajany  zoznam  bol  usporiadany.\n");
    }
    else
    {
        printf("Chyba\n");
    }
}

void p_command(RECORD **first, int *record_count)
{
    RECORD *akt = *first;
    RECORD *new = (RECORD *)malloc(sizeof(RECORD));

    int pos;
    scanf("%d", &pos);

    scanf("%lld\n", &(*new).id);
    gets(new->name);
    scanf("%c%d", &(*new).m_mod1, &(*new).m_mod2);
    scanf("%s", &(*new).type);
    scanf("%f", &(*new).value);
    scanf("%d", &(*new).time);
    scanf("%d", &(*new).date);
    getchar();

    if (*record_count == 0)
    {
        pos = 1;
    }

    if (pos == 1)
    {
        new->next = *first;
        *first = new;
        (*record_count)++;
    }
    else
    {
        int i = 2;
        while (akt->next != NULL && i < pos)
        {
            akt = akt->next;
            i++;
        }
        new->next = akt->next;
        akt->next = new;
        (*record_count)++;
    }
}

void h_command(RECORD *akt)
{
    char m_mod1;
    int m_mod2;

    scanf("%c%d", &m_mod1, &m_mod2);
    getchar();

    int i = 0;
    while (akt != NULL)
    {
        if (akt->m_mod1 == m_mod1 && akt->m_mod2 == m_mod2)
        {
            i++;
            printf("%d.\n", i);
            print_data(akt->id, akt->name, akt->m_mod1, akt->m_mod2, akt->type, akt->value, akt->time, akt->date);
        }
        akt = akt->next;
    }

    if (!i)
    {
        printf("Pre  meraci  modul  %c%d  niesu  zaznamy.\n", m_mod1, m_mod2);
    }
}

void r_command(RECORD **first, int record_count)
{
    int pos1, pos2;
    scanf("%d %d", &pos1, &pos2);
    getchar();

    if (pos1 <= record_count && pos2 <= record_count)
    {
        if (pos1 < pos2)
        {
            int h = pos1;
            pos1 = pos2;
            pos2 = h;
        }

        RECORD *akt1 = *first;
        RECORD *akt2 = *first;
        RECORD *prev1 = NULL;
        RECORD *prev2 = NULL;
        RECORD *help = NULL;

        if (pos2 == 1)
        {
            int i = 1;
            while (akt1 != NULL && i < pos1)
            {
                prev1 = akt1;
                akt1 = akt1->next;
                i++;
            }

            help = akt1->next;
            prev1->next = akt2;
            akt1->next = akt2->next;
            *first = akt1;
            akt2->next = help;
        }
        else
        {
            int i = 1;
            while (akt1 != NULL && i < pos1)
            {
                prev1 = akt1;
                akt1 = akt1->next;
                i++;
            }

            i = 1;
            while (akt2 != NULL && i < pos2)
            {
                prev2 = akt2;
                akt2 = akt2->next;
                i++;
            }

            help = akt1->next;
            prev1->next = akt2;
            akt1->next = akt2->next;
            prev2->next = akt1;
            akt2->next = help;
        }
    }
}

int main()
{
    char command;
    int v = 0, n = 0, record_count = 0;
    RECORD *first = NULL;

    while (command != 'k')
    {
        printf("-> ");
        command = getchar();
        getchar();
        switch (command)
        {
        case 'n':
            n_command(&first, &n, &record_count);
            break;
        case 'v':
            v_command(first);
            break;
        case 'z':
            z_command(&first, &record_count);
            break;
        case 'p':
            p_command(&first, &record_count);
            break;
        case 'u':
            u_command(&first, &record_count);
            break;
        case 'h':
            h_command(first);
            break;
        case 'r':
            r_command(&first, record_count);
            break;
        case 'k':
            if (n)
            {
                record_count = 0;
                RECORD *akt = first;
                while (first != NULL)
                {
                    akt = first;
                    first = (first)->next;
                    free(akt);
                }
            }
            break;
        default:
            break;
        }
    }

    return 0;
}