/**
 * @file EditorApplication.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "SeedEngineEditorAPI.hpp"
#include "EntryPoint.hpp"
// TODO: Should headers have better encapsulation to prevent client confusion?

namespace seedengine {

    class EditorApplication : public Application {
            friend Application* ::seedengine::CreateApplication();

        protected:

            EditorApplication() : Application() {
                Logger logger("Editor");
                logger.info("Editor created!");
            }

    };

    Application* CreateApplication() {
        return new EditorApplication();
    }

}