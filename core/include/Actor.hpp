#ifndef SEEDENGINE_INCLUDE_ACTOR_H_
#define SEEDENGINE_INCLUDE_ACTOR_H_

#include "Core.hpp"
#include "Object.hpp"
#include "Transform.hpp"

namespace seedengine {

     //TODO: Control actor loading, add ability to write to file

    class Actor; // Forward declare Actor

    /**
     * @brief Properties of an Actor.
     * @details This class is used to encapsulate properties of an actor that will remain constant at
     *          runtime. The members of this class are only accessible by the Actor class and child classes.
     *
     * @see #Actor
     */
    class ActorProperties {

        friend class Actor;

    public:
        /**
         * @brief Creates a new set of actor properties.
         *
         * @param never_ticks Does this actor never recieve tick events?
         * @param can_pause Can this actor be paused?
         */
        ActorProperties(    const bool never_ticks = false,
                            const bool can_pause   = true);

    protected:
        /**
         * @brief Does this actor never recieve tick events?
         */
        bool never_ticks_;
        /**
         * @brief Can this actor be paused?
         */
        bool can_pause_;

    };

    /**
     * @brief A component to be connected to an actor.
     * @details The Component class is the base class for all behaviors that can be attached to an Actor. A
     *          Component cannot exist independent of an Actor, and can only be instanced by Actor::addComponent.
     *
     * @see #Actor
     * @see Actor::addComponent
     * @see #Object
     */
    class Component : public Object {

        friend class Actor;

    public:

        /**
         * @brief The function called when the game updates.
         * @details The Update() method should be overriden to create functionality that will be called
         *          every frame.
         */
        virtual void update() = 0;

    protected:
        /**
         * @brief The actor that this component is attached to.
         */
        Actor& actor_;
        /**
         * @brief Constructs a new Component.
         *
         * @param actor The Actor to attach to.
         */
        Component(Actor& actor);

    private:

    };
    /**
     * @brief An actor that can be placed in a level or scene.
     * @details
     */
    class Actor : public Object {

    public:
        /**
         * @brief Constructs a new actor.
         *
         * @param transform The transfrom of this actor.
         * @param properties The properties of this actor.
         */
        Actor(const Transform& transfrom = Transform(),
            const ActorProperties& properties = ActorProperties());

        /**
         * @brief The transform of this actor.
         *
         * @see #Property
         * @see #Transform
         */
        Property<Transform> transform;
        /**
         * @brief Is this actor active in the scene?
         *
         * @see #Property
         */
        Property<bool> active;

        /**
         * @brief Adds a Component of type T to this Actor.
         *
         * @tparam T The Component class to add.
         */
        template <class T>
        void addComponent() {
            // Ensure that T is a Component
            static_assert(std::is_base_of<Component, T>::value, "T is not of type Component.");
            components_.push_back(std::make_unique<T>(this));
        }

        /**
         * @brief Gets a pointer to the first Component of type T attached to this Actor. Returns nullptr
         *        if none are found.
         *
         * @tparam T The Component class to get.
         *
         * @return A pointer to the first Component of type T attached to this Actor. Nullptr if
         *         none are found.
         */
        template <class T>
        std::unique_ptr<T> getComponent() {
            // Ensure that T is a Component
            static_assert(std::is_base_of<Component, T>::value, "T is not of type Component.");
            for (int i = 0; i < components_.size(); i++) {
                if (dynamic_cast<std::unique_ptr<T>>(components_.at(i)) != nullptr) return components_.at(i);
                else continue;
            }
            return nullptr;
        }

        /**
         * @brief Gets a list of pointers to all Components of type T attached to this Actor. Returns an
         *        empty list if none are found.
         *
         * @tparam T The Component subclass to get.
         *
         * @return A list of pointers to all Components of type T attached to this Actor. Returns
         *         an empty list if none are found.
         */
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
        /**
         * @brief The properties of this actor.
         */
        ActorProperties actor_properties_;
        /**
         * @brief The parent of this actor in the hierarchy.
         */
        Actor* parent_;
        /**
         * @brief The children of this actor.
         */
        std::vector<Actor*> children_;
        /**
         * @brief The components of this actor.
         */
        std::vector<std::unique_ptr<Component>> components_;

    private:

    };

}

#endif