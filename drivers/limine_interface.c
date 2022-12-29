#include <limine.h>
#include <limine_interface.h>

/*
static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

void print_char(const char *string)
{
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
   terminal_request.response->write(terminal, (const char *) string, 1);
}
*/