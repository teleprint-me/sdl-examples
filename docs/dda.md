# Digital Differential Analyzer

The DDA is used for line drawing in computer graphics. It calculates the midpoint between two endpoints and then iteratively moves to the next point by adding a fractional increment to each coordinate until the line segment is drawn.

## Algorithm

1. Input the two endpoints of the line segment, (x1,y1) and (x2,y2).
2. Calculate the difference between the x-coordinates and y-coordinates of the endpoints as dx and dy respectively.
3. Calculate the slope of the line as m = dy/dx.
4. Set the initial point of the line as (x1,y1).
5. Loop through the x-coordinates of the line, incrementing by one each time, and calculate the corresponding y-coordinate using the equation y = y1 + m(x – x1).
6. Plot the pixel at the calculated (x,y) coordinate.
7. Repeat steps 5 and 6 until the endpoint (x2,y2) is reached.
