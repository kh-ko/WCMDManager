import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

Dialog {
    id: loadingDialog
    modal: true
    dim : true
    closePolicy: Popup.NoAutoClose

    anchors.centerIn : parent
    topPadding: 0
    topInset: 0
    bottomPadding: 0
    bottomInset: 0
    leftPadding: 0
    rightPadding: 0

    background: Rectangle
    {
        color : "#00000000"
    }


    BusyIndicator{
        implicitWidth: 200
        implicitHeight: 200

        running: loadingDialog.visible
    }
}
