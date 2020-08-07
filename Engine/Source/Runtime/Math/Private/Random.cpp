/**
 * Random.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Random.hpp"

namespace seedengine {

    Random::Random() : Random(1) {

    }

    Random::Random(const unsigned int& seed) : seed_(seed), next_(seed) {

    }

    Random::~Random() {
        
    }

    void Random::setSeed(const unsigned int& seed) {
        this->seed_ = seed;
        this->next_ = seed;
    }

    unsigned int Random::getSeed() {
        return this->seed_;
    }

    void Random::reset() {
        this->next_ = this->seed_;
    }

    int Random::next() {
        next_ = next_ * 1103515245 + 12345;
        return (unsigned int)(next_/65536) % 32768;
    }

}