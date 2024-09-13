// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

package dev.coder4869.gplugin;

import org.gradle.api.Plugin;
import org.gradle.api.Project
import org.gradle.api.Task;

public class PluginDemoExtension {
    String userName = "coder4869";
}

public class PluginDemo implements Plugin<Project> {

    public void apply(Project project) {
        project.extensions.create("pluginDemo", PluginDemoExtension);
        println("PluginDemo apply. Author: ${project.pluginDemo.userName}")

        project.afterEvaluate {
            String uname = project.pluginDemo.userName
            println("PluginDemo: uname = ${uname}")
        }
	
//        Task runShell = project.task("runShell", group:'coder4869') {
//            doLast {
//                String shellScript = (project.rootDir.toString() + "/scripts/deps.sh").toString()
//                exec {
//                    println shellScript
//                    commandLine 'sh', shellScript
//                }
//            }
//        }
//        Task preBuild = project.tasks.findByPath("preBuild")
//        if (preBuild) {
//            preBuild.dependsOn runShell // Demo for run shell
//        }
    }
}
// Usage
// plugins {
//     id 'dev.coder4869.PluginDemo'
// }
// pluginDemo {
//     userName = "coder4869"
// }