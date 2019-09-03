# Seed Engine
[![License](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

An open source game engine that supports both 3D and 2D games. The engine is designed with flexibility in mind, with Lua scripting support and an intuitive editor.

## Current Project Status

[![Linux Build Status](https://travis-ci.org/ConficturaStudios/seed-engine.svg?branch=master)](https://travis-ci.org/ConficturaStudios/seed-engine) 
[![Windows Build status](https://ci.appveyor.com/api/projects/status/n7te2x6t1ie888tv?svg=true)](https://ci.appveyor.com/project/ConficturaStudios/seed-engine)
[![Coverage Status](https://coveralls.io/repos/github/ConficturaStudios/seed-engine/badge.svg?branch=master)](https://coveralls.io/github/ConficturaStudios/seed-engine?branch=master)

***NOTE:*** *Coverage reports and issue tracking are still being set up, and will be available at a later time.*

## Features

As an application still in the early phases of development, most features still need to be implemented. To request a feature, please add a [new issue](https://github.com/ConficturaStudios/seed-engine/issues/new) detailing the desired feature. A changelog and feature tracking system are currently in the works.

### Planned Features

The following are features planned for v1.0.0:

- Deferred and Forward Rendering options
- HLSL as a cross-platform shader language using [Microsoft's Shader Conductor](https://github.com/Microsoft/ShaderConductor)
- Multiple Graphics APIs (see [Graphics](#Graphics))
- Mobile platform support (see [Platforms](#Platforms))
- LUA and Python scripting
- Generation of procedural assets
- 3D Environment Editor
- 2D Tilemap Editor

### Graphics

The engine currently supports the following Graphics APIs:

- OpenGL

With planned support for:

- OpenGL ES
- DirectX 12
- DirectX 11
- Vulkan
- Metal

### Platforms

The following platforms are currently supported:

- Windows
- Linux
- Mac OS X

With planned support for:

- Android
- iOS
- Windows Mobile

## Requirements

Seed Engine has been designed to have minimal requirements to build the project. The following requirements represent the oldest configurations that have been tested successfully. Earlier versions of these tools may still successfully build the project, but have not yet been tested.

***Note:*** *GCC compilers older than GCC 4.9.0 are not supported due to a lack of implementation for std::regex.*

### Linux Requirements
- GCC/G++ 5.0 or newer
- Clang 6.0 or newer
### Mac OS X Requirements
- Mac OS X v10.11 El Capitan or newer
- XCode Developer Tools 8.0 or newer
### Windows Requirements
- Microsoft Visual C++ 2015 or newer

## Build Information

This project is set up using CMake. A [clean build script](https://github.com/ConficturaStudios/seed-engine/blob/master/scripts/clean_rebuild.py) can be found in the scripts folder. The minimum CMake version is 3.0.

The desired Graphics API must be specified at build time, or the program will not compile. To specify the Graphics API, include one of the following options when running CMake:

    OpenGL    ->  -DGRAPHICS_API:STRING=OPENGL
    Vulkan    ->  -DGRAPHICS_API:STRING=VULKAN
    DirectX   ->  -DGRAPHICS_API:STRING=DIRECTX
    Metal     ->  -DGRAPHICS_API:STRING=METAL

***NOTE:*** *Currently the only option supported in the code is OpenGL. The other options will cause compiler errors.*

## Repository Structure

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

## Dependencies

The following third party dependencies are used:

- [Open Asset Import Library (assimp) v4.1.0](https://github.com/assimp/assimp)<sup>[1]</sup>
- [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [Google Test](https://github.com/google/googletest)
- [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb)

All external dependencies are either included with source, or are linked as a git submodule. GLAD has been configured for C/C++ OpenGL (gl Version 4.6) Core with no extensions. To change this configuration locally, a new set of source files can be created from the [GLAD webservice](https://glad.dav1d.de/).

<sub name="DependencyNote1">[1] - ASSIMP is currently added as a submodule, but no implementation has been created due to concerns about the library size and dependencies. Other options for 3D model handling are currently being evaluated.</sub>

## Contact Information

- [Zachary Harris](mailto:zach@conficturastudios.com)

## License

The Seed Engine is released as open source under the MIT License.

See [`LICENSE`](LICENSE) for the specific terms of the license.