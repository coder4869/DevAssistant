## Release Notes

### Release v1.0

#### 1. Universal
- 1.Create CMake Project by Json Config(Format Refer To `app/conf/project.json`). 
    * Supports platforms: Windows, MacOS, iOS, Android.
    * Use Python and CMake Plugin(Refer to `plugins`)
- 2.Query Environment Var. Supports Windows, MacOS.
- 3.Add spdlog based multi-platforms logger. 
    * Supports platforms: Windows, MacOS, iOS, Android.
- 4.Add `app-auto-start-ability` on operation system start.
    * Supports Windows, MacOS.

#### 2. Windows(Only)
- 1.Add Regedit Get and Set Functions.
- 2.Add TrayIcon Based Hide and Show Window Functions.
- 3.Add RightAction based adapter to any `run_win.bat` for VS2019 and VS2022. e.g. `app/run_win.bat`

#### 3. MacOS(Only)

#### 4. Linux(Only)
