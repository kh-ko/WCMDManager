import QtQuick 2.0
import "."

Item {
    property color splitColor: "#00000000"

    id : control

    Rectangle{
        anchors.fill : parent
        color        : control.splitColor
    }

    MouseArea {
        anchors.fill: parent

        cursorShape : Qt.SizeHorCursor

        drag.target: parent
/*
        onMouseXChanged: {

            if(control.isDisable)
                return;

            if(control.x < control.preSpliterX + 20)
            {
                control.x = control.preSpliterX + 20
            }
            else if(control.x  > control.nextSpliterX - 20)
            {
                control.x = control.nextSpliterX - 20
            }
        }
        */
    }
/*
    onNextSpliterXChanged:
    {
        if (control.nextSpliterX < 1)
            return;

        if(control.x  > control.nextSpliterX)
        {
            control.x = control.nextSpliterX - control.width
        }
    }
    */
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
