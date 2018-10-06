#include <stdio.h>
#include <locale.h>
#include <monetary.h>

int main()
{
    double amount = 12654.376;
    char buf[256];

    setlocale(LC_ALL, "");  // enable environment locale

    strfmon(buf, sizeof buf, "Local: %n, Int'l: %i, Decimal: %!6.2n",
            amount, amount, amount);
    printf("%s\n", buf);
    return 0;
}
