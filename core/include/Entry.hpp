#ifndef SEEDENGINE_INCLUDE_ENTRY_H_
#define SEEDENGINE_INCLUDE_ENTRY_H_

#include "Core.hpp"
#include "Program.hpp"
#include "Parser.hpp"
#include "Event.hpp"

namespace seedengine {

    // To be definied by client application
    // @returns: A pointer to a new program object.
    extern Program* CreateProgram();

    // The main entry point of the Seed Engine Core.
    // @param(int) argc: Command line argc.
    // @param(char**) argv: Command line argv.
    int main(int argc, char** argv) {

        Log::init();
        ENGINE_DEBUG("Launching the engine...");

        Program* program = CreateProgram();

        int exit_code = 0;

        //program->run(&exit_code);
        ENGINE_INFO("Spawning program thread...");

        std::thread main_exe(&Program::run, program, &exit_code);

        ENGINE_INFO("Program running on a new thread.");

        program->loadGame();

        ENGINE_INFO("Press enter to exit...");

        std::cin.get();

        program->exit(0);

        // Wait for the main execution thread to complete before closing the program
        main_exe.join();
        ENGINE_INFO("Threads joined.");
        // Delete any memory used by the program
        delete program;

        //TODO: Change finished message type based on exit code
        ENGINE_INFO("Finishing with exit code " + std::to_string(exit_code) + "...");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return exit_code;
    }
}
#endif