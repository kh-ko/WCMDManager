import QtQuick 2.0
import QtQuick.Controls 2.3
import FontManager 1.0
import EnumDefine 1.0
import ViewManager 1.0

Item {
    property int    eventType        : EnumDefine.EVENT_TYPE_WEIGHT_NORMAL
    property int    weight           : 999000

    id : control

    width: 400
    height: 42

    Rectangle{
        id: rectInputText

        anchors.fill : parent

        radius       : height / 2
        color        : control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER  ? "#59F59A23" :
                       control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER ? "#59D9001B" : "#59000000"

        border.width : 0

        Rectangle{
            id : labelBg
            height                  : parent.height - 4
            width                   : parent.height - 4
            anchors.verticalCenter  : parent.verticalCenter
            anchors.left            : parent.left
            anchors.leftMargin      : 2

            color : control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER  ? "#F59A23" :
                    control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER ? "#D9001B" : "#0085FF"
            radius                  : height / 2
            border.width            : 2
            border.color            : "#59FFFFFF"

            Image{
                visible: control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER ? true : false
                height: parent.height * 0.5
                width : parent.width  * 0.5
                rotation: 180

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "image/gauge_down_white.png"
            }

            Image{
                visible: control.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER ? true : false
                height: parent.height * 0.5
                width : parent.width  * 0.5

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "image/gauge_down_white.png"
            }

            Image{
                visible: control.eventType !== EnumDefine.EVENT_TYPE_WEIGHT_OVER  && control.eventType !== EnumDefine.EVENT_TYPE_WEIGHT_UNDER ? true : false
                height: parent.height * 0.5
                width : parent.width  * 0.5

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                source: "image/normal.png"
            }
        }

        Text{
            id : valueText
            anchors.left: labelBg.right
            anchors.leftMargin: labelBg.radius / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: rectInputText.radius / 2

            horizontalAlignment: Text.AlignRight
            verticalAlignment  : Text.AlignVCenter

            height: parent.height * (70/90)
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            color : "#FFFFFF"
            text : (weight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            font.pixelSize: 100
            fontSizeMode: Text.VerticalFit
        }
    }
}


