/**
 * @file Application.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_APPLICATION_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_APPLICATION_H_

#include "EngineCoreAPI.hpp"

// Forward declare main

/**
 * The main program entry point.
 * @param argc The number of command line arguments passed.
 * @param argv The command line arguments provided to the program.
 * @return The exit code of the program.
 */
int main(int argc, char** argv);

namespace seedengine {

    /**
     * @brief The main application class instanced and run by the client application.
     *
     * @details The Application class is responsible for instancing and running the main game loop
     *          and the initialization of all other program paths. An Application object should be
     *          created by the client by overriding the CreateApplication function and returning an instance
     *          of a custom Application class with any needed behaviors.
     *
     *          The main entry point of the program is provided in EntryPoint.hpp, which should be included by the .cpp
     *          where CreateApplication is overridden, and will handle instancing an Application
     *          on its own thread and providing necessary data to the main loop.
     *
     *          When runtime is complete, the Application will handle memory cleanup and return
     *          information about the program execution and success back to the main entry point. The client
     *          can access this data during the closing phase of the program by overriding onShutdown().
     */
    class ENGINE_API Application {

            friend int ::main(int, char**);

        protected:

        // Constructors and destructor

            /**
             * @brief The default constructor for Application objects.
             * @details Constructs a new Application with default initialization for all members.
             */
            Application();

            /**
             * @brief The destructor for Application objects.
             * @details Called when an instance of Application is deleted.
             */
            virtual ~Application();

        private:

            /**
             * Runs the main game loop.
             * @return The exit status of the application.
             */
            int run();

            /**
             * Loads the game data from the specified file.
             * TODO: Create game file format, update this method
             * @return True if the game was successfully loaded.
             */
            bool loadGameData();

        public:

            /**
             * Returns true if this program should attempt to safely exit.
             * @return True if the program should attempt to exit.
             */
            [[nodiscard]] bool shouldExit() const;

            /**
             * Instructs the application to safely exit execution.
             * @param exitCode The exit status of the program.
             */
            void exit(int exitCode);

            /**
             * Returns true if this program should quickly abort due to an issue encountered
             * during runtime.
             * @return True if the program should abort.
             */
            [[nodiscard]] bool shouldAbort() const;

            /**
             * Instructs the application to exit execution due to a critical error.
             * @param exitCode The exit status of the program.
             * @param msg A message to display related to the error leading to the abort.
             */
            void abort(int exitCode, const char* msg);

        protected:

            virtual void onStartup();
            virtual void onLoadGameData();
            virtual void onShutdown();

    };

    /**
     * The factory function implemented by the client to create a new Application instance.
     * @return A pointer to a new Application instance.
     */
    Application* CreateApplication();

}

#endif