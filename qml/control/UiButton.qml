import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0

Item {
    property int    colType          : EnumDefine.BTN_COLOR_TYPE_DEFAULT
    property int    fontSize         : 15
    property color  fontColor        : "#ACACAC"
    property string text             : "Button"
    property bool   isTextBtn        : false
    property alias  iconSource       : imageIcon.source
    property bool   isHover          : false
    property bool   isPress          : false

    signal signalEventClicked()

    id : control

    width: 187
    height: 60

    Rectangle{
        id: rectButton

        anchors.fill : parent

        radius       : control.isTextBtn ? 10 : height / 2
        color        : "#59000000"

        border.width : 2
        border.color : control.isHover && control.isPress == false ? "#0085FF" : "#00000000"

        Rectangle{
            id: rectIcon
            height                  : parent.height - 4
            width                   : control.isTextBtn ? parent.width - 4: height
            anchors.verticalCenter  : parent.verticalCenter
            anchors.left            : parent.left
            anchors.leftMargin      : 2

            radius                  : control.isTextBtn ? 10 : height / 2
            border.width            : 2
            border.color            : "#59FFFFFF"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: control.colType === EnumDefine.BTN_COLOR_TYPE_DEFAULT ? "#333333" : "#0085FF"

                }

                GradientStop {
                    position: 1
                    color: control.colType === EnumDefine.BTN_COLOR_TYPE_DEFAULT ? "#535353" : "#76BDFF"
                }
            }

            Image{
                id : imageIcon
                width: 20
                height: 20
                anchors.horizontalCenter : parent.horizontalCenter
                anchors.verticalCenter   : parent.verticalCenter

                fillMode: Image.PreserveAspectFit
            }
        }

        Text{
            id : textContent

            anchors.right: parent.right
            anchors.rightMargin: control.isTextBtn ? 0 :rectButton.radius / 2
            anchors.left: control.isTextBtn ? parent.left : rectIcon.right
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            font.pixelSize      : control.fontSize
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
        hoverEnabled: true

        onContainsMouseChanged  :  { control.isHover = containsMouse }
        onPressed               :  { control.isPress = true          }
        onReleased              :  { control.isPress = false         }
        onClicked               :  { control.signalEventClicked()    }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
