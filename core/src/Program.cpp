#include <Program.hpp>

namespace Engine {

    Program::Program() {

    }

    Program::~Program() {

    }

    void Program::run(int* exit_code) {
        ENGINE_DEBUG("Main loop running.");
        while (this->game_ == nullptr && !this->abort_flag_) {
            ENGINE_DEBUG("Waiting for game to be loaded...");
        }
        if (this->abort_flag_) {
            *exit_code = this->abort_code_;
            ENGINE_WARN("Program aborted. Exiting exection thread.");
            return;
        }
        else if (this->exit_flag_) {
            *exit_code = this->exit_code_;
            ENGINE_INFO("Execution complete. Exiting exection thread.");
            return;
        }

        ENGINE_DEBUG("Starting program clock");
        // Set the starting time for the Time class
        Time::start();

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

        //TODO: store the execution time of the this from load

        ENGINE_DEBUG("Starting main loop...");
        // Main this loop
        // TODO: allow the game and window to each control the this exit
        while (!this->abort_flag_ && !this->exit_flag_) {

            //TODO: create Time calss

            delta_time = Time::getUpTime(); //TODO: set deltaTime equal to Time::getUpTime()
            accumulator += delta_time;

            // Handle event buffer and event dispatchers
            Event::EventDispatcher::run(0);

            // Manage update rate
            while (accumulator >= interval) {

                // Distribute updates/game ticks

                Time::delta_time_ = interval;

                this->current_ups_ = 1 / interval;
                accumulator -= interval;
            }

            //ENGINE_DEBUG("Running render pass...");

            // Run pre-render logic

            // Run render pass

            //ENGINE_DEBUG("Updating render window...");
            // Update window

            //ENGINE_DEBUG("Updating Current FPS value...");
            this->current_fps_ = 1 / delta_time;

            // Sync time if vsync is enabled
            if (false) {
                //ENGINE_DEBUG("Applying VSync...");
                float loop_slot = 1.0f / this->TARGET_FPS;
                float end_time = Time::getLastLoopTime() + loop_slot;
                while (Time::currentSysTimeS().count() < end_time) {
                    //ENGINE_DEBUG("Sleeping on main loop thread...");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    //ENGINE_DEBUG("Main loop thread is awake.");
                }
            }

        }

        ENGINE_DEBUG("Closing main window...");
        // Close the window

        ENGINE_DEBUG("Cleaning up memory...");
        // Delete any consumed memory


        if (this->abort_flag_) {
            *exit_code = this->abort_code_;
            ENGINE_ERROR("Program aborted. Exiting exection thread.");
        }
        // TODO: add game and window exit logic
        else {
            *exit_code = this->exit_code_;
            ENGINE_INFO("Execution complete. Exiting exection thread.");
        }

        return;

    }

    //TODO: clean up abort functionality, wrap into exit(int) call
    void Program::abort(int error) {
        this->abort_code_ = error;
        this->abort_flag_ = true;
        ENGINE_ERROR("Aborting program...");
    }

    void Program::exit(int exit_code) {
        this->exit_code_ = exit_code;
        this->exit_flag_ = true;
        ENGINE_INFO("Exiting program...");
    }

    void Program::loadGame() {
        ENGINE_INFO("Loading Game...");
        if (this->game_ == nullptr) {
            this->game_ = new int(0);
        }
        else {
            ENGINE_WARN("A game has already been loaded to the program. Aborting current application, relaunching with new game.");
            this->abort(0);
        }
    }

    void Program::loadGameState() {
        if (this->game_ == nullptr) {
            ENGINE_ERROR("No game data is available to load into this state. Skipping operation.");
            return;
        }
        ENGINE_INFO("Loading Game State...");
        if (this->game_state_ == nullptr) {
            this->game_state_ = new int(0);
        }
        else {
            ENGINE_WARN("A game state has already been loaded to the program. This action will reload the game with the new data.");
        }
    }
}

