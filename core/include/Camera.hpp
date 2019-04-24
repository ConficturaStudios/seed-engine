#ifndef SEEDENGINE_INCLUDE_CAMERA_H_
#define SEEDENGINE_INCLUDE_CAMERA_H_

#include "Core.hpp"
#include "Actor.hpp"

namespace seedengine {

    // Available camera modes.
    enum class CameraMode {
        ORTHOGRAPHIC,
        PERSPECTIVE
    }

    // Properties of a camera.
    class CameraProperties {

        friend class Camera;

    public:

        // Creates a new set of camera properties.
        // @param(const CameraMode&) camera_mode:
        // @param(const float) width: The width of the resulting view.
        // @param(const float) height: The height of the resulting view.
        // @param(const float) field_of_view: The vertical field of view of the camera.
        // @param(const float) near_plane: The near clipping plane of the camera.
        // @param(const float) far_plane: The far clipping plane of the camera.
        // @param(const float) left_plane: The left clipping plane of the camera.
        // @param(const float) right_plane: The right clipping plane of the camera.
        // @param(const float) bottom_plane: The bottom clipping plane of the camera.
        // @param(const float) top_plane: The top clipping plane of the camera.
        CameraProperties(   const CameraMode& camera_mode = CameraMode::PERSPECTIVE,
                            const float width             = 1280.0f,
                            const float height            =  720.0f,
                            const float field_of_view     =   70.0f,
                            const float near_plane        =    0.1f,
                            const float far_plane         = 1000.0f,
                            const float left_plane        =  -10.0f,
                            const float right_plane       =   10.0f,
                            const float bottom_plane      =  -10.0f,
                            const float top_plane         =   10.0f)
            : camera_mode_(camera_mode), fov_(field_of_view),
                near_plane_(near_plane), far_plane_(far_plane), left_plane_(left_plane),
                right_plane_(right_plane), bottom_plane_(bottom_plane), top_plane_(top_plane) {}

    protected:

        // The type of camera mode to be used.
        CameraMode camera_mode_;
        // The width of the resulting view.
        float width_;
        // The height of the resulting view.
        float height_;
        // The vertical field of view.
        float fov_;
        // The near clipping plane.
        float near_plane_;
        // The far clipping plane.
        float far_plane_;
        // The left clipping plane.
        float left_plane_;
        // The right clipping plane.
        float right_plane_;
        // The bottom clipping plane.
        float bottom_plane_;
        // The top clipping plane.
        float top_plane_;

    };

    // A camera that can render a frame.
    class Camera : public Actor {

    public:

        // Constructs a new camera.
        // @param(const Transform&) transform: The transfrom of this actor.
        // @param(const CameraProperties&) camera_properties: The properties of this camera.
        // @param(const ActorProperties&) actor_properties: The properties of this actor.
        Camera(  const Transform& transfrom                = Transform(),
                 const CameraProperties& camera_properties = CameraProperties(),
                 const ActorProperties& actor_properties   = ActorProperties())
            : Actor(transform, actor_properties), camera_properties_(camera_properties) {

            if (camera_properties.camera_mode_ == CameraMode::ORTHOGRAPHIC) {
                projection_matrix_ = glm::ortho(
                    camera_properties.left_plane_,
                    camera_properties.right_plane_,
                    camera_properties.bottom_plane_,
                    camera_properties.top_plane_,
                    camera_properties.near_plane_,
                    camera_properties.far_plane_);
            }
            else if (camera_properties.camera_mode_ == CameraMode::PERSPECTIVE) {
                projection_matrix_ = glm::perspective(
                    glm::radians(camera_properties.fov_),
                    camera_properties.width_ / camera_properties.height_,
                    camera_properties.near_plane_,
                    camera_properties.far_plane_);
            }
            inv_projection_matrix_ = glm::inverse(projection_matrix_);

        }

        // Gets the view matrix from this camera.
        // @returns: The view matrix from this camera.
        inline glm::mat4 getViewMatrix() {
            return glm::inverse(transform_.getTransformationMatrix());
        }

        // Gets the projection matrix from this camera.
        // @returns: The projection matrix from this camera.
        inline glm::mat4 getProjectionMatrix() { return projection_matrix_; }
        // Gets the inverse projection matrix from this camera.
        // @returns: The inverse projection matrix from this camera.
        inline glm::mat4 getInvProjectionMatrix() { return inv_projection_matrix_; }

    protected:

        // The properties of this camera.
        CameraProperties camera_properties_;

    private:

        // The projection matrix of this camera.
        glm::mat4 projection_matrix_;
        // The inverse projection matrix of this camera.
        glm::mat4 inv_projection_matrix_;


    };

}

#endif