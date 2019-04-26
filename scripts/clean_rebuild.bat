call rm -rf bin
call rm -rf build
call rm -rf lib
call rm -rf .vs
call bash ./scripts/list_todos.bash
call cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGRAPHICS_API:STRING=OPENGL
call cmake --build build/Debug --config Debug
call cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGRAPHICS_API:STRING=OPENGL
call cmake --build build/Release --config Release