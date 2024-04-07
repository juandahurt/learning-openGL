//
// Created by Juan Hurtado on 3/04/24.
//

#ifndef INC_7_MULTIPLE_OBJECTS_CORE_H
#define INC_7_MULTIPLE_OBJECTS_CORE_H

#include <string>
#include <iostream>
#include <cassert>
#include <GL/glew.h>

#define WINDOW_WIDTH 2560.0
#define WINDOW_HEIGHT 1440.0

class Time {
public:
    inline static double deltaTime = 0;
};

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

#endif //INC_7_MULTIPLE_OBJECTS_CORE_H
