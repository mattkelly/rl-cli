#include<readline/readline.h>
#include<readline/history.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define PROMPT "> "

enum {
    MAX_COMMAND_NAME_LEN = 128,
    MAX_INFO_LEN = 2048,
};

typedef int (*command_function_t)(void);

typedef struct
{
    char *name;
    command_function_t func;
    char *info;
} command_t;

static int _cmd_help()
{
    return 0;
}

static const command_t _command_registry[] = {
    {"help", _cmd_help, "Print help."},
    {(char*)NULL, NULL, (char*)NULL}
};

static void _interactive()
{
    char *line;

    while (true)
    {
        line  = readline(PROMPT); 
        if (line)
        {
            printf("%s\n", line);
            free(line);
        }
    }
}

int main()
{
    _interactive();
}

