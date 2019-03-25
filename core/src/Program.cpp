#include <Program.hpp>

namespace Engine {

    Program::Program() {

    }

    Program::~Program() {

    }

    int Program::run() {
        std::cout << "Hello World!" << std::endl;
        std::cout << "Press any key to finish...";
        std::getchar();
        return 0;
    }

}

