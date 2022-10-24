import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

Rectangle
{
    property bool checked : false

    signal signalEventClicked()

    id : control

    radius: 3
    color : "#00000000"
    border.width : 3
    border.color: control.down ? "#17a81a" : "#21be2b"

    Rectangle {
        width: parent.width * 0.5
        height: parent.height * 0.5

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        radius: 2
        color: mouseArea.isPress ? "#17a81a" : "#21be2b"
        visible: control.checked
    }

    MouseArea{
        property bool isPress : false

        id : mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onPressed: { isPress = true}
        onReleased: { isPress = false}
        onClicked: { control.signalEventClicked()}
    }
}


