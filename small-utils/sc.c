#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define ECOUNT(x) (sizeof(x)/sizeof(*(x)))

int lex_count = 0;
int loc_count = 0;

static int compare_lex(const void *a, const void *b)
{
    lex_count++;
    return strcmp(*(const char **)a, *(const char **)b);
}

static int compare_loc(const void *a, const void *b)
{
    loc_count++;
    return strcoll(*(const char **)a, *(const char **)b);
}

static void print_list(const char * const *list, size_t sz)
{
    for (int i = 0; i < sz; i++)
        printf("%s%s", i ? ", " : "", list[i]);
    printf("\n");
}

int main()
{
    const char *words[] = {"rana", "rastrillo", "radio", "rápido", "ráfaga"};

    setlocale(LC_ALL, "");  // enable environment locale

    printf("Unsorted        : ");
    print_list(words, ECOUNT(words));

    qsort(words, ECOUNT(words), sizeof *words, &compare_lex);

    printf("Lex (strcmp)    : ");
    print_list(words, ECOUNT(words));

    qsort(words, ECOUNT(words), sizeof *words, &compare_loc);

    printf("Locale (strcoll): ");
    print_list(words, ECOUNT(words));

//    printf("Lex comparisons : %d\n", lex_count);
//    printf("Loc comparisons : %d\n", loc_count);

    return 0;
}
