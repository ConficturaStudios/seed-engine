#include <Program.hpp>

namespace seedengine {

    Program::Program() {
        renderer_ = Renderer(RenderOptions());
        // Bind onClose event deligate
        EventDispatcher::registerDeligate(WindowCloseEvent::EVENT_ID, [this](Event& e) {
            this->onClose(static_cast<WindowCloseEvent&>(e));
        });
    }

    Program::~Program() {

    }

    void Program::run(int* exit_code) {
        ENGINE_DEBUG("Main loop running.");
        ENGINE_DEBUG("Waiting for game to be loaded...");
        while (this->getGame() == nullptr && !this->shouldAbort() && !this->shouldExit()) {

        }
        if (this->shouldAbort()) {
            *exit_code = this->abort_code_;
            ENGINE_WARN("Program aborted. Exiting exection thread.");
            return;
        }
        else if (this->shouldExit()) {
            *exit_code = this->exit_code_;
            ENGINE_INFO("Execution complete. Exiting exection thread.");
            return;
        }

        try {

            ENGINE_DEBUG("Starting program clock");
            // Set the starting time for the Time class
            Time::start();

            ENGINE_DEBUG("Initializing program window and input.");
            // Spawn window
            Window* window = Window::create();

            if (window == nullptr) {
                ENGINE_ERROR("Failed to create window.");
                abort();
                *exit_code = this->abort_code_;
                ENGINE_ERROR("Program aborted. Exiting exection thread.");
                return;
            }

            string icon_path;
            util::DEFAULTS.get("Window", "icon_path", icon_path);
            string core_icon = CORE_PATH("") + icon_path;

            {
                // Set window icon
                AssetLibrary<Image>::load(core_icon);
                window->setIcon(AssetLibrary<Image>::request(core_icon));

                AssetLibrary<Mesh>::load(CORE_PATH("data/models/primatives/quad.mesh"));
                AssetLibrary<Mesh>::load(CORE_PATH("data/models/primatives/triangle.mesh"));
            }

            // The time in ms between each frame.
            float delta_time;
            // Stores time information for frame update loop
            float accumulator = 0.0f;
            // Controls the time between updates.
            float update_interval = 1000.0f / this->TARGET_UPS;
            // Controls the time between frame renders.
            float render_interval = 1000.0f / this->TARGET_FPS;

            ENGINE_DEBUG("Loading game data.");
            // Load game data into application
            EventDispatcher::force<EngineGameLoadEvent>();

            ENGINE_DEBUG("Starting main loop...");

            // Prepare for first loop iteration
            Time::last_loop_time_ = Time::elapsedTimeMS();

            // Main loop
            while (!this->shouldAbort() && !this->shouldExit() && !window->shouldClose()) {

                delta_time = Time::getUpTime();
                accumulator += delta_time;

                Time::delta_time_ = delta_time / 1000.0f;

                // Handle event buffer and event dispatchers
                EventDispatcher::run(0);

                //ENGINE_DEBUG("DT {2} ACC {0} UP-INT {1}", accumulator, update_interval, delta_time);

                int update_count = 0;

                // Manage update rate
                while (accumulator >= update_interval && update_count < MAX_UPF) {

                    // Only update logic if the game is not paused
                    if (!Time::isPaused()) {
                        // Distribute updates/game ticks
                        EventDispatcher::force<EngineTickEvent>(Time::delta_time_);
                        //ENGINE_DEBUG("Update!");
                    }

                    this->current_ups_ = 1000.0f / update_interval;
                    accumulator -= update_interval;
                    update_count++;
                }



                // Run pre-render logic

                EventDispatcher::force<EnginePreRenderEvent>();

                // Run render pass

                EventDispatcher::force<EngineRenderEvent>();

                // Run post-render logic

                EventDispatcher::force<EnginePostRenderEvent>();

                // Update window
                window->update();

                this->current_fps_ = 1000.0f / delta_time;

                //ENGINE_DEBUG("FPS: {0}", this->current_fps_);

                // Sync time if vsync is enabled
                if (window->isVSync()) {
                    //ENGINE_DEBUG("Applying VSync...");
                    float loop_slot = 1000.0f / this->TARGET_FPS;
                    float end_time = Time::getLastLoopTime() + loop_slot;
                    while (Time::elapsedTimeMS().count() < end_time) {
                        //ENGINE_DEBUG("Sleeping on main loop thread...");
                        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        //ENGINE_DEBUG("Main loop thread is awake.");
                    }
                }

            }

            ENGINE_DEBUG("Closing main window...");
            // Close the window
            window->close();

            ENGINE_DEBUG("Cleaning up memory...");
            // Delete any consumed memory
            delete window;

        }
        catch (std::exception& e) {
            abort(-1, e.what());
        }

        if (this->shouldAbort()) {
            *exit_code = this->abort_code_;
            ENGINE_ERROR("Program aborted. Exiting execution thread.");
        }
        else {
            *exit_code = this->exit_code_;
            ENGINE_INFO("Execution complete. Exiting execution thread.");
        }

        AssetLibrary<Mesh>::unloadAll();
        AssetLibrary<Image>::unloadAll();

        return;

    }

    //TODO: Clean up abort functionality, wrap into exit(int) call
    void Program::abort(int error, string msg) {
        std::lock_guard<std::mutex> gaurd(mu);
        this->abort_code_ = error;
        this->abort_flag_ = true;
        if (msg != "") ENGINE_ERROR("Aborting program: " + msg);
        else ENGINE_ERROR("Aborting program...");
    }

    void Program::exit(int exit_code) {
        std::lock_guard<std::mutex> gaurd(mu);
        this->exit_code_ = exit_code;
        this->exit_flag_ = true;
        ENGINE_INFO("Exiting program...");
    }

    void Program::loadGame() {
        std::lock_guard<std::mutex> gaurd(mu);
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
        std::lock_guard<std::mutex> gaurd(mu);
        if (this->game_ == nullptr) {
            ENGINE_WARN("No game data is available to load into this state. Skipping operation.");
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

    void Program::onClose(WindowCloseEvent& e) {
        exit(0);
    }

}

