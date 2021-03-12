# Seed Engine
[![License](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

An open source game engine that supports both 3D and 2D games. The engine is designed with flexibility and extensibility in mind.

## Current Project Status

[![Linux Build Status](https://travis-ci.org/ConficturaStudios/seed-engine.svg?branch=master)](https://travis-ci.org/ConficturaStudios/seed-engine) 
[![Windows Build status](https://ci.appveyor.com/api/projects/status/n7te2x6t1ie888tv?svg=true)](https://ci.appveyor.com/project/ConficturaStudios/seed-engine)
[![Coverage Status](https://coveralls.io/repos/github/ConficturaStudios/seed-engine/badge.svg?branch=master)](https://coveralls.io/github/ConficturaStudios/seed-engine?branch=master)

***NOTE:*** *Coverage reports and issue tracking are still being set up, and will be available at a later time.*

## Documentation

Documentation for this project is generated using [Doxygen](https://www.doxygen.org) and will be hosted here on github as well as on the [Confictura Studios website](https://www.conficturastudios.com).

## Features

As an application still in the early phases of development, most features still need to be implemented. To request a feature, please add a [new issue](https://github.com/ConficturaStudios/seed-engine/issues/new) detailing the desired feature. A changelog and feature tracking system are currently in the works.

### Planned Features

The following are features planned for v1.0.0:

- ECS based arcitecture using [EnTT](https://github.com/skypjack/entt)
- Deferred and Forward Rendering options
- Multiple Graphics APIs (see [Graphics](#Graphics))
- Mobile platform support (see [Platforms](#Platforms))
- C# scripting using Mono
- Generation of procedural assets
- 3D Environment Editor
- 2D Tilemap Editor

Several [additional features](#Features-Under-Consideration) are also under consideration, but have been deferred for a later decision.

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

### Features Under Consideration

The following features are under consideration for future iterations of the engine.

- Console support
- HLSL as a cross-platform shader language using [Microsoft's Shader Conductor](https://github.com/Microsoft/ShaderConductor)

For more information about planned features and this project's roadmap, visit our Trello* page.

<sub name = "FeaturesNote1">* - *Trello board not publicly available at the time of this commit*</sub>

## Requirements

Seed Engine is built using the C++17 standard. The following requirements represent the oldest configurations that have been tested successfully. Earlier versions of these tools may still successfully build the project, but have not yet been tested.

***Note:*** *GCC compilers older than GCC 4.9.0 are not supported due to a lack of implementation for std::regex.*

### Linux Requirements
- GCC/G++ 6.0 or newer
- Clang 6.0 or newer
### Mac OS X Requirements
- Mac OS X v10.11 El Capitan or newer
- XCode Developer Tools 8.0 or newer
### Windows Requirements
- Microsoft Visual C++ 2015 or newer

## Build Information

A [utility script](https://github.com/ConficturaStudios/seed-engine/blob/master/Scripts/Tools.py) with build automation and other command line utilities can be found in the scripts folder.

From the project root directory run

    python -B Scripts/Tools.py build -c

to build the project for the first time or perform a clean build (erasing all old build files and outputs). Subsequent builds can be generated by running

    python -B Scripts/Tools.py build

and more build options can be seen by running

    python -B Scripts/Tools.py build -h


Binary outputs from builds are placed into `Engine/Bin/Debug/` or `Engine/Bin/Release/` depending on the build configuration used. By default, both build modes are built along with their corresponding test suites. 

This project is set up using CMake 3.0, with most module CMakeLists.txt files being procedurally generated.

***NOTE:*** *Currently the only graphics API supported in the code is OpenGL. The other options will cause compiler errors.*

## Repository Structure

The engine source code can be found in [`Engine/Source/`](https://github.com/ConficturaStudios/seed-engine/tree/master/Engine/Source). The source code is broken up into serveral application domains:

    /Dev             Developer features that are experimental in nature.
    /Editor          Editor specific code.
    /Extern          External dependencies.
    /Runtime         The runtime code used by the engine. This is the foundation of the engine and is included in shipped projects.
    /Tools           Development tools built on top of or as part of the engine.

Within these domains, modules exist and can be added containing encapsulated behaviors. These modules should be added using the [utility script](https://github.com/ConficturaStudios/seed-engine/blob/master/Scripts/Tools.py) with **python -B Scripts/Tools.py add module ...**

You can run **python -B Scripts/Tools.py -h** for more information about the development utility.

## Dependencies

The following third party dependencies are used:

- [Open Asset Import Library (assimp) v4.1.0](https://github.com/assimp/assimp) <sup>[1]</sup>
- [EnTT](https://github.com/skypjack/entt)
- [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [Google Test](https://github.com/google/googletest)
- [spdlog](https://github.com/gabime/spdlog)
- [stb](https://github.com/nothings/stb)
- [ImGUI](https://github.com/ocornut/imgui)

All external dependencies are either included with source, or are linked as a git submodule. GLAD has been configured for C/C++ OpenGL (gl Version 4.6) Core with no extensions. To change this configuration locally, a new set of source files can be created from the [GLAD webservice](https://glad.dav1d.de/).

<sub name="DependencyNote1">[1] - ASSIMP is currently added as a submodule, but no implementation has been created due to concerns about the library size and dependencies. Other options for 3D model handling are currently being evaluated.</sub>

## Contact Information

- [Zachary Harris](mailto:zach@conficturastudios.com)

## License

The Seed Engine is released as open source under the MIT License.

See [`LICENSE`](LICENSE) for the specific terms of the license.