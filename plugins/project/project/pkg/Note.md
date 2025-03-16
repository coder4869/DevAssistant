## windows
- nsis: https://sourceforge.net/projects/nsis/
    * 安装 nsis-v3.09.exe，右键执行 pkg-win-nsis.nsi 脚本 (Compile NSIS Scripts)
    * 问题：
        * 现象：中文执行nsi脚本时，会出现乱码导致的打包失败问题
        * 方案：配置nsis安装目录到PATH环境变量，双击 pkg-win-nsis.bat 脚本