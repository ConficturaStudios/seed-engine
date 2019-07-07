#include "Transform.hpp"

namespace seedengine {

    Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position_(position), euler_rotation_(rotation), scale_(scale)
    {
        rotation_ = glm::quat(rotation);
    }

    Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
        : position_(position), rotation_(rotation), scale_(scale)
    {
        euler_rotation_ = glm::eulerAngles(rotation) * glm::pi<float>() / 180.0f;
    }

}