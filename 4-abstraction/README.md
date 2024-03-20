# Abstraction

In this example, all the OpenGL function calls have been 
abstracted into come classes:
- **Index Buffer:** It tells OpenGL the indices that we want to draw. It also holds the number of indices.
- **Vertex Buffer:** allocates the actual data (VBO) that represents every vertex. 
- **Vertex Array:** It allocates the VAO using some layout and a vertex buffer. 
- **Vertex Buffer Layout:** It indicates the layout of data located inside the VBO. 
- **Shader:** It handles all the shader stuff (the compiling, parsing, reading from file) and allows us to pass data to the 
shader using uniforms.
- **Renderer:** It abstracts the clear and draw functions.