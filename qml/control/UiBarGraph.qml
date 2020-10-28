import QtQuick 2.0

Rectangle {
    property alias labelText    : labelText.text
    property alias labelWidth   : labelBg.width
    property alias labelBgColor : labelBg.color
    property alias labelColor   : labelText.color
    property alias barColor     : bar.color
    property var   max          : 100
    property var   min          : 0
    property var   value        : 50

    radius: height / 2
    color:  "#59000000"

    Rectangle{
        property real  barLen : (max - min) < 0 || (max - min) == 0 ? 0 : ((parent.width - 4 - labelBg.width)) * ((value - min) / (max - min))

        id : bar

        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter

        height: parent.height - 4
        width : labelBg.width + barLen
        radius: height / 2
        color:  "#0085FF"
    }

    Rectangle{
        id : labelBg

        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter

        height: parent.height - 4
        width : 104
        radius: height / 2
        color:  "#59000000"

        UiLabel{
            id : labelText
            anchors.left: parent.left
            anchors.leftMargin: labelBg.radius
            anchors.right: parent.right
            anchors.rightMargin: labelBg.radius

            horizontalAlignment: Text.AlignHCenter
            height: parent.height
            color: "#FFFFFF"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
