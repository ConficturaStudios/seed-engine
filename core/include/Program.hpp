#ifndef SEEDENGINE_INCLUDE_PROGRAM_H_
#define SEEDENGINE_INCLUDE_PROGRAM_H_

#include "Core.hpp"
#include "Time.hpp"
#include "Parser.hpp"
#include "Event.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

namespace seedengine {

    /**
     * @brief The program that controls the window and all logic.
     * @details
     */
    class Program {
        public:
            /** Constructs a new Program. */
            Program();
            /** Program destructor. */
            virtual ~Program();

            /** Target Frames per Second. */
            const float TARGET_FPS = util::DEFAULTS.getFloat("Engine", "target_fps");
            /** Target Updates per Second. */
            const float TARGET_UPS = util::DEFAULTS.getFloat("Engine", "target_ups");
            /** Max Updates per Frame. */
            const int MAX_UPF = util::DEFAULTS.getInt("Engine", "max_updates_per_frame");

            /**
             * @brief Runs the program logic. Should be launched on a new thread.
             * 
             * @param exit_code A pointer to pass the returned exit code of the main loop.
             */
            void run(int* exit_code);

            /**
             * @brief Aborts this program during runtime.
             * 
             * @param error The error code to return to the console. Defaults to -1;
             * @param msg The error message to display. Defaults to an empty string.
             */
            void abort(int error = -1, string msg = "");

            /**
             * @brief Exits this program.
             * 
             * @param exit_code The exit code to return to the console. Defaults to 0;
             */
            void exit(int exit_code = 0);

            /**
             * @brief Specifies the game to run.
             *        ** IN DEVELOPMENT **
             */
            void loadGame();
            //TODO: Create game class, pass to this function

            /**
             * @brief Loads a specific game state into the running game. This data
             *        must match the loaded game. To be called during program execution.
             *        ** IN DEVELOPMENT **
             */
            void loadGameState();
            //TODO: Create game state (similar to save game data) class, pass to this function

            /**
             * @brief Returns the currently loaded game.
             *        ** IN DEVELOPMENT **
             * 
             * @return int* The currently loaded game.
             */
            inline int* getGame() const {
                std::lock_guard<std::mutex> guard(mu);
                return game_;
            }
            /**
             * @brief Returns the currently loaded game state.
             *        ** IN DEVELOPMENT **
             * 
             * @return int* The currently loaded game state.
             */
            inline int* getGameState() const {
                std::lock_guard<std::mutex> guard(mu);
                return game_state_;
            }

            /**
             * @brief Should the program abort?
             * 
             * @return true If the program should abort.
             * @return false If the program should not abort.
             */
            inline bool shouldAbort() const {
                //std::lock_guard<std::mutex> guard(mu);
                return abort_flag_;
            }
            /**
             * @brief Should the program exit?
             * 
             * @return true If the program should exit.
             * @return false If the program should not exit.
             */
            inline bool shouldExit() const {
                //std::lock_guard<std::mutex> guard(mu);
                return exit_flag_;
            }

        private:

            /** A mutex to lock program functions for thread safety */
            mutable std::mutex mu;

            /**
             * @brief The game loaded into this program. Will be nullptr if none has been loaded.
             *        ** IN DEVELOPMENT **
             */
            int* game_ = nullptr; //TODO: replace int* with actual game class

            /**
             * @brief The game state loaded into this program. Will be nullptr if none has
             *        been loaded.
             *        ** IN DEVELOPMENT **
             */
            int* game_state_ = nullptr; //TODO: replace int* with actual game state class

            /** Internal flag that instructs the program to abort. */
            bool abort_flag_ = false;
            /** Stores the required error code upon abort. */
            int abort_code_ = 0;

            /** Internal flag that instructs the program to exit. */
            bool exit_flag_ = false;
            /** Stores the required exit code upon exit. */
            int exit_code_ = 0;

            /** The current frames per second of this instance. */
            float current_fps_ = TARGET_FPS;
            /** The current updates per second of this instance. */
            float current_ups_ = TARGET_UPS;

            /** The dedicated renderer of this program. */
            Renderer renderer_;
            //TODO: Move renderer into window or viewport class

            /**
             * @brief The event binding to be called when the window is closed.
             * 
             * @param e A reference to the window closed event being called.
             */
            void onClose(WindowCloseEvent& e);

    };

}

#endif