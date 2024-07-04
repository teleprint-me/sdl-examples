#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char* session_type    = getenv("XDG_SESSION_TYPE");
    const char* x11_display     = getenv("X11_DISPLAY");
    const char* wayland_display = getenv("WAYLAND_DISPLAY");

    // If WAYLAND_DISPLAY is set, it means Wayland is being used
    if (wayland_display != NULL && strcmp(session_type, "wayland") == 0) {
        printf("Using display backend: Wayland\n");

    } else if ((x11_display != NULL && strcmp(session_type, "x11") == 0)) {
        // Otherwise, we fall back to checking for X11
        printf("Using display backend: X11\n");

    } else {
        fprintf(stderr, "Could not detect display backend.\n");
    }

    return 0;
}
