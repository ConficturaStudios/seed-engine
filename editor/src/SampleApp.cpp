#include <seedengine>

// The main entry point of the Seed Engine Editor.
// @param(int) argc: Command line argument count.
// @param(char**) argv: Command line arguments.
int main(int argc, char** argv) {
    seedengine::Log::init();
    CLIENT_DEBUG("Launching the engine...");

    seedengine::Program* program = new seedengine::Program();

    int exit_code = 0;

    //program->run(&exit_code);
    CLIENT_INFO("Spawning program thread...");

    std::thread main_exe(&seedengine::Program::run, program, &exit_code);

    CLIENT_INFO("Program running on a new thread.");

    program->loadGame();

    // Wait for the main execution thread to complete before closing the program
    main_exe.join();
    CLIENT_INFO("Threads joined.");
    // Delete any memory used by the program
    delete program;

    switch(exit_code) {
        case -1:
            CLIENT_ERROR("Finishing with exit code {0}...", exit_code);
            break;
        case 0:
            CLIENT_INFO("Finishing with exit code {0}...", exit_code);
            break;
        default:
            CLIENT_WARN("Finishing with exit code {0}...", exit_code);
            break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return exit_code;
    //return seedengine::main(argc, argv);
}