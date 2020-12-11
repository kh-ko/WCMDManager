import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."

Item {
    property int    dNum
    property string company
    property string department
    property string position
    property string name
    property alias  deviceList : comboDeviceNum.listModel

    id : panel
    width: 300
    height: 300

    signal signalEventChagnedValue(string dNum, string dName, string company, string department, string position, string name)

    function open(dNum, dName, company, department, position, name, limitCriteriaFe, limitCriteriaSus, haccp, checkupcycle)
    {
        comboDeviceNum.inputText    = ("000" + dNum).slice(-3)
        inputDeviceName.inputText   = dName
        inputCompany.inputText      = company
        inputDepartment.inputText   = department
        inputPosition.inputText     = position
        inputName.inputText         = name

        popup.show()
    }

    Window
    {
        id : popup

        modality : Qt.WindowModal
        minimumHeight: 630
        minimumWidth: 500

        title: qsTr("Management infomation")
        flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

        Rectangle
        {
            color : "#333333"
            anchors.fill: parent

            Item{
                width: parent.width / ViewManager.scale
                height: parent.height / ViewManager.scale
                scale : ViewManager.scale

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                Item{
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    height: 800

                    UiComboBox{
                        id : comboDeviceNum
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        z : 1
                        labelText: qsTr("Device number")
                        labelWidth: 160

                        onSignalEventClick:
                        {
                            comboDeviceNum.inputText = tag

                            inputDeviceName.inputText = value.split(" ")[1]
                        }
                    }
                    UiInputText{
                        id: inputDeviceName
                        anchors.top: comboDeviceNum.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        inputText: panel.company
                        labelText: qsTr("Device Name")
                        labelWidth: 160
                    }

                    UiInputText{
                        id: inputCompany
                        anchors.top: inputDeviceName.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        inputText: panel.company
                        labelText: qsTr("Company")
                        labelWidth: 160
                    }

                    UiInputText{
                        id: inputDepartment
                        anchors.top: inputCompany.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        inputText: panel.department
                        labelText: qsTr("Department")
                        labelWidth: 160
                    }

                    UiInputText{
                        id: inputPosition
                        anchors.top: inputDepartment.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        inputText: panel.position
                        labelText: qsTr("Position")
                        labelWidth: 160
                    }

                    UiInputText{
                        id: inputName
                        anchors.top: inputPosition.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                        height: 42
                        inputText: panel.name
                        labelText: qsTr("Name")
                        labelWidth: 160
                    }
                }


                Item{
                    id : containerBtn
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    height: 80
                    //color :"#434343"

                    UiButton{
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        text        : qsTr("Cancle")
                        isTextBtn   : true
                        fontColor: "#FFFFFF"

                        onSignalEventClicked: { popup.close()}
                    }

                    UiButton{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        text        : qsTr("Apply")
                        isTextBtn   : true
                        colType     : EnumDefine.BTN_COLOR_TYPE_BLUE
                        fontColor: "#FFFFFF"

                        onSignalEventClicked: {
                            panel.signalEventChagnedValue(comboDeviceNum.inputText   ,
                                                          inputDeviceName.inputText  ,
                                                          inputCompany.inputText     ,
                                                          inputDepartment.inputText  ,
                                                          inputPosition.inputText    ,
                                                          inputName.inputText        )

                            popup.close()
                        }
                    }
                }
            }
        }
    }
}
