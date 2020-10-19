import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelMDCheckReportContainerModel 1.0
import PanelMDCheckReportModel    1.0

import "."
import "../../control/."

Flow {
    property PanelMDCheckReportContainerModel containerModel : null
    property PanelMDCheckReportModel reportModel : null
    signal signalEventDeleteRow(int pageIdx, int rowIdxInPage)
    signal signalEventPrintEnd()

    id : containerPage

    Layout.fillWidth: true

    spacing: 10

    function setData(containerModel, dailyModel)
    {
        clearPage()

        if(dailyModel === null)
            return;

        for(var i = 0; i < dailyModel.onCommandGetPageCnt(); i ++)
        {
            if(i === 0)
            {
                firstPage.createObject(containerPage, {"containerModel":containerModel, "reportModel":dailyModel, "pageIdx":i})
            }
            else
            {
                otherPage.createObject(containerPage, {"containerModel":containerModel, "reportModel":dailyModel, "pageIdx":i})
            }
        }
    }

    function printDrawReport(containerModel, dailyModel)
    {
        clearPage()

        containerPage.containerModel = containerModel;
        containerPage.reportModel    = dailyModel;

        var item = firstPage.createObject(containerPage, {"containerModel":containerModel, "reportModel":dailyModel, "pageIdx":0})

        item.grabToImage(function(result){
            containerModel.onCommandPrint(result.image);
            printDrawReportNext(1)
        })
    }

    function printDrawReportNext(pageIdx)
    {
        if(pageIdx >= reportModel.onCommandGetPageCnt())
        {
            containerPage.signalEventPrintEnd();
            return;
        }

        var item = otherPage.createObject(containerPage, {"containerModel":containerPage.containerModel, "reportModel":containerPage.reportModel, "pageIdx":pageIdx})

        item.grabToImage(function(result){
            containerModel.onCommandPrint(result.image);
            printDrawReportNext(pageIdx + 1)
        })
    }

    function clearPage()
    {
        for(var i = 0; i < containerPage.children.length; i ++)
        {
            containerPage.children[i].destroy()
        }
    }

    Component{
        id : firstPage

        PanelMDCheckReportFirstPage{
            onSignalEventDeleteRow: { containerPage.signalEventDeleteRow(pageIdx, rowIdxInPage)}
        }
    }

    Component{
        id : otherPage

        PanelMDCheckReportOtherPage{
            onSignalEventDeleteRow: {
                containerPage.signalEventDeleteRow(pageIdx, rowIdxInPage)}
        }
    }
}

