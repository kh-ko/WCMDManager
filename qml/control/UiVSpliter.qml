import QtQuick 2.0

Item {
    property bool  isDisable : false
    property int   minGap    : 0
    property color splitColor: "#00000000"

    property int  previousY

    id : control

    Rectangle{
        anchors.fill : parent
        color        : control.splitColor
    }

    MouseArea {
        anchors.fill: parent

        cursorShape: control.isDisable ? undefined : Qt.SizeVerCursor

        drag.target: parent

        onPressed: {
            control.previousY = mouseY
        }

        onMouseYChanged: {

            if(control.isDisable)
                return;

            var dy = mouseY - control.previousY
            var margin = control.anchors.topMargin + dy

            if(margin < control.minGap)
                margin = minGap

            control.anchors.topMargin = margin
        }
    }
}
