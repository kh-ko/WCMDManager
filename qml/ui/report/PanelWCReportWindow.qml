import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."
import PanelWCReportContainerModel 1.0
//import PanelMDCheckReportModel    1.0
//import PanelMDCheckReportRowModel 1.0

Window{
    id : dialog
    modality : Qt.WindowModal

    height: 600
    width: 1014
    minimumHeight: 600
    minimumWidth: 1014

    title : qsTr("Weight checker report")

    signal signalEventClosed()

    function open(year, month, day)
    {
        dateRange.setDate(year, month, day, year, month, day)

        dialog.show()
        loadReportModel();
    }

    function loadReportModel()
    {
        loadingDialog.open()
        reportContainerModel.onCommandLoadData(dateRange.fDate.getFullYear(), dateRange.fDate.getMonth() + 1, dateRange.fDate.getDate(),
                                               dateRange.tDate.getFullYear(), dateRange.tDate.getMonth() + 1, dateRange.tDate.getDate())
    }

    function setDailyReport(idx)
    {
        reportContainerModel.onCommandSelectDay(idx)
        dailyReportContainer.refresh()
    }

    function selectPSeq(pseq)
    {
        reportContainerModel.onCommandSelectProduct(pseq);
        dailyReportContainer.refresh()
    }


    function setDailyReportPrint(idx)
    {
        //dailyReportPrintContainer.printDrawReport(reportContainerModel, reportContainerModel.onCommandGetDailyListReport(idx))
    }

    Component.onCompleted: {console.debug("PanelWCReportWindow:Create")}
    Component.onDestruction:{console.debug("PanelWCReportWindow:Destroy")}

    onVisibilityChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();
    }


    PanelWCReportContainerModel{
        id : reportContainerModel
        onSignalEventCompleteLoad: {

            loadingDialog.close()
            leftMenu.clearDate()
            for(var i = 0; i < onCommandGetDailyListCnt(); i++)
            {
                leftMenu.addDate(onCommandGetDailyListDate(i), i)
            }

            leftMenu.selectDateIdx(0)
        }

        onSignalEventSelectedPrint: {
            bgPrint.printIdx = 0
            setDailyReportPrint(bgPrint.printIdx++)
        }


        onSignalEventSelectedPrintCancle: {loadingDialog.close()}
    }


    Rectangle{
        property int printIdx : 0
        id: bgPrint
        color : "#131313"
        anchors.fill: parent


        PanelWCReportContainer{
            id : dailyReportPrintContainer

            onSignalEventPrintEnd: {

                if(bgPrint.printIdx < reportContainerModel.onCommandGetDailyListCnt())
                    setDailyReportPrint(bgPrint.printIdx++)
                else
                {
                    reportContainerModel.onCommandPrintEnd()
                    loadingDialog.close()
                }
            }
        }
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
            isEditMode : reportContainerModel.mIsEditMode

            width: 142
            anchors.top: dateRange.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0


            onSignalEventClickPrint: {
                if(reportContainerModel.onCommandGetDailyListCnt() < 1)
                {
                    return;
                }

                loadingDialog.open()
                reportContainerModel.onCommandSelectPrint()
            }

            onSignalEventClickEdit:{
                if(reportContainerModel.mIsEditMode)
                    reportContainerModel.onCommandSetIsEditMode(false);
                else
                    pwdDialog.open()
            }
            onSignalEventSelectDate: {setDailyReport (idx)}
            onSignalEventClickLoad : {loadReportModel(   )}

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

                PanelWCReportContainer{
                    id : dailyReportContainer
                    containerModel : reportContainerModel
                }
            }
        }

        ControlSignatureCheck{
            width: 382
            height: 58
            isCheckedWrite   : reportContainerModel.mIsCheckWrite
            isCheckedReview  : reportContainerModel.mIsCheckReview
            isCheckedApproved: reportContainerModel.mIsCheckApproved

            anchors.top: scrollView.top
            anchors.topMargin: 20
            anchors.right: scrollView.right
            anchors.rightMargin: 20

            onSignalEventClickWrite   : {reportContainerModel.onCommandSetIsCheckWrite   (!reportContainerModel.mIsCheckWrite   )}
            onSignalEventClickReview  : {reportContainerModel.onCommandSetIsCheckReview  (!reportContainerModel.mIsCheckReview  )}
            onSignalEventClickApproved: {reportContainerModel.onCommandSetIsCheckApproved(!reportContainerModel.mIsCheckApproved)}

        }

        DialogPassword{
            id : pwdDialog
            onSignalEventMatchPassword: {
                reportContainerModel.onCommandSetIsEditMode(true)
            }
        }
    }

    UiDialogLoading{ id :loadingDialog }
}

/*##^##
Designer {
    D{i:6;anchors_y:88}D{i:11;anchors_height:200;anchors_x:65;anchors_y:220}
}
##^##*/
