import QtQuick 2.0
import "."

Item {
    property int   senstivity : 400
    property int   signal     : 399
    property alias bgHeight   : bg.height
    id : control

    Image{
        id : arrow
        anchors.horizontalCenter: bg.horizontalCenter
        anchors.bottom: bg.top
        anchors.bottomMargin: 0

        sourceSize.height: 15
        sourceSize.width: 15
        source : "image/gauge_down_white.png"
    }

    Rectangle
    {
        id : bg
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin : 0
        anchors.verticalCenter: parent.verticalCenter

        height: 10

        Rectangle
        {
            property real min : control.senstivity * 2 * 0.25
            property real max : control.senstivity * 2 * 0.75
            property real range : max - min

            id : bar
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter

            width : range === 0 ? 0 :
                    (control.signal < min) ? 0 :
                    (control.signal > max) ? parent.width - 4 :
                    (parent.width - 4) * ((control.signal - min)/range)
            height: parent.height - 4
            color: control.signal > control.senstivity ? "#D9001B": "#0085FF"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.5;height:480;width:640}
}
##^##*/
