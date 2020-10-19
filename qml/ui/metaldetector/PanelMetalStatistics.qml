import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ViewManager 1.0
import EnumDefine 1.0
import PanelMetalStatisticsModel 1.0

import "../../control/."

Rectangle {
    property int month : 8
    property int year  : 2020
    id : panel

    width : 1196
    height: 418

    color : "#333333"
    radius: 10

    function updateData()
    {
        if(model.mIsLoading)
            return;

        productList.clear()

        for(var productIdx = 0; productIdx < model.onCommandGetProductListSize(); productIdx ++)
        {
            var seq = model.onCommandGetProductSeqInProductList(productIdx)
            var no = model.onCommandGetProductNoInProductList(productIdx)
            var name = model.onCommandGetProductNameInProductList(productIdx)

            productList.append({"productSeq":seq,"productNo":no, "productName":name})
        }

        graph.clear();

        for(var i = 0; i < model.mMaxDay; i ++)
        {
            graph.add("" + model.mYear + "." + model.mMonth + "." + i+1, model.onCommandGetTotalCnt(i+1), model.onCommandGetDetectCnt(i + 1), i + 1)
        }
    }

    PanelMetalStatisticsModel
    {
        id : model

        onSignalEventCompletedUpdate: { updateData();}
    }

    Component.onCompleted: {updateData();}

    UiLabel
    {
        id : labelTitle

        color : "#FFFFFF"
        text  : qsTr("Statistics for ") + model.mMonth + ". " + model.mYear
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    UiLabel{
        id : labelProductName
        anchors.left: comboProduct.left
        anchors.leftMargin: 20
        anchors.top: comboProduct.bottom
        anchors.topMargin: 10

        text : model.mSelProductName
        color: "#ffffff"
    }

    Rectangle{
        id : rectTotalBar
        width: 12
        height: 5
        anchors.left: comboProduct.left
        anchors.leftMargin: 20
        anchors.verticalCenter: labelTotal.verticalCenter

        radius: 2
        color: "#0085ff"
    }

    UiLabel{
        id : labelTotal
        anchors.left: rectTotalBar.right
        anchors.leftMargin: 10
        anchors.top: labelProductName.bottom
        anchors.topMargin: 40


        text : qsTr("Total")
    }

    UiLabel{
        id : labelTotalCnt
        anchors.right: comboProduct.right
        anchors.rightMargin: 0
        anchors.verticalCenter: labelTotal.verticalCenter

        text : model.mTotalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        color: "#ffffff"
    }

    Rectangle{
        id : rectNGBar
        width: 12
        height: 5
        anchors.left: labelProductName.left
        anchors.leftMargin: 0
        anchors.verticalCenter: labelNG.verticalCenter

        radius: 2
        color: "#FD4359"
    }

    UiLabel{
        id : labelNG
        anchors.left: rectNGBar.right
        anchors.leftMargin: 10
        anchors.top: labelTotal.bottom
        anchors.topMargin: 20

        text : qsTr("NG")
    }

    UiLabel{
        id : labelNGCnt
        anchors.right: comboProduct.right
        anchors.rightMargin: 0
        anchors.verticalCenter: labelNG.verticalCenter

        text : model.mNGCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        color: "#ffffff"
    }

    UiLabel{
        id : labelNGRate
        anchors.left: labelNG.left
        anchors.leftMargin: 0
        anchors.top: labelNG.bottom
        anchors.topMargin: 20

        text : qsTr("NG rate")
    }


    UiLabel{
        id : labelNGRateValue
        anchors.right: comboProduct.right
        anchors.rightMargin: 0
        anchors.verticalCenter: labelNGRate.verticalCenter

        text : model.mTotalCnt < 1 ? "0.0 %" : ((model.mNGCnt / model.mTotalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + "%"
        color: "#ffffff"
    }

    UiProductComboBox{
        id : comboProduct
        width  : 245
        height : 42
        labelText: qsTr("Product")
        inputText: ("000" + model.mSelProductNo).slice(-3)
        labelWidth: 144
        anchors.top: labelTitle.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        listModel : productList

        ListModel{
            id : productList
        }

        onSignalEventClick:
        {
            model.onCommandSelProduct(data);
        }
    }

    UiMDStatisticsGraph{
        id : graph
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: comboProduct.right
        anchors.leftMargin: 10
    }

}
