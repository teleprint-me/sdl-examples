# Primitives

This section outlines the basic geometric shapes and structures used in our software rendering engine project inspired by DOOM to create 3D scenes, walls, and objects.

## Points (Vertices)

- **Definition**: A single point in 2D or 3D space.

- **Data structure**:
  - `point2d_t` for 2D points
  - (Future consideration: potentially a custom float type like half or quarter precision for reduced memory usage)

## Line Segments

- **Definition**: Connects two points with a straight line.

- **Data structure**:
  - `line_t` struct containing start and end points.

## Polygons

- **Definition**: A flat shape formed by connecting three or more vertices with edges.

- **Data structure**:
  - `polygon_t` struct containing an array of vertices, the count of vertices, height, and distance from the camera.

## Model Space

- **Definition**: An abstract coordinate system used to describe the positions, orientations, and dimensions of geometric objects before applying transformations.

- **Note**: This concept is not covered directly in our project but is fundamental for understanding transformations.

## World Space

- **Definition**: Represents the game level where all 3D objects exist.

## Screen Space

- **Definition**: Everything that is transformed into a shape displayed on your screen.

## Quadrilateral (Screen-space representation)

- **Definition**: A four-sided polygon used to represent shapes in the screen space.

- **Data structure**:
  - `screen_space_t` struct containing vertices, depth, and an id for storing polygon information.
