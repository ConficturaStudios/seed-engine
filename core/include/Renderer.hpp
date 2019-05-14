#ifndef SEEDENGINE_INCLUDE_RENDERER_H_
#define SEEDENGINE_INCLUDE_RENDERER_H_

#include "Core.hpp"
#include "Event.hpp"
#include "Image.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace seedengine {

    // Flags used to determine how mesh data is rendered.
    enum RenderFlag : unsigned int {
        // Renders mesh surfaces.
        SURFACE   = FLAG(1),
        // Renders colors, using a default if textures are not enabled.
        // Forces the SURFACE flag to be enabled.
        COLOR     = FLAG(2) | SURFACE,
        // Renders textures.
        // Forces the COLOR flag to be enabled.
        TEXTURE   = FLAG(3) | COLOR,
        // Renders lighting and shadows.
        // Forces the SURFACE flag to be enabled.
        LIGHTING  = FLAG(4) | SURFACE,
        // Renders mesh wireframes.
        WIREFRAME = FLAG(5)
    };

    // A set of data to pass to the renderer.
    enum class RenderMode : unsigned int {
        // Renders all meshes with textures and no lighting information.
        TEXTURED_UNLIT = RenderFlag::TEXTURE,
        // Renders all meshes with textures and lighting information.
        TEXTURED_LIT   = RenderFlag::TEXTURE | RenderFlag::LIGHTING,
        // Renders all meshes with default colors and no lighting information.
        COLORED_UNLIT  = RenderFlag::COLOR,
        // Renders all meshes with default colors and lighting information.
        COLORED_LIT    = RenderFlag::COLOR   | RenderFlag::LIGHTING,
        // Renders all meshes as white surfaces with no lighting information.
        SURFACE_UNLIT  = RenderFlag::SURFACE,
        // Renders all meshes as white surfaces with lighting information.
        SURFACE_LIT    = RenderFlag::SURFACE | RenderFlag::LIGHTING,
        // Only renders mesh wireframes.
        WIREFRAME      = RenderFlag::WIREFRAME
    };

    // Options to apply to the Renderer class.
    class RenderOptions {

        friend class Renderer;

    public:

        // Creates a new set of renderer options.
        // @param(const RenderMode&) render_mode: The data to render.
        // @param(const bool) gui_flag: Enables the rendering of generated user interfaces.
        // @param(const bool) post_flag: Enables the rendering of post process effects.
        // @param(const bool) debug_flag: Enables the rendering of debug information.
        RenderOptions(  const RenderMode& render_mode = RenderMode::TEXTURED_LIT,
                        const bool gui_flag           = true,
                        const bool post_flag          = true,
                        const bool debug_flag         = false)
            : render_mode_(render_mode), gui_flag_(gui_flag), post_flag_(post_flag),
                debug_flag_(debug_flag) {}

    private:

        // The data to render.
        RenderMode render_mode_;
        // Enables the rendering of generated user interfaces.
        bool gui_flag_;
        // Enables the rendering of post process effects.
        bool post_flag_;
        // Enables the rendering of debug information.
        bool debug_flag_;

    };

    // A renderer that should be bound to a specific window.
    class Renderer {
        
    public:

        // Initializes a new renderer.
        // @param(const RenderOptions&) options: The options to apply to the renderer.
        Renderer(const RenderOptions& = RenderOptions());

        // Renders out the current render queue
        // @param(EngineRenderEvent&) e: A reference to the event used to trigger this render pass.
        void render(EngineRenderEvent&);

    private:
        //TODO: Create render queue.
        //TODO: Create texture queue. (?)
        //TODO: Bind renderer to viewport, or choose a more optimized alternative.
        //TODO: Tie renderer into event system.

        //TODO: Create shader class.
        //TODO: Create light class.
        //TODO: Create mesh class and mesh loader. Choose a library for file loading.

        // The options applied to the renderer.
        RenderOptions options_;
        // The number of usable texture slots filled.
        unsigned int filled_texture_slots_;

        // Is backface culling enabled?
        bool backface_culling_;
        // Is depth testing enabled?
        bool depth_test_;

        // Prepares for the next rendering pass.
        void prepare();

        // Sets the clear color for the renderer. This should be black for deferred rendering.
        // @param(float) r: The red color value.
        // @param(float) g: The green color value.
        // @param(float) b: The blue color value.
        // @param(float) a: The alpha color value.
        void setClearColor(float, float, float, float);

        // Binds the specified texture to the next available texture slot.
        // @param(int) texture: The texture to bind.
        void bindTexture(int);

        // Clears out all framebuffers.
        void clearBuffers();
        // Clears all bound textures.
        void clearTextures();
        // Cleans up all remaining data before the next render pass.
        void cleanUp();

        // Enables backface culling.
        void enableBackfaceCulling();
        // Disables backface culling.
        void disableCulling();
        // Enables depth testing.
        void enableDepthTest();
        // Disables depth testing.
        void disableDepthTest();

        // Renders an unlit framebuffer.
        void unlitRender();
        // Renders an unlit framebuffer with all data channels, and merges the data into a lit image.
        void deferredRender();
        // Renders all post process effects.
        void postProcessRender();
        // Renders all GUIs.
        void guiRender();
        // Renders the built in console GUI.
        void consoleRender();
        // Renders wireframe data.
        void wireRender();
        // Renders defined lines.
        void lineRender();
        // Renders debug information.
        void debugRender();
        // Renders volume data.
        void volumeRender();

    };

}

#endif