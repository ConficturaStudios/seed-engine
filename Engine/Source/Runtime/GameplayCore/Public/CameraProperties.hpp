/**
 * CameraProperties.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_CAMERA_PROPERTIES_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_CAMERA_PROPERTIES_H_

#include "GameplayCoreAPI.hpp"

namespace seedengine {

    // Forward declare CameraComponent class
    class CameraComponent;

    /**
     * @brief The camera mode to use when calculating projection matrices.
     */
    enum class CameraMode : uint8_t {
        ORTHOGRAPHIC = 1,
        PERSPECTIVE = 2,
        FRUSTUM = 4
    };

    /**
     * @brief The base class for processing camera properties.
     * @details The base class for processing camera properties.
     * 
     * @see CameraComponent
     * @see OrthographicCameraProperties
     * @see PerspectiveCameraProperties
     * @see FrustumCameraProperties
     * @see CameraMode
     */
    class ENGINE_API ICameraProperties {

        public:

            /**
             * @brief Get the CameraMode of this property set.
             * 
             * @return CameraMode The CameraMode of this property type.
             */
            virtual CameraMode getCameraMode() const = 0;

            /**
             * @brief Get the projection matrix of this camera.
             * 
             * @return Matrix4 The projection matrix for this CameraMode.
             */
            Matrix4 getProjectionMatrix() const;

            /**
             * @brief Get the inverse projection matrix of this camera.
             * 
             * @return Matrix4 The inverse projection matrix for this CameraMode.
             */
            Matrix4 getInvProjectionMatrix() const;

            /**
             * @brief Updates the cached projection matrices.
             * 
             */
            virtual void updateProjectionMatrix() = 0;

        protected:

            Matrix4 m_projection_mat;
            Matrix4 m_inv_projection_mat;

    };

    //TODO: Load default camera property values from ini

    /**
     * @brief The properties of an orthographic camera.
     * 
     * @see ICameraProperties
     * @see CameraComponent
     * @see CameraMode
     */
    class ENGINE_API OrthographicCameraProperties final : public ICameraProperties {

        public:

            /**
             * @brief Get the CameraMode of this property set.
             * 
             * @return CameraMode The CameraMode of this property type.
             */
            virtual CameraMode getCameraMode() const override;

            /**
             * @brief Updates the cached projection matrices.
             * 
             */
            virtual void updateProjectionMatrix() override;

            float left;
            float right;
            float bottom;
            float top;
            float near_plane;
            float far_plane;

    };
    
    /**
     * @brief The properties of an perspective camera.
     * 
     * @see ICameraProperties
     * @see CameraComponent
     * @see CameraMode
     */
    class ENGINE_API PerspectiveCameraProperties final : public ICameraProperties {

        public:

            /**
             * @brief Get the CameraMode of this property set.
             * 
             * @return CameraMode The CameraMode of this property type.
             */
            virtual CameraMode getCameraMode() const override;

            /**
             * @brief Updates the cached projection matrices.
             * 
             */
            virtual void updateProjectionMatrix() override;

            float fov;
            float aspect_ratio;
            float near_plane;
            float far_plane;

    };

    /**
     * @brief The properties of an frustum camera.
     * 
     * @see ICameraProperties
     * @see CameraComponent
     * @see CameraMode
     */
    class ENGINE_API FrustumCameraProperties final : public ICameraProperties {

        public:

            /**
             * @brief Get the CameraMode of this property set.
             * 
             * @return CameraMode The CameraMode of this property type.
             */
            virtual CameraMode getCameraMode() const override;

            /**
             * @brief Updates the cached projection matrices.
             * 
             */
            virtual void updateProjectionMatrix() override;

            float left;
            float right;
            float bottom;
            float top;
            float near_plane;
            float far_plane;

    };

}

#endif