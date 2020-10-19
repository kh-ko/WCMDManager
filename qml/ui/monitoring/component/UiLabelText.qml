import QtQuick 2.0
import QtQuick.Controls 2.3
import FontManager 1.0

Item {
    property int    fontSize         : 15

    property alias  icon             : image.source
    property alias  labelBgWidth     : labelBg.width
    property alias  labelColor       : labelText.color
    property alias  label            : labelText.text
    property alias  textColor        : valueText.color
    property alias  text             : valueText.text

    id : control

    width: 400
    height: 42

    Rectangle{
        id: rectInputText

        anchors.fill : parent

        radius       : height / 2
        color        : "#59000000"
        border.width : 0

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
            text : "일이삼사오륙칠팍구십일이삼사오"
        }
    }
}


