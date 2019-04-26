Seed Engine
===========
An open source game engine that supports both 3D and 2D games. The engine is designed with flexibility in mind, with Lua scripting support and an intuitive editor.
### Current Project Status ###

***NOTE:*** *Continuous Integration is still being set up for this project. The current build state and other CI information will be available at a later time.*

| Platform | Build Status | Coverage | Issues | Alerts |
|:--------:|:------------:|:--------:|:------:|:------:|
| Linux/MacOS | [![Linux Build Status](https://travis-ci.org/ConficturaStudios/seed-engine.svg?branch=master)](https://travis-ci.org/ConficturaStudios/seed-engine) | [![Coverage Status](https://coveralls.io/repos/github/ConficturaStudios/seed-engine/badge.svg?branch=master)](https://coveralls.io/github/ConficturaStudios/seed-engine?branch=master) | | |
| Windows | | | | |
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

### Build Information ###
This project is set up using CMake. A [clean build script](https://github.com/ConficturaStudios/seed-engine/blob/master/scripts/clean_rebuild.py) can be found in the scripts folder.

The desired Graphics API must be specified at build time, or the program will not compile. To specify the Graphics API, include one of the following options when running CMake:

    OpenGL    ->  -DGRAPHICS_API:STRING=OPENGL
    Vulkan    ->  -DGRAPHICS_API:STRING=VULKAN
    DirectX   ->  -DGRAPHICS_API:STRING=DIRECTX
    Metal     ->  -DGRAPHICS_API:STRING=METAL

***NOTE:*** *Currently the only option supported in the code is OpenGL. The other options will cause compiler errors.*

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

### Dependencies ###

The following third party dependencies are used:

- [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [Google Test](https://github.com/google/googletest)
- [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb)

All external dependencies are either included with source, or are linked as a git submodule. GLAD has been configured for C/C++ OpenGL (gl Version 4.6) Core with no extensions. To change this configuration locally, a new set of source files can be created from the [GLAD webservice](https://glad.dav1d.de/).