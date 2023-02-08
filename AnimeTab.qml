import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Particles 2.0
import Qt5Compat.GraphicalEffects
import QtQml 2.3

import Anime 1.0
import AnimeCompleted 1.0

Item {
    Timer {
        id: timer1
        repeat: false
    }
    Timer{
        id: timerforSearchLimit
        repeat: false
    }

    AnimeHandler {
        id: handler
        objectName: "HandlerObject"
        onThisTrySignal: {
        }
    }
    id: topparent
    TabBar{
        id: bar
        width: parent.width
        TabButton {
            id: animecompleted
            height: 35
            property bool nowactive: true
            background: Rectangle {
                color:  "#302b35"

            }
            onToggled: ()=>{
                           animecompleted.nowactive = true
                           animecompletedorangebaranimation.running = true
                           animewatching.nowactive = false
                           animedropped.nowactive = false
                           addanime.nowactive = false
                       }
            contentItem: Text{
                text: animecompleted.text
                font: animecompleted.font
                opacity: enabled ? 1.0 : 0.3
                color: animecompleted.nowactive ? "orange" : "gray"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                Rectangle {
                    visible: animecompleted.nowactive ? true : false
                    color: "orange"
                    height: 3
                    width: 0
                    x: parent.width/2 - width/2
                    anchors.top: parent.bottom
                    anchors.topMargin: -7
                    radius: 20
                    NumberAnimation on width {
                        id: animecompletedorangebaranimation
                        from: 0
                        to: 70
                        duration: 500
                    }
                }

                Rectangle {
                    id: completedwatchingseperator
                    color: "grey"
                    height: 20
                    width: 2
                    x: parent.width
                    y: parent.height/2 - height/2
                }
            }

            text: "Completed"
        }
        TabButton {
            height: 35
            id: animewatching
            property bool nowactive: false
            background: Rectangle {
                color: "#302b35"
            }
            onToggled: ()=>{
                           animewatching.nowactive = true
                           animewatchingorangebaranimation.running = true
                           animecompleted.nowactive = false
                           animedropped.nowactive = false
                           addanime.nowactive = false
                       }

            contentItem: Text{
                text: animewatching.text
                font: animewatching.font
                opacity: enabled ? 1.0 : 0.3
                color: animewatching.nowactive ? "orange" : "gray"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                Rectangle {
                    visible: animewatching.nowactive ? true : false
                    color: "orange"
                    height: 3
                    width: 0
                    x: parent.width/2 - width/2
                    anchors.top: parent.bottom
                    anchors.topMargin: -7
                    radius: 20
                    NumberAnimation on width {
                        id: animewatchingorangebaranimation
                        from: 0
                        to: 55
                        duration: 500
                    }
                }
                Rectangle {
                    id: watchingdroppedseperator
                    color: "grey"
                    height: 20
                    width: 2
                    x: parent.width
                    y: parent.height/2 - height/2
                }
            }


            text: "Watching"
        }
        TabButton {
            height: 35
            id: animedropped
            property bool nowactive: false
            text: "Dropped"
            background: Rectangle {
                color: "#302b35"
            }
            onToggled: ()=>{
                           animewatching.nowactive = false
                           animecompleted.nowactive = false
                           animedropped.nowactive = true
                           animedroppedorangebaranimation.running = true
                           addanime.nowactive =false
                       }
            contentItem: Text{
                text: animedropped.text
                font: animedropped.font
                opacity: enabled ? 1.0 : 0.3
                color: animedropped.nowactive ? "orange" : "gray"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                Rectangle {
                    visible: animedropped.nowactive ? true : false
                    color: "orange"
                    height: 3
                    width: 0
                    x: parent.width/2 - width/2
                    anchors.top: parent.bottom
                    anchors.topMargin: -7
                    radius: 20
                    NumberAnimation on width {
                        id: animedroppedorangebaranimation
                        from: 0
                        to:50
                        duration: 500
                    }
                }
                Rectangle {
                    id: adddroppedseperator
                    color: "grey"
                    height: 20
                    width: 2
                    x: parent.width
                    y: parent.height/2 - height/2
                }
            }

        }
        TabButton {
            height: 35
            id: addanime
            property bool nowactive: false
            background: Rectangle {
                color: "#302b35"
            }
            onToggled: ()=>{
                           animewatching.nowactive = false
                           addanimeorangebaranimation.running = true
                           animecompleted.nowactive = false
                           animedropped.nowactive = false
                           addanime.nowactive = true
                       }


            contentItem: Text{
                text: addanime.text
                font: addanime.font
                opacity: enabled ? 1.0 : 0.3
                color: addanime.nowactive ? "orange" : "gray"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                Rectangle {
                    visible: addanime.nowactive ? true : false
                    color: "orange"
                    height: 3
                    width: 0
                    x: parent.width/2 - width/2
                    anchors.top: parent.bottom
                    anchors.topMargin: -7
                    radius: 20
                    NumberAnimation on width {
                        id: addanimeorangebaranimation
                        from: 0
                        to: 65
                        duration: 500
                    }
                }
            }


            text: "Add Anime"
        }



    }
    Component.onCompleted: {
        handler.getList();
    }
    Component {
        id: highlightC
        Rectangle {
            width: view.cellWidth; height: view.cellHeight
            color: "lightsteelblue"; radius: 5
            x: view.currentItem.x
            y: view.currentItem.y
            Behavior on x { SpringAnimation { spring: 3; damping: 0.2 } }
            Behavior on y { SpringAnimation { spring: 3; damping: 0.2 } }
        }
    }
    StackLayout{
        anchors.fill: parent
        currentIndex: bar.currentIndex
        Item {
            id: completed
            Rectangle {
                id: completedlayoutroot
                anchors.fill: parent
                anchors.topMargin: 25
                color: "#302b35"
                width: parent.width
                height: parent.height
                GridView {
                    anchors.fill: parent
                    anchors.margins: 4
                    id: view
                    //highlight: highlightC
                    //highlightFollowsCurrentItem: true
                    clip: true
                    model:  AnimeCompletedModel { id: animecompletedmodel ; }
                    cellWidth: 185
                    cellHeight: 320
                    delegate: numberDelegate
                }
                Component {
                    id: numberDelegate
                    Rectangle {
                        layer.enabled: true
                        objectName: "DelegateMainRectangle"
                        id: delegatebackgroundrectangle
                        width: 175
                        height: 300
                        color: "#302b35"
                        clip:true
                        radius: 10
                        Column {
                            anchors.fill: parent
                            spacing: 5
                            Image {
                                id: imageid
                                width: 170
                                height: 225
                                source: "file:" + model.imagepath
                            }
                            Text	{
                                id:titletext
                                clip:true
                                //anchors.top: imageid.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                elide: Text.ElideRight
                                width: parent.width
                                wrapMode: Text.Wrap
                                text: model.title
                                color: "white"
                            }
                        }
                        MouseArea {
                            width: parent.width
                            property bool ychange: false
                            property bool xchange: false
                            height: parent.height
                            hoverEnabled: true
                            onEntered: {

                                delegatebackgroundrectangle.z += 1
                                imageid.height += 50
                                imageid.width += 50
                                delegatebackgroundrectangle.height += 50
                                delegatebackgroundrectangle.width += 50
                                if(delegatebackgroundrectangle.height + delegatebackgroundrectangle.y > topparent.height)
                                {
                                    delegatebackgroundrectangle.y -= 75
                                    ychange = true
                                }
                                if(delegatebackgroundrectangle.width + delegatebackgroundrectangle.x > topparent.width)
                                {
                                    delegatebackgroundrectangle.x -= 100
                                    xchange = true
                                }
                                //Create timed event for the effect
                                timer1.interval = 100
                                timer1.triggered.connect(function() {
                                    for(var child in view.contentItem.children) {
                                        view.contentItem.children[child].opacity = 0.3
                                    }
                                    delegatebackgroundrectangle.opacity = 1
                                }
                                )
                                timer1.start()
                            }
                            onExited: {

                                delegatebackgroundrectangle.z -= 1
                                delegatebackgroundrectangle.clip = true
                                titletext.clip = true
                                imageid.clip = true

                                imageid.height -= 50
                                imageid.width -= 50

                                delegatebackgroundrectangle.height -= 50
                                delegatebackgroundrectangle.width -= 50
                                parent.color = "#302b35"
                                if(ychange === true)
                                {
                                    delegatebackgroundrectangle.y += 75
                                    ychange = false
                                }
                                if(xchange === true)
                                {
                                    delegatebackgroundrectangle.x += 100
                                    xchange = false
                                }
                                for(var child in view.contentItem.children) {
                                    view.contentItem.children[child].opacity = 1
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                id: completedfooter
                anchors.top: completedlayoutroot.bottom
                width:parent.width
                height: 40
                color: "#302b35"
            }
        }
        Item {
            id: watching
        }
        Item {
            id: dropped
            /*    Rectangle {
                anchors.fill: parent
                color: "blue"
            }*/
        }
        Item {
            id: add
            Rectangle {
                id: addrootrectangle
                anchors.fill: parent
                color: "#302b35"
                anchors.topMargin: 25
                height: parent.height + 25
                width: parent.width
                Rectangle {
                    id: addimagebackground
                    color: parent.color
                    height: 260
                    width: 185
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: 10
                    anchors.leftMargin: 10
                    Image {
                        id: addimage
                        height: 250
                        width: 175
                        anchors.centerIn: parent
                        source: "images/noimage.png"
                    }
                }
                Rectangle{
                    height: 200
                    width: parent.width - addimagebackground.width - 10
                    color: parent.color
                    anchors.left: addimagebackground.right
                    anchors.top: parent.top
                    anchors.leftMargin: 5
                    anchors.topMargin: 10
                    clip:true
                    Text {
                        id: titlelabel
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.leftMargin: 5
                        text: "Title: "
                        color: "orange"
                        font.pointSize: 12
                    }
                    TextInput {
                        width: parent.width - titlelabel.width - 20
                        height: 40
                        font.pointSize: 12
                        color: "orange"
                        id: titleedit
                        focus: true
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        anchors.left: titlelabel.right
                        anchors.leftMargin: 5
                        onTextChanged: {
                            if(timerforSearchLimit.running === true)
                            {
                                timerforSearchLimit.restart();
                                return;
                            }
                            timerforSearchLimit.interval = 1000
                            timerforSearchLimit.start();
                            timerforSearchLimit.triggered.connect(searchTitle)
                        }
                    }

                }

            }
        }
    }

    Keys.onPressed: (event) => {
                        if(event.key === Qt.Key_A && event.modifiers === Qt.ControlModifier)
                        addToAnime();
                    }

    function searchTitle() {
                                    if(titleedit.text.length === 0)
                                        return;
                                    console.log("Searching for  " + titleedit.text)
                                    var list = handler.searchTitle(titleedit.text)
                                    timerforSearchLimit.triggered.disconnect(searchTitle)
                                }

    function addToAnime()
    {
        console.log("Going to add new show to anime list");
    }
}
