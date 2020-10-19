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

Rectangle {
    property PanelMDCheckReportContainerModel containerModel : null
    property PanelMDCheckReportModel reportModel
    property int  pageIdx
    property bool isEditMode : containerModel.mIsEditMode

    signal signalEventDeleteRow(int pageIdx, int rowIdxInPage)

    id : page

    width: 840
    height: 1188

    color: "#FFFFFF"

    Component.onDestruction: {
    }

    Component.onCompleted: {
        for(var i = 0; i < reportModel.onCommandGetPageRowCnt(); i ++)
        {
            listRow.createObject(list, {"rowPageIdx" : i });
        }
    }

    DocTextField {
        id: title
        height: 50
        text: containerModel == null ? "" : containerModel.mReportTitle
        fontFamily: "Arial"
        anchors.top: parent.top
        anchors.topMargin: 100
        fontSize:  25
        fontBold:  true
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        onTextChanged: {
            if(inputFocus == false) return;
            containerModel.onCommandSetReportTitle(text)
        }
    }

    Rectangle {
        id: rectangle7
        color: "#00000000"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: title.bottom
        anchors.topMargin: 30
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
                text: qsTr("Check history")
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
                    id: labelTimeTitle
                    width: 80
                    color: "#00000000"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: labelPNumTitle.right
                    anchors.leftMargin: -1
                    Text {
                        text: qsTr("Check time")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                    border.width: 1
                }

                Rectangle {
                    id: labelPNameTitle
                    width: 200
                    color: "#00000000"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: labelTimeTitle.right
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
                    width: 99
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
                        height: 34
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

                ColumnLayout {
                    id: labelJudgTitle
                    width: 200
                    spacing: -1
                    anchors.left: labellimitTitle.right
                    anchors.leftMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    Rectangle {
                        id: rectangle9
                        width: 200
                        height: 200
                        color: "#ffffff"
                        border.width: 1
                        Layout.preferredHeight: 1
                        Layout.preferredWidth: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Text {
                            text: qsTr("Judgment")
                            anchors.fill: parent
                            font.pixelSize: 12
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }

                    RowLayout {
                        id: rowLayout1
                        width: 100
                        height: 100
                        spacing: -1
                        Layout.preferredHeight: 1
                        Layout.preferredWidth: 1
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Rectangle {
                            id: rectangle11
                            width: 200
                            height: 200
                            color: "#ffffff"
                            border.width: 1
                            Layout.preferredHeight: 1
                            Layout.preferredWidth: 1
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Text {
                                text: qsTr("Fe")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle14
                            width: 200
                            height: 200
                            color: "#ffffff"
                            border.width: 1
                            Layout.preferredWidth: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("Sus")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }

                    RowLayout {
                        id: rowLayout2
                        width: 100
                        height: 100
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        spacing: -1
                        Layout.fillHeight: true
                        Layout.preferredHeight: 1
                        Rectangle {
                            id: rectangle15
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            Layout.fillWidth: true
                            border.width: 1
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("1th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle16
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            Layout.fillWidth: true
                            border.width: 1
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("2th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle17
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            border.width: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("3th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle18
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            border.width: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("1th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle19
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            border.width: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("2th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }

                        Rectangle {
                            id: rectangle20
                            width: 200
                            height: 200
                            color: "#ffffff"
                            Layout.preferredWidth: 1
                            border.width: 1
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: 1

                            Text {
                                text: qsTr("3th")
                                anchors.fill: parent
                                font.pixelSize: 12
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }

                Rectangle {
                    id: labelComment
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    Text {
                        id: element14
                        text: qsTr("Comment")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    anchors.left: labelJudgTitle.right
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
        id : listRow

        Rectangle {
            color: "#00000000"
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            property int rowPageIdx
            property PanelMDCheckReportRowModel rowModel : reportModel === null ? null : reportModel.onCommandGetRowInPage(page.pageIdx, rowPageIdx)

            function setValus()
            {
                if(rowModel != null)
                {
                    inputPNum.text      = rowModel.mPno
                    inputTime.text      = rowModel.mCheckTime
                    inputPName.text     = rowModel.mPName
                    inputLimitFe.text   = rowModel.mLimitFe
                    inputLimitSus.text  = rowModel.mLimitSus
                    inputJudgFe01.text  = rowModel.mFe01
                    inputJudgFe02.text  = rowModel.mFe02
                    inputJudgFe03.text  = rowModel.mFe03
                    inputJudgSus01.text = rowModel.mSus01
                    inputJudgSus02.text = rowModel.mSus02
                    inputJudgSus03.text = rowModel.mSus03
                    inputComment.text   = rowModel.mComment
                }
                else
                {
                    inputPNum.text      = ""
                    inputTime.text      = ""
                    inputPName.text     = ""
                    inputLimitFe.text   = ""
                    inputLimitSus.text  = ""
                    inputJudgFe01.text  = ""
                    inputJudgFe02.text  = ""
                    inputJudgFe03.text  = ""
                    inputJudgSus01.text = ""
                    inputJudgSus02.text = ""
                    inputJudgSus03.text = ""
                    inputComment.text   = ""
                }
            }

            Component.onCompleted: {
                setValus();
            }

            Rectangle {
                id: inputPNumBox
                width: 50
                color: "#00000000"
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                border.width: 1

                DocTextField {
                    id : inputPNum
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetPNo(text)
                    }
                }
            }

            Rectangle {
                id: inputTimeBox
                width: 80
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputPNumBox.right
                anchors.leftMargin: -1
                border.width: 1

                DocTextField {
                    id : inputTime
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetCheckTime(text)
                    }
                }
            }

            Rectangle {
                id: inputPNameBox
                width: 200
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputTimeBox.right
                anchors.leftMargin: -1
                border.width: 1

                DocTextField {
                    id : inputPName
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetPName(text)
                    }
                }
            }

            Rectangle {
                id: inputLimitBox
                width: 99
                color: "#00000000"
                anchors.left: inputPNameBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0

                Rectangle {
                    id: inputLimitFeBox
                    y: 87
                    width: parent.width / 2
                    height: parent.height
                    color: "#00000000"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 1

                    DocTextField {
                        id : inputLimitFe
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetLimitFe(text)
                        }
                    }
                }

                Rectangle {
                    id: inputLimitSusBox
                    color: "#00000000"
                    border.width: 1
                    anchors.top: inputLimitFeBox.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: inputLimitFeBox.right
                    anchors.leftMargin: -1

                    DocTextField {
                        id : inputLimitSus
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetLimitSus(text)
                        }
                    }
                }

            }

            RowLayout {
                id: inputJudgBox
                width: 200
                spacing: -1
                anchors.left: inputLimitBox.right
                anchors.leftMargin: -1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgFe01
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetFe01(text)
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgFe02
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetFe02(text)
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgFe03
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetFe03(text)
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgSus01
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetSus01(text)
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgSus02
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetSus02(text)
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 200
                    color: "#00000000"
                    Layout.preferredWidth: 1
                    Layout.fillWidth: true
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1

                    DocTextField {
                        id : inputJudgSus03
                        anchors.fill: parent

                        onTextChanged: {
                            if(inputFocus == false) return;
                            if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                            rowModel.onCommandSetSus03(text)
                        }
                    }
                }
            }

            Rectangle {
                id: inputCommentBox
                color: "#00000000"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: inputJudgBox.right
                anchors.leftMargin: -1
                border.width: 1
                anchors.bottom: parent.bottom
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.bottomMargin: 0

                DocTextField {
                    id : inputComment
                    anchors.fill: parent

                    onTextChanged: {
                        if(inputFocus == false) return;
                        if(rowModel == null){ rowModel = reportModel.onCommandAddRow(page.pageIdx, rowPageIdx); setValus();}
                        rowModel.onCommandSetComment(text)
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:18;anchors_height:200;anchors_width:200;anchors_x:78;anchors_y:463}
D{i:23;anchors_x:200}D{i:30;anchors_x:200}D{i:40;anchors_x:200}D{i:49;anchors_x:203}
D{i:46;anchors_x:203}
}
##^##*/
