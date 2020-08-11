import QtQuick 2.12
import QtQuick.Window 2.12
import "../control/."

import SampleModel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SampleModel{
        id : model
    }

    UiButton {
        id: uiButton
        x: 179
        y: 140
        iconSource: "image_sample/btn_home.png"
        text : model.mText

        onSignalEventClicked: {
            model.onCommandTest(model.mText + "01")
        }
    }
}
