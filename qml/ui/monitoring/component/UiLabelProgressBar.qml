import QtQuick 2.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0
import ViewManager 1.0


Item {
    property int    fontSize         : 15
    property color  eventColor       : "#0085FF"
    property real   maxValue         : 100
    property real   value            : 100
    property bool   isNonHighlight   : false
    property alias  labelBgWidth     : labelBg.width
    property alias  labelColor       : labelText.color
    property alias  label            : labelText.text
    property alias  value01          : value01Text.text
    property alias  value01Width     : value01Text.width
    property alias  value02          : value02Text.text
    property alias  value02Width     : value02Text.width
    property alias  value03          : value03Text.text
    property alias  value03Width     : value03Text.width


    id : control

    width: 400
    height: 42


    onValueChanged:
    {
        if(control.isNonHighlight || control.value == 0)
            return;

        showAni.start();
        timer.restart();
    }

    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            closeAni.start()
        }
    }

    ParallelAnimation {
        id :showAni

        NumberAnimation {
            target: highlight
            properties: "opacity"
            duration: 250
            from : 0
            to: 0.5
            easing.type: Easing.InOutQuad
        }
    }

    ParallelAnimation {
        id :closeAni

        NumberAnimation {
            target: highlight
            properties: "opacity"
            duration: 250
            from : 0.5
            to: 0
            easing.type: Easing.InOutQuad
        }
    }

    Rectangle{
        id: bg

        anchors.fill : parent

        radius       : height / 2
        color        : "#59000000"
        border.width : 0

    }

    Glow {
        id : highlight
        anchors.fill: bg
        radius: 10
        samples: 17
        source: bg
        color: control.eventColor
        opacity: 0
    }

    Rectangle{
        id                      : bar
        color                   : control.eventColor
        radius                  : height / 2
        height                  : parent.height - 4
        width                   : control.maxValue === 0 ? 0 : labelBg.width + ((bg.width - labelBg.width - 4) * (control.value / control.maxValue))
        anchors.verticalCenter  : parent.verticalCenter
        anchors.left            : parent.left
        anchors.leftMargin      : 2
    }

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
    }

    Item {
        anchors.left: labelBg.right
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 20

        Text{
            id : value01Text
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            width: 100

            horizontalAlignment: Text.AlignRight
            verticalAlignment  : Text.AlignVCenter

            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            color : "#FFFFFF"
            text : "99,999.9 g"
        }
        Text{
            id : value02Text
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            width: 100

            horizontalAlignment: Text.AlignRight
            verticalAlignment  : Text.AlignVCenter

            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            color : "#FFFFFF"
            text : "0.44 %"
        }
        Text{
            id : value03Text
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            width: 100

            horizontalAlignment: Text.AlignRight
            verticalAlignment  : Text.AlignVCenter

            font.pixelSize: control.fontSize
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            color : "#FFFFFF"
            text : "99,999.9 pcs"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
