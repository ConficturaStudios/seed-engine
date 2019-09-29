// test_mesh.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Mesh.hpp"

TEST(MeshTest, GeneralTest) {
    using namespace seedengine;
    
}

/*

TEST(MeshTest, MeshFileCubeCreate) {
    using namespace seedengine;

    string path = CORE_PATH("data/assets/models/primatives/cube.mesh");

    std::vector<float> positions = {
        -1, -1,  1,
         1, -1,  1,
        -1,  1,  1,
         1,  1,  1,
        -1,  1, -1,
         1,  1, -1,
        -1, -1, -1,
         1, -1, -1
    };

    std::vector<float> normals = {
         0,  0,  1,
         0,  1,  0,
         0,  0, -1,
         0, -1,  0,
         1,  0,  0,
        -1,  0,  0
    };

    std::vector<float> uvs = {
        0, 0,
        0, 1,
        1, 0,
        1, 1
    };

    std::vector<float> colors = {
        0, 1, 1, 1,
        0, 1, 0, 1,
        1, 1, 0, 1,
        1, 1, 1, 1,
    };

    std::vector<uint32_t> vertices = {
        // POS, NOR, UV, COL
        // Face 1
        0, 0, 0, 0,
        1, 0, 2, 2,
        2, 0, 1, 1,
        3, 0, 3, 3,
        // Face 2
        2, 1, 0, 0,
        3, 1, 2, 2,
        4, 1, 1, 1,
        5, 1, 3, 3,
        // Face 3
        4, 2, 0, 0,
        5, 2, 2, 2,
        6, 2, 1, 1,
        8, 2, 3, 3,
        // Face 4
        6, 3, 0, 0,
        7, 3, 2, 2,
        0, 3, 1, 1,
        1, 3, 3, 3,
        // Face 5
        1, 4, 0, 0,
        7, 4, 2, 2,
        3, 4, 1, 1,
        5, 4, 3, 3,
        // Face 6
        6, 5, 0, 0,
        0, 5, 2, 2,
        4, 5, 1, 1,
        2, 5, 3, 3
    };

    std::vector<std::vector<uint32_t>> smoothing_groups = {
        {
            0, 1, 2,
            2, 1, 3
        },
        {
            4, 5, 6,
            6, 5, 7
        },
        {
             8, 9, 10,
            10, 9, 11
        },
        {
            12, 13, 14,
            14, 13, 15
        },
        {
            16, 17, 18,
            18, 17, 19
        },
        {
            20, 21, 22,
            22, 21, 23
        }
    };

    uint32_t uvs_per_vertex = 1;
    uint32_t colors_per_vertex = 1;

    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::trunc);

    uint32_t group_count = htonl(smoothing_groups.size());
    uint32_t position_count = htonl(positions.size() / 3);
    uint32_t normal_count = htonl(normals.size() / 3);
    uint32_t uv_count = htonl(uvs.size() / 2);
    uint32_t color_count = htonl(colors.size() / 4);
    uint32_t bone_weight_count = 0;
    uint32_t morph_count = 0;

    uint32_t vertex_count = htonl(vertices.size() / (2 + uvs_per_vertex + colors_per_vertex));


    uint16_t bone_count = 0;

    uint8_t uv_c_counts = ((uvs_per_vertex & 0b111) << 5) | ((colors_per_vertex & 0b111) << 2);
    uint8_t empty_8 = 0;

    file.write(reinterpret_cast<char*>(&group_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&position_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&normal_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&uv_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&color_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&bone_weight_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&morph_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&vertex_count), sizeof(uint32_t));

    file.write(reinterpret_cast<char*>(&bone_count), sizeof(uint16_t));

    file.write(reinterpret_cast<char*>(&uv_c_counts), sizeof(uint8_t));
    file.write(reinterpret_cast<char*>(&empty_8), sizeof(uint8_t));

    for (float f : positions) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : normals) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : uvs) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : colors) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }

    for (uint32_t i : vertices) {
        uint32_t ni = htonl(i);
        file.write(reinterpret_cast<char*>(&ni), sizeof(uint32_t));
    }

    for (std::vector<uint32_t> g : smoothing_groups) {
        uint32_t size = htonl(g.size() / 3);
        file.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
        for (uint32_t i : g) {
            uint32_t ni = htonl(i);
            file.write(reinterpret_cast<char*>(&ni), sizeof(uint32_t));
        }
    }
}

TEST(MeshTest, MeshFileQuadCreate) {
    using namespace seedengine;

    string path = CORE_PATH("data/assets/models/primatives/quad.mesh");

    std::vector<float> positions = {
        -1,  1,  0,
        -1, -1,  0,
         1, -1,  0,
         1,  1,  0
    };

    std::vector<float> normals = {
         0,  0,  1
    };

    std::vector<float> uvs = {
        0, 0,
        0, 1,
        1, 0,
        1, 1
    };

    std::vector<float> colors = {
        0, 1, 1, 1,
        0, 1, 0, 1,
        1, 1, 0, 1,
        1, 1, 1, 1,
    };

    std::vector<uint32_t> vertices = {
        // POS, NOR, UV, COL
        0, 0, 0, 0,
        1, 0, 1, 1,
        2, 0, 2, 2,
        3, 0, 3, 3
    };

    std::vector<std::vector<uint32_t>> smoothing_groups = {
        {
            0, 1, 3,
            3, 1, 2
        }
    };

    uint32_t uvs_per_vertex = 1;
    uint32_t colors_per_vertex = 1;

    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::trunc);

    uint32_t group_count = htonl(smoothing_groups.size());
    uint32_t position_count = htonl(positions.size() / 3);
    uint32_t normal_count = htonl(normals.size() / 3);
    uint32_t uv_count = htonl(uvs.size() / 2);
    uint32_t color_count = htonl(colors.size() / 4);
    uint32_t bone_weight_count = 0;
    uint32_t morph_count = 0;

    uint32_t vertex_count = htonl(vertices.size() / (2 + uvs_per_vertex + colors_per_vertex));


    uint16_t bone_count = 0;

    uint8_t uv_c_counts = ((uvs_per_vertex & 0b111) << 5) | ((colors_per_vertex & 0b111) << 2);
    uint8_t empty_8 = 0;

    file.write(reinterpret_cast<char*>(&group_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&position_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&normal_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&uv_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&color_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&bone_weight_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&morph_count), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(&vertex_count), sizeof(uint32_t));

    file.write(reinterpret_cast<char*>(&bone_count), sizeof(uint16_t));

    file.write(reinterpret_cast<char*>(&uv_c_counts), sizeof(uint8_t));
    file.write(reinterpret_cast<char*>(&empty_8), sizeof(uint8_t));

    for (float f : positions) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : normals) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : uvs) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }
    for (float f : colors) {
        uint32_t nf = htonf(f);
        file.write(reinterpret_cast<char*>(&nf), sizeof(uint32_t));
    }

    for (uint32_t i : vertices) {
        uint32_t ni = htonl(i);
        file.write(reinterpret_cast<char*>(&ni), sizeof(uint32_t));
    }

    for (std::vector<uint32_t> g : smoothing_groups) {
        uint32_t size = htonl(g.size() / 3);
        file.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
        for (uint32_t i : g) {
            uint32_t ni = htonl(i);
            file.write(reinterpret_cast<char*>(&ni), sizeof(uint32_t));
        }
    }
}

*/