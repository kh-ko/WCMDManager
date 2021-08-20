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
                text: qsTr("Monitoring history")
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
                height: 60
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
                        text: qsTr("Detect time")
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
                    id: labelDescriptionTitle
                    width: 140
                    color: "#00000000"
                    anchors.left: labelPNameTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0

                    Text {
                        id: element9
                        text: qsTr("Description")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    id: labelActionTitle
                    width: 140
                    color: "#00000000"
                    anchors.left: labelDescriptionTitle.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0

                    Text {
                        id: element10
                        text: qsTr("Follow up<br>action")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    id: labelComplete
                    color: "#00000000"
                    width: 70
                    border.width: 1
                    anchors.left: labelActionTitle.right
                    anchors.leftMargin: -1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                    Text {
                        id: element14
                        text: qsTr("Action<br>complete<br>/Sign")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    id: labelComment
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: labelComplete.right
                    anchors.leftMargin: -1
                    border.width: 1
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    anchors.bottomMargin: 0
                    Text {
                        text: qsTr("Confirmer<br>/Sign")
                        anchors.fill: parent
                        font.pixelSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
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
                inputPNum.text           = pageModel.onCommandGetColumnValue(rowPageIdx, 0 )
                inputTime.text           = pageModel.onCommandGetColumnValue(rowPageIdx, 1 )
                inputPName.text          = pageModel.onCommandGetColumnValue(rowPageIdx, 2 )
                inputDescription.text    = pageModel.onCommandGetColumnValue(rowPageIdx, 3 )
                inputFollowUpAction.text = pageModel.onCommandGetColumnValue(rowPageIdx, 4 )
                inputActionComplete.text = pageModel.onCommandGetColumnValue(rowPageIdx, 5 )
                inputConfirmer.text      = pageModel.onCommandGetColumnValue(rowPageIdx, 6 )
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
                id: inputDescriptionBox
                width: 140
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputPNameBox.right
                anchors.leftMargin: -1
                border.width: 1

                DocTextField {
                    id : inputDescription
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: inputFollowUpActionBox
                width: 140
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputDescriptionBox.right
                anchors.leftMargin: -1
                border.width: 1

                DocTextField {
                    id : inputFollowUpAction
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: inputActionCompleteBox
                width: 70
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputFollowUpActionBox.right
                anchors.leftMargin: -1
                border.width: 1

                DocTextField {
                    id : inputActionComplete
                    anchors.fill: parent
                }
            }


            Rectangle {
                id: inputConfirmerBox
                color: "#00000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: inputActionCompleteBox.right
                anchors.leftMargin: -1
                anchors.right: parent.right
                border.width: 1

                DocTextField {
                    id : inputConfirmer
                    anchors.fill: parent
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
