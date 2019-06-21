# QtWS18
## Qt Designer = Qt Design Studio
1. can export from photoshop (.PSD) or sketch, and then do prototyping
2. app looks a little bit like QtCreator
3. app can edit animations
4. app only with commercial Qt license available
## Automotive Suite
1. Parts of the Suite: App Manager, IVI, Reference UI (Neptune UI), QmlLive, GammaRay, QtCreator-Plugin.
2. Neptune UI is an architecture of UI: AppShell, Store, View, Panel, Control. Helper
3. Neptune depends on IVI and Qt Application Manager
4. Neptune 3 shows the capability of Qt Automotive Suite to create mulit-process UI

```qml
import application.window 1.0
import stores 1.0
import views 1.0
ApplicationCCWindow {
    id: root
    MusicView {
        x: root.exposedRect.x
        state: root.neptuneState
        store: MuiscStore()
        //...
    }
}
//----
import QtQuick 2.11
import shared utils 1.0
AbstractStore {
    id: root
    property int musicCount: 0
    property ListModel playlistModel
    //...other properties
}
//----
import QtQuick 2.11
import your.media.backend 1.0
MusicStoreInterface {
    id: root
    readonly property Player musicPlayer: MusicPlayer()
    musicCount: musicPlayer.musicCount
    //...other properties
    function pause() {
        player.pause()
    }
}
//----
import QtQuick 2.11
import stores 1.0
Item {
    id: root
    property MusicStore store
    WidgetPanel {
        width: root.width
        state: root.state
        store: root.store
    }
    MaximizedPanel {
        width: root.width
        height: root.height - widgetContent.height
        visibilit: root.state == 'Maximized'
    }
}
```
## MapBox Auto on Qt
1. MapBox Qt SDK (incl QML plugins), From Finland, MapBox Automotive
2. MapBox OEMs: lot of car companies, like VW, GM, Mercedes, BMW, Audi, Harman...
3. can be built into IVI (=embedded linux based on Yocto/Boot2Qt)
## Qt Creator IDE
1. C++: offers navigation, highlighting, understand also overloaded operators
    1. supports QSharedPointer, auto(by tooltip)
    2. has Clang & Clazy Analyzer/Diagnostic support
    3. has ClangFormat (AutoFormatter, Code-Beautifier)
2. has Language Server Protocol (supports py, C++, haskell, Go, Rust)
## WASM - Qt for WebAssembly
1. Platform Stack: App + Qt + Emscripten + HTML/Wasm. Example: https://github.com/msorvig/QtWS18/
2. Empscipten = a toolchain for compiling to asm.js, uses LLVM
3. #define Q_OS_WASM
4. no binaries from Qt company -> you have to build Qt from source for this target platform
    1. cmd: ~Qt/5.12.0/src/configure -xplatform wasm-emscripten -nomake examples
    2. cmd: make module-qtbase module-qtquickcontrols2
5. supported modules: QtBase, QtDeclarative, Qt-Quick-Controls2, QtCharts, QtWebSockets, QtMqTT
6. qmake & make will build a .wasm.js and html files, can be served from any web server:
    1. app.html: app is embedded in a &lt;canvas&gt;, app sees that as a QScreen
    2. qtloader.js
    3. app.js
    4. app.wasm
7. file sizes:
    1. core gui: >2MB
    2. Core gui widgets: >3MB
    3. Charts: >6MB
8. memory usage: large! (but not bigger than other WASM apps)
9. Emscripten creates an in-memory file system, accessible by QFile (no QFileDialog support)
    1. callback-based loadFile(); QWasmFile(...
10. Networking: QNetworkAccessManager (constraint: CORS), QWebSocket (any host!), QAbstractSocket (=websocket-protocol, Websockify forwarding host (=tunnel)); MQTT over WebSocket possible!
11. Empscripten provides API for interop C++ with JavaScript!
```c++
//C++:
#include <empscripten/bind.h>
void setColor(int r, int g, int b);
EMSCRIPTEN_BINDINGS(colorDebugger) {
    empscripten::function("setColor", &setColor);
}
//JS:
Module.setColor(rgb[0], rgb[1], rgb[2]);
```
12. not yet working in Qtv.5.12: Threading, Qt3D, nested event loops
## KDAB Open Source Tools:
Clazy & GammaRay & Heaptrack(https://projects.kde.org/heaptrack/) & Hotspot(GUI for linux perf)
### Clazy
Clazy is integrated in QtCreator
```c++
export CLAZY_CHECKS=level0,level1,level2
clazy -I/usr/include/qt&/ -std=c++11 f.cpp
export CLAZY_FIXIT="fix-string-allocations"
```
```c++
//Clazy warning:
void t(QObject *pO) {
    int a = 1;
    auto f = [&a]() { /*...*/ };
    pO->connect(pO, &QObject::destroyed, [a]()  { /*...*/ });
    pO->connect(pO, &QObject::destroyed, [&a]() { /*...*/ }); //->CRASH //warning by Clazy!
}
bool isF(const QString& s) {
    return s == "f";    //warning by Clazy! better: return s == QLatin1String("f");
}
QString f() {
    return QLatin1String("f");//warning by Clazy! better: return QStringLiteral("f");
}
```
## WASM
1. WASM = web assembly = stack based virtual machine
1. in WASM, there is no DOM!
1. in WASM, there is no Garbage Collector! (year: 2019)
1. in WASM, there is no well-supported Thread support (but a preview-implementation is available starting from Chrome74 upwards: simd)
1. input can be C, C++(Qt), Rust(wasm-pack), ... AssemblyScript
1. output: .wasm, running in the browser (in sandbox!)
1. emscripten = drop-in replacement of C compiler (./emcc)
    1. the older version of emscripten: asm.js: converts C++ code to JS
    1. the current version of emscripten: like an operating system running in the browser (emulating file system, opengl(->webgl))
    1. gotcha: output js can be large
1. use cases for WASM:
    1. use lib of the input language (which maybe has no JS version) (eg. image encoder)
1. WASM and JS have the **same speed** but *it is easier to stay in the fast path with WASM*
    1. both run in the V8 engine
        1. .js -> V8 = **ignition**(=interpreter) & **turbofan** , with optimization but sometimes needs also de-optimization (when code ~worse)
        1. .wasm -> V8 = **liftoff**(=compiler generating machine code) & **turbofan** , with optimization (no de-optimization necessary, **no deopt**) -> speed is more pedictable
1. AssemblyScript = TypeScript to WASM compiler
