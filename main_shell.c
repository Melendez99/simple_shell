#include "george.h"
/**
 * main - Entry point of the program.
 * @arg_count: Argument count.
 * @arg_vector: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int arg_count, char **arg_vector) {
    info_t information[] = { INFO_INIT };
    int file_descriptor = 2;

    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (file_descriptor)
        : "r" (file_descriptor)
    );

    if (arg_count == 2) {
        file_descriptor = open(arg_vector[1], O_RDONLY);
        if (file_descriptor == -1) {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT) {
                _eputs(arg_vector[0]);
                _eputs(": 0: Can't open ");
                _eputs(arg_vector[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        information->readfd = file_descriptor;
    }

    populate_env_list(information);
    read_history(information);
    hsh(information, arg_vector);
    return EXIT_SUCCESS;
}
