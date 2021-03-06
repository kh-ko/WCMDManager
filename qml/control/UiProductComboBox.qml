import QtQuick 2.0
import QtQuick.Controls 2.3
import FontManager 1.0
import ViewManager 1.0
import MouseEventSpy 1.0

Item {
    property ListModel listModel

    property int    fontSize         : 15
    property int    labelWidth       : 0
    property color  labelColor       : "#ACACAC"
    property string labelText        : "Button"
    property color  inputColor       : "#FFFFFF"
    property string inputText        : "Button"
    property bool   isHover          : false
    property bool   isPress          : false

    id : control

    width: 187
    height: 60

    signal signalEventClick(var data)

    Rectangle{
        id: rectCombo

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
            border.width            : 2
            border.color            : "#59FFFFFF"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#333333"

                }

                GradientStop {
                    position: 1
                    color: "#535353"
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

        UiLabel{
            id : labelText

            color : control.inputColor
            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName

            text : control.inputText
            anchors.left: rectLabel.right
            anchors.leftMargin: rectLabel.radius / 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: rectLabel.radius / 2
        }


        Rectangle{
            id : rectDim

            anchors.fill: parent

            radius      : rectLabel.radius
            color       : "#59000000"

            visible     : control.isPress
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents : true

        onContainsMouseChanged  :  { control.isHover = containsMouse }
        onPressed               :  { control.isPress = true          }
        onReleased              :  { control.isPress = false         }
        onClicked               :  { dlgExtend.open()                }
    }

    Dialog {
        id: dlgExtend
        modal: true
        dim : false
        closePolicy: Popup.CloseOnPressOutside
        background: Rectangle{
            color : "#d9000000"
            radius: 10
            border.width: 1
            border.color: "#000000"
        }

        y: parent.height
        topPadding: 0
        topInset: 0
        bottomPadding: 0
        bottomInset: 0
        leftPadding: 0
        rightPadding: 0

        width: control.width * ViewManager.scale
        height: 220 * ViewManager.scale

        Item{
            width : parent.width / ViewManager.scale
            height: parent.height / ViewManager.scale
            anchors.centerIn: parent
            scale: ViewManager.scale

            Item{
                anchors.left : parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                width : parent.width
                height: parent.height

                ListView {
                    id: productList
                    spacing: 0
                    anchors.fill : parent
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    model: control.listModel
                    clip: true

                    delegate: Rectangle{

                        id : comboItem
                        height: 60
                        //radius: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        color : mouseAreaItem.containsMouse ? "#0085FF" :"#00000000"

                        UiLabel
                        {
                            height: 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.bottom: parent.verticalCenter
                            anchors.bottomMargin: 0

                            color     : "#FFFFFF"
                            text : ("000" + productNo).slice(-3)
                        }
                        UiLabel
                        {
                            height: 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.top: parent.verticalCenter
                            anchors.topMargin: 0

                            color     : "#FFFFFF"
                            text : productName
                        }

                        MouseArea{
                            id : mouseAreaItem
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                dlgExtend.close()

                                control.signalEventClick(productSeq)
                            }
                        }
                    }
                }
            }
        }
    }
}








