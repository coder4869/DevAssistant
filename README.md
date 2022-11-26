## DevAssistant
开发助手用于提高开发工作效率。

### 1. DA_App
基础APP，包括：基本UI框架、配置解析、插件调用等。

### 2. plugins
可被DA_App识别的扩展插件，插件自定义规则和功能列表如下：

#### 2.1 自定义规则

#### 2.2 插件列表
- core：核心基础插件。
    * `pytool`：基础Python脚本。
    * `project`：工程项目创建。包含:CMake修正
    * `module`：工程模块管理。
    * `config.json`：工程创建配置文件。
    * `core.py`：上述模块使用示例文档。
- xcode：xcode相关的开发工具插件。
    * `xcodeproj`：基于`xcodeproj`的CMake工程自动化修正脚本。
- visual-studio：VS相关的开发工具插件。
    * `vs-cmake`：vs工程转CMake工程组件。

```s
config.json 相关关键字约定，不限制大小写:
1. group 
 类型选项：QtAPP、APP、QtKit、Kit、Lib等。模块分组以此为类型依据。
 有Qt依赖的模块，必须使用Qt前缀；无Qt依赖的，不建议开启。
 APP 后缀为可执行的应用程序标识，对于APP的模块，同一时间只能设置一个的 option 选项为ON，其余为OFF。
 Kit 通常作为无应用程序的SDK标识字段，Lib为第三方依赖库的标识字段。
2. module 
 名称：有Qt依赖的模块，必须使用Qt前缀；无Qt依赖的，不建议开启。
```

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

### 3. 迭代规划
- 近期
    * DA_App 的本地版本。内置插件的核心功能有：
        * 基于CMake的工程创建。
        * lib库创建
        * XCode工程生成
- 中期
    * 支持网络交互能力，支持插件的按需配置、下载。