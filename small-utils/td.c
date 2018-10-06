#include <stdio.h>
#include <locale.h>
#include <time.h>

int main(void)
{
    time_t t = time(0);
    char buf[128];

    setlocale(LC_ALL, "");  // enable environmental locale

    strftime(buf, sizeof buf, "%c", gmtime(&t));
    printf("Calendar time: %s\n", buf);
    return 0;
}
