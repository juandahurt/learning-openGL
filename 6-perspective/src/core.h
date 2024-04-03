//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_CORE_H
#define INC_6_PERSPECTIVE_CORE_H

#include <string>
#include <iostream>
#include <cassert>
#include <GL/glew.h>

// to wrap the error clearing/finding
#define GLCall(x) clearError(); \
    x;                          \
    assert(lookForError(#x))

static void clearError() {
    while (glGetError());
}

static int lookForError(const std::string& function) {
    auto errCode = glGetError();
    if (errCode) {
        std::cout << "[OpenGL ERROR] (" << errCode << ") " << function << std::endl;
    }
    return errCode == GL_NO_ERROR;
}

#endif //INC_6_PERSPECTIVE_CORE_H
