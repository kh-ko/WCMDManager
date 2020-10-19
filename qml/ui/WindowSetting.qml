import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import WindowSettingModel 1.0

import "../control/."

ApplicationWindow{
    id : win
    modality : Qt.WindowModal

    height: 500
    width: 550
    minimumHeight: 500
    minimumWidth: 550

    title : qsTr("Setting")

    function open()
    {
        comboLanguage.selLanguage = settingModel.onCommandGetLanguage();
        inputPassword.inputText = settingModel.onCommandGetPassword();
        inputMonitoringRefreshCycle.inputText = (settingModel.onCommandGetRefreshCycle() / 1000).toLocaleString(ViewManager.locale, 'f', 1)

        for(var i = 0; i < settingModel.onCommandGetDeviceCnt(); i ++)
        {
            deviceInfoComponent.createObject(containerInfo,{"dataIdx":i})
        }

        win.show()
    }

    Component.onCompleted: {console.debug("WindowSetting:Create")}
    Component.onDestruction:{console.debug("WindowSetting:Destroy")}

    onClosing: { win.destroy() }

    WindowSettingModel{ id : settingModel }

    Rectangle{
        width: parent.width / ViewManager.scale
        height: parent.height / ViewManager.scale
        scale : ViewManager.scale
        color : "#333333"

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        UiScrollView{
            id : scrollView
            width: parent.width

            anchors.left : parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: containerBtn.top
            anchors.bottomMargin: 0

            contentWidth: scrollView.width
            contentHeight: 447 > containerInfo.height + 40 ? 447 : containerInfo.height + 40

            Rectangle{
                color: "#333333"
                anchors.fill: parent

                ColumnLayout{
                    id : containerInfo
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left : parent.left
                    anchors.leftMargin: 20
                    width : scrollView.width - 40
                    spacing: 10

                    UiComboBox{
                        property int selLanguage : EnumDefine.LANG_ENG
                        id : comboLanguage
                        labelText: qsTr("Language")
                        labelWidth: 220
                        inputText: selLanguage === EnumDefine.LANG_ENG ? "Eng" : "한국어"

                        Layout.fillWidth: true
                        height: 42

                        onSignalEventClick:
                        {
                            inputText = value
                            comboLanguage.selLanguage = tag
                        }

                        listModel : ListModel{
                            ListElement {
                                itemTag: EnumDefine.LANG_ENG
                                itemValue: "Eng"
                            }
                            ListElement {
                                itemTag: EnumDefine.LANG_KOR
                                itemValue: "한국어"
                            }
                        }
                    }

                    UiInputText{
                        id: inputPassword
                        inputText: ""
                        labelText: qsTr("Password")
                        labelWidth: 220

                        Layout.fillWidth: true
                        height: 42
                    }

                    UiInputText{
                        id: inputMonitoringRefreshCycle
                        inputText: ""
                        labelText: qsTr("Monitoring refresh cycle")
                        labelWidth: 220

                        Layout.fillWidth: true
                        height: 42
                    }

                    UiButton{
                        id :btnNewDevice
                        text: qsTr("New device")
                        isTextBtn : true
                        colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                        fontColor : "#FFFFFF"

                        Layout.fillWidth: true
                        height: 42

                        onSignalEventClicked:
                        {
                            deviceInfoComponent.createObject(containerInfo,{"dataIdx":-1})
                        }
                    }

                    UiLabel{
                        verticalAlignment: Text.AlignBottom
                        Layout.fillWidth: true
                        height: 50
                        color: "#FFFFFF"
                        font.pixelSize : 20

                        text : qsTr("Device list")
                    }
                }
            }
        }

        Item{
            id : containerBtn
            height: 60
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            UiButton{
                id :btnApply
                text: qsTr("Apply")
                isTextBtn : true
                colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                fontColor : "#FFFFFF"

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                onSignalEventClicked:
                {
                    settingModel.onCommandSetSetting(comboLanguage.selLanguage, inputPassword.inputText, inputMonitoringRefreshCycle.inputText)

                    for(var i = 5; i < containerInfo.children.length; i ++)
                    {
                        var item = containerInfo.children[i]
                        settingModel.onCommandSetDeviceInfo(item.isNew(), item.getDNum(), item.getDName(), item.getDIP())
                    }

                    win.close()
                }
            }

            UiButton{
                id :btnCancle
                text: qsTr("Cancle")
                isTextBtn : true

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: btnApply.left
                anchors.rightMargin: 20

                onSignalEventClicked :{
                    win.close()
                }
            }
        }
    }

    Component{
        id : deviceInfoComponent

        Item
        {
            function isNew()
            {
                return (dataIdx == -1)
            }

            function getDNum()
            {
                return inputDeviceNum.inputText
            }

            function getDName()
            {
                return inputDeviceName.inputText
            }

            function getDIP()
            {
                return inputDeviceIp.inputText
            }

            property int dataIdx : -1
            Layout.preferredHeight: 42 * 3 + 40
            Layout.fillWidth: true

            Component.onCompleted: {

                if(dataIdx == -1)
                {
                    inputDeviceNum.inputText = ""
                    inputDeviceName.inputText = ""
                    inputDeviceIp.inputText = ""
                    return;
                }

                inputDeviceNum.inputText = settingModel.onCommandGetDeviceNum(dataIdx)
                inputDeviceName.inputText = settingModel.onCommandGetDeviceName(dataIdx)
                inputDeviceIp.inputText = settingModel.onCommandGetDeviceIP(dataIdx)
            }

            Rectangle{ anchors.fill: parent; radius: 10; color : "#434343"}

            ColumnLayout{
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                spacing: 10

                UiInputText{
                    id: inputDeviceNum
                    inputText: ""
                    labelText: qsTr("Device number")
                    labelWidth: 210
                    isDisable: !(dataIdx == -1)

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight : 1
                }

                UiInputText{
                    id: inputDeviceName
                    inputText: ""
                    labelText: qsTr("Device name")
                    labelWidth: 210

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight : 1
                }

                UiInputText{
                    id: inputDeviceIp
                    inputText: ""
                    labelText: qsTr("Device IP")
                    labelWidth: 210

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight : 1
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:6;anchors_y:88}D{i:11;anchors_height:200;anchors_x:65;anchors_y:220}
}
##^##*/
