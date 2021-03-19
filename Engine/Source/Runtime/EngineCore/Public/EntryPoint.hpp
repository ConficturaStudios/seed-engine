/**
 * @file EntryPoint.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_ENTRY_POINT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_ENTRY_POINT_H_

#include <future>

#include "EngineCoreAPI.hpp"
#include "Application.hpp"

#include "Log.hpp"

namespace seedengine {
/**
 * The factory function implemented by the client to create a new Application instance.
 * @return A pointer to a new Application instance.
 */
    extern Application* CreateApplication();
}

/**
 * The main program entry point.
 * @param argc The number of command line arguments passed.
 * @param argv The command line arguments provided to the program.
 * @return The exit code of the program.
 */
int main(int argc, char** argv) {
    using namespace seedengine;

    Logger logger("Main");

    logger.info("Creating application instance...");
    Application* application = CreateApplication();

    // Handle failure to create application
    if (!application) {
        logger.error("Failed to create application instance, exiting with status -1.");
        return -1;
    }

    logger.info("Created application instance successfully.");
    logger.info("Running application instance on a new thread...");
    std::future<int> future = std::async(&Application::run, application);

    logger.info("Awaiting application completion...");
    int exitStatus = future.get();

    if (exitStatus == 0)
        logger.info("Application completed successfully.");
    else
        logger.error("Application completed with error code {0}.", exitStatus);

    logger.info("Deleting application instance...");
    delete application;
    logger.info("Application instance deleted, exiting with code {0}.", exitStatus);
    return exitStatus;
}

#endif