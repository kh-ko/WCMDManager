import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    property bool isOn
    property alias onImage : imageOn.source
    property alias offImage : imageOff.source

    id : component

    Image {
        id: imageOn
        anchors.fill: parent

        fillMode: Image.PreserveAspectFit
        visible: isOn ? true : false
    }

    Image {
        id: imageOff
        anchors.fill: parent

        fillMode: Image.PreserveAspectFit
        visible: isOn ? false : true
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
