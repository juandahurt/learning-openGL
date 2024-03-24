//
// Created by Juan Hurtado on 21/03/24.
//

#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string &path) {
    m_textureId = 0;
    m_path = path;
    m_buffer = nullptr;
    m_width = 0;
    m_height = 0;
    m_bbp = 0;
    GLCall(glGenTextures(1, &m_textureId));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));

    // load the image
    stbi_set_flip_vertically_on_load(1); // flips the texture vertically
    m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bbp, 4);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_buffer)
        stbi_image_free(m_buffer); // clean all the image data
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_textureId));
}

void Texture::bind(int slot) {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // selecting the slot
    GLCall(glBindTexture(GL_TEXTURE_2D, m_textureId));
}
