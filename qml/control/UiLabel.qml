import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0

Text{
    id : control

    font.pixelSize      : 15
    verticalAlignment   : Text.AlignVCenter
    horizontalAlignment : Text.AlignLeft
    color               : "#ACACAC"
    elide: Text.ElideRight
    font.family         : FontManager.nanumGothicName
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
