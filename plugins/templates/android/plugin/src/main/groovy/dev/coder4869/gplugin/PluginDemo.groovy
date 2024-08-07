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