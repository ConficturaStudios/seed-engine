// test_asset.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Asset.hpp"
#include "Mesh.hpp"
#include "Image.hpp"

TEST(AssetTest, ImageRequestTest) {
    using namespace seedengine;

    EXPECT_NE(AssetLibrary<Image>::load(CORE_PATH("data/confictura_flame_icon.png")), nullptr);

    auto tex = AssetLibrary<Image>::request(CORE_PATH("data/confictura_flame_icon.png"));
    auto tex2 = AssetLibrary<Image>::request(CORE_PATH("data/test_fail_x.png"));

    EXPECT_NE(tex, nullptr);
    EXPECT_EQ(tex2, nullptr);

}

TEST(AssetTest, ImageRequestTest2) {
    using namespace seedengine;

    EXPECT_NE(AssetLibrary<Image>::load(CORE_PATH("data/confictura_flame_icon.png")), nullptr);

    auto tex = AssetLibrary<Image>::request(CORE_PATH("data/confictura_flame_icon.png"));
    auto tex2 = AssetLibrary<Image>::request(CORE_PATH("data/confictura_flame_icon.png"));

    EXPECT_NE(tex, nullptr);
    EXPECT_NE(tex2, nullptr);

}

TEST(AssetTest, LoadTest) {
    using namespace seedengine;

    EXPECT_NE(AssetLibrary<Image>::load(CORE_PATH("data/confictura_flame_icon.png")), nullptr);
    EXPECT_NE(AssetLibrary<Image>::load(CORE_PATH("data/confictura_flame_icon.png")), nullptr);

}