/**
 * CameraProperties.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "CameraProperties.hpp"

namespace seedengine {

    Matrix4 ICameraProperties::getProjectionMatrix() const {
        return this->m_projection_mat;
    }

    Matrix4 ICameraProperties::getInvProjectionMatrix() const {
        return this->m_inv_projection_mat;
    }

    // Orthographic properties

    CameraMode OrthographicCameraProperties::getCameraMode() const {
        return CameraMode::ORTHOGRAPHIC;
    }

    void OrthographicCameraProperties::updateProjectionMatrix() {

        float i_fn = 1.0f / (far_plane - near_plane);
        float i_rl = 1.0f / (right - left);
        float i_tb = 1.0f / (top - bottom);

        float tx = -(right + left) * i_rl;
        float ty = -(top + bottom) * i_tb;
        float tz = -(far_plane + near_plane) * i_fn;
        
        this->m_projection_mat = Matrix4({
            { 2 * i_rl , 0        , 0         , tx },
            { 0        , 2 * i_tb , 0         , ty },
            { 0        , 0        , -2 * i_fn , tz },
            { 0        , 0        , 0         , 0  }
        });

        this->m_inv_projection_mat = this->m_projection_mat.inverse();
    }

    // Perspective properties
    
    CameraMode PerspectiveCameraProperties::getCameraMode() const {
        return CameraMode::PERSPECTIVE;
    }

    void PerspectiveCameraProperties::updateProjectionMatrix() {

        float f = 1.0f / math::tan(math::toRadians(fov) / 2.0f);
        float i_nf = 1.0f / (near_plane - far_plane);

        this->m_projection_mat = Matrix4({
            { f / aspect_ratio , 0 , 0                               , 0                                   },
            { 0                , f , 0                               , 0                                   },
            { 0                , 0 , (far_plane + near_plane) * i_nf , (2 * near_plane * far_plane) * i_nf },
            { 0                , 0 , -1.0f                           , 0                                   }
        });

        this->m_inv_projection_mat = this->m_projection_mat.inverse();
    }

    // Frustum properties

    CameraMode FrustumCameraProperties::getCameraMode() const {
        return CameraMode::FRUSTUM;
    }

    void FrustumCameraProperties::updateProjectionMatrix() {

        float i_fn = 1.0f / (far_plane - near_plane);
        float i_rl = 1.0f / (right - left);
        float i_tb = 1.0f / (top - bottom);
        float n2 = 2 * near_plane;

        float a = (right + left) * i_rl;
        float b = (top + bottom) * i_tb;
        float c = -(far_plane + near_plane) * i_fn;
        float d = -(n2 * far_plane) * i_fn;
        
        this->m_projection_mat = Matrix4({
            { n2 * i_rl , 0         , a     , 0 },
            { 0         , n2 * i_tb , b     , 0 },
            { 0         , 0         , c     , d },
            { 0         , 0         , -1.0f , 0 }
        });

        this->m_inv_projection_mat = this->m_projection_mat.inverse();
    }

}