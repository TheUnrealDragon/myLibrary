import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    TabBar {
        id: tabbar
        width: parent.width
        anchors.left: parent.left
        anchors.right: parent.right
        TabButton {
            height: 35
            id: animebutton
            text: "Anime"
        }
        TabButton {
            height:35
            id: mangabutton
            text: "Manga"
        }
        TabButton {
            height: 35
            id: novelsbutton
            text: "Novels"
        }
    }
    StackLayout {
        id: slayout
        anchors.fill: parent
        height: parent.height - tabbar.height
        currentIndex: tabbar.currentIndex
        Item {
            id: anime
            Loader {
                id: animeLoader
                source: "AnimeTab.qml"
                anchors.fill: parent
                anchors.topMargin: 35
            }
        }
        Item {
            id: manga
        }
        Item {
            id: novels
        }

    }
}
