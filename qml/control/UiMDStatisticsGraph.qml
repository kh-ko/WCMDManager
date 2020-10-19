import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0

Item {
    property int yAxisMax : 1
    property int yAxisGap : 1

    function clear()
    {
        yAxisMax = -1

        for(var i = barArea.children.length; i > 0 ; i --)
        {
            barArea.children[i - 1].destroy()
        }

        for(var j = xAxisArea.children.length; j > 0 ; j --)
        {
            xAxisArea.children[j - 1].destroy()
        }
    }

    function add( date, totalCnt, ngCnt, index)
    {

        if(yAxisMax < totalCnt)
        {
            var firstNum = parseInt(totalCnt.toString().slice(0,1))
            var maxFirstNum = ((Math.floor(firstNum / 2)+ 1) * 2 )
            yAxisMax = maxFirstNum * Math.pow(10, totalCnt.toString().length - 1)

            if(maxFirstNum <= 2)
            {
                yAxisGap = 1 * Math.pow(10, totalCnt.toString().length - 1)
            }
            else if(maxFirstNum <= 8)
            {
                yAxisGap = 2 * Math.pow(10, totalCnt.toString().length - 1)
            }
            else
            {
                yAxisGap = 5 * Math.pow(10, totalCnt.toString().length - 1)
            }
        }

        barGraphItem.createObject(barArea,{"date":date, "totalCount" : totalCnt, "ngCount" : ngCnt})
        barGraphXDate.createObject(xAxisArea,{"idx": index})
    }

    id : graph

    width : 911
    height: 324

    Item{
        id :yAxisArea
        width: 96
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 37
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabel{ anchors.right: parent.right; anchors.rightMargin: 0; anchors.verticalCenter: parent.bottom; text : "0"}
        UiLabel{
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * graph.yAxisGap / graph.yAxisMax)
            text : graph.yAxisGap.toString()
        }
        UiLabel{
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 2) / graph.yAxisMax)
            text : (graph.yAxisGap * 2).toString()
        }
        UiLabel{
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 3) / graph.yAxisMax)

            visible: (graph.yAxisGap * 3) <  graph.yAxisMax + 1
            text : (graph.yAxisGap * 3).toString()
        }
        UiLabel{
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 4) / graph.yAxisMax)

            visible: (graph.yAxisGap * 4) <  graph.yAxisMax + 1
            text : (graph.yAxisGap * 4).toString()
        }
    }

    Item{
        id :yAxisLineArea

        anchors.fill: barArea

        Rectangle{
            height : 2;
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.left: parent.left;
            anchors.leftMargin: 0;
            anchors.verticalCenter: parent.bottom;

            color: "#59ACACAC"
        }
        Rectangle{
            height : 2
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.left: parent.left;
            anchors.leftMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * graph.yAxisGap / graph.yAxisMax)

            color: "#59ACACAC"
        }
        Rectangle{
            height : 2
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.left: parent.left;
            anchors.leftMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 2) / graph.yAxisMax)

            color: "#59ACACAC"
        }
        Rectangle{
            height : 2
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.left: parent.left;
            anchors.leftMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 3) / graph.yAxisMax)

            visible: (graph.yAxisGap * 3) <  graph.yAxisMax + 1
            color: "#59ACACAC"
        }
        Rectangle{
            height : 2
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.left: parent.left;
            anchors.leftMargin: 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * (graph.yAxisGap * 4) / graph.yAxisMax)

            visible: (graph.yAxisGap * 4) <  graph.yAxisMax + 1
            color: "#59ACACAC"
        }
    }

    RowLayout{
        id : barArea
        anchors.bottom: yAxisArea.bottom
        anchors.bottomMargin: 0
        anchors.top: yAxisArea.top
        anchors.topMargin: 0
        anchors.left: yAxisArea.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20

        clip: true
    }

    RowLayout{
        id : xAxisArea
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: barArea.bottom
        anchors.topMargin: 0
        anchors.right: barArea.right
        anchors.rightMargin: 0
        anchors.left: barArea.left
        anchors.leftMargin: 0

    }

    Component
    {
        id : barGraphItem

        Item{
            id: barItem
            property int  totalCount : 100
            property int  ngCount    : 100
            property bool isHover    : false

            Layout.preferredHeight: 1
            Layout.preferredWidth : 1
            Layout.fillWidth      : true
            Layout.fillHeight     : true

            Rectangle{
                id : bar01
                width: 6
                height: (radius * 2) + (parent.height * (barItem.totalCount / graph.yAxisMax))
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -2 * radius
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -2

                radius: 3
                border.color: "#f59a23"
                border.width: barItem.isHover ? 2 : 0
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#0085FF"
                    }

                    GradientStop {
                        position: 1
                        color: "#83C4FF"
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onContainsMouseChanged: { barItem.isHover = containsMouse}
                }
            }

            Rectangle{
                id : bar02
                width: 6
                height: (radius * 2) + (parent.height * (barItem.ngCount / graph.yAxisMax))
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -2 * radius
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 2

                radius: 3
                border.color: "#f59a23"
                border.width: barItem.isHover ? 2 : 0

                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#D9001B"
                    }

                    GradientStop {
                        position: 1
                        color: "#FF8080"
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onContainsMouseChanged: { barItem.isHover = containsMouse}
                }
            }
        }

    }

    Component
    {
        id : barGraphXDate

        Item{
            property int idx

            id: barX

            Layout.preferredHeight: 1
            Layout.preferredWidth : 1
            Layout.fillWidth      : true
            Layout.fillHeight     : true

            UiLabel{
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment  : Text.AlignVCenter


                text: idx

            }
        }

    }
}

/*##^##
Designer {
    D{i:1;anchors_width:96}
}
##^##*/
