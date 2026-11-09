#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_comments(char *);
void header_inclusion(FILE *, char *, int);
void user_defined_header(FILE *, char *, int);
void replace_macro(char **, char **, char *, char *, int *);
char *replaceArguments(char *, char *, char *);

typedef struct argument
{
    char formal[100];
    char actual[100];
    struct argument *next;
} arg;

#endif
