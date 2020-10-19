import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0


Item {
    id :control

    width: 100
    height: 200

    property alias text       : inputText.text
    property alias fontFamily : inputText.font.family
    property alias fontColor  : inputText.color
    property alias fontSize   : inputText.font.pixelSize
    property alias fontBold   : inputText.font.bold
    property alias hAlignment : inputText.horizontalAlignment
    property alias vAlignment : viewText.verticalAlignment
    property alias inputFocus : inputText.focus

    signal signalEventChangedText(string text)

    Text{
        id : viewText
        anchors.fill: parent

        opacity: inputText.focus ? 0.001 : 1

        text                : inputText.text

        fontSizeMode        : Text.HorizontalFit
        font.family         : inputText.font.family
        color               : inputText.color
        font.pixelSize      : inputText.font.pixelSize
        font.bold           : inputText.font.bold
        horizontalAlignment : inputText.horizontalAlignment
        verticalAlignment   : Text.AlignVCenter
    }

    TextField{
        id : inputText
        anchors.fill: parent

        opacity: focus ? 1 : 0.001

        text                : "doc input"
        font.family         : "Gulim"
        color               : "#000000"
        font.pixelSize      : 12
        font.bold           : false
        horizontalAlignment : Text.AlignHCenter
        verticalAlignment   : Text.AlignVCenter

        background: Rectangle{
            color : "#00000000"
        }
    }
}


