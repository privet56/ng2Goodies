# QtWS18
## Qt Designer = Qt Design Studio
1. can export from photoshop (.PSD) or sketch, and then do prototyping
2. app looks a little bit like QtCreator
3. app can edit animations
4. app only with commercial Qt license available
## Automotive Suite
Parts of the Suite: App Manager, IVI, Reference UI (Neptune UI), QmlLive, GammaRay, QtCreator-Plugin.
Neptune UI is an architecture of UI: AppShell, Store, View, Panel, Control. Helper
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
----
import QtQuick 2.11
import shared utils 1.0
AbstractStore {
    id: root
    property int musicCount: 0
    property ListModel playlistModel
    //...other properties
}
----
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
```
