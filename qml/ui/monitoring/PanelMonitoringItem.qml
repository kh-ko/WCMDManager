import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import EnumDefine 1.0
import ViewManager 1.0
import PanelMonitorItemModel 1.0

import "."
import "./component/."
import "../../control/."

Rectangle {
    property PanelMonitorItemModel itemModel: null
    id : panel
    color: "#333333"
    radius: 10

    width: itemModel.mIsDetail ? 830 : 415
    height: itemModel.mIsDetail ? 688 : 313

    border.color: mouseArea.containsMouse ? "#0085FF" : "#00000000"
    border.width: 2

    PanelMonotorItemTitle
    {
        id : title
        height: itemModel.mIsDetail? 77 : 127
        width: parent.width - 40
        isVMode: !itemModel.mIsDetail
        isAlarm: itemModel.mIsAlarm
        isComm : itemModel.mIsComm
        isRun  : itemModel.mIsRun
        dNum   : itemModel.mDeviceNum
        dName  : itemModel.mDeviceName
        pNum   : itemModel.mProductNo
        pName  : itemModel.mProductName

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Rectangle{
        id : dividerTitle

        height: 2
        width: parent.width - 40
        color: "#26ffffff"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: title.bottom
        anchors.topMargin: 10
    }

    PanelMonitorItemSimple
    {
        height: 94
        width: parent.width - 40
        visible : itemModel.mIsDetail ? false : true
        wcEventType : itemModel.mWcEventType
        currWeight  : itemModel.mCurrWeight
        totalCnt    : itemModel.mTotalcnt
        wcNGCnt     : itemModel.mWCNGCnt
        mdNGCnt     : itemModel.mMDNgCnt

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dividerTitle.bottom
        anchors.topMargin: 10
    }

    PanelMonitorItemDetail
    {
        height: 564
        width: parent.width - 40
        visible : itemModel.mIsDetail ? true : false
        wcEventType        : itemModel.mWcEventType
        mdSenstivity       : itemModel.mMdSenstivity
        mdSignal           : itemModel.mMdSignal
        currWeight         : itemModel.mCurrWeight
        tareWeight         : itemModel.mTareWeight
        underWeight        : itemModel.mUnderWeight
        underWarningWeight : itemModel.mUnderWaringWeight
        normalWeight       : itemModel.mNormalWeight
        overWarningWeight  : itemModel.mOverWaringWeight
        overWeight         : itemModel.mOverWeight
        totalCnt           : itemModel.mTotalcnt
        mdNGCnt            : itemModel.mMDNgCnt
        underCnt           : itemModel.mWCUnderNGCnt
        underWCnt          : itemModel.mWCUnderWaringNGCnt
        normalCnt          : itemModel.mWCNoramlCnt
        overWCnt           : itemModel.mWCOverWaringCnt
        overCnt            : itemModel.mWCOverCnt
        etcErrCnt          : itemModel.mWCEtcErrCnt
        tradeTotalWeight   : itemModel.mTradeTotalWeight

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dividerTitle.bottom
        anchors.topMargin: 10
    }

    Rectangle{
        anchors.fill: parent
        color : "#a9000000"
        visible: itemModel.mConnectState != EnumDefine.CONN_STATE_CONNECT
        UiLabel{
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            text : qsTr("Disconnet device")
            font.pixelSize : 20
            color: "#FFFFFF"
        }
    }

    MouseArea{
        id :mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onDoubleClicked: {
            itemModel.onCommandToggleDetail()
        }
    }
}
