## DevAssistant
DevAssistant is used for improving development efficiency, with good project architecture and multi-platforms compatibility.

The tool is designed with pluggable APP and scripts. The overview is as follows:

- **DA_App** : UI tools for DevAssistant, which is pluggable.
- **plugins** : plugin script modules for DA_App, which supports custom extension. Read [plugins](#2-plugins) for more detail.


### 1. DA_App
UI-Application project for DevAssistant, which is initialize generated by `plugins/core/core.py` and extension is depends on plugins! 

`DA_App` will check and load all the `plugins` modules at start! Read [plugins](#2-plugins) for more detail.


### 2. plugins
`plugins` is identifiable script modules for `DA_App`, which supports [custom extension](#23-custom-plugin).

The developing modules is refer to [List](#21-list).

#### 2.1 List

```txt
plugins:
    |- core: core script modules for DevAssistant.
        |- module: module management for project. Including add sub module for Group.
        |- project: initialize generatation for project, which depends on [module] and [pytool].
        |- pytool: universal python tools for core.
        |- config.json: demo json for init one template project.
        |- core.py: demo python script for core usage.
    
    |- visual-studio: VS script tools.
        |- vs-cmake: TODO::Designed for converting VS project(module) to CMake project(module).
    
    |- xcode: XCode script tools.
        |- xcodeproj: xcodeproj based CMake project auto fixing ruby script.
```

#### 2.2 custom project
Custom project is depends on `plugins/core/config.json`. The Demo and rules as following:

- `config.json` Demo 

```json
{
    "proj_name" : "DevKits",
    "dir_proj" : "../../../DevKits",
    "dir_codes":[
        {
            "group" : "QtAPP",          
            "group_dir" : "/src/app",
            "modules": [
                {
                    "module" : "QtDevAPP",  
                    "option" : "ON"
                },
                {
                    "module" : "QtCryptoAPP",
                    "option" : "OFF"
                }
            ]
        },
        {
            "group" : "QtKit",
            "group_dir" : "/src/qtkits",
            "modules": [
                {
                    "module" : "QtCryptoKit",
                    "option" : "ON"
                }
            ]
        },
        {
            "group" : "Kit",
            "group_dir" : "/src/kits",
            "modules": [
                {
                    "module" : "CCoreKit",
                    "option" : "ON"
                },
                {
                    "module" : "CConcurrencyKit",
                    "option" : "ON"
                },
                {
                    "module" : "CCryptoKit",
                    "option" : "ON"
                }
            ]
        },
        {
            "group" : "Lib",
            "group_dir" : "/deps",
            "modules": [
                {
                    "module" : "Boost",
                    "option" : "OFF"
                }
            ]
        }
    ],
    "dir_help": {
        "scripts" : "scripts", 
        "tools" : "tools", 
        "res" : "res"
    }
}
```

- Rules for custom `config.json`:
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
            * [Required]-`group_dir`: group relative dir path for project.
            * [Required]-`modules`: module list with same group type. **For each module**:
                * [Required]-`module`: module name. **`Qt` prefix is required for Qt module.**
                * [Required]-`option`: module is `ON` or `OFF` for application integration.
        * [Required]-`dir_help` :
            * [Required]-`scripts`: scripts for application. eg. `build`, `cmake` etc.
            * [Optional]-`tools`: extra tools for application. eg. `tolua++` etc.
            * [Optional]-`res`  : for none-application resources.
            * [Optional]-`other`: eg. `doc` etc.
    * Keyword Convention:
        * No limition for `Upper-Case` or `Lower-Case`.
        * `Qt` prefix is required for Qt module.

#### 2.3 custom plugin
- **TODO**


### 3. Develop Milestone Plan
- Short Term
    * `DA_App` develop.
    * CMake supports for other platforms.
    * module add class script function.
- Medium Term:
    * VS project(module) to CMake project(module) converting scripts.
    * Module auto migrate scripts.
- Long Term:
    * dev some easy integration kits for online download.
    * module downloads as needs!