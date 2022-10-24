import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."
import PanelReportWindowModel 1.0
import ReportPageModel    1.0

Window{
    id : dialog
    modality : Qt.WindowModal

    height: 600; width: 1014
    minimumHeight: 600; minimumWidth: 1014

    title : qsTr("Report")

    property bool    isEditMode : false
    property var     reportType : EnumDefine.REPORT_MD_CHECKUP
    property string  selectedPList

    signal signalEventClosed()

    function open(reportType ,year, month, day, selectedPList)
    {
        dialog.reportType = reportType;
        dialog.selectedPList = selectedPList;
        dateRange.setDate(year, month, day, year, month, day)

        dialog.show()
        load();
    }

    function load()
    {
        loadingDialog.open();
        leftMenu.clearDate();

        for(var i = 0; i < reportList.children.length; i ++)
        {
            reportList.children[i].destroy()
        }

        reportContainerModel.onCommandLoadData(dialog.reportType, dateRange.fDate.getFullYear(), dateRange.fDate.getMonth() + 1, dateRange.fDate.getDate(),
                                               dateRange.tDate.getFullYear(), dateRange.tDate.getMonth() + 1, dateRange.tDate.getDate(), dialog.selectedPList)
    }

    function loadFinish()
    {
        loadingDialog.close()
    }

    function addDate(date)
    {
        leftMenu.addDate(date)
    }

    function addPage(pageModel)
    {
        switch(pageModel.mPageType)
        {
        case EnumDefine.REPORT_PAGE_MD_CHECKUP:
            if(pageModel.mIsFirst){ mdCheckFirstPage.createObject(reportList, {"pageModel":pageModel}) }
            else                  { mdCheckNextPage.createObject (reportList, {"pageModel":pageModel}) }
            break;
        case EnumDefine.REPORT_PAGE_MD_DETECT:
            if(pageModel.mIsFirst){ mdDetectFirstPage.createObject(reportList, {"pageModel":pageModel}) }
            else                  { mdDetectNextPage.createObject (reportList, {"pageModel":pageModel}) }
            break;
        case EnumDefine.REPORT_PAGE_MD_OP:
            if(pageModel.mIsFirst){ mdOpFirstPage.createObject    (reportList, {"pageModel":pageModel}) }
            else                  { mdOpNextPage.createObject     (reportList, {"pageModel":pageModel}) }
            break;
        case EnumDefine.REPORT_PAGE_WC_DETECT:
            if(pageModel.mIsFirst){ wcDetectFirstPage.createObject(reportList, {"pageModel":pageModel}) }
            else                  { wcDetectNextPage.createObject (reportList, {"pageModel":pageModel}) }
            break;
        case EnumDefine.REPORT_PAGE_WC_OP:
            if(pageModel.mIsFirst){ wcOpFirstPage.createObject    (reportList, {"pageModel":pageModel}) }
            else                  { wcOpNextPage.createObject     (reportList, {"pageModel":pageModel}) }
            break;
        }
    }

    function printDrawReport(idx)
    {
        if(idx >= reportList.children.length)
        {
            reportContainerModel.onCommandPrintEnd()
            loadingDialog.close();
            return;
        }

        reportList.children[idx].printing = true;

        reportList.children[idx].grabToImage(function(result)
        {
            reportList.children[idx].printing = false;
            reportContainerModel.onCommandPrint(result.image);
            printDrawReport(idx + 1)
        })
    }

    onVisibilityChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();
    }

    PanelReportWindowModel{
        id : reportContainerModel
        onSignalEventLoadedPage    : { addPage(pageModel)  ; }
        onSignalEventAddedDate     : { addDate(date)       ; }
        onSignalEventCompletedLoad : { loadFinish()        ; }
        onSignalEventSelectedPrint : { loadingDialog.open(); printDrawReport(0);}
    }

    Rectangle{
        id: bg
        color : "#131313"
        anchors.fill: parent
    }

    Item{
        width: parent.width / ViewManager.scale
        height: parent.height / ViewManager.scale
        scale : ViewManager.scale

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        ControlInputDate{
            id : dateRange
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left : parent.left
            anchors.leftMargin: 0
            width: parent.width
        }

        ControlReportMenu{
            id : leftMenu
            isEditMode : dialog.isEditMode

            width: 142
            anchors.top: dateRange.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            onSignalEventClickPrint: {
                reportContainerModel.onCommandSelectPrint();
            }

            onSignalEventClickEdit:{
                if(dialog.isEditMode)
                    dialog.isEditMode = true
                else
                    pwdDialog.open()
            }
            onSignalEventClickLoad : {load()}
        }

        UiScrollView{
            id : scrollView
            width: parent.width - leftMenu.width
            height: parent.height - dateRange.height
            barPressColor : "#17a81a"
            barColor : "#21be2b"

            anchors.left : leftMenu.right
            anchors.leftMargin: 0
            anchors.top: dateRange.bottom
            anchors.topMargin: 0

            ColumnLayout{
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left : parent.left
                anchors.leftMargin: 20
                width : scrollView.width - 4

                Flow{
                    id : reportList
                    Layout.fillWidth: true
                    spacing: 10
                }
            }
        }

        ControlSignatureCheck{
            width: 382; height: 58
            anchors.top: scrollView.top; anchors.topMargin: 20; anchors.right: scrollView.right; anchors.rightMargin: 20;

            isCheckedWrite   : reportContainerModel.mIsCheckWrite
            isCheckedReview  : reportContainerModel.mIsCheckReview
            isCheckedApproved: reportContainerModel.mIsCheckApproved

            onSignalEventClickWrite   : {reportContainerModel.onCommandSetIsCheckWrite   (!reportContainerModel.mIsCheckWrite   )}
            onSignalEventClickReview  : {reportContainerModel.onCommandSetIsCheckReview  (!reportContainerModel.mIsCheckReview  )}
            onSignalEventClickApproved: {reportContainerModel.onCommandSetIsCheckApproved(!reportContainerModel.mIsCheckApproved)}

        }

        DialogPassword{
            id : pwdDialog
            onSignalEventMatchPassword: {
                dialog.isEditMode = true;
            }
        }

        UiDialogLoading{ id :loadingDialog }
    }

    Component{ id : mdCheckFirstPage ; PanelMDCheckReportFirstPage { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : mdCheckNextPage  ; PanelMDCheckReportNextPage  { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : mdDetectFirstPage; PanelMDDetectReportFirstPage{ visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : mdDetectNextPage ; PanelMDDetectReportNextPage { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : mdOpFirstPage    ; PanelMDOPReportFirstPage    { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : mdOpNextPage     ; PanelMDOPReportNextPage     { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : wcDetectFirstPage; PanelWCDetectReportFirstPage{ visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : wcDetectNextPage ; PanelWCDetectReportNextPage { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : wcOpFirstPage    ; PanelWCOPReportFirstPage    { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
    Component{ id : wcOpNextPage     ; PanelWCOPReportNextPage     { visible: leftMenu.selectDate === reportDate || printing;  isEditMode : dialog.isEditMode; isCheckWrite : reportContainerModel.mIsCheckWrite; isCheckReview : reportContainerModel.mIsCheckReview; isCheckApproved : reportContainerModel.mIsCheckApproved} }
}
/*##^##
Designer {
    D{i:6;anchors_y:88}D{i:11;anchors_height:200;anchors_x:65;anchors_y:220}
}
##^##*/
