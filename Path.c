#include "george.h"
/**
 * is_executable - Checks if a file is an executable command.
 * @info: The info struct.
 * @file_path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_executable(info_t *info, char *file_path) {
    struct stat file_stat;

    (void)info;
    if (!file_path || stat(file_path, &file_stat))
        return 0;

    if (file_stat.st_mode & S_IFREG)
        return 1;

    return 0;
}

/**
 * copy_characters - Duplicates characters from a string.
 * @src_string: The source string.
 * @start_idx: Starting index.
 * @end_idx: Ending index.
 *
 * Return: Pointer to the new buffer.
 */
char *copy_characters(char *src_string, int start_idx, int end_idx) {
    static char buffer[1024];
    int buffer_index = 0;

    for (int i = start_idx; i < end_idx; i++) {
        if (src_string[i] != ':')
            buffer[buffer_index++] = src_string[i];
    }
    buffer[buffer_index] = '\0';
    return buffer;
}

/**
 * find_cmd_path - Finds the specified command in the PATH string.
 * @info: The info struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of command if found, otherwise NULL.
 */
char *find_cmd_path(info_t *info, char *path_str, char *command) {
    int index = 0, curr_position = 0;
    char *found_path;

    if (!path_str)
        return NULL;

    if ((_strlen(command) > 2) && starts_with(command, "./")) {
        if (is_executable(info, command))
            return command;
    }

    while (1) {
        if (!path_str[index] || path_str[index] == ':') {
            found_path = copy_characters(path_str, curr_position, index);
            if (!*found_path)
                _strcat(found_path, command);
            else {
                _strcat(found_path, "/");
                _strcat(found_path, command);
            }
            if (is_executable(info, found_path))
                return found_path;
            if (!path_str[index])
                break;
            curr_position = index;
        }
        index++;
    }
    return NULL;
}
