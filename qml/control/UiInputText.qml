import QtQuick 2.0
import QtQuick.Controls 2.3
import FontManager 1.0
import MouseEventSpy 1.0

Item {
    property int    fontSize         : 15
    property int    labelWidth       : 0
    property color  labelColor       : "#ACACAC"
    property string labelText        : "Button"
    property color  inputColor       : "#FFFFFF"
    property alias  inputText        : inputText.text
    property alias  echoMode         : inputText.echoMode
    property alias  validator        : inputText.validator
    property bool   isDisable        : false
    property bool   isHover          : false
    property bool   isPress          : false

    id : control

    width: 187
    height: 60

    signal signalEventChangedInputFocus(var value)

    Rectangle{
        id: rectInputText

        anchors.fill : parent

        radius       : height / 2
        color        : "#59000000"

        border.width : 2
        border.color : control.isHover && control.isPress == false ? "#0085FF" : "#00000000"

        Rectangle{
            id: rectLabel
            height                  : parent.height - 4
            width                   : control.labelWidth
            anchors.verticalCenter  : parent.verticalCenter
            anchors.left            : parent.left
            anchors.leftMargin      : 2

            radius                  : height / 2
            border.width            : control.isDisable ? 0 : 2
            border.color            : "#59FFFFFF"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: control.isDisable ? "#59000000" : "#333333"

                }

                GradientStop {
                    position: 1
                    color: control.isDisable ? "#59000000" : "#535353"
                }
            }

            UiLabel{
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter

                color : control.labelColor
                text  : control.labelText
            }
        }

        TextField{
            id : inputText

            background: Rectangle{ color: "#00000000" }

            color : control.inputColor
            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName

            text : "Button"
            anchors.left: rectLabel.right
            anchors.leftMargin: rectInputText.radius / 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: rectInputText.radius / 2

            onFocusChanged: {
                console.debug("focus changed : " + focus)
                control.signalEventChangedInputFocus(focus)
            }
        }

        MouseArea{
            anchors.fill: parent
            visible: control.isDisable
        }

        Rectangle{
            id : rectDim

            anchors.fill: parent

            radius      : rectLabel.radius
            color       : "#59000000"

            visible     : control.isPress && !control.isDisable
        }
    }

    MouseArea{
        anchors.fill: parent
        visible: !control.isDisable

        hoverEnabled: true
        propagateComposedEvents : true

        onContainsMouseChanged  :  { control.isHover = containsMouse }
        onPressed               :  { if(inputText.focus) {mouse.accepted = false; return;} control.isPress = true          }
        onReleased              :  { if(inputText.focus) {mouse.accepted = false; return;} control.isPress = false         }
        onClicked               :
        {
            mouse.accepted = false

            if(inputText.focus == false)
            {
                inputText.forceActiveFocus()

                if(inputText.text.length > 0)
                inputText.selectAll()
            }
        }
    }

    Connections {
        target: MouseEventSpy
        onMouseEventDetected: {

            if(inputText.focus == true)
            {
                inputText.focus = false
            }
        }
    }
}








