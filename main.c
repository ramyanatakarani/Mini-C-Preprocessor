#include "header.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./preprocessor inputfile.c\n");
        return 1;
    }

    int len = strlen(argv[1]);

    char *output = calloc(len + 3, sizeof(char));
    strcpy(output, argv[1]);

    char *ptr = strrchr(output, '.');

    if (ptr != NULL)
        strcpy(ptr, ".i");
    else
        strcat(output, ".i");

    FILE *src = fopen(argv[1], "r");

    if (src == NULL)
    {
        printf("File not present\n");
        free(output);
        return 1;
    }

    int size = 0, i = 0;
    char ch;

    while (fgetc(src) != EOF)
        size++;

    rewind(src);

    char *data = calloc(size + 1, sizeof(char));

    while ((ch = fgetc(src)) != EOF)
        data[i++] = ch;

    data[i] = '\0';
    fclose(src);

    remove_comments(data);

    FILE *ft = fopen("temp_file", "w");

    if (ft == NULL)
    {
        printf("Temporary file not created\n");
        free(data);
        free(output);
        return 1;
    }

    fputs(data, ft);
    fclose(ft);

    FILE *dest = fopen(output, "w");

    if (dest == NULL)
    {
        printf("Output file not created\n");
        free(data);
        free(output);
        return 1;
    }

    header_inclusion(dest, "temp_file", size);

    FILE *fm = fopen("temp_file", "r");

    if (fm == NULL)
    {
        printf("Temporary file not present\n");
        fclose(dest);
        free(data);
        free(output);
        return 1;
    }

    int longline = 100;

    char *line = calloc(longline + 1, sizeof(char));
    char *s = calloc(size + 1, sizeof(char));
    char *name = calloc(longline, sizeof(char));
    char *body = calloc(longline, sizeof(char));

    int j, k, m, f, flag = 0;

    while (fgets(line, longline + 1, fm))
    {
        if (strstr(line, "#define"))
        {
            if (strstr(data, line))
            {
                for (i = 0, j = 0, k = 0,
                     m = 0, f = 0, flag = 0;
                     line[i]; i++)
                {
                    if (f == 0)
                    {
                        if (line[i] == ' ')
                            m = 1;

                        if (m == 1)
                            if (isalpha(line[i]) ||
                                line[i] == '_' ||
                                isdigit(line[i]))
                                f = 1;
                    }

                    if (f == 1)
                    {
                        if (line[i] == '(')
                            flag = 1;

                        if (flag == 0 && line[i] == ' ')
                        {
                            f = 2;
                            continue;
                        }

                        if (flag == 1 && line[i] == ')')
                            flag = 0;

                        name[j++] = line[i];
                    }

                    if (f == 2)
                    {
                        if (line[i] == '\n')
                            continue;

                        body[k++] = line[i];
                    }
                }

                name[j] = '\0';
                body[k] = '\0';

                replace_macro(&data, &s, name, body, &size);

                memset(name, 0, longline);
                memset(body, 0, longline);
            }
        }
    }

    len = strlen(data);

    char st[] = "main(";

    for (i = 0, f = 0; data[i]; i++)
    {
        for (j = 0, k = i; st[j]; j++, k++)
            if (st[j] != data[k])
                break;

        if (st[j] == '\0')
        {
            f = 1;

            while (i > 0 && data[i - 1] != '\n')
                i--;

            break;
        }
    }

    if (f == 0)
        i = 0;

    while (data[i])
        fputc(data[i++], dest);

    printf("File preprocessed successfully\n");

    free(data);
    free(s);
    free(name);
    free(body);
    free(line);
    free(output);

    remove("temp_file");

    fclose(dest);
    fclose(fm);

    return 0;
}
