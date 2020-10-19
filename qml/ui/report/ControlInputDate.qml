import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."

Rectangle{
    property alias fDate : fromDate.inputDate
    property alias tDate : toDate.inputDate

    function setDate(fyear,fmonth, fday, tyear,tmonth, tday){
        fromDate.setDate(fyear, fmonth, fday)
        toDate.setDate(tyear, tmonth, tday)
    }

    id: control
    color : "#333333"
    height: headerBtnContainer.height + 40

    Flow{
        id : headerBtnContainer
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left : parent.left
        anchors.leftMargin: 20

        width: parent.width - 40
        spacing: 10

        UiInputDate{
            id : fromDate
            width: 208
            height: 42
            labelBgWidth: 80
            label: qsTr("From")
        }

        UiInputDate{
            id : toDate
            width: 208
            height: 42
            labelBgWidth: 80
            label: qsTr("To")
        }

        UiButton{
            width: 88
            height: 42
            isTextBtn: true
            text: qsTr("Today")

            onSignalEventClicked: {
                var tempDate = new Date();

                fromDate.setDate(tempDate.getFullYear(), tempDate.getMonth() + 1, tempDate.getDate())
                toDate.setDate(tempDate.getFullYear(), tempDate.getMonth() + 1, tempDate.getDate())
            }
        }

        UiButton{
            width: 88
            height: 42
            isTextBtn: true
            text: qsTr("1 Month")

            onSignalEventClicked: {
                var newToDate = new Date()
                var newFromDate = new Date()
                newFromDate.setMonth(newToDate.getMonth() - 1)

                toDate.inputDate = newToDate
                fromDate.inputDate = newFromDate
            }
        }

        UiButton{
            width: 88
            height: 42
            isTextBtn: true
            text: qsTr("3 Month")
            onSignalEventClicked: {
                var newToDate = new Date()
                var newFromDate = new Date()
                newFromDate.setMonth(newToDate.getMonth() - 3)

                toDate.inputDate = newToDate
                fromDate.inputDate = newFromDate
            }
        }

        UiButton{
            width: 88
            height: 42
            isTextBtn: true
            text: qsTr("6 Month")
            onSignalEventClicked: {
                var newToDate = new Date()
                var newFromDate = new Date()
                newFromDate.setMonth(newToDate.getMonth() - 6)

                toDate.inputDate = newToDate
                fromDate.inputDate = newFromDate
            }
        }

        UiButton{
            width: 88
            height: 42
            isTextBtn: true
            text: qsTr("1 year")
            onSignalEventClicked: {
                var newToDate = new Date()
                var newFromDate = new Date()
                newFromDate.setMonth(newToDate.getMonth() - 12)

                toDate.inputDate = newToDate
                fromDate.inputDate = newFromDate
            }
        }
    }
}
