#include "header.h"

void header_inclusion(FILE *dest, char *temp_file, int size)
{
    char *s = malloc(size + 1);
    char path[256] = "/usr/include/";
    char r[256];
    int i, j, k, len;
    char ch, flag;
    FILE *ft = fopen(temp_file, "r");

    if (ft == NULL)
    {
        printf("Temporary file not present\n");
        free(s);
        return;
    }

    len = strlen(path);

    while (fgets(s, size + 1, ft))
    {
        if (strstr(s, "main"))
            break;

        if (!strstr(s, "#include"))
            goto l;

        for (i = 0, j = 0, k = len, flag = 0; s[i]; i++)
        {
            if (flag == 1 && s[i] == '>')
                break;

            if (flag == 1)
                path[k++] = s[i];

            if (flag == 2 && s[i] == '"')
                break;

            if (flag == 2)
                r[j++] = s[i];

            if (s[i] == '<')
                flag = 1;

            if (s[i] == '"')
                flag = 2;
        }

        if (flag == 1)
        {
            path[k] = '\\0';

            FILE *fp = fopen(path, "r");

            if (fp == NULL)
            {
                printf("%s Header file not present\n", path);
                continue;
            }

            while ((ch = fgetc(fp)) != EOF)
                fputc(ch, dest);

            fclose(fp);
            continue;
        }

        if (flag == 2)
        {
            r[j] = '\\0';
            user_defined_header(dest, r, size);
            continue;
        }

    l:
        if (strstr(s, "#define"))
            continue;

        for (i = 0; s[i]; i++)
            fputc(s[i], dest);
    }

    fclose(ft);
    free(s);
}


void user_defined_header(FILE *dest, char *temp_file, int size)
{
    char *s = malloc(size + 1);
    int i;
    FILE *ft = fopen(temp_file, "r");

    if (ft == NULL)
    {
        printf("Header file not present: %s\\n", temp_file);
        free(s);
        return;
    }

    while (fgets(s, size + 1, ft))
    {
        if (strstr(s, "#include"))
            continue;

        if (strstr(s, "#define"))
            continue;

        for (i = 0; s[i]; i++)
            fputc(s[i], dest);
    }

    fclose(ft);
    free(s);
}
