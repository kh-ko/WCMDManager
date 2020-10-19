import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0
import PanelMonitorListModel 1.0
import PanelMonitorItemModel 1.0

import "../control/."
import "./monitoring/."

Window{
    property PanelMonitorListModel dlgModel : null
    property real lookScale : 1.0

    id : dialog
    modality : Qt.NonModal

    height: 300
    width: 870

    title : qsTr("Remote monitoring")
    //flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowMaximizeButtonHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint

    function open()
    {
        if(dialog.visible)
            return;

        dialog.dlgModel = modelComponent.createObject(dialog)

        for(var i = 0; i < dialog.dlgModel.onCommandGetMonitorListSize(); i ++)
        {
            itemComponent.createObject(containerItem, {"itemModel":dialog.dlgModel.onCommandGetMonitorListItem(i)})
        }

        dialog.show()
    }

    onVisibilityChanged:
    {
        if(dialog.visible)
            return;

        for(var i = 0; i < containerItem.children.length; i ++)
        {
            containerItem.children[i].destroy();
        }

        if(dialog.dlgModel == null)
            return;

        dialog.dlgModel.destroy();
        dialog.dlgModel = null;
    }

    Rectangle{
        color : "#131313"
        anchors.centerIn: parent
        width: parent.width / ViewManager.scale
        height: parent.height / ViewManager.scale
        scale: ViewManager.scale

        UiScrollView{
            id : scrollView
            clip: true
            anchors.fill: parent
            scale: dialog.lookScale

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Flow{
                id : containerItem
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left : parent.left
                anchors.leftMargin: 20

                width: scrollView.width - 20

                spacing: 10
            }
        }
    }

    Component{
        id : modelComponent

        PanelMonitorListModel{
            onSignalEventAddedItem: {
                itemComponent.createObject(containerItem, {"itemModel":dialog.dlgModel.onCommandGetMonitorListItem(idx)})
            }
        }
    }

    Component{
        id : itemComponent

        PanelMonitoringItem{

        }
    }
}
