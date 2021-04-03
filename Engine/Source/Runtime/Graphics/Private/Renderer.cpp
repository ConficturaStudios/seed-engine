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

    void Renderer::setClearColor(const LinearColor& color) {
        m_clearColor = color;
    }

    void Renderer::setUseDepthTest(bool state) {
        m_useDepth = state;
    }

    void Renderer::setUseBackfaceCulling(bool state) {
        m_useBackfaceCulling = state;
    }

    void Renderer::bindShader(const Shader& shader) {
        m_currentShader = &shader;
    }

    void Renderer::bindMesh(const Mesh& mesh) {
        m_currentMesh = &mesh;
    }

    void Renderer::bindMaterial(const Material& material) {
        m_currentMaterial = &material;
    }

    void Renderer::unbindShader() {
        m_currentShader = nullptr;
    }

    void Renderer::unbindMesh() {
        m_currentMesh = nullptr;
    }

    void Renderer::unbindMaterial() {
        m_currentMaterial = nullptr;
    }

    void Renderer::bindTexture(const Texture& texture) {
        m_textures.addLast(&texture);
        m_filledTextureSlots++;
    }

    void Renderer::clearTextures() {
        m_textures.clear();
        m_filledTextureSlots = 0;
    }

}