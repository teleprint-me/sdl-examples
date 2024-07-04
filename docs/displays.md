**Title:** SDL on Linux - Detecting Display Backend (X11 vs. Wayland)

**Introduction**

* Brief overview of Simple DirectMedia Layer (SDL) library
        + Cross-platform support for multimedia applications
        + Example projects in C and C++
* Importance of detecting the display backend on Linux systems

**Building SDL Projects with CMake**

* Explanation of provided `CMakeLists.txt` file
        + Support for multiple platforms
        + Automated build process

**Detecting Display Backend (X11 vs. Wayland) in Linux Systems**

* Overview of environment variables related to X11 and Wayland
* Example program using SDL library to determine display backend
        + Function signature for `SDL_GetVideoDriver(int index)`
        + Doxygen documentation

**Implementation Details**

* Code snippets demonstrating the implementation

**Conclusion**

* Summary of what we've learned and achieved
