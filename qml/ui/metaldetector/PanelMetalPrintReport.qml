import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0

import "../../control/."

Rectangle {
    id : panel

    width : 439
    height: 93

    color : "#333333"
    radius: 10

    signal signalClickedOperateReport()
    signal signalClickedCheckupReport()

    UiButton{
        id : btnOperateReport
        width: 200
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Operate report")
        iconSource: "image_icon/print.png"

        onSignalEventClicked: { panel.signalClickedOperateReport(); }
    }

    UiButton{
        id : btnCheckupReport
        width: 200
        anchors.verticalCenterOffset: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Checkup report")
        iconSource: "image_icon/print.png"

        onSignalEventClicked: { panel.signalClickedCheckupReport(); }
    }
}
