## Android 
- https://developer.android.google.cn/tools
- address sanitizer
    * https://clang.llvm.org/docs/AddressSanitizer.html
    * https://github.com/google/sanitizers
    * https://github.com/google/sanitizers/wiki/AddressSanitizerOnAndroid/01f8df1ac1a447a8475cdfcb03e8b13140042dbd
    * https://source.android.google.cn/docs/security/test/asan?hl=zh-cn

### Java
- class2java: jad, jd-gui, procyon-decompiler
    * `procyon-decompiler -jar <xx.jar> -o out_dir`

### Gradle
- 多版本jdk，需要保证环境变量中的 JAVA_HOME 与 Android Studio 选择的版本一致，否则在命令行运行 `./gradlew task` 时会失败。
    * 常见提示：Could not resolve all files for configuration ':classpath': 
    * jdk 版本不兼容：

- Plugin
    * [Developing Custom Gradle Plugins](https://docs.gradle.org/7.2/userguide/custom_plugins.html)
    * [https://plugins.gradle.org](https://plugins.gradle.org/u/coder4869?tab=publishing)
        * Copy the following to your `HOME_DIR/.gradle/gradle.properties (~/.gradle/gradle.properties)` file:
            * `gradle.publish.key=g2fXs50kSGudoenTcYTdOYvdOJBCnUKt`
            * `gradle.publish.secret=yAluquvwuM0y4YIjPM8GPrij1AenuhOy`

- Tasks
    *  `./gradlew task --all`
    * [Exec](https:-docs.gradle.org/current/dsl/org.gradle.api.tasks.Exec.html)
    * Refresh depends: `./gradlew app:mergeDebugNativeLibs --refresh-dependencies`
    * Task depends list: `./gradlew app:mergeDebugNativeLibs --dry-run`

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