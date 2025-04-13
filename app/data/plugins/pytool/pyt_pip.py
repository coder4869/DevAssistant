#coding-utf-8
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

import os

def cmd_run(cmd):
    ret = os.system(cmd + " > cmd.log")
    fp = open("cmd.log", "r", encoding="utf-8")
    lines = fp.readlines()
    fp.close()
    for line in lines:
        print(line)
    os.remove("cmd.log")
    return lines[0]

def check_pip():
    ctx = cmd_run("pip --version")
    return True if ctx.startswith("pip") else False

def pip_install(pkgs):
    if check_pip():
        cmd = "pip install -i https://pypi.tuna.tsinghua.edu.cn/simple " + pkgs
        ctx = cmd_run(cmd)
    else:
        print("pip not installed")

# pip_install("numpy")
# pip_install("pywin32")
# pip_install("xlwings")
# pip_install("et_xmlfile")
# pip_install("email") 
# pip_install("PyEmail") 
# pip_install("excel2img") 
