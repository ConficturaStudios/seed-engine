#ifndef SEEDENGINE_INCLUDE_ACTOR_H_
#define SEEDENGINE_INCLUDE_ACTOR_H_

#include "Core.hpp"
#include "Object.hpp"
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

    class Component : public Object {

        friend class Actor;

    public:

        // The function called when the game updates.
        virtual void update() = 0;

    protected:

        // The actor that this component is attached to.
        Actor& actor_;

        // Constructs a new Component.
        // @param(Actor&) actor: The actor to attach to.
        Component(Actor& actor) : actor_(actor) {

        }

    private:

    };

    // An actor that can take part in a level or scene.
    class Actor : public Object {

    public:

        // Constructs a new actor.
        // @param(const Transform&) transform: The transfrom of this actor.
        // @param(const ActorProperties&) actor_properties: The properties of this actor.
        Actor(  const Transform& transfrom        = Transform(),
                const ActorProperties& properties = ActorProperties())
            : Object("actor"), actor_properties_(properties) {
            this->transform = transform;
            this->active = true;
            this->parent_ = nullptr;
        }

        // The transform of this actor.
        Property<Transform> transform;
        // Is this actor active in the scene?
        Property<bool> active;

        // Adds a Component of type T to this Actor.
        template <class T>
        void addComponent() {
            // Ensure that T is a Component
            static_assert(std::is_base_of<Component, T>::value, "T is not of type Component.");
            components_.push_back(std::make_unique<T>(this));
        }

        // Gets a pointer to the first Component of type T attached to this Actor. Returns nullptr if none are found.
        // @returns: A pointer to the first Component of type T attached to this Actor. Nullptr if none are found.
        template <class T>
        std::unique_ptr<T> getComponent() {
            // Ensure that T is a Component
            static_assert(std::is_base_of<Component, T>::value, "T is not of type Component.");
            for (int i = 0; i < components_.size(); i++) {
                if (dynamic_cast<std::unique_ptr<T>>components_.at(i) != nullptr) return components_.at(i);
                else continue;
            }
            return nullptr;
        }

        // Gets a list of pointers to all Components of type T attached to this Actor. Returns an empty list if none are found.
        // @returns: A list of pointers to all Components of type T attached to this Actor. Returns an empty list if none are found.
        template <class T>
        std::vector<std::unique_ptr<T>> getComponents() {
            // Ensure that T is a Component
            static_assert(std::is_base_of<Component, T>::value, "T is not of type Component.");
            std::vector<std::unique_ptr<T>> ptrs;
            for (int i = 0; i < components_.size(); i++) {
                if (dynamic_cast<std::unique_ptr<T>>(components_.at(i)) != nullptr) ptrs.push_back(components_.at(i));
                else continue;
            }
            return ptrs;
        }

    protected:
        // The properties of this actor.
        ActorProperties actor_properties_;
        // The parent of this actor in the hierarchy.
        Actor* parent_;
        // The children of this actor.
        std::vector<Actor*> children_;
        // The components of this actor.
        std::vector<std::unique_ptr<Component>> components_;

    private:

    };

}

#endif