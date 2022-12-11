## contents
- [1. App](#1-app)
- [2. plugins](#2-plugins)
    * [2.1 List](#21-list)
    * [2.2 custom project](#22-custom-project)
    * [2.3 custom extension](#23-custom-plugin)
- [3. Usage](#3-usage)
    * [3.1 Install Help Tools](#31-install-help-tools)
    * [3.2 Create and Open project](#32-create-and-open-project)
    * [3.3 Run project](#33-run-project) 
- [4. Develop Milestone Plan](#4-develop-milestone-plan)

## DevAssistant
DevAssistant is used for improving development efficiency, with good project architecture and multi-platforms compatibility.

The tool is designed with pluggable APP and scripts. The overview is as follows:

- **App** : UI tools for DevAssistant, which is pluggable.
- **plugins** : plugin script modules for App, which supports custom extension. Read [plugins](#2-plugins) for more detail.


### 1. App
UI-Application project for DevAssistant, which is initialize generated by `plugins/project/run.py` and extension is depends on plugins! 

`App` will check and load all the `plugins` modules at start! Read [plugins](#2-plugins) for more detail.


### 2. plugins
`plugins` is identifiable script modules for `App`, which supports [custom extension](#23-custom-plugin).

The developing modules is refer to [List](#21-list).

#### 2.1 List

```txt
plugins:
    |- project: project script modules for DevAssistant.
        |- module: module management for project. Including add sub module for Group.
            |- template: templates for module. 
                |- cmake: module cmake for different module type.
                |- code: code template for module. eg. module header and class.
        |- project: initialize generatation for project, which depends on [module] and [pytool].
            |- build: scipts for build project.
            |- cmake: cmake scripts. [https://github.com/coder4869/cmake-toolchains] for more.
            |- template: templates for project. eg. Project CMakeLists.txt, Group-Module cmake etc.
        |- pytool: universal python tools for project.
        |- project.json: json for init one template project.
        |- run.py: python script for project usage.
    
    |- visual-studio: VS script tools.
        |- vs-cmake: TODO::Designed for converting VS project(module) to CMake project(module).
    
    |- xcode: XCode script tools.
        |- xcodeproj: xcodeproj based CMake project auto fixing ruby script.
```

#### 2.2 custom project
Custom project is depends on `plugins/project/project.json`. The Demo and rules as following:

- `project.json` Demo 

```json
{
    "proj_name" : "DevAssistant",
    "dir_proj" : "../../../app/",
    "dir_codes":[
        {
            "group" : "QtAPP",
            "group_dir" : "/src/app",
            "modules": [
                {
                    "module" : "QtDevAssistant",
                    "option" : "ON",
                    "gen_lib" : "NO"
                }
            ]
        },
        {
            "group" : "QtKit",
            "group_dir" : "/src/qtmodules",
            "modules": [
                {
                    "module" : "QtProject",
                    "option" : "ON",
                    "gen_lib" : "YES"
                },
                {
                    "module" : "QtExample",
                    "option" : "ON",
                    "gen_lib" : "YES"
                },
                {
                    "module" : "QtPractical",
                    "option" : "ON",
                    "gen_lib" : "YES"
                },
                {
                    "module" : "QtCustom",
                    "option" : "ON",
                    "gen_lib" : "YES"
                },
                {
                    "module" : "QtPlan",
                    "option" : "ON",
                    "gen_lib" : "YES"
                },
                {
                    "module" : "QtHelp",
                    "option" : "ON",
                    "gen_lib" : "YES"
                }
            ]
        },
        {
            "group" : "Kit",
            "group_dir" : "/src/kits",
            "modules": [
                {
                    "module" : "DACoreKit",
                    "option" : "ON",
                    "gen_lib" : "YES"
                }
            ]
        },
        {
            "group" : "Lib",
            "group_dir" : "/deps",
            "modules": [
                {
                    "module" : "QtCryptoKit",
                    "option" : "ON"
                }
            ]
        }
    ],
    "dir_help": {
        "scripts" : "scripts", 
        "tools" : "tools", 
        "doc" : "doc"
    }
}
```

- Rules for custom `project.json`:
    * Composition
        * [Required]-`proj_name`: project_name, same to generated `APP_NAME`.
        * [Required]-`dir_proj` : location for generated project.
        * [Required]-`dir_codes`: source codes and libs for project. Generally contains of a list module groups! **For each module group**:
            * [Required]-`group`: group type. **Value is Optional:QtAPP, APP, QtKit, Kit, Lib.**
                * [Optional]-`QtAPP`: application modules for Qt.
                * [Optional]-`APP`: normal application modules without QT. **Only one of `APP` or `QtAPP` is `ON` at once running.**
                * [Optional]-`QtKit`: none application modules for Qt. e.g. `QtSDK` etc.
                * [Optional]-`Kit`: none application normal modules without QT. e.g. none qt `SDK` etc.
                * [Optional]-`Lib`: third-party libs for applications. Including headers and libs.
                * **Note:** each group has one `${last/path/of/group_dir}.cmake`, which is a summary of group modules.
            * [Required]-`group_dir`: group relative dir path for project.
            * [Required]-`modules`: module list with same group type. **For each module**:
                * [Required]-`module`: module name. **`Qt` prefix is required for Qt module.**
                * [Required]-`option`: module is `ON` or `OFF` for application integration.
                * [Optional]-`gen_lib`: default is `NO`, not avaliable for group `Lib` type.
                    * **Note:** When `gen_lib` is `YES`, default is `static` lib, not `shared`.
                * **Note:** each module has one `${module}.cmake`, which is a summary of module resources, create lib with `add_library()` when `gen_lib` is `YES`.
        * [Required]-`dir_help` :
            * [Required]-`scripts`: scripts for application. eg. `build`, `cmake` etc.
            * [Optional]-`tools`: extra tools for application. eg. `tolua++` etc.
            * [Optional]-`doc`  : application documents.
            * [Optional]-`res`  : for none-application resources.
            * [Optional]-`other`: eg. `doc` etc.
    * Keyword Convention:
        * No limition for `Upper-Case` or `Lower-Case`.
        * `Qt` prefix is required for Qt module.

#### 2.3 custom plugin
- **TODO**


### 3. Usage
#### 3.1 Install Help Tools
- **Shared for Windows and MacOS and Linux**
    * [CMake](https://cmake.org/download/)
    * [python3](https://www.python.org/downloads/)
    * [Qt](https://download.qt.io/archive/qt/) 

- **For MacOS Special**
    * XCode

- **For Windows Special**
    * [Visual Studio](https://visualstudio.microsoft.com/zh-hans/vs/older-downloads/) **use VS2019 as default**
    * [qt-vsaddin](https://download.qt.io/archive/vsaddin/)
    * [Visual Assist](https://support.wholetomato.com/default.asp)
        * [Archive of Visual Assist builds and release notes](https://support.wholetomato.com/default.asp?W422)

#### 3.2 Create and Open project
- 1.Write `plugins/project/project.json` according to [custom project](#22-custom-project).

- 2.Generate project by `plugins/project/run.py` script. 
    * run `python3 run.py --type project` in dir `plugins/project`.

- 3.Check options in `${Project_Dir}/CMakeLists.txt`. e.g.
    * `platform options`:
    * `MODULE options`:
    * ...

- 4.Check options in build script(in dir `${Project_Dir}/scripts/build`). E.g.
    * **For Qt Project**：Check Qt-Path in `run_win.bat` and `run_unix.sh`. 
    * **For VS project**：Check vs-bin path and `CMAKE_BUILD_TYPE` in `run_win.bat`.
    * **For XCode project**：Check XCode default config(`XCode->Preferences->Locations->Command Line Tools`) and `CMAKE_BUILD_TYPE`(in `run_unix.sh`).

- 5.Open project by build script(in dir `${Project_Dir}/scripts/build`). e.g. 
    * **For linux and macos**: `bash ${Project_Dir}/scripts/build/run_unix.sh` .
    * **For windows**: run `.\scripts\build\run_win.bat` in `${Project_Dir}` dir.

```s
[dir] Project
    |- [dir] deps(third-party-libs)
        |- [file] deps.cmake
        |- [dir] lib1
            |- [file] lib1.cmake
            |- [file] xxx.h/xxx.a
        |- [dir] lib2
            |- [file] lib2.cmake
            |- [file] xxx.h/xxx.a

    |-[dir] src
        |- [dir] group1
            |- [file] group1.cmake

            |- [dir] module1
                |- [file] module1.cmake
                |- [file] module1.h
                |- [file] xxx.h/xxx.cpp
                |- [dir] Forms  # Qt ui Forms
                |- [dir] Res    # Module Resources
                |- [dir] pimp   # Private Implement
                |- ...
            
            |- [dir] module2 
                |- ...

        |- [dir] group2
            |- ...

    |- [dir] scripts
        |- [dir] build
            |- [file] run_arm.sh
            |- [file] run_unix.sh
            |- [file] run_win.bat
        |- [dir] cmake
        |- [file] project.json  # project init json

    |- ...(others)
    |- [file] CMakeLists.txt
```

#### 3.3 Run project
- **For VS project**：
    * Select App project and  `Set As StartUp Project` in vs.
- **For XCode project**：
    * Select App project scheme and run direct.


### 4. Develop Milestone Plan
- Short Term
    * `App` develop.
    * CMake supports for other platforms.
    * module add class script function.
- Medium Term:
    * VS project(module) to CMake project(module) converting scripts.
    * Module auto migrate scripts.
- Long Term:
    * dev some easy integration kits for online download.
    * module downloads as needs!
