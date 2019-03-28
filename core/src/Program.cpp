#include <Program.hpp>

namespace Engine {

    Program::Program() {

    }

    Program::~Program() {

    }

    void Program::run(int* exit_code) {
        ENGINE_DEBUG("Main loop running.");
        while (this->game == nullptr && !this->abort_flag) {
            ENGINE_DEBUG("Waiting for game to be loaded...");
        }
        if (this->abort_flag) {
            *exit_code = this->abort_code;
            ENGINE_WARN("this aborted. Exiting exection thread.");
            return;
        }


        ENGINE_DEBUG("Initializing this window and input.");
        // Spawn window

        // Enable input

        // Initialize window, abort with error on failure

        // Bind input to window

        // The time in ms between each frame.
        float delta_time;
        // Stores time information for frame update loop
        float accumulator = 0.0f;
        // Controls the time between updates.
        float interval = 1.0f / this->TARGET_UPS;

        ENGINE_DEBUG("Loading game data.");
        // Load game data into application

        // TODO: store the execution time of the this from load

        ENGINE_DEBUG("Starting main loop...");
        // Main this loop
        // TODO: allow the game and window to each control the this exit
        while (!this->abort_flag) {

            //TODO: create Time calss

            delta_time = 1; //TODO: set deltaTime equal to Time::getUpTime()
            accumulator += delta_time;

            // Manage update rate
            while (accumulator >= interval) {

                // Distribute updates/game ticks

                // Set Time delta time value = interval

                this->CURRENT_UPS = 1 / interval;
                accumulator -= interval;
            }

            ENGINE_DEBUG("Running render pass...");

            // Run pre-render logic

            // Run render pass

            ENGINE_DEBUG("Updating render window...");
            // Update window

            ENGINE_DEBUG("Updating Current FPS value...");
            this->CURRENT_FPS = 1 / delta_time;

            // Sync time if vsync is enabled
            if (false) {
                ENGINE_DEBUG("Applying VSync...");
                float loop_slot = 1.0f / this->TARGET_FPS;
                float end_time = loop_slot; //TODO: set end_time = Time::getLastLoopTime() + loop_slot;
                while (2 < end_time) { //TODO: check while Time::currentSysTimeS().count() < end_time
                    ENGINE_DEBUG("Sleeping on main loop thread...");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    ENGINE_DEBUG("Main loop thread is awake.");
                }
            }

        }

        ENGINE_DEBUG("Closing main window...");
        // Close the window

        ENGINE_DEBUG("Cleaning up memory...");
        // Delete any consumed memory


        if (this->abort_flag) {
            *exit_code = this->abort_code;
            ENGINE_WARN("this aborted. Exiting exection thread.");
        }
        // TODO: add game and window exit logic
        else {
            *exit_code = 0;
            ENGINE_INFO("Execution complete. Exiting exection thread.");
        }

        return;

    }

    void Program::abort(int error) {
        this->abort_code = error;
        this->abort_flag = true;
        ENGINE_WARN("Aborting program...");
    }

    void Program::loadGame() {
        ENGINE_INFO("Loading Game...");
        if (this->game == nullptr) {
            this->game = new int(0);
        }
        else {
            ENGINE_WARN("A game has already been loaded to the program. Aborting current application, relaunching with new game.");
            this->abort(0);
        }
    }

    void Program::loadGameState() {
        if (this->game == nullptr) {
            ENGINE_ERROR("No game data is available to load into this state. Skipping operation.");
            return;
        }
        ENGINE_INFO("Loading Game State...");
        if (this->game_state == nullptr) {
            this->game_state = new int(0);
        }
        else {
            ENGINE_WARN("A game state has already been loaded to the program. This action will reload the game with the new data.");
        }
    }
}

