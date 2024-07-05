/**
 * @file dda.c
 *
 * The Digital Differential Analyzer is used for line drawing
 * in computer graphics, providing a simple and efficient method
 * to render lines with antialiasing capabilities.
 */

// A structure representing a point
typedef struct Point {
    float x;
    float y;
} point_t;

int main(int argc, char* argv[]) {
    // Points (2, 3) and (10, 8) are arbitrary and mostly for illustrative purposes
    point_t p_start = {2, 3};  // x_1, y_1
    point_t p_end   = {10, 8}; // x_2, y_2

    return 0;
}
