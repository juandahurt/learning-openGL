# vertex shader
# version 330 core

layout(location=0) in vec3 vertPos;
layout(location=1) in vec3 color;

uniform mat4 u_mvp;
out vec4 v_color;

void main() {
    gl_Position = u_mvp * vec4(vertPos, 1);
    v_color = vec4(color, 1);
}

# fragment shader

#version 330 core

in vec4 v_color;

out vec4 pixelColor;

//uniform sampler2D u_texture;

void main() {
//    pixelColor = texture(u_texture, v_texCoord);
//        pixelColor = vec4(1);
    pixelColor = v_color;
}