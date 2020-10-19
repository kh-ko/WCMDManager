import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelMDOPReportContainerModel 1.0
import PanelMDOPReportModel    1.0
import PanelMDOPReportRowModel 1.0

import "../../control/."
import "."

Rectangle {
    property PanelMDOPReportContainerModel containerModel : null
    property PanelMDOPReportModel reportModel
    property int  pageIdx
    property bool isEditMode : containerModel === null ? false : containerModel.mIsEditMode

    signal signalEventDeleteRow(int pageIdx, int rowIdxInPage)

    id : page

    width: 840
    height: 1188

    color: "#FFFFFF"

    Component.onCompleted: {
        for(var i = 0; i < reportModel.onCommandGetPageRowCnt(); i ++)
        {
            listRow.createObject(list, {"rowPageIdx" : i });
        }
    }

    Rectangle {
        id: rectangle7
        color: "#00000000"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50

        Rectangle {
            id: labelOperateHistory
            height: 40
            color: "#515151"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            border.width: 2

            Text {
                id: element3
                height: 34
                color: "#ffffff"
                text: qsTr("Operate history")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
            }
        }

        ColumnLayout {
            id: list
            spacing: -1
            anchors.top: labelOperateHistory.bottom
            anchors.topMargin: -1
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Rectangle {
                id: listHeader
                width: 200
                height: 100
                color: "#00000000"
                Layout.fillWidth: true

                Rectangle {
                    id: labelPNumTitle
                    width: 50
                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    border.width: 1

                    Text {
                        id: element5
                        text: qsTr("P NO")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                }

                Rectangle {
                    id: labelPNameTitle
                    width: 200
                    color: "#00000000"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: labelPNumTitle.right
                    anchors.leftMargin: -1
                    Text {
                        id: element8
                        text: qsTr("Product name")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    border.width: 1
                }

                Rectangle {
                    id: labellimitTitle
                    width: 150
                    color: "#00000000"
                    Text {
                        id: element9
                        text: qsTr("Limit criteria<br><br>(θ, mm)")
                        anchors.bottom: labelLimitFeTitle.top
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 0
                        anchors.rightMargin: 0
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Rectangle {
                        id: labelLimitFeTitle
                        y: 87
                        width: parent.width / 2
                        height: 33
                        color: "#00000000"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.left: parent.left
                        anchors.leftMargin: 0
                        border.width: 1

                        Text {
                            id: element10
                            text: qsTr("Fe")
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                            font.pixelSize: 12
                        }
                    }

                    Rectangle {
                        id: labelLimitSusTitle
                        color: "#00000000"
                        border.width: 1
                        anchors.top: labelLimitFeTitle.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.left: labelLimitFeTitle.right
                        anchors.leftMargin: -1

                        Text {
                            id: element11
                            text: qsTr("Sus")
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.fill: parent
                            font.pixelSize: 12
                        }
                    }
                    anchors.left: labelPNameTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                Rectangle {
                    id: labelTotalCntTitle
                    width: 120
                    color: "#00000000"
                    Text {
                        id: element12
                        text: qsTr("Total count")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    anchors.left: labellimitTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                Rectangle {
                    id: labelNGCntTitle
                    width: 120
                    color: "#00000000"
                    Text {
                        id: element13
                        text: qsTr("Detect count")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    anchors.left: labelTotalCntTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                Rectangle {
                    id: labelNGRateTitle
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    Text {
                        id: element14
                        text: qsTr("Detect rate(%)")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    anchors.left: labelNGCntTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }
            }
        }
    }

    Image{

        width: 194
        height: 93
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        fillMode: Image.PreserveAspectFit
        source: "image_icon/protect.jpg"

    }

    Text {
        id: pageNum
        x: 408
        y: 1131
        text: page.pageIdx + 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 12
    }


    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        visible: !page.isEditMode
    }


    Component{
        id: listRow
        Rectangle {
            property int rowPageIdx
            property PanelMDOPReportRowModel rowModel : reportModel === null ? null : reportModel.onCommandGetRowInPage(page.pageIdx, rowPageIdx)

            function setValus()
            {
                if(rowModel != null)
                {
                    inputPNum.text = rowModel.mPno
                    inputPName.text = rowModel.mPName
                    inputTotalCnt.text = rowModel.mTotalCnt
                    inputNGCnt.text = rowModel.mNGCnt
                    inputNGRate.text = rowModel.mNGRate
                    inputLimitFe.text = rowModel.mLimitFe;
                    inputLimitSus.text = rowModel.mLimitSus;
                }
                else
                {
                    inputPNum.text = ""
                    inputPName.text = ""
                    inputTotalCnt.text = ""
                    inputNGCnt.text = ""
                    inputNGRate.text = ""
                    inputLimitFe.text = ""
                    inputLimitSus.text = ""
                }
            }

            Component.onCompleted: {
                setValus();
            }

            width: 200
            height: 120
            color: "#00000000"

            Rectangle {
                id: inputPNumBox
                width: 50
                color: "#00000000"
                DocTextField {
                    id : inputPNum
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetPno(text)
                    }
                }
                anchors.left: parent.left
                anchors.leftMargin: 0
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0
            }

            Rectangle {
                id: inputPNameBox
                width: 200
                color: "#00000000"
                DocTextField {
                    id : inputPName
                    anchors.fill: parent
                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetPName(text)
                    }
                }
                anchors.left: inputPNumBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0
            }

            Rectangle {
                id: inputlimitBox
                width: 150
                color: "#00000000"
                Rectangle {
                    id: inputLimitFeBox
                    width: parent.width / 2
                    color: "#00000000"
                    DocTextField {
                        id : inputLimitFe
                        anchors.fill: parent
                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetLimitFe(text)
                        }
                    }
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                Rectangle {
                    id: inputLimitSusBox
                    color: "#00000000"
                    DocTextField {
                        id: inputLimitSus
                        anchors.fill: parent
                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetLimitSus(text)
                        }
                    }
                    anchors.left: inputLimitFeBox.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: inputLimitFeBox.top
                    anchors.rightMargin: 0
                    anchors.right: parent.right
                    anchors.bottomMargin: 0
                }
                anchors.left: inputPNameBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0
            }

            Rectangle {
                id: inputTotalCntBox
                width: 120
                color: "#00000000"
                DocTextField {
                    id : inputTotalCnt
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetTotalCnt(text)
                    }
                }
                anchors.left: inputlimitBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0
            }

            Rectangle {
                id: inputNGCntBox
                width: 120
                color: "#00000000"
                DocTextField {
                    id : inputNGCnt
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetNGCnt(text)
                    }
                }
                anchors.left: inputTotalCntBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0
            }

            Rectangle {
                id: inputNGRateBox
                color: "#00000000"
                DocTextField {
                    id : inputNGRate
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetNGRate(text)
                    }
                }
                anchors.left: inputNGCntBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.rightMargin: 0
                anchors.right: parent.right
                anchors.bottomMargin: 0
            }

            DocButton {
                width: height
                text: "X"
                visible: page.isEditMode

                anchors.left: parent.right
                anchors.leftMargin: 3
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5

                onClicked: {
                    page.signalEventDeleteRow(page.pageIdx, rowPageIdx)}
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:78;anchors_y:463}
}
##^##*/
