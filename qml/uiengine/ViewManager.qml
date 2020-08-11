pragma Singleton

import QtQuick 2.0

Item 
{
    property  var windows : null
    property var locale : Qt.locale("en-US")

    function setWindows(win)
    {
        windows = win;
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
