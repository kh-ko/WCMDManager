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
        id: listRow
        Rectangle {
            property int rowPageIdx

            function setValus()
            {
                inputPNum.text     = pageModel.onCommandGetColumnValue(rowPageIdx, 0 )
                inputPName.text    = pageModel.onCommandGetColumnValue(rowPageIdx, 1 )
                inputLimitFe.text  = pageModel.onCommandGetColumnValue(rowPageIdx, 2 )
                inputLimitSus.text = pageModel.onCommandGetColumnValue(rowPageIdx, 3 )
                inputTotalCnt.text = pageModel.onCommandGetColumnValue(rowPageIdx, 4 )
                inputNGCnt.text    = pageModel.onCommandGetColumnValue(rowPageIdx, 5 )
                inputNGRate.text   = pageModel.onCommandGetColumnValue(rowPageIdx, 6 )
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

            /*
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
            }*/
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
