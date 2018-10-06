#include "config.h"

#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#ifndef LOCALE_DIR
# define LOCALE_DIR "/usr/local/share/locale"
#endif

#define _(x) gettext(x)

int main()
{
    const char *localedir = LOCALE_DIR;

    setlocale(LC_ALL, "");
    bindtextdomain("gt", localedir);
    textdomain("gt");

    printf(_("Hello, world!\n"));

    return 0;
}
