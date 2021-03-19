/**
 * @file Application.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Application.hpp"

namespace seedengine {

    Application::Application() {

    }

    Application::~Application() {
        
    }

    int Application::run() {
        Logger logger("Seed Engine");
        logger.info("Program has started");

        logger.info("Loading engine preferences...");

        logger.info("Loading game data...");
        logger.info("Loading game preferences...");

        // Allocate any memory needed outside of try block or at close

        try {
            logger.info("Initializing program clock...");
            logger.info("Program clock started successfully at MM/DD/YYYY HH:MM:SSS.");

            logger.info("Creating application window...");
            // TODO: Create a console only mode option

            logger.info("Loading engine assets...");
            logger.info("Loading game assets...");

            logger.info("Initializing statistics...");

            logger.info("Starting main loop...");
            while (!this->shouldExit() && !this->shouldAbort()) {
                logger.debug("Updating game time data...");
                logger.debug("Running event dispatcher...");

                // Run logic update loop

                logger.debug("Running renderer...");

                // Update window
                // Update statistics
                // VSync loop (if enabled)
            }

        } catch (...) {
            logger.critical("Unknown exception was thrown during program runtime. Exiting...");
        }

        logger.info("Closing application window...");

        logger.info("Unloading engine assets...");
        logger.info("Unloading game assets...");

        logger.info("Program has ended with exit code {0}", 0);
        return 0;
    }

    bool Application::shouldExit() const {
        return true; // TODO: Handle exiting, either in application or in System
    }

    void Application::exit(int exitCode) {

    }

    bool Application::shouldAbort() const {
        return false;
    }

    void Application::abort(int exitCode, const char* msg) {

    }

    bool Application::loadGameData() {
        return false;
    }

    void Application::onStartup() {

    }

    void Application::onLoadGameData() {

    }

    void Application::onShutdown() {

    }

}