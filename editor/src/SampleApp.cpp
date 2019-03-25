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

int main(int argc, char** argv) {
    return Engine::main(argc, argv);
}