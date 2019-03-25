#ifndef SEEDENGINE_INCLUDE_PROGRAM_H_
#define SEEDENGINE_INCLUDE_PROGRAM_H_

#include "Core.hpp"

namespace Engine {

    class ENGINE_DLL Program {
        public:
            Program();
            virtual ~Program();

            int run();

        private:

    };
}

#endif