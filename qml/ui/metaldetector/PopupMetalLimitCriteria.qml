import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import ViewManager 1.0
import PopupMetalLimitCriteriaModel 1.0

import "../../control/."

Item {

    id : panel
    width: 300
    height: 300

    signal signalEventChagnedValue()

    function open(dNum)
    {
        limitCriterialModel.onCommandLoad()

        listModel.clear()

        for(var i = 0; i < limitCriterialModel.onCommandGetLimitCriteriaCnt(); i ++)
        {
            var pdNum = limitCriterialModel.onCommandGetPDNum(i)
            var pdName = limitCriterialModel.onCommandGetPDName(i)
            var limitCriteriaFe = limitCriterialModel.onCommandGetlimitCriteriaFe(i)
            var limitCriteriaSus = limitCriterialModel.onCommandGetlimitCriteriaSus(i)
            listModel.append({"idx":i, "pdNum" : pdNum, "pdName" : pdName, "limitCriteriaFe" : limitCriteriaFe, "limitCriteriaSus" : limitCriteriaSus})
        }

        popup.show()
    }

    PopupMetalLimitCriteriaModel{
        id : limitCriterialModel
    }

    Window
    {
        id : popup

        modality : Qt.WindowModal
        minimumHeight: 526
        minimumWidth: 800

        title: qsTr("Edit limit criteria")
        flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

        Rectangle
        {
            color : "#131313"
            anchors.fill: parent

            Item{
                width: parent.width / ViewManager.scale
                height: parent.height / ViewManager.scale
                scale : ViewManager.scale

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                ListView{
                    anchors.top: parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
                    height: 430

                    spacing: 10
                    clip: true;

                    model : ListModel{
                        id : listModel
                    }

                    delegate :
                        Rectangle
                        {
                            id : rowItem

                            height: 50; width: parent.width
                            color: "#232323"

                            Label{
                                id : labelPDNum
                                height: 50; width: 50
                                anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter

                                text : ("000" + pdNum).slice(-3)
                            }

                            Label{
                                id : labelPDName
                                height: 50; width: 220
                                anchors.left: labelPDNum.right; anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                text : pdName
                            }

                            Label{
                                id : labelTitleLimitFe
                                height: 50; width: 120
                                anchors.left: labelPDName.right; anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                text : qsTr("Limit criteria(Fe)")
                            }

                            TextField {
                                id: inputLimitFe
                                height: 30; width: 100
                                anchors.left: labelTitleLimitFe.right; anchors.verticalCenter: parent.verticalCenter
                                text : limitCriteriaFe

                                onTextChanged: {
                                    limitCriterialModel.onCommandSetLimitCriteriaFe(idx, inputLimitFe.text)
                                }
                            }

                            Label{
                                id : labelTitleLimitSus
                                height: 50; width: 120
                                anchors.left: inputLimitFe.right; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter
                                verticalAlignment: Text.AlignVCenter
                                text : qsTr("Limit criteria(Sus)")


                            }

                            TextField {
                                id: inputLimitSus
                                height: 30; width: 100
                                anchors.left: labelTitleLimitSus.right; anchors.verticalCenter: parent.verticalCenter
                                text : limitCriteriaSus

                                onTextChanged: {
                                    limitCriterialModel.onCommandSetLimitCriteriaSus(idx, inputLimitSus.text)
                                }
                            }
                        }
                }


                Item{
                    id : containerBtn
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    height: 80
                    //color :"#434343"

                    UiButton{
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        text        : qsTr("Cancle")
                        isTextBtn   : true
                        fontColor: "#FFFFFF"

                        onSignalEventClicked: { popup.close()}
                    }

                    UiButton{
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        text        : qsTr("Apply")
                        isTextBtn   : true
                        colType     : EnumDefine.BTN_COLOR_TYPE_BLUE
                        fontColor: "#FFFFFF"

                        onSignalEventClicked: {
                            limitCriterialModel.onCommandApply()

                            popup.close()
                        }
                    }
                }
            }
        }
    }
}
