#include <seedengine>

class SampleApp : public Engine::Program
{

public:
    SampleApp() {

    }

    ~SampleApp() {

    }
};

Engine::Program* Engine::CreateProgram() {
    return new SampleApp();
}