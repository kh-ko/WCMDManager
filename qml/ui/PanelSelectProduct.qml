import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelSelectProductModel 1.0
import CheckProductModel 1.0

import "../control/."

Window{
    id : dialog
    modality : Qt.WindowModal

    height: 600; width: 400
    minimumHeight: 600; minimumWidth: 400

    title : qsTr("Select product")

    signal signalEventClosed(string value)

    function open()
    {
        dialog.show()
    }

    onVisibilityChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();
    }

    Component.onCompleted: {

        var size = dialogModel.onCommandGetProductListSize()

        for(var idx = 0; idx < dialogModel.onCommandGetProductListSize(); idx++)
        {
            var tempModel = dialogModel.onCommandGetProductModel(idx)
            productlistViewModel.append({"idx":idx, "itemModel":tempModel})
            //itemComponent.createObject(productList, {"idx":idx, "itemModel":model.onCommandGetProductModel(idx)})
        }
    }

    PanelSelectProductModel{
        id : dialogModel
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

        Rectangle{
            id : listHeader
            anchors.top: parent.top; anchors.left : parent.left; anchors.right: parent.right;
            color: "#333333"

            height: 50

            UiCheckBox{
                id : totalCheck
                anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter
                width: 25; height: 25

                checked : dialogModel.mIsAllChecked

                onSignalEventClicked: {
                    dialogModel.onCommandSetAllSelect(!dialogModel.mIsAllChecked)
                }
            }

            UiLabel{
                id : labelTotalCheck
                height: 26
                anchors.verticalCenter: totalCheck.verticalCenter
                anchors.left: totalCheck.right
                anchors.leftMargin: 10

                text: qsTr("Total")
            }
        }

        UiScrollView{
            id : scrollView
            width: parent.width
            height: parent.height - listHeader.height - listFooter.height
            barPressColor : "#17a81a"
            barColor : "#21be2b"

            anchors.left : parent.left
            anchors.leftMargin: 0
            anchors.top: listHeader.bottom
            anchors.topMargin: 0

            Item{
                anchors.fill: parent

                ListView {
                    id: productList
                    spacing: 10
                    anchors.top : parent.top
                    anchors.topMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10

                    model: productlistViewModel
                    clip: true

                    ListModel
                    {
                        id: productlistViewModel
                    }

                    delegate : Rectangle
                    {
                        //property int idx
                        //property CheckProductModel itemModel

                        height: 50; width: parent.width
                        color: "#333333"

                        radius : 10

                        UiCheckBox{
                            id : productCheck
                            anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter
                            width: 25; height: 25

                            checked : itemModel.mIsChecked

                            onSignalEventClicked: {
                                dialogModel.onCommandSetSelect(idx,!itemModel.mIsChecked)
                            }
                        }

                        UiLabel{
                            height: 26
                            anchors.verticalCenter: productCheck.verticalCenter
                            anchors.left: productCheck.right
                            anchors.leftMargin: 20
                            anchors.right: parent.right
                            anchors.rightMargin: 20

                            text: itemModel.mPName
                        }
                    }
                }
            }

            /*
            ColumnLayout{
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left : parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10

                Flow{
                    id : productList
                    Layout.fillWidth: true
                    spacing: 10
                }
            }
            */
        }

        Rectangle{
            id : listFooter
            anchors.top: scrollView.bottom; anchors.left : parent.left; anchors.right: parent.right;
            color: "#333333"

            height: 80

            UiButton{
                id :btnConfirm
                text: qsTr("Confirm")
                isTextBtn : true
                colType: EnumDefine.BTN_COLOR_TYPE_BLUE
                fontColor : "#FFFFFF"

                height: 60
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10

                onSignalEventClicked:
                {
                    dialog.close();
                    dialog.signalEventClosed(dialogModel.onCommandGetSelectProductList())

                }
            }

            UiButton{
                id :btnCancel
                text: qsTr("Cancel")
                isTextBtn : true

                height: 60
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: btnConfirm.left
                anchors.rightMargin: 10

                onSignalEventClicked :{

                    dialog.close();
                }
            }
        }
    }
/*
    Component{
        id : itemComponent

        Rectangle{
            property int idx
            property CheckProductModel itemModel

            height: 50; width: parent.width
            color: "#222222"
        }
    }
    */
}
/*##^##
Designer {
    D{i:6;anchors_y:88}D{i:11;anchors_height:200;anchors_x:65;anchors_y:220}
}
##^##*/
