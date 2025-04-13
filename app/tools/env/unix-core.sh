#!/bin/bash
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${script_dir}

UNIX_OS=""
function get_os() {
    # lsb_release
    if [[ -x "/usr/bin/lsb_release" ]]; then
        # Ubuntu, Debian, openkylin2.0
        lsb_a=$(/usr/bin/lsb_release -a a>/dev/null)

        if echo "$lsb_a" | grep -q "Ubuntu"; then
            UNIX_OS="Ubuntu"
        elif echo "$lsb_a" | grep -q "Debian"; then
            UNIX_OS="Debian"
        elif echo "$lsb_a" | grep -q "CentOS"; then
            UNIX_OS="CentOS"
        elif echo "$lsb_a" | grep -q "Red Hat"; then
            UNIX_OS="RedHat"
        fi
    fi

    # os-release
    if [[ "$UNIX_OS" == "" ]]; then
        if [[ -x "/etc/os-release" ]]; then
            # Ubuntu, Debian
            # CentOS/RedHat 7+(old is /etc/centos-release and /etc/redhat-release)
            os_release=$(cat /etc/os-release)

            if echo "$os_release" | grep -q "Ubuntu"; then
                UNIX_OS="Ubuntu"
            elif echo "$os_release" | grep -q "Debian"; then
                UNIX_OS="Debian"
            elif echo "$os_release" | grep -q "CentOS"; then
                UNIX_OS="CentOS"
            elif echo "$os_release" | grep -q "Red Hat"; then
                UNIX_OS="RedHat"
            fi
        fi
    fi

    if [[ "$UNIX_OS" == "" ]]; then
        echo "Unknown Unix-OS"
    else
        echo $UNIX_OS
    fi
}

UNIX_MIRROR=""
function get_mirror() {
    if [[ -x "/etc/apt/sources.list" ]]; then
        # Ubuntu, Debian
        UNIX_MIRROR=apt
    elif [[ -x "/etc/yum.repos.d/" ]]; then
        # Red Hat, CentOS, RHEL, Fedora
        UNIX_MIRROR=yum
    fi

    if [[ "$UNIX_MIRROR" == "" ]]; then
        echo "Unknown Unix-Mirror"
    else
        echo $UNIX_MIRROR
    fi
}

SUDO_CMD=sudo
function get_sudo() {
    if [[ `whoami` == "root" ]]; then
        SUDO_CMD=
    fi
    echo $SUDO_CMD
}
