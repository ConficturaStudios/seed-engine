#ifndef SEEDENGINE_INCLUDE_ENTRY_H_
#define SEEDENGINE_INCLUDE_ENTRY_H_

#include "Core.hpp"
#include "Log.hpp"
#include "Program.hpp"

namespace Engine {
    // To be definied by client application
    extern Program* CreateProgram();

    int main(int argc, char** argv) {

        Log::init();
        ENGINE_INFO("Hello World!");

        Program* program = CreateProgram();
        int result = program->run();
        delete program;
        return 0;
    }
}
#endif