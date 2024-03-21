//
// Created by Juan Hurtado on 19/03/24.
//

#ifndef INC_4_ABSTRACTION_CORE_H
#define INC_4_ABSTRACTION_CORE_H

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
    while (errCode != GL_NO_ERROR) {
        std::cout << "[OpenGL ERROR] (" << errCode << ") " << function << std::endl;
        errCode = glGetError(); // unreachable, but just wanted to show that it should be inside a loop to get all the errors
        return false;
    }
    return true;
}

#endif //INC_4_ABSTRACTION_CORE_H
