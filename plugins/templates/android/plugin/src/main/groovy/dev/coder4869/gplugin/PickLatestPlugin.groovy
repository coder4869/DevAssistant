// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// Usage: in target project add following line 
package dev.coder4869.gplugin

import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.Task
import org.gradle.api.GradleException
import org.gradle.api.artifacts.*

import java.nio.file.Files
import java.nio.file.Paths
import java.nio.file.StandardCopyOption

class GradleFile {
    private static String TAG = "GradleFile";
    public static void createDir(String path) {
        File folder = new File(path)
        if (!folder.exists()) {
            folder.mkdirs();
            println("${TAG}: Folder ${folder.absolutePath} created!")
        } else {
            println("${TAG}: Folder ${folder.absolutePath} already exist!")
        }
    }

    /// @param dstDir   dir path, end with /
    public static void copyFiles(HashSet<File> fileList, String dstDir) {
        if (fileList == null || dstDir == null) {
            println("${TAG}: copyFiles invalid parameter !")
            return
        }

        println("${TAG}: copyFiles begin !")
        createDir(dstDir)

        fileList.forEach { File f ->
            String srcPath = f.toString()
            String fullName = f.getName()
            println("${TAG}: srcPath is ${srcPath}; fullName is ${fullName}")

            try {
                Files.copy(Paths.get(srcPath), Paths.get(dstDir + fullName), StandardCopyOption.REPLACE_EXISTING)
                System.out.println("${TAG}: File copy succeed")
            } catch (IOException exc) {
                System.err.println("${TAG}: File copy error: " + exc.getMessage())
            }
        }
        println("${TAG}: copyFiles end !")
    }

    // @return unziped aar pathes
    public static HashSet<String> unzipArchives(Project project, HashSet<File> fileList, String dstDir, Boolean isCopy) {
        if (project == null || fileList == null || dstDir == null) {
            println("${TAG}: unzipArchives invalid parameter !")
            return new HashSet<String>()
        }

        println("${TAG}: unzipArchives begin !")
        createDir(dstDir)

        HashSet<String> dirList = new HashSet<String>()
        File record = new File(dstDir + '/path_list.txt')
        record.write(isCopy ? "Copy" : "NoCopy") // clear text content

        fileList.forEach { File f ->
            String srcPath = f.toString()
            String fullName = f.getName()
            String baseName = fullName.substring(0, fullName.length() - 4) // remove .jar or .aar

            // unzip archive
            project.exec {
                commandLine 'unzip', '-o', srcPath, '-d', dstDir + baseName
                println("unzip ${srcPath} to ${dstDir +  baseName}")
            }

            // copy archive from srcPath to dstDir and save "archive path + unzip dir"
            try {
                if (isCopy) {
                    Files.copy(Paths.get(srcPath), Paths.get(dstDir + fullName), StandardCopyOption.REPLACE_EXISTING)
                    System.out.println("${TAG}: File copy succeed")
                    record.append("\n" + dstDir + fullName)
                }
                record.append("\n" + srcPath)
                record.append("\n" + dstDir + baseName)
                dirList.add(dstDir + baseName)
            } catch (IOException exc) {
                System.err.println("${TAG}: File copy error: " + exc.getMessage())
            }
        }

        println("${TAG}: unzipArchives end !")
        return dirList
    }

    public static boolean pathContainsKeys(String path, HashSet<String> keys) {
        if (keys == null || keys.size() == 0) {
            return false;
        }

        for (int idx=0; idx<keys.size(); idx++) {
            if (path.contains(keys[idx])) {
                return true;
            }
        }
        return false;
    }
}

class GradleTransform {
    private static String TAG = "GradleTransform";
    public static Project project;

    private static String getTransformRootDir(int num = 3) {
        return project.gradle.properties["gradleUserHomeDir"].toString() + "/caches/transforms-${num}"
    }

    /// @param keys     keys for checking file path
    /// @param suffix   transforms files' suffix. e.g. ['.so', '.bin']
    public static ArrayList<String> getTransformFileList(HashSet<String> keys, HashSet<String> suffix = []) {
        println("${TAG}: getTransformFileList begin !")
        ArrayList<String> fileList2 = getTransformFileList(getTransformRootDir(2), keys, suffix)
        ArrayList<String> fileList3 = getTransformFileList(getTransformRootDir(3), keys, suffix)
        ArrayList<String> fileList4 = getTransformFileList(getTransformRootDir(4), keys, suffix)
        fileList2.addAll(fileList3)
        fileList2.addAll(fileList4)
        println("${TAG}: getTransformFileList end !")
        return fileList2
    }

    /// @param suffix transforms files‘ suffix. e.g. ['.so', '.bin']
    public static ArrayList<String> getTransformFileList(String transRootDir, HashSet<String> keys, HashSet<String> suffix = []) {
        if (transRootDir == null || keys == null) {
            println("${TAG}: getTransformFileList invalid parameter !")
            return new ArrayList<String>();
        }
        println("${TAG}: getTransformFileList begin. transformDir is: " + transRootDir)

        ArrayList<String> fileList = new ArrayList<String>();
        if (suffix.size() == 0) {
            project.fileTree(transRootDir).forEach { File f ->
                String fpath = f.toString();
                if (GradleFile.pathContainsKeys(fpath, keys)) {
                    println("${TAG}: add file: " + fpath)
                    fileList.add(fpath)
                }
            }
        } else {
            project.fileTree(transRootDir).forEach { File f ->
                String fpath = f.toString();
                for (final String sf in suffix) {
                    if (fpath.endsWith(sf) && GradleFile.pathContainsKeys(fpath, keys)) {
                        println("${TAG}: add file: " + fpath)
                        fileList.add(fpath)
                        break
                    }
                }
            }
        }

        println("${TAG}: getTransformFileList end. Found ${fileList.size()} file for suffixs : " + suffix.toString())
        return fileList
    }

    /// @param suffix   search file suffix. e.g. .so or .jar
    /// @param keys     keys for checking file path
    public static HashSet<String> getTransformSubDirs(String suffix, HashSet<String> keys) {
        println("${TAG}: getTransformSubDirs begin !")
        HashSet<String> dirList2 = getTransformSubDirs(getTransformRootDir(2), suffix, keys)
        HashSet<String> dirList3 = getTransformSubDirs(getTransformRootDir(3), suffix, keys)
        HashSet<String> dirList4 = getTransformSubDirs(getTransformRootDir(4), suffix, keys)
        dirList2.addAll(dirList3)
        dirList2.addAll(dirList4)
        println("${TAG}: getTransformSubDirs end !")
        return dirList2
    }

    /// @param suffix   search file suffix. e.g. .so or .jar
    /// @param keys     keys for checking file path
    public static HashSet<String> getTransformSubDirs(String transRootDir, String suffix, HashSet<String> keys) {
        if (transRootDir == null || suffix == null || keys == null) {
            println("${TAG}: getTransformSubDirs invalid parameter !")
            return new HashSet<String>();
        }
        println("${TAG}: getTransformSubDirs begin. transformDir is: " + transRootDir)

        HashSet<String> dirList = new HashSet<String>()
        if (suffix.equals('.so')) {
            project.fileTree(transRootDir).forEach {
                if (it.toString().endsWith('.so')) {
                    String soPath = it.toString()
                    if (soPath.contains("/jni/arm64-v8a") && GradleFile.pathContainsKeys(soPath, keys)) {
                        String depsDir = soPath.substring(0, soPath.indexOf("/jni/arm64-v8a"))
                        int size = dirList.size()
                        dirList.add(depsDir)
                        if (dirList.size() > size) {
                            println("add dir : " + depsDir)
                        }
                    }
                }
            }
        } else if (suffix.equals('.jar')) {
            project.fileTree(transRootDir).forEach {
                if (it.toString().endsWith('.jar')) {
                    String jarPath = it.toString()
                    if (jarPath.contains("/jars/classes.jar") && GradleFile.pathContainsKeys(jarPath, keys)) {
                        String depsDir = jarPath.substring(0, jarPath.indexOf("/jars/classes.jar"))
                        int size = dirList.size()
                        dirList.add(depsDir)
                        if (dirList.size() > size) {
                            println("add dir : " + depsDir)
                        }
                    }
                }
            }
        }

        println("${TAG}: getTransformSubDirs end. Found ${dirList.size()} directories ! ")
        return dirList
    }
}

class GradleDepends {
    private static String TAG = "GradleDepends";
    public static Project project;

    public static void clearDir(String path) {
        project.delete(path)
    }

    public static String getDependsDir() {
        return project.gradle.properties["gradleUserHomeDir"].toString() + "/caches/modules-2/files-2.1";
    }

    // todo check keys
    public static HashSet<File> getConfigurationDependencies(Configuration cfg, HashSet<String> keys,
                                                             String suffix = '.aar', boolean isAll = false) {
        println("${TAG}: getConfigurationDependencies ${cfg.getIncoming().toString()}")
        println("${TAG}: getConfigurationDependencies begin !")

        HashSet<File> depends = []
        Configuration cfgCopy = cfg.copyRecursive()
        try {
            cfgCopy.setCanBeResolved(true)

            if (isAll) {
                for (final File f in cfgCopy.getFiles()) {
                    if (f.toString().endsWith(suffix)) {
                        int size = depends.size()
                        depends.add(f)
                        if (depends.size() > size) {
                            println("${TAG}: add ${f.toString()}")
                        }
                    }
                }
            } else { // Only first level
                for (final Dependency dep in cfgCopy.getDependencies()) {
                    def dep_str = dep.group + '/' + dep.name + '/' + dep.version
                    println dep_str

                    for (final File f in cfgCopy.getFiles()) {
                        if (f.toString().contains(dep_str)) {
                            int size = depends.size()
                            depends.add(f)
                            if (depends.size() > size) {
                                println("${TAG}: add ${f.toString()}")
                            }
                        }
                    }
                }
            }
        } catch (Exception exc) {
            System.err.println("${TAG}: error = " + exc.getMessage())
        }
        println("${TAG}: getConfigurationDependencies end !")
        return depends
    }

    // getTypedDependencies([], "api")
    // getTypedDependencies([], "implementation")
    /// @param type target type in dependencies. e.g. api, implementation
    public static HashSet<File> getTypedDependencies(HashSet<String> keys, String type = "",
                                                     String suffix = '.aar', boolean isAll = false) {
        println("${TAG}: getTypedDependencies begin !")
        HashSet<File> fileSet = []
        project.configurations.findAll {
            it.getExtendsFrom().forEach {
                if (it.getName().contains(type)) {
                    fileSet = getConfigurationDependencies(it, keys, suffix, isAll)
//                    showConfigurationInfo(it)
                }
            }
        }

        println("${TAG}: getTypedDependencies end !")
        return fileSet
    }

    public static void showConfigurationInfo(Configuration cfg) {
        println("${TAG}: showConfigurationInfo ${cfg.getIncoming().toString()}")
        Configuration cfgCopy = cfg.copyRecursive()
        try {
            cfgCopy.setCanBeResolved(true)
            println("${TAG}: ConfigurationFiles = " + cfgCopy.getFiles().toString())

            ResolvedConfiguration resolvedCfg = cfgCopy.getResolvedConfiguration()
            println("${TAG}: ResolvedConfiguration = " + resolvedCfg.getFiles().toString())
        } catch (Exception exc) {
            System.err.println("${TAG}: showConfigurationInfo error = " + exc.getMessage())
        }
    }

    public static HashSet<File> getDependencies(HashSet<String> keys, String suffix = '.aar', boolean isAll = false) {
        println("${TAG}: getDependencies begin !")
        HashSet<File> fileSet = getTypedDependencies(keys, "api", suffix, isAll)
        HashSet<File> implSet = getTypedDependencies(keys, "implementation", suffix, isAll)
        fileSet.addAll(implSet)
        println("${TAG}: getDependencies end !")
        return fileSet
    }

    public static void resetTransformSo(HashSet<String> aarUnzipDirs, HashSet<String> transformDirs) {
        println("${TAG}: resetTransformSo begin.")
        if (aarUnzipDirs == null || transformDirs == null) {
            throw new GradleException("${TAG} Error: aarUnzipDirs or transformDirs is null");
        }

        aarUnzipDirs.forEach {
            String[] pathComps = it.split('/')
            String aarName = pathComps[pathComps.length - 1]
            project.fileTree(it).forEach { File f ->
                if (f.toString().endsWith('.so')) {
                    String soPath = f.toString()
                    String soName = f.getName()

                    // move so to .gradle/cache/transforms-{num} '/jni/arm64-v8a/'
                    transformDirs.forEach { String dir ->
                        if (dir.endsWith(aarName)) {
                            println("${TAG}: copy ${soPath} to ${dir}/jni/arm64-v8a/${soName}")
                            Files.copy(Paths.get(soPath), Paths.get(dir + '/jni/arm64-v8a/' + soName),
                                    StandardCopyOption.REPLACE_EXISTING)
                        }
                    }
                }
            }
        }

        println("${TAG}: resetTransformSo end.")
    }

    /// @brief  v1/v2 format xxx.xxx.xxx[-ignoredFlags][-suffix], xxx is number.
    /// @brief  v1/v2 demo: 0.0.1 or 0.0.1-debug or 0.0.1-inner-debug
    /// @param  suffix  high priority suffix, means version with suffix has higher priority than no
    /// @return 1 means v1 > v2; -1 means v1 < v2; 0 means equal or on is empty
    public static int compareVersion(String v1, String v2, String suffix = '-debug') {
        if (v1.isEmpty() || v2.isEmpty()) {
            return 0;
        }
        if (!suffix.empty()) { // version with suffix has higher priority than no
            if (v1.endsWith(suffix) && !v2.endsWith(suffix)) { return 1;}
            if (!v1.endsWith(suffix) && v2.endsWith(suffix)) { return -1;}
        }

        // get number section
        String v1Str = v1.contains('-') ? v1.split('-')[0] : v1
        String[] v1Nums = v1Str.split('\\.')
        String v2Str = v2.contains('-') ? v2.split('-')[0] : v2
        String[] v2Nums = v2Str.split('\\.')

        int minSize = Math.min(v1Nums.size(), v2Nums.size())
        for (int idx=0; idx<minSize; idx++) {
            if (v1Nums[idx].toInteger() > v2Nums[idx].toInteger()) {
                return 1
            }
            if (v1Nums[idx].toInteger() < v2Nums[idx].toInteger()) {
                return -1
            }
        }
        return v1Nums.size() > v2Nums.size() ? 1 : (v1Nums.size() < v2Nums.size() ? -1 : 0)
    }

    /// @return Map<LibName, AarDir>
    public static HashMap<String, String> getLib_AarDirMap(HashSet<String> unzipDirs) {
        println("${TAG}: getLib_AarDirMap begin.")
        if (unzipDirs == null) {
            println("${TAG}: unzipDirs is null.")
            return null;
        }

        HashMap<String, String> lib_AarDirMap = new HashMap<>();
        HashMap<String, String> libVersionMap = new HashMap<>();
        unzipDirs.forEach { String dir ->
            File vf = new File(dir + '/assets/version_deps_lib')
            if (vf.exists()) {
                def prop = new Properties()
                try {
                    prop.load(vf.newInputStream())
                } catch (IOException e) {
                    e.printStackTrace()
                }
                prop.each {
                    println("${TAG}: version info: ${it.toString()}")
                    // libxx.so = "0.0.1" or libxx.so = "v0.0.1" or libxx.so = "v0.0.1-flag" or libxx.so = "v0.0.1-debug"
                    String version = it.value.toString().replaceFirst('v', '').replace('\"', '')
                    // println("${TAG}: version info: ${it.toString()}")
                    if (libVersionMap.containsKey(it.key)) {
                        if (compareVersion(libVersionMap[it.key], version) < 0 ) {
                            lib_AarDirMap[it.key] = dir
                            libVersionMap[it.key] = version
                            println("${TAG}: find new version: lib = ${it.key} ; version = ${version} ; dir = ${dir}")
                        }
                    } else {
                        lib_AarDirMap[it.key] = dir
                        libVersionMap[it.key] = version
                        println("${TAG}: find new lib: lib = ${it.key} ; version = ${version} ; dir = ${dir}")
                    }
                }
            }
        }

        libVersionMap.each {
            println("${TAG}: final version: lib = ${it.key} ; version = ${it.value.toString()} ; dir = ${lib_AarDirMap[it.key].toString()}")
        }

        println("${TAG}: getLib_AarDirMap end.")
        return lib_AarDirMap
    }

    public static void deleteOldSo(HashMap<String, String> lib_AarDirMap, Set<String> transformDirs) {
        println("${TAG}: deleteOldSo begin.")
        if (lib_AarDirMap == null || transformDirs == null) {
            throw new GradleException("${TAG} Error: lib_AarDirMap or transformDirs is null");
        }

        lib_AarDirMap.each {
            String lib = it.key
            String dir = it.value.toString()

            // delete old from transformDirs
            String dirName = dir.split('/').last().toString()
            transformDirs.forEach { String transDir ->
                if (!transDir.endsWith(dirName)) {
                    File soFile = new File(transDir + "/jni/arm84-v8a/" + lib)
                    if (soFile.exists()) {
                        println("${TAG}: delete so file: ${transDir + "/jni/arm84-v8a/" + lib}")
                        soFile.delete()
                    }
                }
            }
        }

        println("${TAG}: deleteOldSo end.")
    }

    public static void replaceOldSo(HashMap<String, String> lib_AarDirMap, Set<String> transformDirs) {
        println("${TAG}: replaceOldSo begin.")
        if (lib_AarDirMap == null || transformDirs == null) {
            throw new GradleException("${TAG} Error: lib_AarDirMap or transformDirs is null");
        }

        lib_AarDirMap.each {
            String lib = it.key
            String dir = it.value.toString()

            // replace old so to latest of transformDirs
            String dirName = dir.split('/').last().toString()
            transformDirs.forEach { String transDir ->
                if (!transDir.endsWith(dirName)) {
                    String srcPath = dir + "/jni/arm84-v8a/" + lib;
                    String dstPath = transDir + "/jni/arm84-v8a/" + lib;
                    File soFile = new File(dstPath)
                    if (soFile.exists()) {
                        println("${TAG}: replace so file: ${srcPath} ro ${dstPath}")
                        Files.copy(Paths.get(srcPath), Paths.get(dstPath), StandardCopyOption.REPLACE_EXISTING)
                    }
                }
            }
        }

        println("${TAG}: replaceOldSo end.")
    }

    public static void pickLatest(HashSet<String> aarKeys) {
        println("${TAG}: pickLatest begin !")
        String cacheDir = (project.buildDir.toString() + "/deps-aar/").toString()
        clearDir(cacheDir)
        println("${TAG}: cacheDir = " + cacheDir)

        HashSet<File> list = getDependencies(aarKeys, ".aar", true)
        GradleFile.copyFiles(list, cacheDir)
        Set<String> unzipDirs = GradleFile.unzipArchives(project, list, cacheDir, false)
        println("${TAG}: unzipDirs = " + unzipDirs)

        // get unzip aarName list
        HashSet<String> aarNames = [];
        unzipDirs.forEach {
            String[] pathComps = it.split('/')
            String aarName = pathComps[pathComps.length - 1]
            aarNames.add(aarName)
        }
        println("${TAG}: aarNames = " + aarNames)
        Set<String> transformDirs = GradleTransform.getTransformSubDirs('.so', aarNames)
        println("${TAG}: transformDirs = " + transformDirs)

        if (transformDirs.size() > 0) {
            HashMap<String, String> lib_AarDirMap = getLib_AarDirMap(unzipDirs)
            resetTransformSo(unzipDirs, transformDirs)
            replaceOldSo(lib_AarDirMap, transformDirs)
            // deleteOldSo(lib_AarDirMap, transformDirs)
        }

        println("${TAG}: pickLatest end !")
    }
}

public class PickLatestPluginExtension {
    String userName = "coder4869";
    String tag = "";
    HashSet<String> aarCheckKeys = new HashSet<String>();
}

public class PickLatestPlugin implements Plugin<Project> {
    private String TAG = "PickLatestPlugin";
    @Override
    void apply(Project project) {
        project.extensions.create("pickLatestPlugin", PickLatestPluginExtension);
        println("${TAG} apply. Author: ${project.pickLatestPlugin.userName}")

        Task pickLatestSo = project.task("pickLatestSo", group:'coder4869') {
            doLast {
                GradleTransform.project = project
                GradleDepends.project = project
                GradleDepends.pickLatest(project.pickLatestPlugin.aarCheckKeys)
            }
        }

        project.afterEvaluate {
            bindParentAndChildTask(project, pickLatestSo);
        }
    }

    void bindParentAndChildTask(Project project, Task task) {
        if (project == null || task == null) {
            println("${TAG}: invalid project = ${project} or task = ${task} !");
            return;
        }
        project.tasks.findAll {
            // mergeExtDex-xx-Debug
            // merge-xx-NativeLibs
            if (it.getName().endsWith("NativeLibs") && it.getName().startsWith("merge") ) {
                Task preTask = (Task)it;
                preTask.dependsOn task
                println("${TAG}: ${preTask.getName()}.dependsOn ${task.getName()}!");
            }

            // merge-xx-JniLibFolders
            if (it.getName().endsWith("JniLibFolders") && it.getName().startsWith("merge") ) {
                Task sufTask = (Task)it;
                task.dependsOn sufTask
                println("${TAG}: ${task.getName()}.dependsOn ${sufTask.getName()}!");
            }
        }
    }

//    void setTaskReleationship(Project project, String baseTask, String prefixTask, String suffixTask) {
//        Task task0 = project.tasks.findByName(baseTask);
//        if (task0 == null) {
//            throw new GradleException("${TAG}: baseTask ${prefixTask} not found!");
//            println("${TAG}: baseTask ${prefixTask} not found!");
//            return;
//        }
//
//        Task preTask = project.tasks.findByName(prefixTask)
//        if (preTask == null) {
//            throw new GradleException("${TAG}: prefixTask ${prefixTask} not found!");
//            // println("${TAG}: prefixTask ${prefixTask} not found!");
//        } else {
//            preTask.dependsOn task0
//            println("PickLatestPlugin: ${prefixTask}.dependsOn ${baseTask}!");
//        }
//
//        Task sufTask = project.tasks.findByName(suffixTask)
//        if (sufTask == null) {
//            throw new GradleException("${TAG}: suffixTask ${suffixTask} not found!");
//            // println("${TAG}: suffixTask ${suffixTask} not found!");
//        } else {
//            task0.dependsOn sufTask
//            println("${TAG}: ${baseTask}.dependsOn ${suffixTask}!");
//        }
//    }
}

//apply plugin: PickLatestPlugin
