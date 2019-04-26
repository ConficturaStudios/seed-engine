Seed Engine
===========
An open source game engine that supports both 3D and 2D games. The engine is designed with flexibility in mind, with Lua scripting support and an intuitive editor.
### Current Project Status ###

***NOTE:*** *Continuous Integration is still being set up for this project. The current build state and other CI information will be available at a later time.*
<!---
[![Linux Build Status](https://travis-ci.org/)]()
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/)]()
[![Coverage Status](https://coveralls.io/repos/github/)]()
[![Join the chat at https://gitter.im/]()]()
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/)](http://isitmaintained.com/project/ "Average time to resolve an issue")
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/)](https://www.codacy.com/app/)
[![Total alerts](https://img.shields.io/lgtm/alerts/)](https://lgtm.com/projects/)
-->
<!---
<br>
Donations via Patreon:
<br>[![Patreon](https://cloud.githubusercontent.com/assets/8225057/5990484/70413560-a9ab-11e4-8942-1a63607c0b00.png)]()
-->

### Graphics ###

The engine currently supports the following Graphics APIs:

- OpenGL

With planned support for:
- OpenGL ES
- DirectX 12
- DirectX 11
- Vulkan
- Metal

<br>

### Build Information ###
This project is set up using CMake. A <a href="https://github.com/ConficturaStudios/seed-engine/blob/master/scripts/clean_rebuild.bat">clean build script</a> can be found in the scripts folder.

The desired Graphics API must be specified at build time, or will be defaulted to OpenGL. To specify the Graphics API, include one of the following options when running CMake:

    OpenGL    ->  -DGRAPHICS_API:STRING=OPENGL
    Vulkan    ->  -DGRAPHICS_API:STRING=VULKAN
    DirectX   ->  -DGRAPHICS_API:STRING=DIRECTX
    Metal     ->  -DGRAPHICS_API:STRING=METAL

***NOTE:*** *Currently the only option supported in the code is OpenGL. The other options will cause compiler errors.*

<br>

### Repository Structure ###
The engine core and the editor are both implemented in C++. The post-build directory structure for the overall project is:

    /bin            The output destination for built executibles.
    /build          The output desitination for cmake files and generated solutions.
    /ci             Contains files needed for continuous integration.
    /cmake          Contains cmake dependencies.
    /core           The engine core components.
    /editor         The game editor built with the engine core.
    /extern         All external and Third Party dependencies.
    /lib            The output destination for built library files.
    /scripts        Useful scripts for building the project.

<br>

### Dependencies ###

The following third party dependencies are used:

- <a href="https://github.com/Dav1dde/glad">glad</a>
- <a href="https://github.com/glfw/glfw">GLFW</a>
- <a href="https://github.com/g-truc/glm">GLM</a>
- <a href="https://github.com/google/googletest">Google Test</a>
- <a href="https://github.com/gabime/spdlog">spdlog</a>
- <a href="https://github.com/nothings/stb">stb</a>

All external dependencies are either included with source, or are linked as a git submodule. GLAD has been configured for C/C++ OpenGL (gl Version 4.6) Core with no extensions. To change this configuration locally, a new set of source files can be created from the <a href="https://glad.dav1d.de/">GLAD webservice</a>.