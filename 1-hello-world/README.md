# Hello world program

This is the "Hello world" program in computer graphics.
It renders a triangle using the `GL_TRIANGLES` mode and, obviously, two shaders: one 
for the vertices and the other for the color of every pixel.

The actual buffer data si stored in the VBO and the properties (layout) of it,
 are stored in the VAO.

The resulting triangle is the following:
![hello-world.png](resources%2Fhello-world.png)

*note: it is possible to remove the smoothness of the fragment shader, using the flat kyeword
but that will show only the color of the last vertex.*

:)