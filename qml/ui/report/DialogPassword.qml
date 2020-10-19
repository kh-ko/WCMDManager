import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import DialogPasswordModel 1.0

import "../../control/."

Dialog {
    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside

    anchors.centerIn : parent
    topPadding: 0
    topInset: 0
    bottomPadding: 0
    bottomInset: 0
    leftPadding: 0
    rightPadding: 0

    signal signalEventMatchPassword()

    background: Rectangle
    {
        color : "#333333"
        radius : 10
    }


    onVisibleChanged: {
        if(visible)
        {
            warningMsg.visible = false
            inputPassword.inputText = ""
        }
    }

    DialogPasswordModel{
        id : pwdModel
    }

    Item{
        implicitWidth: 500
        implicitHeight: 300

        UiLabel{
            id : warningMsg
            color : "#D9001B"
            text: qsTr("* Please check password")
            visible: false

            anchors.left: inputPassword.left
            anchors.leftMargin: 20
            anchors.right: inputPassword.right
            anchors.rightMargin: 0
            anchors.bottom: inputPassword.top
            anchors.bottomMargin: 10
        }

        UiInputText{
            id: inputPassword
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            echoMode : TextInput.Password
            labelText: qsTr("Password")
            labelWidth: 150
            anchors.verticalCenter: parent.verticalCenter
        }

        UiButton{
            id : btnOk
            isTextBtn: true
            text : qsTr("Ok")
            fontColor : "#FFFFFF"
            colType: EnumDefine.BTN_COLOR_TYPE_BLUE

            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onSignalEventClicked:
            {
                if(inputPassword.inputText == pwdModel.onCommandGetPassword())
                {
                    dialog.signalEventMatchPassword()
                    dialog.close()
                }
                else
                {
                    warningMsg.visible = true
                }
            }
        }

        UiButton{
            id : btnCancle
            isTextBtn: true
            text : qsTr("cancle")
            fontColor : "#FFFFFF"

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onSignalEventClicked: { dialog.close()}
        }
    }
}
