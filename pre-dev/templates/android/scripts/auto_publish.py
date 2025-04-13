# Demo:
# python3 scripts/auto_publish.py $CI_COMMIT_BRANCH $VERSION_SUFFIX
import os
import sys 
import subprocess
import re
import time

CHANGE_LOG_FILE = "CHANGELOG.md"

# REMOTE_REPOS = [
#     "https://github.com/coder4869/DevAssistant.git",
#     "https://github.com/bazeltools/bazel-deps.git",
#     "https://github.com/Kitware/CMake.git"
# ]
REMOTE_REPOS = [
    "https://github.com/coder4869/DevAssistant.git"
]

# get the head commit_id from <repo> in <branch>
def get_head_commit_id(repo:str, branch:str):
    print("get_head_commit_id(repo, branch)")

    git_cmd = "git ls-remote {} refs/heads/{}".format(repo, branch)
    output = subprocess.getoutput([git_cmd])
    print("git_cmd = {} ; output = {}".format(git_cmd, output))

    commit_info = output.split()
    if len(commit_info) != 2:
        print("error: invalid git cmd output")
        return ""
    return commit_info[0]


# find <repo> tag by <commit_id> from tag list
def get_commit_id_tag(repo:str, commit_id:str):
    print("get_commit_id_tag(repo, commit_id)")

    tag_cmd = "git ls-remote {} refs/tags/*".format(repo) # get commit-tag list
    tags_output = subprocess.getoutput([tag_cmd])
    print("tag_cmd = {} ; tag list: \n{}".format(tag_cmd, tags_output))

    tag_list = tags_output.split('\n')
    for tag in tag_list:            # tag: <commit-id, tag_id>
        if tag.find(commit_id) != -1:
            print("find commit-id tag : " + tag)
            tag_id = tag.split()[1]             # e.g. refs/tags/v0.1-1
            return tag_id[len('refs/tags/'):]   # remove refs/tags/
    return ""


def get_tag_list(repo:str):
    print("get_tag_list({})".format(repo))

    tag_cmd = "git ls-remote {} refs/tags/*".format(repo) # get commit-tag list
    tags_output = subprocess.getoutput([tag_cmd]).split('\n')[::-1]
    # print("tag_cmd = {} ; tag list: \n{}".format(tag_cmd, tags_output))
    tag_list = []
    for tag in tags_output:
        info = tag.split('\t')
        if len(info) == 2 and info[1].startswith('refs/tags/'):
            tag_list.append(info[1][len('refs/tags/'):])
    print("tag_list = {}".format(tag_list))
    return tag_list


def get_branch_list(repo:str):
    print("get_branch_list({})".format(repo))

    branch_cmd = "git ls-remote {} refs/heads/*".format(repo) # get branch list
    branch_output = subprocess.getoutput([branch_cmd]).split('\n')[::-1]
    # print("branch_cmd = {} ; branch list: \n{}".format(branch_cmd, branch_output))
    branch_list = []
    for branch in branch_output:
        info = branch.split('\t')
        if len(info) == 2 and info[1].startswith('refs/heads/'):
            branch_list.append(info[1][len('refs/heads/'):])
    print("branch_list = {}".format(branch_list))
    return branch_list


# tag format: X.X.X or vX.X.X or X.X.X-flag or vX.X.X-flag
def parse_tag(tag:str):
    if tag.startswith('v'):
        tag = tag[1:]
    tag = tag.split('-')[0]
    tag = tag.split('^')[0]

    v_num = len(tag.split('.'))    
    major = int(tag.split('.')[0]) if v_num >= 1 else 0
    minor = int(tag.split('.')[1]) if v_num >= 2 else 0
    patch = int(tag.split('.')[2]) if v_num >= 3 else 0
    return major, minor, patch

def gen_new_version(repo:str):
    print("get_new_version({})".format(repo))

    # branch_list = get_branch_list(repo)
    tag_list = get_tag_list(repo)
    
    v_major:int = 0
    v_minor:int = 0
    v_patch:int = 0
    for tag in tag_list:
        major, minor, patch = parse_tag(tag)
        if v_major <= major:
            if v_major < major:
                v_minor = 0
                v_major = major
            
            if v_minor <= minor:
                if v_minor < minor:
                    v_patch = 0
                    v_minor = minor

                if v_patch < patch:
                    v_patch = patch

    new_version = str(v_major) + '.' + str(v_minor) + '.' + str(v_patch+1)
    print("new_version({})".format(new_version))
    return new_version


def commit_tag(repo:str, tag:str):
    ret = subprocess.getoutput("git tag {}".format(tag))
    print("create tag {} ret = {}".format(tag, ret))
    ret = subprocess.getoutput("git push {} tag {}".format(repo, tag))
    print("push tag ret = {}".format(ret))


def update_change_log(version:str):
    change_log_head = "## [%s] - [%s]" # add `## [version] - [YYYY.MM.DD]` to CHANGELOG.md head for new change
    with open(CHANGE_LOG_FILE, mode='r+') as f:
        lines = f.readlines()
        has_change = False
        for line in lines:
            if (not line) or (not line.strip()): # Empty line or only space line
                continue
            change_regex = re.match( r'## \[\d+\.\d+\.\d+.*\] - \d+\.\d+\.\d+', line)
            if change_regex:
                print("found change: {}".format(line))
                break
            has_change = True 
        print("change log has_change = {}".format(has_change))

        if not has_change:
            print("add auto gen log to {}".format(CHANGE_LOG_FILE))
            lines.insert(0, "- Auto update changelog !\n\n")
        
        date = time.strftime("%Y.%m.%d", time.localtime())
        lines.insert(0, "## [{}] - {} \n".format(version, date))

        f.seek(0, 0)
        f.writelines(lines)
        f.close

def commit_change_log(repo:str, branch:str):
    ret = subprocess.getoutput("git add {}".format(CHANGE_LOG_FILE))
    print("git add CHANGELOG.md ret = {}".format(ret))
    ret = subprocess.getoutput('''git commit -m "Auto update CHANGELOG.md"''')
    print("git commit ret = {}".format(ret))
    ret = subprocess.getoutput("git push {} HEAD:{}".format(repo, branch))
    print("git push ret = {}".format(ret))


if __name__ == '__main__':
    branch = sys.argv[1]

    # check if new commit exist in branch for REMOTE_REPOS
    enable_new_tag = False
    for repo in REMOTE_REPOS:
        commit_id = get_head_commit_id(repo, branch)
        if commit_id == "":
            print("Failed to get_head_commit_id from branch : " + branch)
            sys.exit(1)
        enable_new_tag |= (get_commit_id_tag(repo, commit_id) == "")

    # update changelog and add new tag for new changes
    if enable_new_tag:
        repo = REMOTE_REPOS[0]
        new_tag = gen_new_version(repo)
        print("new_version({})".format(new_tag))
        update_change_log(new_tag)
        # commit_change_log(repo, branch)
        # commit_tag(repo, new_tag)