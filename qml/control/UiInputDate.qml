import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls 1.5
import FontManager 1.0

Item {
    property int    fontSize         : 15
    property date   inputDate        : new Date()
    property alias  icon             : image.source
    property alias  labelBgWidth     : labelBg.width
    property alias  labelColor       : labelText.color
    property alias  label            : labelText.text
    property alias  textColor        : valueText.color


    id : control

    width: 400
    height: 42

    function setDate(year, month, day)
    {
        inputDate = new Date(year, month - 1, day)

        dateDialog.close()
    }

    Rectangle{
        id: rectInputText

        anchors.fill : parent

        radius       : height / 2
        color        : "#59000000"
        border.width : 2
        border.color : mouseArea.containsMouse && mouseArea.isPress == false ? "#0085FF" : "#00000000"

        Rectangle{
            id : labelBg
            height                  : parent.height - 4
            width                   : 125
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

            Text{
                id: labelText
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: labelBg.radius
                anchors.right: parent.right
                anchors.rightMargin: labelBg.radius


                horizontalAlignment: Text.AlignLeft
                verticalAlignment  : Text.AlignVCenter

                font.pixelSize: control.fontSize
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight
                color : "#ACACAC"
                text  : "Weight NG"

            }

            Item
            {
                width: parent.height
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                Image{
                    id : image
                    width: parent.width / 2
                    height: parent.height / 2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                }
            }
        }

        Text{
            id : valueText
            anchors.left: labelBg.right
            anchors.leftMargin: labelBg.radius / 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: rectInputText.radius / 2

            horizontalAlignment: Text.AlignLeft
            verticalAlignment  : Text.AlignVCenter

            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            color : "#FFFFFF"
            text : "" +inputDate.getFullYear() + "-" + (inputDate.getMonth() + 1) + "-" + inputDate.getDate()
        }

        Rectangle{
            id : rectDim

            anchors.fill: parent

            radius      : height / 2
            color       : "#59000000"

            visible     : mouseArea.isPress
        }
    }

    MouseArea{
        property  bool  isPress: false
        id :mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onPressed  :  { mouseArea.isPress = true  }
        onReleased :  { mouseArea.isPress = false }
        onClicked  :  { calendar.selectedDate = control.inputDate; dateDialog.open()}
    }

    Dialog {
        id: dateDialog
        modal: true
        dim : true
        closePolicy: Popup.CloseOnPressOutside

        y: parent.height
        topPadding: 0
        topInset: 0
        bottomPadding: 0
        bottomInset: 0
        leftPadding: 0
        rightPadding: 0

        Calendar {
            id: calendar
            onDoubleClicked: {
                control.inputDate = date
                dateDialog.close();
            }
        }
    }
}
