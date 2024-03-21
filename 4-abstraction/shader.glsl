# vertex shader
# version 330 core

layout(location=0) in vec3 vertPos;
//layout(location=1) in vec3 color;
//out vec3 theColor;

void main() {
    gl_Position = vec4(vertPos, 1.0);
    //    theColor = color;
}

# fragment shader

#version 330 core
out vec4 pixelColor;

uniform vec4 u_color; // color from the CPU

void main() {
    pixelColor = u_color;

}