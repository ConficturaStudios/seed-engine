#include "Camera.hpp"

namespace seedengine {

    CameraProperties::CameraProperties(
                const CameraMode& camera_mode, const float width,
                const float height, const float field_of_view,
                const float near_plane, const float far_plane,
                const float left_plane, const float right_plane,
                const float bottom_plane, const float top_plane)
            : camera_mode_(camera_mode), width_(width), height_(height), fov_(field_of_view),
                near_plane_(near_plane), far_plane_(far_plane), left_plane_(left_plane),
                right_plane_(right_plane), bottom_plane_(bottom_plane), top_plane_(top_plane) {
    
    }

    Camera::Camera(  const Transform& transform, const CameraProperties& camera_properties,
                 const ActorProperties& actor_properties)
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

}