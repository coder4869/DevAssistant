Name:		_PROJ_NAME_
Version:	1.1.4.0
Release:	1%{?dist}
Summary:	Client Application
License:	""
Source0:	.

%description
%{name} is an client application.
 
# 定义安装文件列表
%install
mkdir -p %{buildroot}/usr/local/bin/%{name}/bin64
cp -r %{SOURCE0}/bin64/%{name} %{buildroot}/usr/local/bin/%{name}/bin64/%{name}
#install -D -m 755 %{name} %{buildroot}/usr/local/bin/%{name}/bin64/%{name}
# libs
mkdir -p %{buildroot}/usr/lib64
cp -r %{SOURCE0}/bin64/lib*.so %{buildroot}/usr/lib64/
# data && conf && logs
mkdir -p %{buildroot}/usr/local/bin/%{name}/conf
mkdir -p %{buildroot}/usr/local/bin/%{name}/data
mkdir -p %{buildroot}/usr/local/bin/%{name}/logs
mkdir -p %{buildroot}/tmp/%{name}-logs
cp -r %{SOURCE0}/conf/* %{buildroot}/usr/local/bin/%{name}/conf/
cp -r %{SOURCE0}/data/* %{buildroot}/usr/local/bin/%{name}/data/
echo "/tmp/%{name}-logs" > %{buildroot}/usr/local/bin/%{name}/logs/%{name}.log
echo "/tmp/%{name}-logs" > %{buildroot}/tmp/%{name}-logs/%{name}.log

# .desktop to /usr/share/applications 
mkdir -p %{buildroot}/usr/share/applications 
cp -r %{SOURCE0}/%{name}.desktop %{buildroot}/usr/share/applications/%{name}.desktop
#install -D -m 644 %{SOURCE0}/%{name}.desktop %{buildroot}/usr/share/applications/%{name}.desktop
# icon to /usr/share/icons/hicolor/xxx
mkdir -p %{buildroot}/usr/share/icons/hicolor/48x48/apps
mkdir -p %{buildroot}/usr/share/icons/hicolor/256x256/apps
cp -r %{SOURCE0}/data/Resource/logo-48.png %{buildroot}/usr/share/icons/hicolor/48x48/apps/%{name}.png
cp -r %{SOURCE0}/data/Resource/logo-256.png %{buildroot}/usr/share/icons/hicolor/256x256/apps/%{name}.png
#auto-start
mkdir -p %{buildroot}/etc/xdg/autostart
cp -r %{SOURCE0}/%{name}.desktop %{buildroot}/etc/xdg/autostart/%{name}-autostart.desktop
# install -D -m 644 %{name}-autostart.desktop %{buildroot}/etc/xdg/autostart/%{name}-autostart.desktop

# right-menu
mkdir -p %{buildroot}/usr/share/mime/packages
cp -r %{SOURCE0}/%{name}_loader 			%{buildroot}/usr/local/bin/%{name}_loader
cp -r %{SOURCE0}/%{name}-action.xml %{buildroot}/usr/share/mime/packages/%{name}-action.xml

# 定义安装步骤
%files
/usr/local/bin/%{name}/bin64/%{name}
/usr/local/bin/%{name}/conf/*
/usr/local/bin/%{name}/data/*
/usr/local/bin/%{name}/logs/*
/tmp/%{name}-logs/*
/usr/lib64/*
/etc/xdg/autostart/%{name}-autostart.desktop
/usr/local/bin/%{name}_loader
/usr/share/mime/packages/%{name}-action.xml
%defattr(644, root, root, 755)
%attr(644, appuser, appgroup) /usr/share/applications/%{name}.desktop
%attr(644, appuser, appgroup) /usr/share/icons/hicolor/48x48/apps/%{name}.png
%attr(644, appuser, appgroup) /usr/share/icons/hicolor/256x256/apps/%{name}.png
%attr(755, appuser, appgroup) /usr/local/bin/%{name}_loader
%attr(755, appuser, appgroup) /usr/share/mime/packages/%{name}-action.xml

# 安装前执行的脚本
%pre
echo "安装启动！"
 
# 安装后执行的脚本
%post
echo "安装结束，更新配置变更中。。。"
SUDO_CMD=sudo
if [[ `whoami` == "root" ]]; then
    SUDO_CMD=
fi
${SUDO_CMD} chmod +x /usr/local/bin/%{name}_loader
${SUDO_CMD} update-mime-database /usr/share/mime
echo "安装结束，配置变更完成。"

# 卸载前执行的脚本
%preun
if [ $1 -eq 0 ]; then
    echo "卸载前准备工作(关闭运行中的程序)！"
	PID=$(pidof "%{name}")
	if [ -n "$PID" ]; then
		echo "进程 %{name}（PID: $PID）正在运行，正在终止..."
		kill -15 "$PID"
		sleep 2
		if ps -p "$PID" > /dev/null; then
		    echo "进程未正常终止，强制终止..."
		    kill -9 "$PID"
		fi
	fi
fi
 
# 卸载后执行的脚本
%postun
if [ $1 -eq 0 ]; then
    rm -rf /tmp/%{name}-logs/
    echo "卸载结束！"
fi
