# Primitives

This section outlines the basic geometric shapes and structures used in our software rendering engine project inspired by DOOM to create 3D scenes, walls, and objects.

## Vectors (vector_t)

- **Definition**: The coordinates representing a point in 2D or 3D space. This is commonly referred to as a vertex if one or more edges are connected.

- **Data structure**:
  - `vector_t` struct containing an array of float elements representing the coordinates and the size of the vector.

  ```c
  typedef struct {
      float* elements; // Dynamic array of elements
      size_t size;     // Number of elements in the vector
  } vector_t;
  ```

- **Usage**: Vectors are the building blocks for more complex representations such as shapes like lines, polygons, and screen space representations.

## Matrices (matrix_t)
TODO

## Tensors (tensor_t)
TODO

## Line Segments (line_t)

- **Definition**: Connects two vertices using a straight line. This is also formerly referred to as an edge when one or more lines are connected by at least a single vertex.

- **Data structure**:
  - `line_t` struct containing start and end points represented as vectors.

  ```c
  typedef struct {
      vector_t* start; // Starting point of the line segment
      vector_t* end;   // Ending point of the line segment
  } line_t;
  ```

- **Usage**: Line segments are used to represent edges in our rendering engine.

## Polygons (polygon_t)

- **Definition**: A flat shape formed by connecting three or more vertices with edges.

- **Data structure**:
  - `polygon_t` struct containing an array of vertices, the maximum number of vertices, the count of vertices, height, and distance from the camera.

  ```c
  typedef struct {
      vector_t* vertices;     // Array of vertices
      size_t    max_vertices; // Max number of vertices
      size_t    count;        // Number of vertices within the polygon
      float     height;       // Height of the polygon (for 3D effects)
      float     distance;     // Distance from the camera or reference point
  } polygon_t;
  ```

- **Usage**: Polygons are fundamental for creating the surfaces of 3D objects in our rendering engine.

## Model Space (model_space_t)

- **Definition**: An abstract coordinate system used to describe the positions, orientations, and dimensions of geometric objects before applying transformations.

- **Note**: This concept is not covered directly in our project but is fundamental for understanding transformations.

- **Usage**: Model space is crucial for the initial positioning and scaling of objects before they are transformed into world space.

## World Space (world_space_t)

- **Definition**: Represents the game level where all 3D objects exist.

- **Usage**: World space is where objects are placed in the game environment, allowing for interaction and collision detection.

## Screen Space (screen_space_t)

- **Definition**: Everything that is transformed into a shape displayed on your screen.

- **Usage**: Screen space is where objects are rendered after all transformations and projections are applied.

### Screen-space representation

- **Definition**: A quadrilateral is a four-sided polygon that can be used to represent shapes in the screen space.

- **Data structure**:
  - `screen_space_t` struct containing vertices, maximum number of vertices, current number of vertices, depth, and an identifier for storing polygon information.

  ```c
  typedef struct {
      vector_t* vertices;     // Array of vertices
      size_t    max_vertices; // Max number of vertices
      size_t    count;        // Current number of vertices
      float     depth;        // Depth of the plane from the camera
      int       id;           // Identifier for the plane, used to store polygon info
  } screen_space_t;
  ```

- **Usage**: Quadrilaterals in screen space are used to represent the visible parts of 3D objects after projection and clipping.
