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

    signal signalClickedReport()

    UiButton{
        id : btnReport
        width: 200
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Report")
        iconSource: "image_icon/print.png"

        onSignalEventClicked: { panel.signalClickedReport(); }
    }
}
