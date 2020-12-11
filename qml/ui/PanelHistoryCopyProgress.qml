import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import MainModel 1.0

Dialog {
    property MainModel model : null
    property var value
    property var max

    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.NoAutoClose

    anchors.centerIn : parent
    scale: ViewManager.scale

    background: Rectangle
    {
        color : "#59000000"
        radius : 10
    }

    ProgressBar {
        id: progressBar
        height: parent.height * 0.5
        width: parent.width * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        to: 0
        value: 0
    }

    Connections {
        target: model

        onSignalEventCopyProgress : {
            progressBar.to = totalCnt
            progressBar.value = procIdx

        }

        onSignalEventCopyComplete : {
            dialog.close()
            dialog.destroy()
        }
    }
}
