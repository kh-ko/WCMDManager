import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."

Rectangle {
    property bool isCheckedWrite    : false
    property bool isCheckedReview   : false
    property bool isCheckedApproved : false

    id : control
    color: "#D9000000"
    radius: 10

    signal signalEventClickWrite   ()
    signal signalEventClickReview  ()
    signal signalEventClickApproved()

    RowLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent

        CheckBox{
            id : writeCheck
            text: qsTr("Write")
            checkable: false
            checked: control.isCheckedWrite
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                control.signalEventClickWrite();
            }
        }

        CheckBox {
            id : reviewCheck
            text: qsTr("Review")
            checkable: false
            checked: control.isCheckedReview
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                control.signalEventClickReview();
            }
        }

        CheckBox {
            id : approvedCheck
            width: 87
            height: 32
            text: qsTr("Approved")
            checkable: false
            checked: control.isCheckedApproved
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                control.signalEventClickApproved();
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:100;anchors_width:100}
}
##^##*/
