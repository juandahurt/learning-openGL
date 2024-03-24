//
// Created by Juan Hurtado on 21/03/24.
//

#ifndef INC_5_TEXTURES_TEXTURE_H
#define INC_5_TEXTURES_TEXTURE_H

#include "core.h"

#include <string>

class Texture {
private:
    unsigned int    m_textureId;
    std::string     m_path;
    unsigned char*  m_buffer; // holds the texture's data
    int             m_width;
    int             m_height;
    int             m_bbp; // bits per pixel
public:
    Texture(const std::string& path);
    ~Texture();
    void bind(int slot = 0);
};


#endif //INC_5_TEXTURES_TEXTURE_H
