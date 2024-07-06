# Digital Differential Analyzer (DDA) Algorithm

The [Digital Differential Analyzer](https://en.wikipedia.org/wiki/Digital_differential_analyser) is used for line drawing in computer graphics, providing a simple and efficient method to render lines with antialiasing capabilities.

## Overview

The Digital Differential Analyzer (DDA) algorithm is used for line drawing in computer graphics, providing an efficient method to render lines with antialiasing capabilities. In this document, we will present the steps involved in implementing the DDA algorithm using SDL and the C programming language.

Although it might seem that we are simply following a tutorial or replicating existing code, understanding the underlying mathematics behind algorithms like DDA is crucial for developing your own creative solutions to complex problems within the realm of computer graphics and video game development.

## Mathematical Foundations

The Digital Differential Analyzer algorithm can be thought of in various ways:

- **Midpoint Calculation**: Calculates the midpoint between two endpoints of a line segment.
- **Iterative Increments**: Iteratively moves to the next point by adding fractional increments to each coordinate.
- **Slope and Rate of Change**: Slope and rate of change of a line (Algebra).
- **Average Rate of Change**: Average rate of change (Calculus).
- **Gradient Steps**: Incrementally determining where the next point is based on the number of steps with respect to a gradient (Derivative).

This document aims to provide an accessible understanding of the DDA algorithm while connecting it to relevant mathematical concepts from various resources, such as textbooks like Blitzer's *Introductory Algebra* and Wiley's *Applied Calculus*.
Let's focus on the algorithm and the mathematical foundation of the Digital Differential Analyzer (DDA) algorithm for line drawing. 

## Introduction

The DDA algorithm is an efficient way to draw a straight line between two points in a 2D space. The core idea is to calculate the intermediate points along the line by incrementally adding a small, fixed-step size to the starting point's coordinates. Here's a step-by-step breakdown of the algorithm and its mathematical basis.

### Algorithm Steps

1. **Input the coordinates of the starting $(x_1, y_1)$ and ending points $(x_2, y_2)$**:

   The algorithm begins by taking the coordinates of the two endpoints of the line segment. Let’s denote them as $(x_1, y_1)$ for the starting point and $(x_2, y_2)$ for the ending point.

    - We define our parameters.

        - Define the starting point as $p_{start} = (x_1, y_1) = (0, 0)$
        - Define the ending point as $p_{end} = (x_2, y_2) = (4, 5)$

    - We define a data structure representing a point.

        ```c
        typedef struct Point { // Coordinates of a point
            float x; // horizontal axis
            float y; // vertical axis
        } point_t;
        ```

    - We then instantiate each structure representing a point.

        ```c
        // Points (2, 3) and (10, 8) are arbitrary and mostly for illustrative purposes
        point_t p_start = {0, 0};  // x_1, y_1
        point_t p_end = {4, 5}; // x_2, y_2
        ```

2. **Calculate the differences between the coordinates**:

    We define the **Slope of a Line** as the following:

    $$\frac{Δx}{Δy} = \frac{x_2 - x_1}{y_2 - y_1}$$

    The change in $x$ and $y$ represent the horizontal and vertical distances between the start and end points.

    - **The change in $x$ ($\Delta x$)** is defined as $\Delta x = x_2 - x_1$
    - **The change in $y$ ($\Delta y$)** is defined as $\Delta y = y_2 - y_1$
    
    Given $(x_1, y_1) = (0, 0)$ and $(x_2, y_2) = (4, 5)$, we have

    $$\frac{delta_{x}}{delta_{y}} = \frac{Δx}{Δy} = \frac{x_2 - x_1}{y_2 - y_1} = \frac{4-0}{5-0} = \boxed{\frac{4}{5}}$$

    We can reason this as having a 2-dimensional plane that only allows us to move $\text{left}$, $\text{right}$, $\text{upward}$, or $\text{downward}$.

    We step $4$ places to the $\text{right}$, then step $5$ places $\text{upward}$. The **Slope of a Line $m$** between these points is $\frac{4}{5}$ (or $0.8$).

    We can define the changes in the position of these points in C as the following:

    ```c
    int delta_x = p_end.x - p_start.x;
    int delta_y = p_end.y - p_start.y;
    ```

3. **Determine the number of steps required to draw the line**:

    The number of steps required to draw the line is determined by the maximum of the absolute values of $\Delta x$ and $\Delta y$. This ensures that we take enough steps to cover the entire line.

    $$\text{steps} = \max(|\Delta x|, |\Delta y|)$$

    We can calculate the steps as such by determining the maximum value between each change in position:

    $$\text{steps} = \max(|4|, |5|) = 5$$

    This should be straightforward in the context of whole integers. This gets complicated once we attempt to do this with floating-point values. This is out-of-scope for now though (in another article).

    We can generally calculate this as the following in C:

    ```c
    int steps = abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);
    ```
