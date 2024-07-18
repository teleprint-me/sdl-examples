# Vector (vector_t)

- A mathematical vector represents displacement or movement in n-dimensional space
- SDL defines `SDL_FPoint`, which can be used to represent points with floating-point coordinates
- In graphics programming, vertices serve as the points where lines meet and can also represent single points with additional attributes like color
- A vector can be represented by a struct containing an embedded `SDL_FPoint` for its displacement component
- The magnitude of the vector represents the length or distance from one location to another
- There is no one "right" way to name data structures, as long as they are consistent within your project and easy for others (and yourself) to understand
- Both approaches presented for representing vectors can effectively represent them with their respective semantics clearly conveyed in the code

## Rough Outline
1. Introduction
   - 1.1 Purpose
   - 1.2 Scope

2. Points and Vertices
   - 2.1 Definition
        - 2.1.1 `SDL_FPoint`
        - 2.1.2 `SDL_Vertex`
   - 2.2 Properties

3. Vectors
   - 3.1 Mathematical Representation
   - 3.2 Programming Representation
      - 3.2.1 Array of Points
      - 3.2.2 Struct with Embedded `SDL_FPoint`

4. Magnitude
   - 4.1 Definition
   - 4.2 Calculation

5. Displacement
   - 5.1 Semantic Interpretations

6. Naming Conventions

7. Code Examples

8. Additional Resources

9. References
