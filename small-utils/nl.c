#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
#include <locale.h>
#include <langinfo.h>

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

#ifdef OUTER_LIMITS

#define ECOUNT(x) (sizeof(x)/sizeof(*(x)))

static const char *_get_measurement_system(int system_id)
{
    static const char * const measurement_systems[] = { "Metric", "English" };
    int idx = system_id - 1;
    return idx < ECOUNT(measurement_systems)
            ? measurement_systems[idx] : "unknown";
}

#endif

int main(void)
{
    char *isym;

    setlocale(LC_ALL, "");

    printf("Numeric\n");
    printf("  Decimal: [%s]\n", nl_langinfo(DECIMAL_POINT));
    printf("  Thousands separator: [%s]\n", nl_langinfo(THOUSANDS_SEP));

    print_grouping("  Grouping", nl_langinfo(GROUPING));

    printf("\nMonetary\n");
    printf("  Decimal point: [%s]\n", nl_langinfo(MON_DECIMAL_POINT));
    printf("  Thousands separator: [%s]\n", nl_langinfo(MON_THOUSANDS_SEP));
    printf("  Grouping");

    print_grouping("  Grouping", nl_langinfo(MON_GROUPING));

    printf("  Positive amount sign: [%s]\n", nl_langinfo(POSITIVE_SIGN));
    printf("  Negative amount sign: [%s]\n", nl_langinfo(NEGATIVE_SIGN));
    printf("  Local:\n");
    printf("    Symbol: [%s]\n", nl_langinfo(CURRENCY_SYMBOL));
    printf("    Fractional digits: %d\n", *nl_langinfo(FRAC_DIGITS));

    print_monetary(*nl_langinfo(P_CS_PRECEDES), *nl_langinfo(P_SEP_BY_SPACE),
            *nl_langinfo(N_CS_PRECEDES), *nl_langinfo(N_SEP_BY_SPACE),
            *nl_langinfo(P_SIGN_POSN), *nl_langinfo(N_SIGN_POSN));

    printf("  International:\n");
    isym = nl_langinfo(INT_CURR_SYMBOL);
    printf("    Symbol (ISO 4217): [%3.3s], separator: [%s]\n",
           isym, strlen(isym) > 3 ? isym + 3 : "");
    printf("    Fractional digits: %d\n", *nl_langinfo(INT_FRAC_DIGITS));

    print_monetary(*nl_langinfo(INT_P_CS_PRECEDES), *nl_langinfo(INT_P_SEP_BY_SPACE),
            *nl_langinfo(INT_N_CS_PRECEDES), *nl_langinfo(INT_N_SEP_BY_SPACE),
            *nl_langinfo(INT_P_SIGN_POSN), *nl_langinfo(INT_N_SIGN_POSN));

    printf("\nTime\n");
    printf("  AM: [%s]\n", nl_langinfo(AM_STR));
    printf("  PM: [%s]\n", nl_langinfo(PM_STR));
    printf("  Date & time format: [%s]\n", nl_langinfo(D_T_FMT));
    printf("  Date format: [%s]\n", nl_langinfo(D_FMT));
    printf("  Time format: [%s]\n", nl_langinfo(T_FMT));
    printf("  Time format (AM/PM): [%s]\n", nl_langinfo(T_FMT_AMPM));
    printf("  Era: [%s]\n", nl_langinfo(ERA));
    printf("  Year (era): [%s]\n", nl_langinfo(ERA_YEAR));
    printf("  Date & time format (era): [%s]\n", nl_langinfo(ERA_D_T_FMT));
    printf("  Date format (era): [%s]\n", nl_langinfo(ERA_D_FMT));
    printf("  Time format (era): [%s]\n", nl_langinfo(ERA_T_FMT));
    printf("  Alt digits: [%s]\n", nl_langinfo(ALT_DIGITS));

    printf("  Days (abbr)");
    for (int i = 0; i < 7; i++)
        printf("%c %s", i == 0 ? ':' : ',', nl_langinfo(ABDAY_1 + i));
    printf("\n");

    printf("  Days (full)");
    for (int i = 0; i < 7; i++)
        printf("%c %s", i == 0 ? ':' : ',', nl_langinfo(DAY_1 + i));
    printf("\n");

    printf("  Months (abbr)");
    for (int i = 0; i < 12; i++)
        printf("%c %s", i == 0 ? ':' : ',', nl_langinfo(ABMON_1 + i));
    printf("\n");

    printf("  Months (full)");
    for (int i = 0; i < 12; i++)
        printf("%c %s", i == 0 ? ':' : ',', nl_langinfo(MON_1 + i));
    printf("\n");

    printf("\nMessages\n");
    printf("  Codeset: %s\n", nl_langinfo(CODESET));

#ifdef OUTER_LIMITS

    printf("\nQueries\n");
    printf("  YES expression: %s\n", nl_langinfo(YESEXPR));
    printf("  NO expression:  %s\n", nl_langinfo(NOEXPR));

    printf("\nPaper\n");
    printf("  Height:  %dmm\n", (int)(intptr_t)nl_langinfo(_NL_PAPER_HEIGHT));
    printf("  Width:   %dmm\n", (int)(intptr_t)nl_langinfo(_NL_PAPER_WIDTH));
    printf("  Codeset: %s\n", nl_langinfo(_NL_PAPER_CODESET));

    printf("\nName\n");
    printf("  Format: %s\n", nl_langinfo(_NL_NAME_NAME_FMT));
    printf("  Gen:    %s\n", nl_langinfo(_NL_NAME_NAME_GEN));
    printf("  Mr:     %s\n", nl_langinfo(_NL_NAME_NAME_MR));
    printf("  Mrs:    %s\n", nl_langinfo(_NL_NAME_NAME_MRS));
    printf("  Miss:   %s\n", nl_langinfo(_NL_NAME_NAME_MISS));
    printf("  Ms:     %s\n", nl_langinfo(_NL_NAME_NAME_MS));

    printf("\nAddress\n");
    printf("  Country name:  %s\n", nl_langinfo(_NL_ADDRESS_COUNTRY_NAME));
    printf("  Country post:  %s\n", nl_langinfo(_NL_ADDRESS_COUNTRY_POST));
    printf("  Country abbr2: %s\n", nl_langinfo(_NL_ADDRESS_COUNTRY_AB2));
    printf("  Country abbr3: %s\n", nl_langinfo(_NL_ADDRESS_COUNTRY_AB3));
    printf("  Country num:   %d\n", (int)(intptr_t)nl_langinfo(_NL_ADDRESS_COUNTRY_NUM));
    printf("  Country ISBN:  %s\n", nl_langinfo(_NL_ADDRESS_COUNTRY_ISBN));
    printf("  Language name: %s\n", nl_langinfo(_NL_ADDRESS_LANG_NAME));
    printf("  Language abbr: %s\n", nl_langinfo(_NL_ADDRESS_LANG_AB));
    printf("  Language term: %s\n", nl_langinfo(_NL_ADDRESS_LANG_TERM));
    printf("  Language lib:  %s\n", nl_langinfo(_NL_ADDRESS_LANG_LIB));
    printf("  Codeset:       %s\n", nl_langinfo(_NL_ADDRESS_CODESET));

    printf("\nTelephone\n");
    printf("  Int'l format:    %s\n", nl_langinfo(_NL_TELEPHONE_TEL_INT_FMT));
    printf("  Domestic format: %s\n", nl_langinfo(_NL_TELEPHONE_TEL_DOM_FMT));
    printf("  Int'l select:    %s\n", nl_langinfo(_NL_TELEPHONE_INT_SELECT));
    printf("  Int'l prefix:    %s\n", nl_langinfo(_NL_TELEPHONE_INT_PREFIX));
    printf("  Codeset:         %s\n", nl_langinfo(_NL_TELEPHONE_CODESET));

    printf("\nMeasurement\n");
    printf("  System:  %s\n", _get_measurement_system((int)*nl_langinfo(_NL_MEASUREMENT_MEASUREMENT)));
    printf("  Codeset: %s\n", nl_langinfo(_NL_MEASUREMENT_CODESET));

    printf("\nIdentification\n");
    printf("  Title:       %s\n", nl_langinfo(_NL_IDENTIFICATION_TITLE));
    printf("  Source:      %s\n", nl_langinfo(_NL_IDENTIFICATION_SOURCE));
    printf("  Address:     %s\n", nl_langinfo(_NL_IDENTIFICATION_ADDRESS));
    printf("  Contact:     %s\n", nl_langinfo(_NL_IDENTIFICATION_CONTACT));
    printf("  Email:       %s\n", nl_langinfo(_NL_IDENTIFICATION_EMAIL));
    printf("  Telephone:   %s\n", nl_langinfo(_NL_IDENTIFICATION_TEL));
    printf("  Language:    %s\n", nl_langinfo(_NL_IDENTIFICATION_LANGUAGE));
    printf("  Territory:   %s\n", nl_langinfo(_NL_IDENTIFICATION_TERRITORY));
    printf("  Audience:    %s\n", nl_langinfo(_NL_IDENTIFICATION_AUDIENCE));
    printf("  Application: %s\n", nl_langinfo(_NL_IDENTIFICATION_APPLICATION));
    printf("  Abbr:        %s\n", nl_langinfo(_NL_IDENTIFICATION_ABBREVIATION));
    printf("  Revision:    %s\n", nl_langinfo(_NL_IDENTIFICATION_REVISION));
    printf("  Date:        %s\n", nl_langinfo(_NL_IDENTIFICATION_DATE));
    printf("  Category:    %s\n", nl_langinfo(_NL_IDENTIFICATION_CATEGORY));
    printf("  Codeset:     %s\n", nl_langinfo(_NL_IDENTIFICATION_CODESET));

#endif // OUTER_LIMITS

    return 0;
}
