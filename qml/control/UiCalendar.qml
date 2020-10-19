import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0
import PanelCalendarModel 1.0
Calendar{
    property PanelCalendarModel vaildChecker : null
    id :control

    width : 500
    height: 500

    frameVisible: false

    signal signalEventClick(int year, int month, int day)
    signal signalEventUpdate()

    function isVaild(year, month, day)
    {
        if(vaildChecker == null)
            return true;

        return vaildChecker.onCommandIsVaildDate(year, month, day)
    }

    function update()
    {
        control.signalEventUpdate();
    }

    style: CalendarStyle{
        id: calendarStyle
        gridVisible: false

        background: Rectangle{
            color: "#00000000"
        }

        navigationBar : Rectangle{
            id: rectangle
            height: 70
            color: "#00000000"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiButton{
                id : preMonth
                width : 50
                height: 50
                text: ""
                iconSource: "image/left.png"
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter

                onSignalEventClicked: {
                    control.showPreviousMonth()
                    control.update();
                }
            }

            UiLabel{
                height: 50
                anchors.right: nextMonth.left
                anchors.rightMargin: 0
                anchors.left: preMonth.right
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter

                text : (control.visibleMonth + 1) + ". " + control.visibleYear


            }

            UiButton{
                id : nextMonth
                width : 50
                height: 50
                text: ""
                iconSource: "image/right.png"
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter

                onSignalEventClicked: {
                    control.showNextMonth()
                    control.update();
                }
            }
        }

        dayOfWeekDelegate: Item{
            width : parent.width
            height: 50

            UiLabel{
                text: styleData.index === 0 ? qsTr("S") :
                      styleData.index === 1 ? qsTr("M") :
                      styleData.index === 2 ? qsTr("T") :
                      styleData.index === 3 ? qsTr("W") :
                      styleData.index === 4 ? qsTr("T") :
                      styleData.index === 5 ? qsTr("F") : qsTr("S")

                anchors.centerIn: parent
                color: styleData.index === 0 ? "#D9001B" :
                       styleData.index === 1 ? "#FFFFFF" :
                       styleData.index === 2 ? "#FFFFFF" :
                       styleData.index === 3 ? "#FFFFFF" :
                       styleData.index === 4 ? "#FFFFFF" :
                       styleData.index === 5 ? "#FFFFFF" : "#0085FF"
            }
        }

        dayDelegate: Item {
            id : dayItem
            property bool isVaild : (control.isVaild(styleData.date.getFullYear(), styleData.date.getMonth() + 1, styleData.date.getDate()) === true && styleData.date.getMonth() === control.visibleMonth)
            Rectangle{
                anchors.fill: parent
                radius      : width / 2
                gradient: Gradient {
                    GradientStop {
                        position: 0.00
                        color: "#0085FF"
                    }
                    GradientStop {
                        position: 1.00
                        color: "#86C5FF"
                    }

                    orientation: Gradient.Horizontal
                }

                visible: styleData.selected
            }

            UiLabel{
                text: styleData.date.getDate()
                anchors.centerIn: parent
                color: styleData.date.getMonth() !== control.visibleMonth ? "#00FFFFFF" :
                       dayItem.isVaild === false   ? "#11FFFFFF":
                       (styleData.index) % 7 === 0 ? "#D9001B" :
                       (styleData.index) % 7 === 1 ? "#FFFFFF" :
                       (styleData.index) % 7 === 2 ? "#FFFFFF" :
                       (styleData.index) % 7 === 3 ? "#FFFFFF" :
                       (styleData.index) % 7 === 4 ? "#FFFFFF" :
                       (styleData.index) % 7 === 5 ? "#FFFFFF" : "#0085FF"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(styleData.date.getMonth() !== control.visibleMonth)
                        return;

                    if(dayItem.isVaild === false)
                        return;

                    control.signalEventClick(styleData.date.getFullYear(), styleData.date.getMonth() + 1, styleData.date.getDate())
                }
            }

            Connections {
                target: control
                onSignalEventUpdate :{
                    if(control.isVaild(styleData.date.getFullYear(), styleData.date.getMonth() + 1, styleData.date.getDate()) === true && styleData.date.getMonth() === control.visibleMonth)
                    {
                        dayItem.isVaild = true;
                    }
                    else
                        dayItem.isVaild = false;
                }
            }
        }
    }
}
