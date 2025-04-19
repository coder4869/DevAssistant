## windows
- nsis: https://sourceforge.net/projects/nsis/
    * 安装 nsis-v3.11.exe，右键执行 pkg-win-nsis.nsi 脚本 (Compile NSIS Scripts)
    * 运行时库：
        * 保持与打包版本VS一致，`vs-env.bat` 脚本可以自动获取 VS2019 和 VS2022 的 vc_redist
    * 问题：
        * 现象：中文执行nsi脚本时，会出现乱码导致的打包失败问题
        * 方案：配置nsis安装目录到PATH环境变量，双击 `pkg-win-nsis.bat` 脚本
        * NSIS：插件库 https://nsis.sourceforge.io/Category:Plugins
        * 插件拷贝到：nsis安装目录/Plugins 下
    * Ref
        * https://github.com/Chadwuo/HHSoftwarePack
        * https://blog.csdn.net/zhichaosong/article/details/106275151