# vertex shader
# version 330 core

layout(location=0) in vec4 vertPos;
layout(location=1) in vec2 textCoord;

uniform mat4 u_projection;
out vec2 v_texCoord;

void main() {
    gl_Position = u_projection * vertPos;
//    gl_Position = vertPos;
    v_texCoord = textCoord;
}

# fragment shader

#version 330 core

in vec2 v_texCoord;

out vec4 pixelColor;

uniform sampler2D u_texture;

void main() {
    pixelColor = texture(u_texture, v_texCoord);
//    pixelColor = vec4(1);
}