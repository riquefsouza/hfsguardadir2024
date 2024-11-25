Disable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-Hypervisor


pkg-config --list-all
pkg-config --list-package-names
pkg-config --cflags --msvc-syntax gtk+-3.0
pkg-config --libs --msvc-syntax gtk+-3.0


pkg-config --cflags gtkmm-4.0 --msvc-syntax

pkg-config --libs gtkmm-4.0 --msvc-syntax


$(GTK3_HOME)\include\gtk-3.0;$(GTK3_HOME)\include\pango-1.0;$(GTK3_HOME)\include\harfbuzz;$(GTK3_HOME)\include;$(GTK3_HOME)\include\cairo;$(GTK3_HOME)\include\freetype2;$(GTK3_HOME)\include\libpng16;$(GTK3_HOME)\include\pixman-1;$(GTK3_HOME)\include\gdk-pixbuf-2.0;$(GTK3_HOME)\include\atk-1.0;$(GTK3_HOME)\include\fribidi;$(GTK3_HOME)\include\glib-2.0;$(GTK3_HOME)\lib\glib-2.0\include

$(GTK3_HOME)\lib

gtk-3.lib;gdk-3.lib;gdi32.lib;imm32.lib;shell32.lib;ole32.lib;winmm.lib;dwmapi.lib;setupapi.lib;cfgmgr32.lib;hid.lib;winspool.lib;comctl32.lib;comdlg32.lib;pangocairo-1.0.lib;pangowin32-1.0.lib;pango-1.0.lib;harfbuzz.lib;cairo-gobject.lib;cairo.lib;gdk_pixbuf-2.0.lib;atk-1.0.lib;gio-2.0.lib;gobject-2.0.lib;glib-2.0.lib;intl.lib


pkg-config gtk4 --cflags --libs
pkg-config gtkmm-4.0 --cflags --libs

g++ helloworld.cpp  helloworld.h  main.cpp -o HFSGuardaDiretorio_Gtkmm4.exe `pkg-config --cflags --libs gtkmm-4.0` -std=c++17

sudo apt install build-essential gdb
sudo apt-get install libgtkmm-4.0-dev

pkg-config --list-all | grep wxw

pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-toolchain base-devel
pacman -S mingw-w64-ucrt-x86_64-gtk4
pacman -S mingw-w64-ucrt-x86_64-gtkmm4
pacman -S mingw-w64-ucrt-x86_64-python-gobject
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-ntldd
pacman -S mingw-w64-ucrt-x86_64-wxwidgets3.2-msw
pacman -S mingw-w64-ucrt-x86_64-sqlite3

pacman -S mingw-w64-ucrt-x86_64-gtk3
pacman -S mingw-w64-ucrt-x86_64-gtkmm3

pacman -S mingw-w64-ucrt-x86_64-fox


fox-config --cflags

-I/ucrt64/include/fox-1.6

fox-config --libs

-L/ucrt64/lib -lFOX-1.6 -lcomctl32 -lwsock32 -lwinspool -lmpr -lgdi32 -limm32 -lopengl32 -lglu32 -lpthread -ljpeg -lpng -ltiff -lz -lbz2 -lglu32 -lopengl32


https://packages.msys2.org/search?t=pkg&q=gprbuild
adacore
pacman -S mingw-w64-ucrt-x86_64-gprbuild

g++ -std=c++17 hfsguardadir.cpp $(pkg-config gtkmm-4.0 --cflags --libs | sed 's/ -I/ -isystem /g')

sudo apt install code_1.95.1-1730355339_amd64.deb


sudo apt install apt-transport-https
sudo apt update
sudo apt install code # or code-insiders

find -iname "g++"
find -iname "gcc"
find -iname "gprbuild"

winget install Microsoft.VisualStudio.2022.BuildTools --force --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 --add Microsoft.VisualStudio.Component.Windows10SDK"



ntldd -R HFSGuardaDiretorio_Gtk4.exe | grep msys64

cd c:
cd C:\HFSGuardaDir\wscodelite\build-Debug\bin

ntldd -R HFSGuardaDiretorio_Gtkmm4.exe | grep msys64


wx-config --cflags
-IC:/msys64/ucrt64/lib/wx/include/msw-unicode-3.2 -IC:/msys64/ucrt64/include/wx-3.2 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMSW__


wx-config --libs
-LC:/msys64/ucrt64/lib   -Wl,--subsystem,windows -mwindows -lwx_mswu_xrc-3.2 -lwx_mswu_html-3.2 -lwx_mswu_qa-3.2 -lwx_mswu_core-3.2 -lwx_baseu_xml-3.2 -lwx_baseu_net-3.2 -lwx_baseu-3.2


pkg-config --cflags wxsqlite3-3.0
-DWXUSINGLIB_WXSQLITE3
pkg-config --libs wxsqlite3-3.0

pacman --query wxsqlite3


"C:\Users\hfs30\AppData\Local\Programs\Microsoft VS Code\Code.exe"


sudo apt-cache search gnat
sudo apt-cache search gprbuild
sudo apt-get install gprbuild
sudo apt-get install gnat



pkg-config gtk+-3.0 --cflags

-IC:/msys64/ucrt64/include/gtk-3.0 -IC:/msys64/ucrt64/include/pango-1.0 -IC:/msys64/ucrt64/include/harfbuzz -IC:/msys64/ucrt64/include/cairo -IC:/msys64/ucrt64/include/freetype2 -IC:/msys64/ucrt64/include/pixma
n-1 -IC:/msys64/ucrt64/include/gdk-pixbuf-2.0 -IC:/msys64/ucrt64/include/libpng16 -IC:/msys64/ucrt64/include/webp -DLIBDEFLATE_DLL -IC:/msys64/ucrt64/include/atk-1.0 -IC:/msys64/ucrt64/include/fribidi -IC:/msys
64/ucrt64/include/glib-2.0 -IC:/msys64/ucrt64/lib/glib-2.0/include


pkg-config gtk+-3.0 --libs

-lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lca
iro-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl


pkg-config gtkmm-3.0 --cflags

-IC:/msys64/ucrt64/include/gtkmm-3.0 -IC:/msys64/ucrt64/lib/gtkmm-3.0/include -IC:/msys64/ucrt64/include/atkmm-1.6 -IC:/msys64/ucrt64/lib/atkmm-1.6/include -IC:/msys64/ucrt64/include/gdkmm-3.0 -IC:/msys64/ucrt64/lib/gdkmm-3.0/include -IC:/msys64/ucrt64/include/giomm-2.4 -IC:/msys64/ucrt64/lib/giomm-2.4/include -IC:/msys64/ucrt64/include/gtk-3.0 -IC:/msys64/ucrt64/include/cairo -IC:/msys64/ucrt64/include/atk-1.0 -IC:/msys64/ucrt64/include/pangomm-1.4 -IC:/msys64/ucrt64/lib/pangomm-1.4/include -IC:/msys64/ucrt64/include/glibmm-2.4 -IC:/msys64/ucrt64/lib/glibmm-2.4/include -IC:/msys64/ucrt64/include/cairomm-1.0 -IC:/msys64/ucrt64/lib/cairomm-1.0/include -IC:/msys64/ucrt64/include/sigc++-2.0 -IC:/msys64/ucrt64/lib/sigc++-2.0/include -IC:/msys64/ucrt64/include/pango-1.0 -IC:/msys64/ucrt64/include/pixman-1 -IC:/msys64/ucrt64/include/fribidi -IC:/msys64/ucrt64/include/harfbuzz -IC:/msys64/ucrt64/include/freetype2 -IC:/msys64/ucrt64/include/gdk-pixbuf-2.0 -IC:/msys64/ucrt64/include/libpng16 -IC:/msys64/ucrt64/include/webp -IC:/msys64/ucrt64/include/glib-2.0 -IC:/msys64/ucrt64/lib/glib-2.0/include

pkg-config gtkmm-3.0 --libs

-lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangowin32-1.0 -latk-1.0 -lcairo-gobject -lgio-2.0 -lpangomm-1.4 -lglibmm-2.4 -lcairomm-1.0 -lsigc-2.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lcairo -lgdk_pixbuf-2.0 -lgobject-2.0 -lglib-2.0 -lintl


set PATH=C:\msys64\ucrt64\bin;%PATH%
cd C:\wxsqlite3-main\build
mingw32-make config=debug_win64 SHELL=cmd.exe

set WXWIN=C:/msys64/ucrt64


cmake CMakeLists.txt
cmake --build . --config debug_win64

HFSGuardaDiretorio_FoxTookit