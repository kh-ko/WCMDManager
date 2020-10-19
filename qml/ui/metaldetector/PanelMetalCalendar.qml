import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import PanelCalendarModel 1.0

import "../../control/."

Rectangle {
    id : control

    width : 439
    height: 418

    color : "#333333"
    radius: 10

    PanelCalendarModel{
        id : model

        onSignalEventChangedDate :{
            calendar.selectedDate = new Date(model.mYear, model.mMonth - 1, model.mDay)
        }

        onSignalEventUpdate: {
            calendar.update();
        }

        Component.onCompleted: {calendar.selectedDate = new Date(model.mYear, model.mMonth - 1, model.mDay)}
    }

    UiCalendar{
        id :calendar

        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent

        vaildChecker : model

        onSignalEventClick: {
            model.onCommandSelectDate(year, month, day)
        }
    }
}
