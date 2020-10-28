import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import PanelSyncModel 1.0
import PanelSyncListItemModel 1.0

import EnumDefine 1.0
import ViewManager 1.0

import "../control/."

Item {
    property bool isOpen : false

    id: panel

    function open()
    {
        panel.isOpen = true

        msgboxConfirm.visible = false;
        busyCancel.visible = false;
        btnSync.visible = true;
        deviceList.model = listModel;
        panelmodel.onCommandOpen();

        dialog.show();
    }

    function close()
    {
        panel.isOpen = false

        deviceList.model = null
        listModel.clear();
        msgboxConfirm.visible = false;
        busyCancel.visible = false;

        panelmodel.onCommandClose()
    }

    PanelSyncModel{
        id :panelmodel

        onSignalEventChangedIsSearch: {
            if(panelmodel.mIsSearch)
                true;

            for(var i = 0; i < panelmodel.onCommandGetDlistSize(); i ++)
            {
                listModel.append({"dataIdx" : i})
            }
        }
    }

    ApplicationWindow{
        id :dialog
        modality: Qt.WindowModal

        height: 600
        minimumHeight: 400
        minimumWidth: 450

        title: qsTr("Sync")
        flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

        onClosing: {
            if(panelmodel.onCommandGetIsSyncing())
                close.accepted = false

            panel.close();
        }

        Rectangle{
            width                   : parent.width / ViewManager.scale
            height                  : parent.height / ViewManager.scale
            anchors.verticalCenter  : parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            scale                   : ViewManager.scale
            color                   : "#131313"

            UiScrollView{
                id : listWrapper
                anchors.fill : parent

                contentWidth    : listWrapper.width < 450 ? 450 : listWrapper.width
                contentHeight   : listWrapper.height < 400 ? 400 : listWrapper.height

                Item{
                    anchors.fill: parent

                    ListView {
                        id: deviceList
                        spacing: 10
                        anchors.top : parent.top
                        anchors.topMargin: 20
                        anchors.bottom: containerBtn.top
                        anchors.bottomMargin: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.right: parent.right
                        anchors.rightMargin: 20

                        clip: true

                        ListModel
                        {
                            id: listModel
                        }

                        delegate : Rectangle
                        {
                            id: itemDdevice
                            property PanelSyncListItemModel itemModel : panelmodel.onCommandGetDlistItem(dataIdx)

                            height: 100
                            anchors.left: parent.left
                            anchors.leftMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0
                            color : "#333333"
                            radius : 10
                            UiLabel{
                                id : labelDNum
                                height: 26
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.top: parent.top
                                anchors.topMargin: 10

                                text: qsTr("Device : ")
                            }

                            UiLabel{
                                id : labelDNumValue
                                height: 26
                                anchors.left: labelDNum.right
                                anchors.leftMargin: 0
                                anchors.top: parent.top
                                anchors.topMargin: 10

                                color: "#FFFFFF"
                                text: ("000" + itemDdevice.itemModel.mDeviceNO).slice(-3) + " " + itemDdevice.itemModel.mDeviceName
                            }


                            UiLabel{
                                id : labelDIP
                                height: 26
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.top: labelDNumValue.bottom
                                anchors.topMargin: 0

                                text: qsTr("IP :  ")
                            }

                            UiLabel{
                                id : labelDIPValue
                                height: 20
                                anchors.left: labelDIP.right
                                anchors.leftMargin: 0
                                anchors.top: labelDNumValue.bottom
                                anchors.topMargin: 0

                                color: "#FFFFFF"
                                text: itemDdevice.itemModel.mDeviceIP
                            }

                            UiLabel{
                                id : labelLastSyncDate
                                height: 26
                                anchors.right: labelLastSyncDateValue.left
                                anchors.rightMargin: 0
                                anchors.top: labelDNumValue.bottom
                                anchors.topMargin: 0

                                text: qsTr("Last sync date : ")
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignRight
                            }

                            UiLabel{
                                id : labelLastSyncDateValue
                                height: 26
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                anchors.top: labelDNumValue.bottom
                                anchors.topMargin: 0

                                color: "#FFFFFF"
                                text: itemDdevice.itemModel.mLastSyncDate
                            }

                            ProgressBar {
                                id: progressBar
                                height: 10
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.right: labelSyncState.left
                                anchors.rightMargin: 20
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 13
                                value: itemDdevice.itemModel.mProgressValue

                                visible:itemDdevice.itemModel.mIsDisconnected                                        ? false :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? false :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? false :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? false :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? false : true
                            }

                            UiLabel{
                                id : labelSyncState
                                width: 170
                                height: 26
                                anchors.leftMargin: itemDdevice.itemModel.mIsDisconnected                                        ? 20 :
                                                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? 20 :
                                                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? 20 :
                                                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? 20 :
                                                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? 20 : undefined
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                anchors.verticalCenter: progressBar.verticalCenter

                                horizontalAlignment : Text.AlignRight

                                color: itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? "#D9001B" :
                                       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? "#D9001B" :
                                       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? "#D9001B" :
                                       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? "#D9001B" : "#FFFFFF"

                                text: itemDdevice.itemModel.mIsDisconnected                           ? qsTr("Disconnected device.") :
                                      itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_READY   ? qsTr("READY")   :
                                      itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_SYNCING ? qsTr("SYNCING") :
                                      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? qsTr("FAIL : Synchronization is in progress on another device.") :
                                      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? qsTr("FAIL : Synchronization has been cancelled.") :
                                      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? qsTr("FAIL : The sync file is invalid.") :
                                      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? qsTr("FAIL : Network error has occurred.") : qsTr("COMPLETE")
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
                            id :btnSync
                            text: qsTr("Sync")
                            isTextBtn : true
                            colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                            fontColor : "#FFFFFF"

                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.right: parent.right
                            anchors.rightMargin: 0

                            onSignalEventClicked:
                            {
                                btnSync.visible = false;
                                panelmodel.onCommandSync()
                            }
                        }

                        UiButton{
                            id :btnClose
                            text: qsTr("Close")
                            isTextBtn : true

                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.right: btnSync.left
                            anchors.rightMargin: 20

                            onSignalEventClicked :{
                                if(panelmodel.onCommandGetIsSyncing())
                                {
                                    msgboxConfirm.visible = true;
                                    return;
                                }


                                dialog.close();
                                //panel.close();
                            }
                        }
                    }

                    Rectangle{
                        id: msgboxConfirm
                        anchors.fill: parent
                        color: "#d9000000"

                        Item{
                            id: element
                            width: 500
                            height: 200
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            UiLabel{
                                color: "#ffffff"
                                text: qsTr("Do you want to cancle sync?")
                                font.pixelSize: 20
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            UiButton{
                                id :btnYes
                                text: qsTr("Yes")
                                isTextBtn : true
                                colType: EnumDefine.BTN_COLOR_TYPE_BLUE

                                fontColor : "#FFFFFF"

                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 20
                                anchors.right: parent.right
                                anchors.rightMargin: 20

                                onSignalEventClicked: {
                                    panelmodel.onCommandCancle()
                                    busyCancel.visible = true;
                                }
                            }

                            UiButton{
                                id :btnNo
                                text: qsTr("No")
                                isTextBtn : true

                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 20
                                anchors.right: btnYes.left
                                anchors.rightMargin: 20

                                onSignalEventClicked :{
                                    msgboxConfirm.visible = false
                                }
                            }
                        }
                    }
                }
            }

            MouseArea{
                id : busyCancel
                anchors.fill: parent
                hoverEnabled: true

                BusyIndicator{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width < parent.height ? parent.width / 10 : parent.height / 10
                    height: width
                    running: true
                }
            }

            Timer {
                interval: 500; running: busyCancel.visible; repeat: true
                onTriggered:
                {
                    if(panelmodel.onCommandGetIsSyncing() === false)
                    {
                        dialog.close();
                    }
                }
            }
        }

        UiDialogLoading{
            id : busyDlg
            visible: panelmodel.mIsSearch
        }
    }
}

/*
Dialog{
    id : panel
    modality: Qt.WindowModal

    anchors.centerIn: parent
    padding: 0

    background: Rectangle{
        radius: 10
        color : "#333333"
    }

    onOpened:
    {
        msgboxConfirm.visible = false;
        busyCancel.visible = false;
        btnSync.visible = true;
        deviceList.model = listModel;
        panelmodel.onCommandOpen();

        for(var i = 0; i < panelmodel.onCommandGetDlistSize(); i ++)
        {
            listModel.append({"dataIdx" : i})
        }
    }

    onClosed:
    {
        deviceList.model = null
        listModel.clear();
        msgboxConfirm.visible = false;
        busyCancel.visible = false;
    }

    PanelSyncModel{
        id :panelmodel
    }

    Item{

        implicitWidth: 600
        implicitHeight: 600

        UiLabel
        {
            id : labelTitle
            height: 40
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            color     : "#FFFFFF"
            text : qsTr("Sync")
        }

        ListView {
            id: deviceList
            spacing: 0
            anchors.top: labelTitle.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: containerBtn.top
            anchors.bottomMargin: 20
            //model: listModel
            clip: true

            ListModel
            {
                id: listModel
            }

            delegate: Item
            {
                id: itemDdevice
                property PanelSyncListItemModel itemModel : panelmodel.onCommandGetDlistItem(dataIdx)

                height: 100
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                UiLabel{
                    id : labelDNum
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    text: qsTr("Device : ")
                }

                UiLabel{
                    id : labelDNumValue
                    height: 26
                    anchors.left: labelDNum.right
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    color: "#FFFFFF"
                    text: ("000" + itemDdevice.itemModel.mDeviceNO).slice(-3) + " " + itemDdevice.itemModel.mDeviceName
                }


                UiLabel{
                    id : labelDIP
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    //visible: !itemDdevice.itemModel.mIsDisconnected
                    text: qsTr("IP :  ")
                }

                UiLabel{
                    id : labelDIPValue
                    height: 20
                    anchors.left: labelDIP.right
                    anchors.leftMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    color: "#FFFFFF"
                    //visible: !itemDdevice.itemModel.mIsDisconnected
                    text: itemDdevice.itemModel.mDeviceIP
                }

                UiLabel{
                    id : labelLastSyncDate
                    height: 26
                    anchors.right: labelLastSyncDateValue.left
                    anchors.rightMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    text: qsTr("Last sync date : ")
                }

                UiLabel{
                    id : labelLastSyncDateValue
                    height: 26
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    color: "#FFFFFF"
                    text: itemDdevice.itemModel.mLastSyncDate
                }

                ProgressBar {
                    id: progressBar
                    height: 10
                    width : 430
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 13
                    value: itemDdevice.itemModel.mProgressValue

                    visible: labelSyncState.anchors.leftMargin > 100 ? true : false
                }

                UiLabel{
                    id : labelSyncState
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: itemDdevice.itemModel.mIsDisconnected                                        ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? 20 : 450
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: progressBar.verticalCenter


                    color: itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? "#D9001B" : "#FFFFFF"

                    text: itemDdevice.itemModel.mIsDisconnected                           ? qsTr("Disconnected device.") :
                          itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_READY   ? qsTr("READY")   :
                          itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_SYNCING ? qsTr("SYNCING") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? qsTr("FAIL : Synchronization is in progress on another device.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? qsTr("FAIL : Synchronization has been cancelled.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? qsTr("FAIL : The sync file is invalid.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? qsTr("FAIL : Network error has occurred.") : qsTr("COMPLETE")
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
            anchors.bottomMargin: 0

            UiButton{
                id :btnSync
                text: qsTr("Sync")
                isTextBtn : true
                colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                fontColor : "#FFFFFF"

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                onSignalEventClicked:
                {
                    btnSync.visible = false;
                    panelmodel.onCommandSync()
                }
            }

            UiButton{
                id :btnClose
                text: qsTr("Close")
                isTextBtn : true

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: btnSync.left
                anchors.rightMargin: 20

                onSignalEventClicked :{
                    if(panelmodel.onCommandGetIsSyncing())
                    {
                        msgboxConfirm.visible = true;
                        return;
                    }

                    panel.close();
                }
            }
        }

        Rectangle{
            id: msgboxConfirm
            anchors.fill: parent
            radius: 20
            color: "#d9000000"

            Item{
                id: element
                width: 500
                height: 200
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                UiLabel{
                    color: "#ffffff"
                    text: qsTr("Do you want to cancle sync?")
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                UiButton{
                    id :btnYes
                    text: qsTr("Yes")
                    isTextBtn : true
                    colType: EnumDefine.BTN_COLOR_TYPE_BLUE

                    fontColor : "#FFFFFF"

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    onSignalEventClicked: {
                        panelmodel.onCommandCancle()
                        busyCancel.visible = true;
                    }
                }

                UiButton{
                    id :btnNo
                    text: qsTr("No")
                    isTextBtn : true

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: btnYes.left
                    anchors.rightMargin: 20

                    onSignalEventClicked :{
                        msgboxConfirm.visible = fales
                    }
                }
            }
        }

        MouseArea{
            id : busyCancel
            anchors.fill: parent
            hoverEnabled: true

            BusyIndicator{
                width: 300
                height: 300
                running: true
            }
        }

        Timer {
            interval: 500; running: busyCancel.visible; repeat: true
            onTriggered:
            {
                if(panelmodel.onCommandGetIsSyncing() === false)
                {
                    panel.close();
                }
            }
        }
    }
}
*/
/*
Item {
    id : panel

    width: 1000
    height: 1000

    visible: false

    function open()
    {
        msgboxConfirm.visible = false;
        busyCancel.visible = false;
        panel.visible = true;
        btnSync.visible = true;
        panelmodel.onCommandOpen();

        for(var i = 0; i < panelmodel.onCommandGetDlistSize(); i ++)
        {
            listModel.append({"dataIdx" : i})
        }
    }

    function close()
    {
        listModel.clear();
        panel.visible = false;
        msgboxConfirm.visible = false;
        busyCancel.visible = false;
    }

    PanelSyncModel{
        id :panelmodel
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
    }

    Rectangle
    {
        height: 900
        width : 600

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        color: "#d9000000"
        radius: 20

        UiLabel
        {
            id : labelTitle
            height: 40
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            color     : "#FFFFFF"
            text : qsTr("Sync")
        }

        ListView {
            id: deviceList
            spacing: 0
            anchors.top: labelTitle.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: containerBtn.top
            anchors.bottomMargin: 20
            model: listModel
            clip: true

            ListModel
            {
                id: listModel
            }

            delegate: Item
            {
                id: itemDdevice
                property PanelSyncListItemModel itemModel : panelmodel.onCommandGetDlistItem(dataIdx)

                height: 100
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                UiLabel{
                    id : labelDNum
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    text: qsTr("Device : ")
                }

                UiLabel{
                    id : labelDNumValue
                    height: 26
                    anchors.left: labelDNum.right
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    color: "#FFFFFF"
                    text: ("000" + itemDdevice.itemModel.mDeviceNO).slice(-3) + " " + itemDdevice.itemModel.mDeviceName
                }


                UiLabel{
                    id : labelDIP
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    //visible: !itemDdevice.itemModel.mIsDisconnected
                    text: qsTr("IP :  ")
                }

                UiLabel{
                    id : labelDIPValue
                    height: 20
                    anchors.left: labelDIP.right
                    anchors.leftMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    color: "#FFFFFF"
                    //visible: !itemDdevice.itemModel.mIsDisconnected
                    text: itemDdevice.itemModel.mDeviceIP
                }

                UiLabel{
                    id : labelLastSyncDate
                    height: 26
                    anchors.right: labelLastSyncDateValue.left
                    anchors.rightMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    text: qsTr("Last sync date : ")
                }

                UiLabel{
                    id : labelLastSyncDateValue
                    height: 26
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: labelDNumValue.bottom
                    anchors.topMargin: 0

                    color: "#FFFFFF"
                    text: itemDdevice.itemModel.mLastSyncDate
                }

                ProgressBar {
                    id: progressBar
                    height: 10
                    width : 430
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 13
                    value: itemDdevice.itemModel.mProgressValue

                    visible: labelSyncState.anchors.leftMargin > 100 ? true : false
                }

                UiLabel{
                    id : labelSyncState
                    height: 26
                    anchors.left: parent.left
                    anchors.leftMargin: itemDdevice.itemModel.mIsDisconnected                                        ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? 20 :
                                        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? 20 : 450
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.verticalCenter: progressBar.verticalCenter


                    color: itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? "#D9001B" :
                           itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? "#D9001B" : "#FFFFFF"

                    text: itemDdevice.itemModel.mIsDisconnected                           ? qsTr("Disconnected device.") :
                          itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_READY   ? qsTr("READY")   :
                          itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_SYNCING ? qsTr("SYNCING") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? qsTr("FAIL : Synchronization is in progress on another device.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? qsTr("FAIL : Synchronization has been cancelled.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? qsTr("FAIL : The sync file is invalid.") :
                          itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? qsTr("FAIL : Network error has occurred.") : qsTr("COMPLETE")
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
                id :btnSync
                text: qsTr("Sync")
                isTextBtn : true
                colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                fontColor : "#FFFFFF"

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                onSignalEventClicked:
                {
                    btnSync.visible = false;
                    panelmodel.onCommandSync()
                }
            }

            UiButton{
                id :btnClose
                text: qsTr("Close")
                isTextBtn : true

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: btnSync.left
                anchors.rightMargin: 20

                onSignalEventClicked :{
                    if(panelmodel.onCommandGetIsSyncing())
                    {
                        msgboxConfirm.visible = true;
                        return;
                    }

                    panel.close();
                }
            }
        }

        Rectangle{
            id: msgboxConfirm
            anchors.fill: parent
            radius: 20
            color: "#d9000000"

            Item{
                id: element
                width: 500
                height: 200
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                UiLabel{
                    color: "#ffffff"
                    text: qsTr("Do you want to cancle sync?")
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                UiButton{
                    id :btnYes
                    text: qsTr("Yes")
                    isTextBtn : true
                    colType: EnumDefine.BTN_COLOR_TYPE_BLUE

                    fontColor : "#FFFFFF"

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    onSignalEventClicked: {
                        panelmodel.onCommandCancle()
                        busyCancel.visible = true;
                    }
                }

                UiButton{
                    id :btnNo
                    text: qsTr("No")
                    isTextBtn : true

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: btnYes.left
                    anchors.rightMargin: 20

                    onSignalEventClicked :{
                        msgboxConfirm.visible = fales
                    }
                }
            }
        }

        MouseArea{
            id : busyCancel
            anchors.fill: parent
            hoverEnabled: true

            BusyIndicator{
                width: 300
                height: 300
                running: true
            }
        }

        Timer {
            interval: 500; running: busyCancel.visible; repeat: true
            onTriggered:
            {
                if(panelmodel.onCommandGetIsSyncing() === false)
                {
                    panel.close();
                }
            }
        }
    }
}
*/
/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
