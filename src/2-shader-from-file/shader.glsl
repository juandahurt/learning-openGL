# vertex shader
# version 330 core

layout(location=0) in vec3 vertPos;
layout(location=1) in vec3 color;
out vec3 theColor;

void main() {
    gl_Position = vec4(vertPos, 1.0);
    theColor = color;
}

# fragment shader

#version 330 core
out vec4 pixelColor;

void main() {
    pixelColor = vec4(0.4, 0.5, 0.4, 1.0);
}
