## Android 
- https://developer.android.google.cn/tools

### Java
- class2java: jad, jd-gui, procyon-decompiler
    * `procyon-decompiler -jar <xx.jar> -o out_dir`

### Gradle
- Plugin
    * [Developing Custom Gradle Plugins](https://docs.gradle.org/7.2/userguide/custom_plugins.html)

- Tasks
    *  `./gradlew task --all`
    * [Exec](https:-docs.gradle.org/current/dsl/org.gradle.api.tasks.Exec.html)

- Depends
    * [native](https:developer.android.com/build/native-dependencies) 
    * [prefab与插件版本](https://blog.csdn.net/weixin_45011939/article/details/128256061)
    * 下载 build.gradle dependencies
        * `./gradlew app:mergeDebugResources`
- aar merge
    * [合并AAR踩坑之旅（fat-aar）](https://www.jianshu.com/p/8f7e32015836)
    * [Github:fat-aar-gradle](https://github.com/wj401625836/fat-aar-gradle)

### maven
- [Maven构建项目](https://blog.csdn.net/Coastlise/article/details/134758646)

```sh
# Env
brew install maven # path : /opt/homebrew/Cellar/maven
brew install openjdk
# install vscode and plugin `Maven for Java (Microsoft)`, restart vscode

# Project
# Create dir in vscode and run following cmd in vscode terminal in dir
mvn archetype:generate -DgorupId=com.example -DartifactId=my-maven
```