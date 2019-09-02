#ifndef SEEDENGINE_INCLUDE_CAMERA_H_
#define SEEDENGINE_INCLUDE_CAMERA_H_

#include "Core.hpp"
#include "Actor.hpp"

namespace seedengine {

    /**
     * @brief Camera Mode
     */
    enum class CameraMode {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    /**
     * @brief Properties of a camera.
     * @details This class encapsulates the view mode properties used by a Camera.
     * 
     * @see #Camera
     */
    class CameraProperties {

        friend class Camera;

    public:

        /**
         * @brief Construct a new Camera Properties object
         * 
         * @param camera_mode The camera mode to use for this camera.
         * @param width The width of the resulting view.
         * @param height The height of the resulting view.
         * @param field_of_view The vertical field of view of the camera.
         * @param near_plane The near clipping plane of the camera.
         * @param far_plane The far clipping plane of the camera.
         * @param left_plane The left clipping plane of the camera.
         * @param right_plane The right clipping plane of the camera.
         * @param bottom_plane The bottom clipping plane of the camera.
         * @param top_plane The top clipping plane of the camera.
         */
        CameraProperties(   const CameraMode& camera_mode = CameraMode::PERSPECTIVE,
                            const float width             = 1280.0f,
                            const float height            =  720.0f,
                            const float field_of_view     =   70.0f,
                            const float near_plane        =    0.1f,
                            const float far_plane         = 1000.0f,
                            const float left_plane        =  -10.0f,
                            const float right_plane       =   10.0f,
                            const float bottom_plane      =  -10.0f,
                            const float top_plane         =   10.0f);

    protected:

        /**
         * @brief The type of camera mode to be used.
         */
        CameraMode camera_mode_;
        /**
         * @brief The width of the resulting view.
         */
        float width_;
        /**
         * @brief The height of the resulting view.
         */
        float height_;
        /**
         * @brief The vertical field of view.
         */
        float fov_;
        /**
         * @brief The near clipping plane.
         */
        float near_plane_;
        /**
         * @brief The far clipping plane.
         */
        float far_plane_;
        /**
         * @brief The left clipping plane.
         */
        float left_plane_;
        /**
         * @brief The right clipping plane.
         */
        float right_plane_;
        /**
         * @brief The bottom clipping plane.
         */
        float bottom_plane_;
        /**
         * @brief The top clipping plane.
         */
        float top_plane_;

    };

    /**
     * @brief A camera that can render a frame.
     * @details The Camera is an Actor that can be placed into the scene. The active Camera
     *          in the scene will be used to render each frame.
     * 
     * @see #Actor
     * @see #CameraProperties
     */
    class Camera : public Actor {

    public:

        /**
         * @brief Construct a new Camera object
         * 
         * @param transform The transfrom of this actor.
         * @param camera_properties The properties of this camera.
         * @param actor_properties The properties of this actor.
         */
        Camera(  const Transform& transform                = Transform(),
                 const CameraProperties& camera_properties = CameraProperties(),
                 const ActorProperties& actor_properties   = ActorProperties());

        /**
         * @brief Construct a new Camera object
         *
         * @param camera_properties The properties of this camera.
         * @param actor_properties The properties of this actor.
         */
        Camera(const CameraProperties& camera_properties,
               const ActorProperties& actor_properties = ActorProperties());

        /**
         * @brief Get the view matrix from this camera.
         * 
         * @return The view matrix from this camera.
         */
        inline glm::mat4 getViewMatrix() const {
            return glm::inverse(transform().getTransformationMatrix());
        }

        /**
         * @brief Get the projection matrix from this camera.
         * 
         * @return The projection matrix from this camera.
         */
        inline glm::mat4 getProjectionMatrix() const { return projection_matrix_; }
        
        /**
         * @brief Get the inverse projection matrix from this camera.
         * 
         * @return The inverse projection matrix from this camera.
         */
        inline glm::mat4 getInvProjectionMatrix() const { return inv_projection_matrix_; }

    protected:

        /**
         * @brief The properties of this camera.
         */
        CameraProperties camera_properties_;

    private:

        /**
         * @brief The projection matrix of this camera.
         */
        glm::mat4 projection_matrix_;
        /**
         * @brief The inverse projection matrix of this camera.
         */
        glm::mat4 inv_projection_matrix_;


    };

}

#endif