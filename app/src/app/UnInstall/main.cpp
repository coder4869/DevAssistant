// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include <stdio.h>

#include <CUtils/logger.h>
#include <COSEnv/CERightAction.h>

int main(int argc, char *argv[])
{
    CE::RightAction::DelAction("DevAssist", CE::RightAction::Mode::FIX_SUFFIX, "batfile");
    LOGI("CE::RightAction::DelAction()");
    return 0;
}
