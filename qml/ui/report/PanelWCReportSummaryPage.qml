import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelWCReportContainerModel 1.0
import PanelWCReportModel    1.0
import PanelWCReportProductModel 1.0

import "../../control/."
import "."

Rectangle {
    property PanelWCReportContainerModel containerModel : null
    property PanelWCReportModel reportModel : null
    property PanelWCReportProductModel productModel : null
    property bool isEditMode : containerModel.mIsEditMode

    signal signalEventDeleteRow(int pageIdx, int rowIdxInPage)

    id : page

    width: 840
    height: 1188

    color: "#FFFFFF"

    Component.onDestruction: {
    }

    Component.onCompleted: {

    }

    Text {
        id: title
        height: 50
        text: qsTr("Weight checker summary")
        font.family: "Arial"
        anchors.top: parent.top
        anchors.topMargin: 100
        font.pixelSize:  25
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
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

                    visible: containerModel === null ? false : !containerModel.mIsCheckWrite
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

                    visible: containerModel === null ? false : !containerModel.mIsCheckReview
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

                    visible: containerModel === null ? false : !containerModel.mIsCheckApproved
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
                    text: containerModel === null ? "" :containerModel.mCompany
                    anchors.left: labelCompany.right
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.leftMargin: 0

                    onTextChanged: {
                        if(inputFocus == false) return;
                        containerModel.onCommandSetCompany(text)
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
                        text: qsTr("Date")
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
                    text: reportModel === null ? "" : reportModel.mStrDate
                    anchors.left: labelCheckDate.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.right: parent.right

                    onTextChanged: {
                        if(inputFocus == false) return;
                        reportModel.onCommandSetStrDate()(text)
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
                    id: labelDevice
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    Text {
                        id: element4
                        width: 120
                        text: qsTr("Device number")
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
                    id: inputDevice
                    width : 240
                    text: containerModel === null ? "" : ("000" + containerModel.mDeviceNum).slice(-3)
                    anchors.left: labelDevice.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top

                    onTextChanged: {
                        if(inputFocus == false) return;
                        containerModel.onCommandSetDeviceNum(text)
                    }
                }

                Rectangle {
                    id: labelProduct
                    width: 130
                    color: "#00000000"
                    border.width: 1
                    Text {
                        width: 120
                        text: qsTr("Product")
                        anchors.fill: parent
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 0
                    }
                    anchors.left: inputDevice.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }

                DocTextField {
                    id: inputProduct
                    width : 240
                    text: productModel === null ? "" : productModel.mNumName
                    anchors.left: labelProduct.right
                    anchors.right: parent.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top

                    onTextChanged: {
                        if(inputFocus == false) return;
                        productModel.onCommandSetNumName(text)
                    }
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
                    text: containerModel === null ? "" :containerModel.mDepartment
                    anchors.left: labelDepartment.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top

                    onTextChanged: {
                        if(inputFocus == false) return;
                        containerModel.onCommandSetDepartment(text)
                    }
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
                    text: containerModel === null ? "" :containerModel.mPosition
                    anchors.left: labelPosition.right
                    anchors.leftMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    onTextChanged: {
                        if(inputFocus == false) return;
                        containerModel.onCommandSetPosition(text)
                    }
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
                    text: containerModel === null ? "" :containerModel.mName
                    anchors.left: labelName.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    onTextChanged: {
                        if(inputFocus == false) return;
                        containerModel.onCommandSetName(text)
                    }
                }

            }
        }

        Rectangle {
            id: labelSummary
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
                text: qsTr("Summary")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 20
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


    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        visible: !page.isEditMode
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.100000023841858}D{i:23}D{i:30}D{i:37}D{i:44}D{i:18}
}
##^##*/
