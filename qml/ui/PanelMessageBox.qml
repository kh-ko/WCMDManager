import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import MainModel 1.0
import "../control/."

Dialog {
    property MainModel model : null
    property var value
    property var max

    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

    anchors.centerIn : parent
    scale: ViewManager.scale

    function showMessage(message)
    {
        labelMessage.text = message
        dialog.open()
    }

    background: Rectangle
    {
        color : "#59000000"
        radius : 10
    }

    Item{
        width: parent.width; height: parent.height

        UiLabel{
            id : labelMessage
            anchors.top: parent.top; anchors.topMargin: 10; anchors.bottom: btnClose.top; anchors.bottomMargin: 10; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

            color : "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiButton{
            id : btnClose
            width: 180
            height: 42
            colType: EnumDefine.BTN_COLOR_TYPE_DEFAULT
            isTextBtn: true
            text : qsTr("Close")

            anchors.bottom: parent.bottom; anchors.bottomMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10
            //fontColor: "#ffffff"

            onSignalEventClicked: {
                dialog.close()
            }
        }
    }
}
