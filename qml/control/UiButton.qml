import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import FontManager 1.0

Item {
    property int    fontSize         : 20
    property color  fontColor        : "#ffffff"
    property string text             : "TEXT"
    property alias  iconSource       : imageIcon.source
    property int    radius           : 5
    property int    borderWidth      : 1
    property color  borderColor      : "#000000"
    property color  color            : "#0085FF"
    property alias  gradient         : rectButton.gradient

    property bool   isPress          : false

    signal signalEventClicked()

    id : control

    width: 200
    height: 200

    Rectangle{
        id: rectButton

        anchors.fill : parent

        radius       : control.radius
        border.width : control.borderWidth
        border.color : control.borderColor
        color        : control.color

        Image{
            id : imageIcon

            anchors.horizontalCenter : parent.horizontalCenter
            anchors.verticalCenter   : parent.verticalCenter
        }

        Text{
            id : textContent

            anchors.fill        : parent

            font.pointSize      : control.fontSize
            verticalAlignment   : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            color               : control.fontColor
            font.family         : FontManager.nanumGothicName

            text: control.text

        }

        Rectangle{
            id : rectDim

            anchors.fill: parent

            radius      : rectButton.radius
            color       : "#59000000"

            visible     : control.isPress
        }
    }

    MouseArea{
        anchors.fill: parent

        onPressed   :  { control.isPress = true       }
        onReleased  :  { control.isPress = false      }
        onClicked   :  { control.signalEventClicked() }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
