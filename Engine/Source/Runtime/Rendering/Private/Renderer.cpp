/**
 * @file Renderer.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Renderer.hpp"

namespace seedengine {

    Renderer::Renderer() {

    }

    Renderer::~Renderer() {
        
    }

    GraphicsMode Renderer::GetGraphicsAPI() {
        // TODO: Read in API choice from a config or preferences file
        return GraphicsMode::OPEN_GL;
    }

}