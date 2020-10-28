import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import PanelWCSelectDeviceProductModel 1.0

import "../../control/."
import "."

Rectangle {

    id : panel

    width : 1196
    height: 93

    color : "#333333"
    radius: 10

    PanelWCSelectDeviceProductModel
    {
        id : model
    }

    RowLayout
    {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40

        height: 42
        spacing: 40

        UiComboBox{
            labelText: qsTr("Device")
            Layout.fillHeight: true
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            labelWidth: 180

            inputText: ("000" + model.mDNum).slice(-3) + " " + model.mDName
            listModel: deviceListModel

            ListModel{
                id : deviceListModel
            }

            onSignalExtendList: {

                deviceListModel.clear()

                for(var i = 0; i < model.onCommandGetDListSize(); i ++)
                {
                    var value =("000" + model.onCommandGetDNum(i)).slice(-3) + " " +  model.onCommandGetDName(i);
                    var tag =model.onCommandGetDNum(i);

                    deviceListModel.append({"itemValue":value,"itemTag":tag})
                }
            }

            onSignalEventClick: {
                model.onCommandSelDevice(tag)
            }
        }

        UiComboBox{
            labelText: qsTr("Product")
            Layout.fillHeight: true
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            labelWidth: 180

            inputText: ("000" + model.mPNum).slice(-3) + " " + model.mPName
            listModel: productListModel

            ListModel{
                id : productListModel
            }
            onSignalExtendList: {

                productListModel.clear();

                for(var i = 0; i < model.onCommandGetProductListSize(); i ++)
                {
                    var value =("000" + model.onCommandGetPNum(i)).slice(-3) + " " +  model.onCommandGetPName(i);
                    var tag =model.onCommandGetPSeq(i);

                    productListModel.append({"itemValue":value,"itemTag":tag})
                }
            }

            onSignalEventClick: {
                model.onCommandSelProduct(tag)
            }
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:1060}
}
##^##*/
