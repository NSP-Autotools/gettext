#include <stdio.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>

int main()
{
    const wchar_t *orig = L"BAÑO";
    wchar_t xfrm[64];

    setlocale(LC_ALL, "");  // enable environment locale

    int i = 0;
    while (i < wcslen(orig))
    {
        xfrm[i] = towlower(orig[i]);
        i++;
    }
    xfrm[i] = 0;
    printf("orig: %ls, xfrm: %ls\n", orig, xfrm);

    return 0;
}
