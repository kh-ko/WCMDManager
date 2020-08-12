import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../control/."
import "."


Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    flags:Qt.FramelessWindowHint

    property int previousX
    property int previousY

    Rectangle
    {
        id    : rootContainer

        width  : parent.width < 1920 ? 1920 : parent.width
        height : (parent.height * width) / parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        scale  : parent.width < 1920 ? parent.width / 1920 : 1

        color : "#131313"

        PanelLeftMenu
        {
            id : leftMenu

            width: 225
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        StackView{
            anchors.left: leftMenu.right
            anchors.leftMargin: 0
            anchors.top: parent.bottom
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

        }
    }

    PanelWindowFrame{
        anchors.fill: parent
        root : window
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
