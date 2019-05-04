#ifndef SEEDENGINE_INCLUDE_ENTITY_H_
#define SEEDENGINE_INCLUDE_ENTITY_H_

#include "Core.hpp"
#include "Asset.hpp"

namespace seedengine {

    class Component {

    public:

        virtual void update() const = 0;

    protected:

        Component() {

        }

    private:

    };

    class Entity {

    public:
    
        // Returns the ID of this Entity.
        // @returns: The ID of this Entity.
        inline const unsigned int getId() { return id_; }

    protected:

        // Constructs a new Entity.
        Entity() : id_(generateId()) {}

        // The id of this entity.
        const unsigned int id_;

        // The latest id generated.
        static unsigned int latest_id_;

        // Generates a unique new Entity ID.
        // @returns: A new Entity ID.
        static unsigned int generateId() {
            std::lock_guard<std::mutex> gaurd(s_mu);
            latest_id_++;
            return latest_id_;
        }

    private:

        // A mutex to lock functions for thread safety
        static std::mutex s_mu;

    };

}

#endif