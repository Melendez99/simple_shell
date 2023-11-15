#include "george.h"
/**
 * freeAndNull - Frees a pointer and NULLs the address.
 * @pointer: Address of the pointer to free.
 *
 * This function frees the memory allocated for the pointer and sets it to NULL.
 *
 * Return: 1 if freed, otherwise 0.
 */
int freeAndNull(void **pointer) {
    if (pointer != NULL && *pointer != NULL) {
        free(*pointer);
        *pointer = NULL;
        return 1;
    }
    return 0;
}
