//
// Created by Juan Hurtado on 8/03/24.
//

#include "1-hello-world/hello_world.h"
#include "2-shader-from-file/shader-from-file.h"

int main() {
    std::cout << "Learning OpenGL :)" << std::endl;
    std::cout << "1. Hello world" << std::endl;
    std::cout << "2. Shader from file" << std::endl;
    std::cout << "Enter an option: " << std::endl;
    std::string line;
    std::getline(std::cin, line);
    int option = std::stoi(line);

    while (option <= 0 || option > 2) {
        std::cout << "Wrong option!" << std::endl;
        std::cout << "Enter a valid option: " << std::endl;
        std::getline(std::cin, line);
        option = std::stoi(line);
    }

    switch (option) {
        case 1:
            return HelloWorld().run();
        case 2:
            return ShaderFromFile().run();
    }
}