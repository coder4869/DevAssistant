## Release Notes

### Release v1.1
#### 1. Windows
- New features
    * 1.pkg-exe: add nsis based exe package scripts.
- Optimize
    * 1.Install setting use nsis-pkg-scripts replace C++ code.
    * 2.`run_win.bat`: auto detect installed visual studio, replace c++ code update `run_win.bat`.
    * 3.build output organization(bin64, lib, logs etc).

#### 2. Linux
- New features
    * 1.logger: spdlog add support for ubuntu, centos, openKylin2.0.
    * 2.cmake: add qt support for ubuntu, centos, openKylin2.0.
- Optimize
    * 1.fix app bugs for ubuntu, centos, openKylin2.0.


### Release v1.0

#### 1. Universal
- 1.Create CMake Project by Json Config(Format Refer To `app/conf/project.json`). 
    * Supports platforms: Windows, MacOS, iOS, Android.
    * Use Python and CMake Plugin(Refer to `plugins`)
- 2.Logger: Add spdlog based multi-platforms logger. 
    * Supports platforms: Windows, MacOS, iOS, Android.

#### 2. Windows(Only)
- 1.Query Environment Var.
- 2.Add Regedit Get and Set Functions.
- 3.Add TrayIcon Based Hide and Show Window Functions.
- 4.Add RightAction based adapter to any `run_win.bat` for VS2019 and VS2022. e.g. `app/run_win.bat`
- 5.Add `app-auto-start-ability` on operation system start.

#### 3. MacOS(Only)
- 1.Query Environment Var.

#### 4. Linux(Only)
