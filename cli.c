#include<readline/readline.h>
#include<readline/history.h>

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define PROMPT "> "

typedef int (*command_function_t)(void);

typedef struct
{
    char *name;
    command_function_t func;
    char *info;
    char *info_long;
} command_t;

/**
 * Command line functions
 */
static int _cmd_help(void);
static int _cmd_test(void);

/**
 * NOTE: Lexicographical order must be maintained for this list
 * in order to facilitate searching.
 */
static const command_t _command_registry[] = {
    {"help", _cmd_help, "Print help.",
        "This command prints the help message."},
    {"test", _cmd_test, "Test function.",
        "This is a test function. I'm not sure what\n"
        "it should do yet. But right here I'm just\n"
        "testing the output of long info strings."},

    {(char*)NULL, NULL, (char*)NULL} // end of table marker
};

static int _cmd_help()
{
    int i;

    printf("\nThis is an example help messsage.\n\n");

    for (i = 0; _command_registry[i].name; ++i)
    {
        printf("%s: %s\n", _command_registry[i].name, _command_registry[i].info);
    }

    return 0;
}

static int _cmd_test()
{
    printf("Test function called!\n");
    return 0;
}

static int _execute_command(char *cmd)
{
    int i;

    // TODO for now no support for anything useful e.g. args,
    // just run a command if it is an exact match
    i = 0;
    while(_command_registry[i].name)
    {
        if (!strcmp(_command_registry[i].name, cmd))
        {
            // Ensure uniqueness
            if (_command_registry[i + 1].name && !strcmp(_command_registry[i + 1].name, cmd))
                return -1; // TODO
            else
                return (*_command_registry[i].func)();
        }
        i++;
    }

    return -1;
}

static void _interactive()
{
    char *line;

    while (true)
    {
        line  = readline(PROMPT); 
        if (line)
        {
            _execute_command(line);
            free(line);
        }
    }
}

int main()
{
    _interactive();
}

