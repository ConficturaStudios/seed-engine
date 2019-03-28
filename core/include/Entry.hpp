#ifndef SEEDENGINE_INCLUDE_ENTRY_H_
#define SEEDENGINE_INCLUDE_ENTRY_H_

#include "Core.hpp"
#include "Log.hpp"
#include "Program.hpp"

namespace Engine {

    // To be definied by client application
    // @returns: A pointer to a new program object.
    extern Program* CreateProgram();

    int main(int argc, char** argv) {

        Log::init();
        ENGINE_DEBUG("Launching the engine...");

        Program* program = CreateProgram();

        int exit_code = 0;

        //program->run(&exit_code);
        ENGINE_INFO("Spawning program thread...");

        std::thread main_exe(&Program::run, program, &exit_code);

        ENGINE_INFO("Program running on a new thread.");

        // Wait for the main execution thread to complete before closing the program
        main_exe.join();
        ENGINE_INFO("Threads joined.");
        // Delete any memory used by the program
        delete program;

        ENGINE_INFO("Exiting...");
        return exit_code;
    }
}
#endif