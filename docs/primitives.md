# Primitives

This section outlines the basic geometric shapes and structures used in our software rendering engine project inspired by DOOM to create 3D scenes, walls, and objects.

## Vectors (vector_t)

- **Definition**: A vector is a 1-dimensional array of numbers representing a point in space, direction, or magnitude.

- **Characteristics**:
  - A vector has only one dimension, consisting of multiple columns.
  - Represents quantities such as direction, velocity, or position in space.

- **Visualization**: 
  - **Vector**: A list of values.
    $$ \vec{v} = \begin{bmatrix} v_1 & v_2 & \cdots & v_m \end{bmatrix} $$

- **Data structure**:
  - `vector_t` struct containing an array of float elements representing the coordinates and the size of the vector.

  ```c
  // N-dimensional vector structure
  // Coordinates for a point in a line or plane
  // May also represent the magnitude and or direction of an object in a line or plane
  typedef struct {
      float* elements; // Dynamic array of elements
      size_t cols;     // The length of a vector
  } vector_t;
  ```

- **Key Concepts**:
  - **Vector**:
    - Single dimension (1D array).
    - `size_t cols` represents the number of elements.
    - Useful for representing points, directions, or magnitudes.

## Matrices (matrix_t)

- **Definition**: A matrix is a 2-dimensional array of numbers arranged in rows and columns.

- **Characteristics**:
  - A matrix has two dimensions: rows and columns.
  - Used for linear transformations, systems of linear equations, and various applications in mathematics and computer science.

- **Visualization**: 
  - **Matrix**: A grid of values.
    $$ \mathbf{M} = \begin{bmatrix} m_{11} & m_{12} \\ m_{21} & m_{22} \end{bmatrix} $$

- **Data structure**:
  - `matrix_t` struct containing a flat array of float elements representing the matrix and the dimensions of the matrix (rows and columns).

  ```c
  // N-dimensional matrix structure
  // A matrix is a rectangular array of rows and columns representing a 2-dimensional space
  typedef struct {
      float* elements; // Flat array representing the matrix elements
      size_t rows;     // The height of a matrix
      size_t cols;     // The length of a matrix
  } matrix_t;
  ```

- **Key Concepts**:
  - **Matrix**:
    - Two dimensions (2D array).
    - `size_t rows` and `size_t cols` represent the dimensions.
    - Useful for linear transformations and systems of equations.

## Tensors (tensor_t)

- **Definition**: A tensor is a multi-dimensional array that generalizes scalars (0D), vectors (1D), and matrices (2D) to higher dimensions, often used to represent data in three or more dimensions.

- **Characteristics**:
  - A tensor can represent data in 1D (vector), 2D (matrix), or 3D and higher dimensions.
  - Commonly used in fields like physics, engineering, and machine learning to represent complex data structures and higher-dimensional spaces.
  - In a 3D context, a tensor can be thought of as a cubic space containing height (rows), length (columns), and width (depth), often used to represent spatial and temporal data.

- **Visualization**: 
  - **Tensor**: A cube or hypercube of values.
    - Example for a 3D tensor:
    $$
    \mathcal{T} = \begin{bmatrix}
    \begin{bmatrix} t_{111} & t_{112} \\ t_{121} & t_{122} \end{bmatrix} \\
    \begin{bmatrix} t_{211} & t_{212} \\ t_{221} & t_{222} \end{bmatrix}
    \end{bmatrix}
    $$

- **Data structure**:
  - `tensor_t` struct containing a flat array of float elements representing the tensor, an array representing the size of each dimension, and the rank (number of dimensions) of the tensor.

  ```c
  // N-dimensional tensor structure
  // A tensor is a rectangular prism where each element may be thought of as a cubic unit
  // A complex, multidimensional, representation of vectors and or matrices
  // Typically used to represent complex 2D and or 3D spaces and planes
  typedef struct {
      float*  elements;   // Flat array representing the tensor elements
      size_t* dimensions; // Array representing the size of each dimension
      size_t  rank;       // Number of dimensions
  } tensor_t;
  ```

- **Key Concepts**:
  - **Tensor**:
    - Multi-dimensional (nD array).
    - `size_t* dimensions` represents the size of each dimension.
    - `size_t rank` represents the number of dimensions.
    - Useful for representing complex data structures and higher-dimensional spaces.

## Line Segments (line_t)

- **Definition**: Connects two vertices using a straight line. This is also formally referred to as an edge when one or more lines are connected by at least a single vertex.

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
