#include <stdint.h>
#include <limine.h>
#include <system.h>
#include <limine_interface.h>
#include <tty.h>

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

//static volatile struct limine_terminal_request terminal_request = {
//    .id = LIMINE_TERMINAL_REQUEST,
//    .revision = 0
//};

static void done(void) {
    for (;;) {
        //__asm__("hlt");
    }
}

// The following will be our kernel's entry point.
void _start(void) {
    extern kernel_start;
    extern end;
    //if (terminal_request.response == NULL
    // || terminal_request.response->terminal_count < 1) {
    //    done();
    //}
    //struct limine_terminal *terminal = terminal_request.response->terminals[0];
    //terminal_request.response->write(terminal, "Hello World", 11);
    // Ensure we got a terminal
    //print_char('a');
    //limine_interface_setterm(terminal_request.response);
    // We should now be able to call the Limine terminal to print out
    // a simple "Hello World" to screen.
    printf("Yes, this is limine tendos, what do you except?\n");
    printf("Kernel location: 0x%x\n", kernel_start);
    printf("Kernel end: 0x%x\n", end);
    printf("Testing GDT...\n");
    test2();
    printf("Done!");
    // We're done, just hang...
    done();
}