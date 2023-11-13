#include "george.h"

/**
 * split_string_ignore_repeat_delim - Splits a string into words. Repeat delimiters are ignored.
 * @inputStr: The input string.
 * @delimiters: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string_ignore_repeat_delim(char *inputStr, char *delimiters)
{
    if (inputStr == NULL || inputStr[0] == '\0')
        return NULL;

    if (!delimiters)
        delimiters = " ";

    int i, j, k, m, numWords = 0;
    char **resultWords;

    for (i = 0; inputStr[i] != '\0'; i++)
        if (!is_delim(inputStr[i], delimiters) && (is_delim(inputStr[i + 1], delimiters) || !inputStr[i + 1]))
            numWords++;

    if (numWords == 0)
        return NULL;

    resultWords = malloc((numWords + 1) * sizeof(char *));
    if (!resultWords)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (is_delim(inputStr[i], delimiters))
            i++;

        k = 0;
        while (!is_delim(inputStr[i + k], delimiters) && inputStr[i + k])
            k++;

        resultWords[j] = malloc((k + 1) * sizeof(char));
        if (!resultWords[j])
        {
            for (k = 0; k < j; k++)
                free(resultWords[k]);
            free(resultWords);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultWords[j][m] = inputStr[i++];
        resultWords[j][m] = '\0';
    }

    resultWords[j] = NULL;
    return resultWords;
}

/**
 * split_string_by_delim - Splits a string into words using a specific delimiter.
 * @inputStr: The input string.
 * @delimiter: The delimiter character.
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string_by_delim(char *inputStr, char delimiter)
{
    if (inputStr == NULL || inputStr[0] == '\0')
        return NULL;

    int i, j, k, m, numWords = 0;
    char **resultWords;

    for (i = 0; inputStr[i] != '\0'; i++)
        if ((inputStr[i] != delimiter && inputStr[i + 1] == delimiter) ||
            (inputStr[i] != delimiter && !inputStr[i + 1]) || inputStr[i + 1] == delimiter)
            numWords++;

    if (numWords == 0)
        return NULL;

    resultWords = malloc((numWords + 1) * sizeof(char *));
    if (!resultWords)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (inputStr[i] == delimiter && inputStr[i] != delimiter)
            i++;

        k = 0;
        while (inputStr[i + k] != delimiter && inputStr[i + k] && inputStr[i + k] != delimiter)
            k++;

        resultWords[j] = malloc((k + 1) * sizeof(char));
        if (!resultWords[j])
        {
            for (k = 0; k < j; k++)
                free(resultWords[k]);
            free(resultWords);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultWords[j][m] = inputStr[i++];
        resultWords[j][m] = '\0';
    }

    resultWords[j] = NULL;
    return resultWords;
}
