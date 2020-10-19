import QtQuick.Window 2.12
import QtQuick 2.0

Item {
    property Window root : null
    property int previousX
    property int previousY

    id : panel

    MouseArea {
        id: topArea
        height: 5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        // We set the shape of the cursor so that it is clear that this resizing
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // We memorize the position along the Y axis
            previousY = mouseY
        }

        // When changing a position, we recalculate the position of the window, and its height
        onMouseYChanged: {
            var dy = mouseY - previousY
            root.setY(root.y + dy)
            root.setHeight(root.height - dy)
        }
    }

    // Similar calculations for the remaining three areas of resize
    MouseArea {
        id: bottomArea
        height: 5
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            previousY = mouseY
        }

        onMouseYChanged: {
            var dy = mouseY - previousY
            root.setHeight(root.height + dy)
        }
    }

    MouseArea {
        id: leftArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            left: parent.left
        }
        cursorShape: Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            root.setX(root.x + dx)
            root.setWidth(root.width - dx)
        }
    }

    MouseArea {
        id: rightArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            right: parent.right
        }
        cursorShape:  Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            root.setWidth(root.width + dx)
        }
    }

    // The central area for moving the application window
    // Here you already need to use the position both along the X axis and the Y axis
    MouseArea {
        height: 35
        anchors.top: topArea.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0


        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            root.setX(root.x + dx)
        }

        onMouseYChanged: {
            var dy = mouseY - previousY
            root.setY(root.y + dy)
        }
    }

    Rectangle
    {
        height              : 35
        width               : 150
        anchors.top         : parent.top
        anchors.topMargin   : 0
        anchors.right       : parent.right
        anchors.rightMargin : 0

        color : "#590085ff"

        Rectangle
        {
            property bool isPress : false
            property bool isHover : false

            id : btnMinimize

            width                 : 25
            height                : 25
            anchors.verticalCenter: parent.verticalCenter
            anchors.right         : btnToggleFullScreen.left
            anchors.rightMargin   : 20

            color        : "#00000000"
            border.width : 2
            border.color : btnMinimize.isHover && btnMinimize.isPress === false ? "#0085FF" : "#00000000"

            Rectangle{
                width: 15
                height: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter  : parent.verticalCenter

                color                   : "#ffffff"
            }

            Rectangle{
                anchors.fill : parent
                color        : "#59000000"

                visible      : btnMinimize.isPress
            }

            MouseArea{
                anchors.fill : parent
                hoverEnabled : true

                onContainsMouseChanged : {btnMinimize.isHover = containsMouse}
                onPressed              : {btnMinimize.isPress = true }
                onReleased             : {btnMinimize.isPress = false}
                onClicked              : {root.showMinimized()}
            }
        }

        Rectangle
        {
            property bool isPress : false
            property bool isHover : false

            id : btnToggleFullScreen

            width                   : 25
            height                  : 25
            anchors.verticalCenter  : parent.verticalCenter
            anchors.right           : btnClose.left
            anchors.rightMargin     : 20

            color        : "#00000000"
            border.width : 2
            border.color : btnToggleFullScreen.isHover &&  btnToggleFullScreen.isPress === false ? "#0085FF" : "#00000000"

            Rectangle{
                width                   : 15
                height                  : 15
                anchors.verticalCenter  : parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                visible     : !(root.visibility === Window.FullScreen)
                color       : "#00000000"
                border.color: "#ffffff"
                border.width: 1
            }

            Rectangle{
                width                   : 13
                height                  : 13
                anchors.verticalCenter  : parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                visible                         : (root.visibility === Window.FullScreen)
                color                           : "#00000000"
                anchors.verticalCenterOffset    : -2
                anchors.horizontalCenterOffset  : -2
                border.color: "#ffffff"
                border.width: 1
            }

            Rectangle{
                width                   : 13
                height                  : 13
                anchors.verticalCenter  : parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                visible                         : (root.visibility === Window.FullScreen)
                color                           : "#00000000"
                anchors.verticalCenterOffset    : 2
                anchors.horizontalCenterOffset  : 2
                border.color                    : "#ffffff"
                border.width                    : 1
            }

            Rectangle{
                anchors.fill: parent
                color       : "#59000000"

                visible     : btnToggleFullScreen.isPress
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled : true

                onContainsMouseChanged  : {btnToggleFullScreen.isHover = containsMouse}
                onPressed               : {btnToggleFullScreen.isPress = true }
                onReleased              : {btnToggleFullScreen.isPress = false}
                onClicked :
                {
                    if(root.visibility === Window.FullScreen)
                        root.showNormal()
                    else
                        root.showFullScreen();
                }
            }
        }

        Rectangle
        {
            property bool isPress : false
            property bool isHover : false

            id : btnClose

            width: 25
            height: 25
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20

            color        : "#00000000"
            border.width : 2
            border.color : btnClose.isHover &&  btnClose.isPress === false ? "#0085FF" : "#00000000"

            Rectangle{
                width: 2
                height: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                color : "#FFFFFF"
                rotation: -45
            }

            Rectangle{
                width: 2
                height: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                color : "#FFFFFF"
                rotation: 45
            }

            Rectangle{
                anchors.fill: parent
                color : "#59000000"

                visible: btnClose.isPress
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled : true

                onContainsMouseChanged  : {btnClose.isHover = containsMouse}
                onPressed               : {btnClose.isPress = true }
                onReleased              : {btnClose.isPress = false}
                onClicked               : {Qt.quit()               }
            }
        }
    }
}
