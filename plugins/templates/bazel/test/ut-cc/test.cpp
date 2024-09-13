// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include <stdio.h>
#include <gtest/gtest.h>
#include <string>

#include "config.h"

int main(int argc, char **argv) {
    printf("test %s \n", __FUNCTION__);
    
    // parse self defined parameters for pre-setting
    for (int idx=1; idx<argc; idx=idx+2) {
        if (std::string(argv[idx]) == "--platform") {
            set_platform(static_cast<Platform>(atoi(argv[idx+1])));
        }
    }

    // run gtest
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
