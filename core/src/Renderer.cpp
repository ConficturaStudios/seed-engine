#include "Renderer.hpp"

namespace seedengine {

    Renderer::Renderer(RenderOptions options) {
        options_ = options;

        backface_culling_ = true;
        depth_test_ = true;

        filled_texture_slots_ = 0;
        
        // Bind pre-render event deligate
        EventDispatcher::registerDeligate(EnginePreRenderEvent::EVENT_ID, [this](Event & e) {
            this->prepare(static_cast<EnginePreRenderEvent&>(e));
        });

        // Bind render event deligate
        EventDispatcher::registerDeligate(EngineRenderEvent::EVENT_ID, [this](Event& e) {
            this->render(static_cast<EngineRenderEvent&>(e));
        });
    }

    void Renderer::render(EngineRenderEvent& e) {
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

    void Renderer::prepare(EnginePreRenderEvent& e) {
        if (depth_test_) enableDepthTest();
        else disableDepthTest();

        if (backface_culling_) enableBackfaceCulling();
        else disableCulling();
        
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
        // Check for OpenGL
            #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
                //ENGINE_DEBUG("OPGL Unlit Render");
                
                auto m = AssetLibrary<Mesh>::request(CORE_PATH("data/models/primatives/quad.mesh"));

                Shader* s = new Shader(
                    CORE_PATH("data/shaders/test.vs.glsl"),
                    CORE_PATH("data/shaders/test.fs.glsl"),
                    std::vector<string> { "position", "normal", "vertex_color_0", "uv_0" },
                    std::vector<string> { "transformation_mat", "projection_mat", "view_mat" });
                    //std::vector<string> { });
                
                s->start();

                Transform t(
                    glm::vec3(0, 0, -5),
                    glm::vec3(0, 0, 0),
                    glm::vec3(1, 1, 1)
                );
                Camera cam = Camera(CameraProperties(CameraMode::PERSPECTIVE));
                

                glBindVertexArray(m->vao_);
                //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->indices_buffer_);
                //glEnableVertexAttribArray(0);
                for (int vaa = 0; vaa < (int)m->vertex_buffers_.size(); vaa++) {
                    glEnableVertexAttribArray(vaa);

                    //TODO: Handle raw shaders with variable inputs from the game engine side
                    //TODO: Create an Editor-side Material system and shader translator
                    //TODO: Look into embedding Microsoft Shader Conductor in the editor for HLSL translation
                    //TODO: Create PBR shader framework and research material parameter implementations

                }

                s->loadUniform("transformation_mat", t.getTransformationMatrix());
                s->loadUniform("projection_mat", cam.getProjectionMatrix());
                s->loadUniform("view_mat", cam.getViewMatrix());

                if (m->data() == nullptr) ENGINE_WARN("Mesh data not loaded.");
                else {
                    glDrawElements(
                        GL_TRIANGLES,
                        m->data()->faces.size(),
                        GL_UNSIGNED_INT,
                        (void*)0
                    );
                }


                for (int vaa = 0; vaa < (int)m->vertex_buffers_.size(); vaa++) {
                    glDisableVertexAttribArray(vaa);
                }
                //glDisableVertexAttribArray(0);
                glBindVertexArray(0);

                s->stop();

                delete s;

            // Check for Vulkan
            #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
            // Check for DirectX
            #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
            // Check for Metal
            #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL
            #endif
    }

    void Renderer::deferredRender() {
        unlitRender();
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