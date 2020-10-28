import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ViewManager 1.0
import EnumDefine 1.0
import PanelWCTrendsModel 1.0

import "../../control/."

Rectangle {
    id : panel

    width : 801
    height: 570

    color : "#333333"
    radius: 10

    function drawTrends()
    {
        if(graphArea.available)
        {
            graphArea.requestPaint()
        }
    }


    PanelWCTrendsModel{
        id :graphModel

        onSignalEventChangedData: {

            drawTrends()
        }
    }

    UiLabel
    {
        id : labelTitle

        color : "#FFFFFF"
        text  : qsTr("Trends")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Item{
        id : graphBg
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: labelTitle.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 100
        Item{
            id: yAxis
            x: 0
            width: 94
            anchors.top: parent.top
            anchors.bottom: yLineArea.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            UiLabel {
                id: yAxis10
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (10 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis09
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (9 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 1 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis08
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (8 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 2 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis07
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (7 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 3 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis06
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (6 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 4 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis05
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (5 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 5 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis04
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (4 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 6 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis03
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (3 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 7 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis02
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (2 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 8 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis01
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight + (1 * graphModel.mWeightGab)) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 9 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                text: graphModel.mIsNonData ? "" : ((graphModel.mDataMinWeight) / 1000).toLocaleString(ViewManager.locale, 'f', 2)
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: parent.height - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

        }

        Item{
            id: yLineArea
            anchors.left: yAxis.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: xAxis.top
            anchors.bottomMargin: 10
            anchors.leftMargin: 10

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 1 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 2 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 3 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 4 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 5 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 6 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 7 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 8 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 9 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height) - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

        }

        Canvas {
            property bool isChangingWidth : false
            id: graphArea
            anchors.left: yLineArea.left
            anchors.right: yLineArea.right
            anchors.top: yLineArea.top
            anchors.bottom: yLineArea.bottom
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0

            enabled: false
            antialiasing: true
            smooth: false
            renderTarget : Canvas.FramebufferObject
            clip: true

            onPaint :{
                var ctx = graphArea.getContext("2d")

                ctx.reset();

                if(graphArea.isChangingWidth)
                    return;

                ctx.lineWidth = 5
                ctx.strokeStyle = "#0085FF"
                ctx.fillStyle = "#00000000"
                ctx.lineCap = "round"

                graphModel.onCommandSetCanvasSize(graphArea.width, graphArea.height)

                overLine.anchors.topMargin = graphModel.onCommandGetLineOverY()
                underLine.anchors.topMargin = graphModel.onCommandGetLineUnderY()

                console.debug("[debug] under = " + underLine.anchors.topMargin)
                ctx.beginPath()

                for(var i = 0; i < graphModel.onCommandGetPointCnt(); i ++)
                {
                    var min = graphModel.onCommandGetPointMinY(i);
                    var max = graphModel.onCommandGetPointMaxY(i);
                    var x   = graphArea.width * (i/(graphModel.onCommandGetPointCnt() - 1.0));

                    if(i === 0)
                    {
                        ctx.moveTo(0,min);
                    }

                    ctx.lineTo(x,min);
                    ctx.moveTo(x,min);
                    ctx.lineTo(x,max);
                    ctx.moveTo(x,max);

                }

                ctx.stroke();

            }

            Rectangle {
                id : overLine
                height: 2
                color: "#F59A23"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0 //panel.graphModel.mOverY - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                id : underLine
                height: 2
                color: "#D9001B"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0// panel.graphModel.mUnderY - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            onWidthChanged: {
                isChangingWidth = true


                drawTrends()

                timer.stop();
                timer.start();
            }

            Timer{
                id : timer
                interval: 1000; running: false; repeat: false
                onTriggered:
                {
                    graphArea.isChangingWidth = false

                    drawTrends()
                }
            }
        }

        MouseArea{
            property int startX : 0
            property int startY : 0

            anchors.fill: graphArea
            hoverEnabled: true

            onPositionChanged:
            {
                //console.debug("onPositionChanged")
            }

            onPressed: {
                startX = mouseX
                startY = mouseY

                console.debug("onPressed x = " + startX + ", y = " + startY)
            }
        }

        Item
        {
            id: xAxis
            y: 391
            height: 84
            anchors.left: graphArea.left
            anchors.right: graphArea.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            clip: false
/*
            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                UiLabel{
                    id: xAXis01
                    text: (graphModel.mDataStartIdx + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis02
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 2) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis03
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 2) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 3) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis04
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 3) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 4) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis05
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 4) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 5) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis06
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 5) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 6) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis07
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 6) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 7) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis08
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 7) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 8) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis09
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 8) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * ((graphModel.mDataStartIdx + graphModel.mDataGap * 9) / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                visible: anchors.leftMargin > parent.width - 30 ? false : true

                UiLabel{
                    id: xAXis10
                    text: ((graphModel.mDataStartIdx + graphModel.mDataGap * 9) + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }
*/
            Item {
                width: 30
                anchors.left: parent.left
                anchors.leftMargin: parent.width * (graphModel.mDataEndIdx / (graphModel.mDataTotalCnt - 1))
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                UiLabel{
                    id: xAXis11
                    text: (graphModel.mDataEndIdx + 1).toLocaleString(ViewManager.locale, 'f', 0)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    anchors.verticalCenterOffset: 0

                }
            }

        }
        UiLabel{
            y: -41
            text: "[g]"
            anchors.left: parent.left
            anchors.bottom: parent.top
            anchors.leftMargin: 45
            anchors.bottomMargin: 26

        }

        UiLabel{
            x: 735
            y: 360
            width: 48
            height: 15
            text: qsTr("[pcs]")
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 40

        }
    }

    UiComboBox {
        id: comboYScope
        x: 507
        width: 250
        height: 42
        anchors.right: comboFilter.left
        anchors.top: parent.top
        labelText: qsTr("Y scope")
        anchors.rightMargin: 20
        anchors.topMargin: 20
        labelWidth: 130
        inputText: graphModel.mMinMaxMode ? qsTr("Min to max") : qsTr("Under to over")
        listModel: yScopeListModel

        ListModel{
            id : yScopeListModel

            ListElement{
                itemValue : qsTr("Under to over")
                itemTag   : false
            }

            ListElement{
                itemValue : qsTr("Min to max")
                itemTag   : true
            }
        }

        onSignalEventClick: {
            graphModel.onCommandSetMinMaxMode(tag)
        }
    }

    UiComboBox {
        id: comboFilter
        x: 507
        width: 250
        height: 42
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        inputText: graphModel.mFilter ? qsTr("Trade") : qsTr("Total")
        labelText: qsTr("Filter")
        labelWidth: 130
        listModel: filterListModel

        ListModel{
            id : filterListModel

            ListElement{
                itemValue : qsTr("Total")
                itemTag   : false
            }

            ListElement{
                itemValue : qsTr("Trade")
                itemTag   : true
            }
        }

        onSignalEventClick: {
            graphModel.onCommandSetFilter(tag)
        }
    }
/*
    UiButton{
        id : btnApply
        width: 120
        height: 42
        colType: EnumDefine.BTN_COLOR_TYPE_BLUE
        isTextBtn: true
        text : qsTr("Apply")

        anchors.top: parent.top
        fontColor: "#ffffff"
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        onSignalEventClicked: {

        }
    }
*/
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
