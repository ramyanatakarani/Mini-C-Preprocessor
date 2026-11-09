#include "header.h"
void remove_comments(char *data)
{
    int i, j;
    for (i = 0; data[i]; i++)
    {
        if (data[i] == '/')
        {
            if (data[i + 1] == '/')
            {
                while (data[i] != '\n' && data[i] !='\0')
                    data[i++] = 32;
                continue;
            }

            if (data[i + 1] == '*')
            {
                while (data[i])
                {
                    if (data[i] == '*')
                        if (data[i + 1] == '/')
                        {
                            data[i] = 32;
                            data[i + 1] = 32;
                            break;
                        }

                    if (data[i] == '\n')
                    {
                        i++;
                        continue;
                    }
                    data[i++] = 32;
                }
            }
        }
    }
}
