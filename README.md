*This project has been created as part of the 42 curriculum by masase.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor and returns **one line at a time**, each time it is called. It works on files as well as on standard input, and the line is returned with its trailing `\n` (if any).

The project is about mastering **static variables**, **dynamic memory management** and **file descriptor reading** with `read()`.

```c
char *get_next_line(int fd);
```

- Returns the line that was read, or `NULL` at end of file / on error.
- The read size is controlled at compile time by `BUFFER_SIZE`.

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` can be any positive value (1, 42, 9999, 10000000...).

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd = open("test.txt", O_RDONLY);
    char    *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Files

| File | Role |
|------|------|
| `get_next_line.c` | Main function |
| `get_next_line_utils.c` | Helper functions |
| `get_next_line.h` | Prototypes and `BUFFER_SIZE` default |


## Algorithm


1. Keep the data already read but not yet returned in a **static** buffer (the "stash").
2. Call `read()` with `BUFFER_SIZE` until the stash contains a `\n` or EOF is reached.
3. Extract the line from the stash and return it.
4. Keep the remainder in the stash for the next call.

## Resources

- `man 2 read`, `man 3 malloc`
- Static variables in C
- AI usage: *describe here which tasks AI helped with (e.g. understanding concepts, writing tests) and which parts you wrote yourself.*
