#include "Renderer.hpp"

namespace seedengine {

    Renderer::Renderer(const RenderOptions& options) {
        options_ = options;
        enableBackfaceCulling();
    }

    void Renderer::render() {
        unsigned int render_mode = static_cast<unsigned int>(options_.render_mode_);
        if (CHECK_FLAG(render_mode, RenderFlag::SURFACE)) {
            if (CHECK_FLAG(render_mode, RenderFlag::LIGHTING)) deferredRender();
            else unlitRender(); 
        }
        else if (CHECK_FLAG(render_mode, RenderFlag::WIREFRAME)) wireRender();

        if (options_.post_flag_) postProcessRender();
        if (options_.gui_flag_) guiRender();

        consoleRender();
    }

    void Renderer::prepare() {
        enableDepthTest();
        clearBuffers();
        setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    void Renderer::setClearColor(float r, float g, float b, float a) {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glClearColor(r, g, b, a);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        #endif
    }

    void Renderer::bindTexture(int texture) {

    }

    void Renderer::clearBuffers() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            return;
        #endif
    }

    void Renderer::clearTextures() {

    }

    void Renderer::cleanUp() {

    }

    void Renderer::enableBackfaceCulling() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        #endif
        backface_culling_ = true;
    }

    void Renderer::disableCulling() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glDisable(GL_CULL_FACE);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        #endif
        backface_culling_ = false;
    }

    void Renderer::enableDepthTest() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glEnable(GL_DEPTH_TEST);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        #endif
        depth_test_ = true;
    }

    void Renderer::disableDepthTest() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            glDisable(GL_DEPTH_TEST);
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
        #endif
        depth_test_ = false;
    }


    void Renderer::unlitRender() {

    }

    void Renderer::deferredRender() {

    }

    void Renderer::postProcessRender() {

    }

    void Renderer::guiRender() {

    }

    void Renderer::consoleRender() {

    }

    void Renderer::wireRender() {

    }

    void Renderer::lineRender() {

    }

    void Renderer::debugRender() {

    }

    void Renderer::volumeRender() {

    }
}