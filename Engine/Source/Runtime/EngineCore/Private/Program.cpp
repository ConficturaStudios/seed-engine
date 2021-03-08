/**
 * Program.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Program.hpp"

namespace seedengine {

    Program::Program() {

    }

    Program::~Program() {
        
    }

    int Program::run() {
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

            logger.info("Loading engine assets...");
            logger.info("Loading game assets...");

            logger.info("Initializing statistics...");

            logger.info("Starting main loop...");
            while (!this->shouldExit()) {
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

        logger.info("Program has ended with exit code %d", 0);
        return 0;
    }

    bool Program::shouldExit() const {
        return true;
    }

}