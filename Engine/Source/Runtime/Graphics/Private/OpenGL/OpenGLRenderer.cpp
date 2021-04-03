/**
 * @file OpenGLRenderer.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "OpenGL/OpenGLRenderer.hpp"
#include "OpenGL/OpenGL.hpp"

namespace seedengine {

    OpenGLRenderer::OpenGLRenderer() {

    }

    OpenGLRenderer::~OpenGLRenderer() {
        
    }

    void OpenGLRenderer::startup() {

    }

    void OpenGLRenderer::shutdown() {

    }

    void OpenGLRenderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OpenGLRenderer::setClearColor(const LinearColor& color) {
        Renderer::setClearColor(color);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::setUseDepthTest(bool state) {
        Renderer::setUseDepthTest(state);
        if (state) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::setUseBackfaceCulling(bool state) {
        Renderer::setUseBackfaceCulling(state);
        if (state) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    void OpenGLRenderer::bindShader(const Shader& shader) {
        Renderer::bindShader(shader);
    }

    void OpenGLRenderer::bindMesh(const Mesh& mesh) {
        Renderer::bindMesh(mesh);
//        glBindVertexArray(mesh.vao());
//        for (uint32 vaa = 0; vaa < mesh.getVertexBuffers().size(); vaa++) {
//            glEnableVertexAttribArray(vaa);
//        }
    }

    void OpenGLRenderer::bindMaterial(const Material& material) {
        Renderer::bindMaterial(material);
    }

    void OpenGLRenderer::unbindShader() {
        Renderer::unbindShader();
    }

    void OpenGLRenderer::unbindMesh() {
        Renderer::unbindMesh();
//        for (uint32 vaa = 0; vaa < m_currentMesh->getVertexBuffers().size(); vaa++) {
//            glEnableVertexAttribArray(vaa);
//        }
//        glBindVertexArray(0);
    }

    void OpenGLRenderer::unbindMaterial() {
        Renderer::unbindMaterial();
    }

    void OpenGLRenderer::drawCurrent() {
        //glDrawElements(GL_TRIANGLES, m_currentMesh->getVertexCount(), GL_UNSIGNED_INT, (void*)0);
    }

    void OpenGLRenderer::bindTexture(const Texture& texture) {
        glActiveTexture(GL_TEXTURE0 + m_filledTextureSlots);
        // TODO: Create OpenGLTexture classes
        //glBindTexture(GL_TEXTURE_2D, texture.getId());
        Renderer::bindTexture(texture);
    }

    void OpenGLRenderer::clearTextures() {
        int i = 0;
        for (const Texture* texture : m_textures) {
            glActiveTexture(GL_TEXTURE0 + i);
            // TODO: Get texture type from texture, support 1D, 3D, etc.
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        Renderer::clearTextures();
    }

}