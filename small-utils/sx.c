#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define ECOUNT(x) (sizeof(x)/sizeof(*(x)))

typedef struct element
{
    const char *input;
    const char *xfrmd;
} element;

static int compare(const void *a, const void *b)
{
    const element *e1 = a;
    const element *e2 = b;
    return strcmp(e1->xfrmd, e2->xfrmd);
}

static void print_list(const element *list, size_t sz)
{
    for (int i = 0; i < sz; i++)
        printf("%s, ", list[i].input);
    printf("\n");
}

int main()
{
    element words[] =
    {
        {"rana"}, {"rastrillo"}, {"radio"}, {"rápido"}, {"ráfaga"}
    };

    setlocale(LC_ALL, "");  // enable environment locale

    // point each xfrmd field at corresponding input field
    for (int i = 0; i < ECOUNT(words); i++)
        words[i].xfrmd = words[i].input;

    printf("Unsorted            : ");
    print_list(words, ECOUNT(words));

    qsort(words, ECOUNT(words), sizeof *words, &compare);

    printf("Lex (strcmp)        : ");
    print_list(words, ECOUNT(words));

    for (int i = 0; i < ECOUNT(words); i++)
    {
        char buf[128];
        strxfrm(buf, words[i].input, sizeof buf);
        words[i].xfrmd = strdup(buf);
    }

    qsort(words, ECOUNT(words), sizeof *words, &compare);

    printf("Locale (strxfrm/cmp): ");
    print_list(words, ECOUNT(words));

    return 0;
}
