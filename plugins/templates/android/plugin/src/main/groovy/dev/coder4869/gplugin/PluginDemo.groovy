package dev.coder4869.gplugin;

import org.gradle.api.Plugin;
import org.gradle.api.Project;

public class PluginDemo implements Plugin<Project> {

    public void apply(Project project) {
        System.out.println("PluginDemo apply !");
    }
}