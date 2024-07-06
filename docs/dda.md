# The Digital Differential Analyzer Algorithm

The [Digital Differential Analyzer](https://en.wikipedia.org/wiki/Digital_differential_analyser) is used for line drawing in computer graphics, providing a simple and efficient method to render lines. Understanding the underlying mathematics behind algorithms like DDA is crucial for developing creative solutions to complex problems in computer graphics and video game development.

## Introduction

The DDA (Digital Differential Analyzer) algorithm is an efficient way to draw a straight line between two points in a 2D space. The core idea is to calculate the intermediate points along the line by incrementally adding a small, fixed-step size to the starting point's coordinates.

## Mathematical Foundations

The DDA (Digital Differential Analyzer) algorithm can be understood through several mathematical concepts:

- **Midpoint Calculation**: Determines the midpoint between two endpoints of a line segment.
- **Iterative Increments**: Moves to the next point by adding fractional increments to each coordinate.
- **Slope and Rate of Change**: Utilizes the slope and rate of change of a line.
- **Average Rate of Change**: Applies the average rate of change.
- **Gradient Steps**: Incrementally determines the next point based on the number of steps with respect to a gradient.

This document aims to provide an accessible understanding of the DDA algorithm while connecting it to relevant mathematical concepts from various resources, such as Blitzer's *Introductory Algebra* and Wiley's *Applied Calculus*.

## Algorithm Steps

### 1. Input the coordinates of the start $(x_1, y_1)$ and end $(x_2, y_2)$ points

The algorithm begins by taking the coordinates of the two endpoints of a line segment. Let’s denote them as $(x_1, y_1)$ for the starting point and $(x_2, y_2)$ for the ending point.

#### Defining Our Parameters

- **Starting Point**: Define the starting point as $p_{start} = (x_1, y_1) = (0, 0)$.
- **Ending Point**: Define the ending point as $p_{end} = (x_2, y_2) = (4, 5)$.

#### Data Structures for Points

We can define a data structure representing a point to manage the coordinates of points.

First, we define a data structure representing points that use floating-point precision, offering higher fidelity and range of expression.

```c
// NOTE: We should use struct SDL_FPoint.
// For illustrative purposes, we will use our custom struct FloatPoint instead.
typedef struct FloatPoint { // Coordinates of a point
    float x; // horizontal axis
    float y; // vertical axis
} float_point_t; // type alias
```

Then we define a data structure representing points as integers, offering lower fidelity and range of expression.

```c
// NOTE: Same for integer types, e.g. SDL_Point
typedef struct IntegerPoint {
    int x;
    int y;
} int_point_t;
```

We use multiple structures because the DDA algorithm requires us to convert between data types, and each structure focuses on that data type.

To simplify conversions, we can introduce a `union` called `Float32`, which can map floating-point values to integers (and vice versa) using the same memory location:

```c
// Note that we can use a union to map floating point values
// to integers and vice-versa. This allows us to hot-swap
// values as needed without creating separate structures or
// performing explicit conversions when switching between them.
typedef union Float32 {
    float value;
    uint32_t bits;
} float32_t;
```

For simplicity, we will use separate structures instead. I just thought this was a potential neat trick we might be able to utilize in other ways. Note that this is more complicated than it seems and its full implementation is outside the scope of this article.

#### Instantiating Points

We then create instances of this structure for the starting and ending points:

```c
// Example points for illustration
float_point_t p_start = {0.0f, 0.0f};  // x_1, y_1
float_point_t p_end   = {4.0f, 5.0f};  // x_2, y_2
```

### 2. Calculate the differences between the coordinates

We define the **Slope of a Line** as follows:

$$\text{slope} = \frac{Δy}{Δx} = \frac{y_2 - y_1}{x_2 - x_1}$$

The changes in $x$ and $y$ represent the horizontal and vertical distances between the start and end points.

- **Change in $y$ ($\Delta y$)** is defined as $\Delta y = y_2 - y_1$
- **Change in $x$ ($\Delta x$)** is defined as $\Delta x = x_2 - x_1$

Given $(x_1, y_1) = (0.0f, 0.0f)$ and $(x_2, y_2) = (4.0f, 5.0f)$, we have:

$$\Delta y = y_2 - y_1 = 5.0f - 0.0f = 5.0f$$

$$\Delta x = x_2 - x_1 = 4.0f - 0.0f = 4.0f$$

We can reason this as having a 2-dimensional plane where we move **right** by 4 units and **upward** by 5 units. The **Slope of the Line (m)** between these points is $\frac{Δy}{Δx} = \frac{5.0f}{4.0f}$ (or $1.25$).

We can define the changes in the positions of these points in C as follows:

```c
int_point_t delta = {
    .y = p_end.y - p_start.y, 
    .x = p_end.x - p_start.x
};
```

_Note that we type cast `delta_y` and `delta_x` from `float` to `int` to allow us to calculate the absolute values in order to determine the number of steps required to draw the line. This step highlights a limitation of the DDA algorithm as it may lose precision during this phase of the process._

### 3. Determine the number of steps required to draw the line

The number of steps required to draw the line is determined by the maximum of the absolute values of $\Delta x$ and $\Delta y$. This ensures that we take enough steps to cover the entire line.

$$\text{steps} = \max(|\Delta x|, |\Delta y|)$$

Given $\Delta x = 4.0f$ and $\Delta y = 5.0f$, we calculate the steps as follows:

$$\text{steps} = \max(|4.0f|, |5.0f|) = 5$$

This calculation is straightforward with whole integers but can become more complex with floating-point values, which is beyond the scope of this article.

We can calculate this in C as follows:

```c
int steps = abs(delta.x) > abs(delta.y) ? abs(delta.x) : abs(delta.y);
```

### 4. Calculate the increments for each step in $x$ and $y$

The increments $y_{\text{increment}}$ and $x_{\text{increment}}$ are the changes in the $y$ and $x$ coordinates for each step. These increments determine how much to move in the $y$ and $x$ directions at each step to reach the next point on the line.

$$y_{\text{increment}} = \frac{\Delta y}{\text{steps}}$$

$$x_{\text{increment}} = \frac{\Delta x}{\text{steps}}$$

Given $\Delta x = 4.0f$ and $\Delta y = 5.0f$, and $\text{steps} = 5$, we calculate the increments as follows:

$$y_{\text{increment}} = \frac{5.0f}{5} = 1.0f$$

$$x_{\text{increment}} = \frac{4.0f}{5} = 0.8f$$

We can implement this in C as follows:

```c
float_point_t increment = {
    .y = delta.y / (float) steps,
    .x = delta.x / (float) steps
};
```

_Note that we typecast `steps` back to `float` to ensure the division yields a floating-point result. This step, similar to when we calculated the differences between the coordinates, highlights a limitation of the DDA algorithm as it may lose precision during this phase of the process._

### 5. Initialize the starting point $(x, y)$

The starting point $(x, y)$ is initialized to the starting coordinates $(x_1, y_1)$.

$$x_{\text{current}} = p_{\text{start}}.x$$
$$y_{\text{current}} = p_{\text{start}}.y$$

We initialize the current point to the starting point in our C code as follows:

```c
float_point_t current = {
    .x = p_start.x,
    .y = p_start.y,
};
```

This sets the starting point of the line, from which the algorithm will begin incrementing to plot each point along the line.

### 6. Loop through the number of steps, incrementing the current point and plotting it

For each step, the algorithm increments the $x$ and $y$ coordinates by $x_{increment}$ and $y_{increment}$ respectively. The new point $(x, y)$ is then plotted. This process repeats until all steps are completed, effectively drawing the line from the start point to the end point.

$$
\begin{aligned}
    \sum_{i = 0}^{steps}
    \text{plot}(x + i \cdot x_{increment}, y + i \cdot y_{increment})
\end{aligned}
$$

In our C code, we implement the loop to increment the current point and plot it as follows:

```c
for (int i = 0; i <= steps; i++) {
    SDL_RenderDrawPointF(renderer, current.x, current.y);
    current.x += increment.x;
    current.y += increment.y;
}
```

#### Additional Explanation

The `SDL_RenderDrawPointF` function plots the current point on the screen. The `current` point is then incremented by $x_{increment}$ and $y_{increment}$ for each step. This continues until the loop has run for the total number of steps calculated earlier.

$$
\begin{aligned}
    \text{for } i = 0 \text{ to } \text{steps} : \\
    \quad x_{current} = x_{current} + x_{increment} \\
    \quad y_{current} = y_{current} + y_{increment} \\
    \quad \text{plot}(x_{current}, y_{current})
\end{aligned}
$$

- **Incrementing the Coordinates**: The current $x$ and $y$ coordinates are incremented by the values of $x_{increment}$ and $y_{increment}$. This ensures that the points are spaced evenly along the line.
  
- **Plotting the Points**: The `SDL_RenderDrawPointF` function is responsible for rendering the point on the screen. By using the current floating-point coordinates directly, it ensures precision in the rendering process.

## Putting it all together

### Step-by-Step Explanation

1. **Initialize the Endpoints**:
   - **Define the start and end points**: Specify the coordinates of the start $(x_1, y_1)$ and end $(x_2, y_2)$ points.
   - **Calculate differences**: Compute the differences in the x and y coordinates ($\Delta x$ and $\Delta y$).

2. **Calculate Steps**:
   - **Determine steps**: Calculate the number of steps needed to draw the line as the maximum of the absolute values of $\Delta x$ and $\Delta y$.

3. **Calculate Increments**:
   - **Compute increments**: Determine the incremental changes in the x and y coordinates for each step ($x_{increment}$ and $y_{increment}$).

4. **Iterate and Plot**:
   - **Initialize current point**: Start from the initial point.
   - **Increment and plot**: Iteratively add the increments to the current point and plot the points until the end point is reached.

### Code Implementation

Here's a complete implementation of the DDA algorithm in C:

```c
// Example implementation of the Digital Differential Analyzer (DDA) algorithm
void dda_line(SDL_Renderer *renderer, float_point_t p_start, float_point_t p_end) {
    // Calculate delta values
    float_point_t delta = {
        .y = p_end.y - p_start.y, 
        .x = p_end.x - p_start.x
    };

    // Calculate number of steps required
    int steps = abs(delta.x) > abs(delta.y) ? abs(delta.x) : abs(delta.y);

    // Calculate increment values
    float_point_t increment = {
        .y = delta.y / (float) steps,
        .x = delta.x / (float) steps
    };

    // Initialize current position to the starting point
    float_point_t current = {
        .x = p_start.x,
        .y = p_start.y,
    };

    // Loop through and plot each point
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPointF(renderer, current.x, current.y);
        current.x += increment.x;
        current.y += increment.y;
    }
}
```

### Integration with SDL

To integrate this function into an SDL application, we need to initialize SDL, create a window and renderer, and then call the `dda_line` function within the rendering loop. Here’s a complete example:

```c
#include <SDL2/SDL.h>
#include <stdio.h>

// Define your float_point_t structure here

// Include the dda_line function here

int main(int argc, char *argv[]) {
    // Initialize SDL
    
    // Create SDL window
    
    // Create SDL renderer

    // Set the draw color to white

    // Clear the window

    // Define start and end points here

    // Draw the line using the DDA algorithm

    // Present the renderer

    // Wait for a few seconds before quitting

    // Cleanup

    // Exit
    return 0;
}
```

This example initializes SDL, creates a window and renderer, and uses the `dda_line` function to draw a line between two points. The window displays the line for 5 seconds before quitting.

## Conclusion

The Digital Differential Analyzer (DDA) algorithm is a fundamental method for line drawing in computer graphics, offering a simple yet effective way to render lines. By understanding and implementing the DDA algorithm, we gain insight into how graphics systems translate mathematical descriptions into visual representations.

This document outlines the steps to implement the DDA algorithm, emphasizing the mathematical concepts that underlie each step. By exploring these connections, we deepen our understanding of both the algorithm and the mathematical principles that support it.

This document's approach serves as a valuable reference for learning and implementing the DDA algorithm, bridging the gap between theory and practical application in computer graphics.
