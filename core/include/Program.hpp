#ifndef SEEDENGINE_INCLUDE_PROGRAM_H_
#define SEEDENGINE_INCLUDE_PROGRAM_H_

#include "Core.hpp"
#include "Log.hpp"
#include "Time.hpp"

namespace Engine {

    // The program that controls the window and all logic.
    class ENGINE_DLL Program {
        public:
            Program();
            virtual ~Program();

            // Target Frames per Second
            const float TARGET_FPS = 75; //TODO: Initialize from engine or game .ini file
            // Target Updates per Second
            const float TARGET_UPS = 30; //TODO: Initialize from engine or game .ini file

            // Runs the program logic. Should be launched on a new thread.
            // @param(int*) exit_code: A pointer to pass the returned exit code of the main loop.
            void run(int*);

            // Aborts this program during runtime.
            // @param(int) error: The error code to return console.
            void abort(int);

            // Exits this program.
            // @param(int) exit_code: The exit code to return to the console.
            void exit(int);

            // Specifies the game to run.
            // ** IN DEVELOPMENT **
            void loadGame(); //TODO: Create game class, pass to this function

            // Loads a specific game state into the running game. This data
            // must match the loaded game. To be called during program execution.
            // ** IN DEVELOPMENT **
            void loadGameState(); //TODO: Create game state (similar to save game data) class, pass to this function

        private:

            // The game loaded into this program. Will be nullptr if none has been loaded.
            // ** IN DEVELOPMENT **
            int* game = nullptr; //TODO: replace int* with actual game class
            // The game state loaded into this program. Will be nullptr if none has been loaded.
            // ** IN DEVELOPMENT **
            int* game_state = nullptr; //TODO: replace int* with actual game state class

            // Internal flag that instructs the program to abort.
            bool abort_flag = false;
            // Stores the required error code upon abort.
            int abort_code = 0;

            // Internal flag that instructs the program to exit.
            bool exit_flag = false;
            // Stores the required exit code upon exit.
            int exit_code = 0;

            // The current frames per second of this instance.
            float CURRENT_FPS = TARGET_FPS;
            // The current updates per second of this instance.
            float CURRENT_UPS = TARGET_UPS;

    };
}

#endif