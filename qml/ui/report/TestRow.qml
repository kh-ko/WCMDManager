import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelMDCheckReportContainerModel 1.0
import PanelMDCheckReportModel    1.0
import PanelMDCheckReportRowModel 1.0

import "../../control/."
import "."

Rectangle
{
    id: itemDdevice
    //property PanelSyncListItemModel itemModel : panelmodel.onCommandGetDlistItem(dataIdx)

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
        //text: ("000" + itemDdevice.itemModel.mDeviceNO).slice(-3) + " " + itemDdevice.itemModel.mDeviceName
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
        //text: itemDdevice.itemModel.mDeviceIP
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
        //text: itemDdevice.itemModel.mLastSyncDate
    }

    ProgressBar {
        id: progressBar
        height: 10
        width : 430
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: labelSyncState.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 13
        //value: itemDdevice.itemModel.mProgressValue

        //visible:itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? false :
        //        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? false :
        //        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? false :
        //        itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? false : true
    }

    UiLabel{
        id : labelSyncState
        width: 170
        height: 26
        //anchors.leftMargin: itemDdevice.itemModel.mIsDisconnected                                        ? 20 :
        //                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? 20 :
        //                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? 20 :
        //                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? 20 :
        //                    itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? 20 : 450
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: progressBar.verticalCenter

        horizontalAlignment : Text.AlignRight

        //color: itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? "#D9001B" :
        //       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? "#D9001B" :
        //       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? "#D9001B" :
        //       itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? "#D9001B" : "#FFFFFF"
        //
        //text: itemDdevice.itemModel.mIsDisconnected                           ? qsTr("Disconnected device.") :
        //      itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_READY   ? qsTr("READY")   :
        //      itemDdevice.itemModel.mState === EnumDefine.RSYNC_STATE_SYNCING ? qsTr("SYNCING") :
        //      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_ALREADY_SYNCING ? qsTr("FAIL : Synchronization is in progress on another device.") :
        //      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_CANCLE          ? qsTr("FAIL : Synchronization has been cancelled.") :
        //      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_FILE_INFO       ? qsTr("FAIL : The sync file is invalid.") :
        //      itemDdevice.itemModel.mRSyncError === EnumDefine.RSYNC_ERROR_NETWORK         ? qsTr("FAIL : Network error has occurred.") : qsTr("COMPLETE")
    }
}
