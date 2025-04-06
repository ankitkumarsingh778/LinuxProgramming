#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Finds the path containing the currently running program executable.
// The path is placed into the BUFFER, which is of length LEN.
// Returns number of characters in the path or -1.
size_t get_executable_path(char* buffer, size_t len) {
    char* path_end;
    
    // Read the target of /proc/self/exe
    ssize_t count = readlink("/proc/self/exe", buffer, len);
    if (count <= 0)
        return -1;

    buffer[count] = '\0'; // Null-terminate the string
    printf("Buffer after readlink: %s\n", buffer); // Debug print

    // Find the last occurrence of a forward slash, the path separator
    path_end = strrchr(buffer, '/');
    if (path_end == NULL)
        return -1;

    printf("Path end after strrchr: %s\n", path_end); // Debug print
    
    // Advances to the character past the last slash
    ++path_end;
    
    // Truncate the path after the last slash
    *path_end = '\0';
    printf("Buffer after truncation: %s\n", buffer); // Debug print
    
    // The length of the path is the number of characters up through the last slash
    return (size_t)(path_end - buffer);
}

int main() {
    char path[PATH_MAX];
    get_executable_path(path, sizeof(path));
    printf("This program is in the directory %s\n", path);
    return 0;
}

