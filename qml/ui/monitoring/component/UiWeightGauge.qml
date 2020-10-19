import QtQuick 2.12
import QtGraphicalEffects 1.12
import ViewManager 1.0
import EnumDefine 1.0

Item {

    property int  eventType     : EnumDefine.EVENT_TYPE_WEIGHT_NORMAL
    property real under         : 100
    property real underWarning  : 200
    property real normal        : 300
    property real overWarning   : 450
    property real over          : 800
    property real weight        : 300

    property real min : normal - under > over - normal ? under - ((normal - under) * 0.4):normal - ((over - normal) * 1.4)
    property real max : normal + (normal - min)
    property real range : max - min

    id: control
    width : 526
    height : 108

    Rectangle{
        id :bg
        height : 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color : "#59000000"
        radius: height / 2
    }

    Rectangle{
        id :bar
        height : 6
        anchors.verticalCenter: bg.verticalCenter
        anchors.right: bg.right
        anchors.rightMargin: 2
        anchors.left: bg.left
        anchors.leftMargin: 2
        color : "#D9001B"
        radius: height / 2

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#D9001B"
            }

            GradientStop {
                position: range === 0 ? 0.001 : ((control.underWarning - control.min) / control.range) - 0.001
                color: "#D9001B"
            }

            GradientStop {
                position: range === 0 ? 0.002 : ((control.underWarning - control.min) / control.range)
                color: "#0085FF"
            }

            GradientStop {
                position: range === 0 ? 0.998 : ((control.overWarning - control.min) / control.range)
                color: "#0085FF"
            }

            GradientStop {
                position: range === 0 ? 0.999 : ((control.overWarning - control.min) / control.range) + 0.001
                color: "#F59A23"
            }
            GradientStop {
                position: 1
                color: "#F59A23"
            }

            orientation: Gradient.Horizontal
        }
    }

    Image{
        id : gaugeWeight
        height: 15
        width:  15
        anchors.left: bar.left
        anchors.leftMargin: control.range === 0 ? -1 * (width / 2) : weight < control.min ?  - 20 - (width / 2) : weight > control.max ? (bar.width - width / 2) + 20 :  (bar.width * ((weight - control.min) / control.range) - (width / 2))
        anchors.bottom: bar.top
        anchors.topMargin: 0
        source: eventType === EnumDefine.WEIGHT_OVER_TYPE ? "image/big_down_yellow.png" :
                eventType === EnumDefine.WEIGHT_UNDER_TYPE ? "image/big_down_red.png" : "image/big_down_blue.png"

    }

}

