#include "Actor.hpp"

namespace seedengine {

    ActorProperties::ActorProperties(const bool never_ticks, const bool can_pause)
        : never_ticks_(never_ticks), can_pause_(can_pause) {

    }

    Component::Component(Actor& actor) : Object("Component"), actor_(actor) {

    }

    Actor::Actor(const Transform& transfrom, const ActorProperties& properties)
        : Object("Actor"), actor_properties_(properties) {
        this->transform = transform;
        this->active = true;
        this->parent_ = nullptr;
    }

}