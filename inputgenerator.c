#include <stdio.h>
#include <stdlib.h>
#include "inputgenerator.h"
#include <time.h>
char *random_string(size_t length)
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!(){}`><-+@$%^&*~/:;\\";
    char *randomString = NULL;

    if (length)
    {
        randomString = malloc(length + 1);
        if (randomString)
        {
            for (size_t i = 0; i < length; i++)
            {
                int key = rand() % (sizeof(charset) - 1);
                randomString[i] = charset[key];
            }
            randomString[length] = '\0';
        }
    }

    return randomString;
}
char *similar_string_generator(char *source)
{
    size_t length = strlen(source);
    char *similarString = malloc(length + 1);
    if (!similarString)
    {
        return NULL;
    }
    strcpy(similarString, source);
    int num_errors = (rand() % length) + 1;
    for (int i = 0; i < num_errors; i++)
    {
        int error_type = rand() % 3;
        int pos = rand() % length;

        if (error_type == 0 && pos < length - 1)
        {
            char temp = similarString[pos];
            similarString[pos] = similarString[pos + 1];
            similarString[pos + 1] = temp;
        }
        else if (error_type == 1 && length > 1)
        {
            memmove(&similarString[pos], &similarString[pos + 1], length - pos);
            similarString[length - 1] = '\0';
            length--;
        }
        else if (error_type == 2)
        {
            similarString[pos] = 'a' + (rand() % 26);
        }
    }
    return similarString;
}

