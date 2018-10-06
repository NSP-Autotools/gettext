#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

static void print_grouping(const char *prefix, const char *grouping)
{
    const char *cg;
    printf("%s", prefix);
    for (cg = grouping; *cg && *cg != CHAR_MAX; cg++)
        printf("%c %d", cg == grouping ? ':' : ',', *cg);
    printf("%s\n", *cg == 0 ? " (repeated)" : "");
}

static void print_monetary(bool p_cs_precedes, bool p_sep_by_space,
        bool n_cs_precedes, bool n_sep_by_space,
        int p_sign_posn, int n_sign_posn)
{
    static const char * const sp_str[] =
    {
        "surround symbol and quantity with parentheses", 
        "before quantity and symbol",
        "after quantity and symbol",
        "right before symbol",
        "right after symbol"
    };

    printf("    Symbol comes %s a positive (or zero) amount\n",
            p_cs_precedes ? "BEFORE" : "AFTER");
    printf("    Symbol %s separated from a positive (or zero) amount by a space\n",
            p_sep_by_space ? "IS" : "is NOT");
    printf("    Symbol comes %s a negative amount\n",
            n_cs_precedes ? "BEFORE" : "AFTER");
    printf("    Symbol %s separated from a negative amount by a space\n",
            n_sep_by_space ? "IS" : "is NOT");
    printf("    Positive (or zero) amount sign position: %s\n",
            sp_str[p_sign_posn == CHAR_MAX? 4: p_sign_posn]);
    printf("    Negative amount sign position: %s\n",
            sp_str[n_sign_posn == CHAR_MAX? 4: n_sign_posn]);
}

int main(void)
{
    struct lconv *lc;
    char *isym;

    setlocale(LC_ALL, "");  // enable environment locale
    lc = localeconv();      // obtain locale attributes

    printf("Numeric:\n");
    printf("  Decimal point: [%s]\n", lc->decimal_point);
    printf("  Thousands separator: [%s]\n", lc->thousands_sep);

    print_grouping("  Grouping", lc->grouping);

    printf("\nMonetary:\n");
    printf("  Decimal point: [%s]\n", lc->mon_decimal_point);
    printf("  Thousands separator: [%s]\n", lc->mon_thousands_sep);

    print_grouping("  Grouping", lc->mon_grouping);

    printf("  Positive amount sign: [%s]\n", lc->positive_sign);
    printf("  Negative amount sign: [%s]\n", lc->negative_sign);
    printf("  Local:\n");
    printf("    Symbol: [%s]\n", lc->currency_symbol);
    printf("    Fractional digits: %d\n", (int)lc->frac_digits);

    print_monetary(lc->p_cs_precedes, lc->p_sep_by_space,
            lc->n_cs_precedes, lc->n_sep_by_space,
            lc->p_sign_posn, lc->n_sign_posn);

    printf("  International:\n");
    isym = lc->int_curr_symbol;
    printf("    Symbol (ISO 4217): [%3.3s], separator: [%s]\n",
            isym, strlen(isym) > 3 ? isym + 3 : "");
    printf("    Fractional digits: %d\n", (int)lc->int_frac_digits);

#ifdef __USE_ISOC99
    print_monetary(lc->int_p_cs_precedes, lc->int_p_sep_by_space,
            lc->int_n_cs_precedes, lc->int_n_sep_by_space,
            lc->int_p_sign_posn, lc->int_n_sign_posn);
#endif

    return 0;
}
