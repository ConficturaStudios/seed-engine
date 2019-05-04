#ifndef SEEDENGINE_INCLUDE_ACTOR_H_
#define SEEDENGINE_INCLUDE_ACOTR_H_

#include "Core.hpp"
#include "Entity.hpp"
#include "Transform.hpp"

namespace seedengine {

    //TODO: Control actor loading, add ability to write to file

    // Properties of an Actor.
    class ActorProperties {

        friend class Actor;

    public:
        // Creates a new set of actor properties.
        // @param(const bool) never_ticks: Does this actor never recieve tick events?
        // @param(const bool) can_pause: Can this actor be paused?
        ActorProperties(const bool never_ticks = false,
                        const bool can_pause   = true)
            : never_ticks_(never_ticks), can_pause_(can_pause) {}

    protected:
        // Does this actor never recieve tick events?
        bool never_ticks_;
        // Can this actor be paused?
        bool can_pause_;

    };

    // An actor that can take part in a level or scene.
    class Actor : public Entity {

    public:

        // Constructs a new actor.
        // @param(const Transform&) transform: The transfrom of this actor.
        // @param(const ActorProperties&) actor_properties: The properties of this actor.
        Actor(  const Transform& transfrom        = Transform(),
                const ActorProperties& properties = ActorProperties())
            : Entity(), actor_properties_(properties) {}

    protected:
        // The properties of this actor.
        ActorProperties actor_properties_;
        // The transform of this actor.
        Transform transform_;

    private:

    };

}

#endif