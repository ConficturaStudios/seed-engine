#include <seedengine>

class SampleApp : public seedengine::Program
{

public:
    SampleApp() {

    }

    ~SampleApp() {

    }
};

seedengine::Program* seedengine::CreateProgram() {
    return new SampleApp();
}

int main(int argc, char** argv) {
    return seedengine::main(argc, argv);
}