#include "buffer_interface.h"
#include "input_interface.h"
#include "macros.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#define READ_SIZE (1 << 10)

char* ReadSTDIN()
{
    return ReadFile(STDIN_FILENO);
}

char* ReadFile(int file)
{
    char    local_buffer[READ_SIZE + 1];
    ssize_t read_size;
    Buffer* buffer;
    char*   result;

    buffer = BufferCreateDefault();
    CHECK_RETURN(buffer, NULL, NULL);

    while (true)
    {
        read_size = read(file, local_buffer, READ_SIZE);

        if (read_size < 0)
        {
            BufferDestoryAll(buffer);
            return NULL;
        }

        if (read_size == 0)
            break ;

        BufferSetLength(buffer, local_buffer, read_size);
    }

    result = BufferGetContent(buffer);
    BufferDestroy(buffer);

    return result;
}

char* ReadFileName(const char* name)
{
    int file;

    file = open(name, O_RDONLY);
    CHECK_CONDITION_RETURN(file < 0, NULL);

    return ReadFile(file);
}