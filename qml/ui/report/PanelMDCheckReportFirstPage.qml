import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import ReportPageModel 1.0

import "../../control/."
import "."

Rectangle {
    property bool printing : false
    property ReportPageModel pageModel
    property string reportDate : pageModel.mReportDate
    property bool isEditMode
    property bool isCheckWrite
    property bool isCheckReview
    property bool isCheckApproved

    id : page

    width: 840
    height: 1188

    color: "#FFFFFF"

    Component.onDestruction: {
        pageModel.onCommandDelete();
    }

    Component.onCompleted: {

        for(var i = 0; i < pageModel.onCommandGetRowCnt(); i ++)
        {
            listRow.createObject(list, {"rowPageIdx" : i });
        }
    }

    DocTextField {
        id: title
        height: 50
        text: pageModel.mTitle
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

            pageModel.onCommandSetTitle(text)
        }
    }

    Rectangle {
        id: approvalbox
        x: 456
        width: 334
        height: 110
        color: "#ffffff"
        anchors.top: title.bottom
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 50
        border.width: 2

        Rectangle {
            id: labelsignature
            width: 58
            color: "#00000000"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            border.width: 1

            Text {
                id: element15
                text: qsTr("Sign")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 12
            }
        }

        RowLayout {
            id: rowLayout
            spacing: -1
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 57
            anchors.right: parent.right
            anchors.rightMargin: 0

            Rectangle {
                id: rectangle
                width: 200
                height: 200
                color: "#00000000"
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                Rectangle {
                    id: rectangle3
                    y: 0
                    height: 30
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text {
                        id: element16
                        text: qsTr("Write")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                }

                Rectangle {
                    id: rectangle1
                    x: 45
                    width: 1
                    height: 125
                    color: "#000000"
                    anchors.verticalCenterOffset: 15
                    rotation: 50
                    anchors.verticalCenter: parent.verticalCenter

                    visible: !page.isCheckWrite
                }
            }

            Rectangle {
                id: rectangle2
                width: 200
                height: 200
                color: "#00000000"
                Rectangle {
                    id: rectangle4
                    y: 0
                    height: 30
                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.rightMargin: 0
                    anchors.right: parent.right

                    Text {
                        id: element17
                        text: qsTr("Review")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                }

                Rectangle {
                    id: rectangle12
                    x: 45
                    y: 7
                    width: 1
                    height: 125
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 15
                    rotation: 50

                    visible: !page.isCheckReview
                }
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Rectangle {
                id: rectangle5
                width: 200
                height: 200
                color: "#00000000"
                Rectangle {
                    id: rectangle6
                    y: 0
                    height: 30
                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.rightMargin: 0
                    anchors.right: parent.right

                    Text {
                        id: element18
                        text: qsTr("Approved")
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 12
                    }
                }

                Rectangle {
                    id: rectangle13
                    x: 45
                    y: 7
                    width: 1
                    height: 125
                    color: "#000000"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 15
                    rotation: 50

                    visible: !page.isCheckApproved
                }
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

    Rectangle {
        id: rectangle7
        color: "#00000000"
        border.width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: approvalbox.bottom
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50

        ColumnLayout {
            id: header
            height: 99
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            spacing: -1

            Rectangle {
                id: rectangle8
                width: 200
                height: 91
                color: "#00000000"
                Layout.fillHeight: true
                Layout.fillWidth: true
                border.width: 1

                Rectangle {
                    id: labelCompany
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0

                    Text {
                        id: element
                        width: 120
                        text: qsTr("Company name")
                        anchors.rightMargin: 0
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 12
                    }
                }

                DocTextField {
                    id: inputCompany
                    y: 0
                    width: 240
                    text: pageModel.mCompany
                    anchors.left: labelCompany.right
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.leftMargin: 0

                    onTextChanged: {
                        if(inputFocus == false) return;
                        pageModel.onCommandSetCompany(text)
                    }
                }

                Rectangle {
                    id: labelCheckDate
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    anchors.left: inputCompany.right
                    anchors.leftMargin: 0
                    Text {
                        id: element1
                        text: qsTr("Checkup date")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                DocTextField {
                    id: inputCheckDate
                    text: pageModel.mStrDate
                    anchors.left: labelCheckDate.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.right: parent.right

                    onTextChanged: {
                        if(inputFocus == false) return;
                        pageModel.onCommandSetStrDate(text)
                    }
                }
            }

            Rectangle {
                id: rectangle10
                width: 200
                height: 91
                color: "#00000000"
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                Rectangle {
                    id: labelCycle
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    Text {
                        id: element4
                        width: 120
                        text: qsTr("Checkup cycle")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                DocTextField {
                    id: inputCycle
                    width : 180
                    text: pageModel.mCheckCycle
                    anchors.left: labelCycle.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top

                    onTextChanged: {
                        if(inputFocus == false) return;
                        pageModel.onCommandSetCheckupCycle(text)
                    }
                }

                Rectangle {
                    id: labelDNum
                    width: 61
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Device")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.left: inputCycle.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                DocTextField {
                    id: inputDNum
                    width : 128
                    text: pageModel.mDevNum
                    anchors.left: labelDNum.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                Rectangle {
                    id: labelJudg
                    width: 82
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Judgment")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.left: inputDNum.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                Text {
                    text: qsTr("PASS : O, FAIL : X")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.left: labelJudg.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

            }

            Rectangle {
                width: 200
                height: 91
                color: "#00000000"
                border.width: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                Rectangle {
                    id: labelDepartment
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Department")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                }

                DocTextField {
                    id: inputDepartment
                    width : 180
                    text: pageModel.mDepartment
                    anchors.left: labelDepartment.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                }

                Rectangle {
                    id: labelPosition
                    width: 61
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Position")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.left: inputDepartment.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                DocTextField {
                    id: inputPosition
                    width : 128
                    text: pageModel.mPosition
                    anchors.left: labelPosition.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                Rectangle {
                    id: labelName
                    width: 82
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Name")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.left: inputPosition.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                DocTextField {
                    id: inputName
                    width : 128
                    text: pageModel.mName
                    anchors.left: labelName.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

            }
        }

        Rectangle {
            id: labelOperateHistory
            height: 40
            color: "#515151"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: header.bottom
            anchors.topMargin: -1
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
        text: pageModel.mPageNum
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

            function setValus()
            {
                inputPNum.text      = pageModel.onCommandGetColumnValue(rowPageIdx, 0 )
                inputTime.text      = pageModel.onCommandGetColumnValue(rowPageIdx, 1 )
                inputPName.text     = pageModel.onCommandGetColumnValue(rowPageIdx, 2 )
                inputLimitFe.text   = pageModel.onCommandGetColumnValue(rowPageIdx, 3 )
                inputLimitSus.text  = pageModel.onCommandGetColumnValue(rowPageIdx, 4 )
                inputJudgFe01.text  = pageModel.onCommandGetColumnValue(rowPageIdx, 5 )
                inputJudgFe02.text  = pageModel.onCommandGetColumnValue(rowPageIdx, 6 )
                inputJudgFe03.text  = pageModel.onCommandGetColumnValue(rowPageIdx, 7 )
                inputJudgSus01.text = pageModel.onCommandGetColumnValue(rowPageIdx, 8 )
                inputJudgSus02.text = pageModel.onCommandGetColumnValue(rowPageIdx, 9 )
                inputJudgSus03.text = pageModel.onCommandGetColumnValue(rowPageIdx, 10)
                inputComment.text   = pageModel.onCommandGetColumnValue(rowPageIdx, 11)
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
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:23;anchors_x:200}D{i:30;anchors_x:200}D{i:40;anchors_x:200}
D{i:47;anchors_x:203}D{i:50;anchors_x:203}D{i:18;anchors_height:200;anchors_width:200;anchors_x:78;anchors_y:463}
}
##^##*/
