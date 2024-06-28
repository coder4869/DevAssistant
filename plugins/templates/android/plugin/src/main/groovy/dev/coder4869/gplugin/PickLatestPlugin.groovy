// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    public static void createDir(String path) {
        File folder = new File(path)
        if (!folder.exists()) {
            folder.mkdirs();
            println("GradleFile: Folder ${folder.absolutePath} created!")
        } else {
            println("GradleFile: Folder ${folder.absolutePath} already exist!")
        }
    }

    /// @param dstDir   dir path, end with /
    public static void copyFiles(Set<File> fileList, String dstDir) {
        println("GradleFile: copyFiles begin !")
        createDir(dstDir)

        fileList.forEach { File f ->
            String srcPath = f.toString()
            String fullName = f.getName()
            println("srcPath is ${srcPath}; fullName is ${fullName}")

            try {
                Files.copy(Paths.get(srcPath), Paths.get(dstDir + fullName), StandardCopyOption.REPLACE_EXISTING)
                System.out.println("File copy succeed")
            } catch (IOException exc) {
                System.out.println("File copy error: " + exc.getMessage())
            }
        }
        println("GradleFile: copyFiles end !")
    }

    public static Set<String> unzipArchives(Project project, Set<File> fileList, String dstDir, Boolean isCopy) {
        println("GradleFile: unzipArchives begin !")
        createDir(dstDir)

        Set<String> dirList = new HashSet<String>()
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
                    System.out.println("File copy succeed")
                    record.append("\n" + dstDir + fullName)
                }
                record.append("\n" + srcPath)
                record.append("\n" + dstDir + baseName)
                dirList.add(dstDir + baseName)
            } catch (IOException exc) {
                System.out.println("File copy error: " + exc.getMessage())
            }
        }

        println("GradleFile: unzipArchives end !")
        return dirList
    }
}


class GradleDepends {
    public static Project project;

    public static void clearDir(String path) {
        project.delete(path)
    }

    public static String getDependsDir() {
        return project.gradle.properties["gradleUserHomeDir"].toString() + "/caches/modules-2/files-2.1";
    }

    public static String getTransformRootDir(int num = 3) {
        return project.gradle.properties["gradleUserHomeDir"].toString() + "/caches/transforms-${num}"
    }

    /// @suffix transforms files‘ suffix. e.g. ['.so', '.bin']
    public static ArrayList<String> getTransformFileList(ArrayList<String> suffix = []) {
        println("getTransformFileList begin !")
        ArrayList<String> fileList3 = getTransformFileList(getTransformRootDir(3), suffix)
        ArrayList<String> fileList4 = getTransformFileList(getTransformRootDir(4), suffix)
        fileList3.addAll(fileList4)
        println("getTransformFileList end !")
        return fileList3
    }

    /// @suffix transforms files‘ suffix. e.g. ['.so', '.bin']
    public static ArrayList<String> getTransformFileList(String transRootDir, ArrayList<String> suffix = []) {
        println("getTransformFileList begin. transformDir is: " + transRootDir)

        ArrayList<String> fileList = new ArrayList<String>();
        if (suffix.size() == 0) {
            project.fileTree(transRootDir).forEach {
                println("add file: " + it.toString())
                fileList.add(it.toString())
            }
        } else {
            project.fileTree(transRootDir).forEach {
                for (final String sf in suffix) {
                    if (it.toString().endsWith(sf)) {
                        println("add file: " + it.toString())
                        fileList.add(it.toString())
                        break
                    }
                }
            }
        }

        println("getTransformFileList end. Found ${fileList.size()} file for suffixs : " + suffix.toString())
        return fileList
    }

    // @param suffix    search file suffix. e.g. .so or .jar
    public static Set<String> getTransformSubDirs(String suffix) {
        println("getTransformSubDirs begin !")
        Set<String> dirList3 = getTransformSubDirs(getTransformRootDir(3), suffix)
        Set<String> dirList4 = getTransformSubDirs(getTransformRootDir(4), suffix)
        dirList3.addAll(dirList4)
        println("getTransformSubDirs end !")
        return dirList3
    }

    // @param suffix    search file suffix. e.g. .so or .jar
    public static Set<String> getTransformSubDirs(String transRootDir, String suffix) {
        println("getTransformSubDirs begin. transformDir is: " + transRootDir)

        Set<String> dirList = new HashSet<String>()
        if (suffix.equals('.so')) {
            project.fileTree(transRootDir).forEach {
                if (it.toString().endsWith('.so')) {
                    String soPath = it.toString()
                    if (soPath.contains("/jni/arm64-v8a")) {
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
                    if (jarPath.contains("/jars/classes.jar")) {
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

        println("getTransformSubDirs end. Found ${dirList.size()} directories ! ")
        return dirList
    }

    public static void resetTransformSo(Set<String> aarUnzipDirs, Set<String> transformDirs) {
        println("resetTransformSo begin.")
        if (aarUnzipDirs == null || transformDirs == null) {
            throw new GradleException("Error: aarUnzipDirs or transformDirs is null");
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
                            println("copy ${soPath} to ${dir}/jni/arm64-v8a/${soName}")
                            Files.copy(Paths.get(soPath), Paths.get(dir + '/jni/arm64-v8a/' + soName),
                                    StandardCopyOption.REPLACE_EXISTING)
                        }
                    }
                }
            }
        }

        println("resetTransformSo end.")
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

    /// @return Map<LibName, Dir>
    public static HashMap<String, String> getLibDirMap(HashSet<String> unzipDirs) {
        println("getLibDirMap begin.")
        if (unzipDirs == null) {
            println("unzipDirs is null.")
            return null;
        }

        HashMap<String, String> libDirMap = new HashMap<>();
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
                    println("version info: ${it.toString()}")
                    // libxx.so = "0.0.1" or libxx.so = "v0.0.1" or libxx.so = "v0.0.1-flag" or libxx.so = "v0.0.1-debug"
                    String version = it.value.toString().replaceFirst('v', '').replace('\"', '')
                    // println("version info: ${it.toString()}")
                    if (libVersionMap.containsKey(it.key)) {
                        if (compareVersion(libVersionMap[it.key], version) < 0 ) {
                            libDirMap[it.key] = dir
                            libVersionMap[it.key] = version
                            println("find new version: lib = ${it.key} ; version = ${version} ; dir = ${dir}")
                        }
                    } else {
                        libDirMap[it.key] = dir
                        libVersionMap[it.key] = version
                        println("find new lib: lib = ${it.key} ; version = ${version} ; dir = ${dir}")
                    }
                }
            }
        }

        libVersionMap.each {
            println("final version: lib = ${it.key} ; version = ${it.value.toString()} ; dir = ${libDirMap[it.key].toString()}")
        }

        println("getLibDirMap end.")
        return libDirMap
    }

    public static void deleteOldSo(HashMap<String, String> libDirMap, Set<String> transformDirs) {
        println("deleteOldSo begin.")
        if (libDirMap == null || transformDirs == null) {
            throw new GradleException("Error: libDirMap or transformDirs is null");
        }

        libDirMap.each {
            String lib = it.key
            String dir = it.value.toString()

            // delete old from transformDirs
            String dirName = dir.split('/').last().toString()
            transformDirs.forEach { String transDir ->
                if (!transDir.endsWith(dirName)) {
                    File soFile = new File(transDir + "/jni/arm84-v8a/" + lib)
                    println("${lib} so file: ${transDir + "/jni/arm84-v8a/" + lib}")
                    if (soFile.exists()) {
                        soFile.delete()
                    }
                }
            }
        }

        println("deleteOldSo end.")
    }

    public static void showConfigurationInfo(Configuration cfg) {
        println cfg.getIncoming().toString()
        Configuration cfgCopy = cfg.copyRecursive()
        try {
            cfgCopy.setCanBeResolved(true)
            println("ConfigurationFiles = " + cfgCopy.getFiles().toString())

            ResolvedConfiguration resolvedCfg = cfgCopy.getResolvedConfiguration()
            println("ResolvedConfiguration = " + resolvedCfg.getFiles().toString())
        } catch (Exception exc) {
            println("showConfigurationInfo error = " + exc.getMessage())
        }
    }

    public static Set<File> getConfigurationDependencies(Configuration cfg,
                                                         String suffix = '.aar',
                                                         boolean isAll = false)
    {
        println cfg.getIncoming().toString()
        println("getConfigurationDependencies begin !")

        Set<File> depends = []
        Configuration cfgCopy = cfg.copyRecursive()
        try {
            cfgCopy.setCanBeResolved(true)
            if (isAll) {
                for (final File f in cfgCopy.getFiles()) {
                    if (f.toString().endsWith(suffix)) {
                        int size = depends.size()
                        depends.add(f)
                        if (depends.size() > size) {
                            println f.toString()
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
                                println f.toString()
                            }
                        }
                    }
                }
            }
        } catch (Exception exc) {
            println("error = " + exc.getMessage())
        }
        println("getConfigurationDependencies end !")
        return depends
    }

    // getTypedDependencies("api")
    // getTypedDependencies("implementation")
    /// @param type target type in dependencies. e.g. api, implementation
    public static Set<File> getTypedDependencies(String type = "",
                                                 String suffix = '.aar',
                                                 boolean isAll = false)
    {
        println("getTypedDependencies begin !")

        Set<File> fileSet = []
        project.configurations.findAll {
            boolean stop = false
            it.getExtendsFrom().forEach {
                if (!stop) {
                    stop = true
                    if (it.getName().contains(type)) {
                        fileSet = getConfigurationDependencies(it, suffix, isAll)
//                        showConfigurationInfo(it)
                    }
                }
            }
        }

        println("getTypedDependencies end !")
        return fileSet
    }

    public static Set<File> getDependencies(String suffix = '.aar', boolean isAll = false)
    {
        println("getDependencies begin !")

        Set<File> fileSet = getTypedDependencies("api", suffix, isAll)
        Set<File> implSet = getTypedDependencies("implementation", suffix, isAll)
        fileSet.addAll(implSet)

        println("getDependencies end !")
        return fileSet
    }

    public static void pickLatest() {
        println("pickLatest begin !")
        String cacheDir = (project.buildDir.toString() + "/cache/deps-aar/").toString()
        clearDir(cacheDir)

        Set<File> list = getDependencies(".aar", true)
        GradleFile.copyFiles(list, cacheDir)
        Set<String> unzipDirs = GradleFile.unzipArchives(project, list, cacheDir, false)

        Set<String> transformDirs = getTransformSubDirs('.so')
        println "transformDirs = " + transformDirs
        resetTransformSo(unzipDirs, transformDirs)
        if (transformDirs.size() > 0) {
            deleteOldSo(unzipDirs, transformDirs)
        }

        println("pickLatest end !")
    }
}

public class PickLatestPlugin implements Plugin<Project> {
    @Override
    void apply(Project project) {
        println("PickLatestPlugin apply")
	
        // ./gradlew app:pickLatestSo
        Task pickLatestSo = project.task("pickLatestSo", group:'coder4869') {
            doLast {
                GradleDepends.project = project
                GradleDepends.pickLatest()
            }
        }

        Task runShell = project.task("runShell", group:'coder4869') {
            doLast {
                String shellScript = (project.rootDir.toString() + "/scripts/deps.sh").toString()
                exec {
                    println shellScript
                    commandLine 'sh', shellScript
                }
            }
        }

        Task preBuild = project.tasks.findByPath("preBuild")
        if (preBuild) {
            preBuild.dependsOn pickLatestSo
            // preBuild.dependsOn runShell // Demo for run shell
        }
    }
}

//apply plugin: PickLatestPlugin
