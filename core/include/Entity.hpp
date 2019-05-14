#ifndef SEEDENGINE_INCLUDE_ENTITY_H_
#define SEEDENGINE_INCLUDE_ENTITY_H_

#include "Core.hpp"
#include "Asset.hpp"

namespace seedengine {

    class Entity {

    public:
    
        // Returns the ID of this Entity.
        // @returns: The ID of this Entity.
        inline const unsigned int getID() const { return id_; }

        inline std::string getName() const { return name_; }

    protected:

        // Constructs a new Entity.
        Entity() : id_(generateID()) {}

        // The id of this entity.
        const unsigned int id_;
        // The name of this entity.
        std::string name_;

        // The latest id generated.
        static unsigned int latest_id_;

        // Generates a unique new Entity ID.
        // @returns: A new Entity ID.
        static unsigned int generateID() {
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