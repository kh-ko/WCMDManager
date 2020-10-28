import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ViewManager 1.0
import EnumDefine 1.0
import PanelWCHistogramModel 1.0

import "../../control/."

Rectangle {
    property int month : 8
    property int year  : 2020
    id : panel

    width : 801
    height: 570

    color : "#333333"
    radius: 10

    PanelWCHistogramModel{
        id :model

        onSignalEventChangedGraphData: {
            yAxis01.text = onCommandGetYGab() * 1; yAxis06.text = onCommandGetYGab() * 6;
            yAxis02.text = onCommandGetYGab() * 2; yAxis07.text = onCommandGetYGab() * 7;
            yAxis03.text = onCommandGetYGab() * 3; yAxis08.text = onCommandGetYGab() * 8;
            yAxis04.text = onCommandGetYGab() * 4; yAxis09.text = onCommandGetYGab() * 9;
            yAxis05.text = onCommandGetYGab() * 5; yAxis10.text = onCommandGetYGab() * 10;

            yValue01.text = onCommandGetYValue(0); yValue07.text = onCommandGetYValue(6);
            yValue02.text = onCommandGetYValue(1); yValue08.text = onCommandGetYValue(7);
            yValue03.text = onCommandGetYValue(2); yValue09.text = onCommandGetYValue(8);
            yValue04.text = onCommandGetYValue(3); yValue10.text = onCommandGetYValue(9);
            yValue05.text = onCommandGetYValue(4); yValue11.text = onCommandGetYValue(10);
            yValue06.text = onCommandGetYValue(5); yValue12.text = onCommandGetYValue(11);

            xAXis01.text = (onCommandGetXValue(0) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis02.text = (onCommandGetXValue(1) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis03.text = (onCommandGetXValue(2) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis04.text = (onCommandGetXValue(3) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis05.text = (onCommandGetXValue(4) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis06.text = (onCommandGetXValue(5) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis07.text = (onCommandGetXValue(6) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis08.text = (onCommandGetXValue(7) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis09.text = (onCommandGetXValue(8) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis10.text = (onCommandGetXValue(9) / 1000).toLocaleString(ViewManager.locale, 'f', 2);
            xAXis11.text = (onCommandGetXValue(10)/ 1000).toLocaleString(ViewManager.locale, 'f', 2);

            var defaultHeight = (-1 * xBarBg01.anchors.bottomMargin) - xBar01.anchors.bottomMargin

            xBar01.height = defaultHeight + (barArea.height * (onCommandGetYValue(0) / (onCommandGetYGab() * 10)))
            xBar02.height = defaultHeight + (barArea.height * (onCommandGetYValue(1) / (onCommandGetYGab() * 10)))
            xBar03.height = defaultHeight + (barArea.height * (onCommandGetYValue(2) / (onCommandGetYGab() * 10)))
            xBar04.height = defaultHeight + (barArea.height * (onCommandGetYValue(3) / (onCommandGetYGab() * 10)))
            xBar05.height = defaultHeight + (barArea.height * (onCommandGetYValue(4) / (onCommandGetYGab() * 10)))
            xBar06.height = defaultHeight + (barArea.height * (onCommandGetYValue(5) / (onCommandGetYGab() * 10)))
            xBar07.height = defaultHeight + (barArea.height * (onCommandGetYValue(6) / (onCommandGetYGab() * 10)))
            xBar08.height = defaultHeight + (barArea.height * (onCommandGetYValue(7) / (onCommandGetYGab() * 10)))
            xBar09.height = defaultHeight + (barArea.height * (onCommandGetYValue(8) / (onCommandGetYGab() * 10)))
            xBar10.height = defaultHeight + (barArea.height * (onCommandGetYValue(9) / (onCommandGetYGab() * 10)))
            xBar11.height = defaultHeight + (barArea.height * (onCommandGetYValue(10)/ (onCommandGetYGab() * 10)))
            xBar12.height = defaultHeight + (barArea.height * (onCommandGetYValue(11)/ (onCommandGetYGab() * 10)))

            inputGMin.inputText =(onCommandGetXMin()/ 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g";
            inputGMax.inputText =(onCommandGetXMax()/ 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g";
        }
    }

    UiLabel
    {
        id : labelTitle

        color : "#FFFFFF"
        text  : qsTr("Histogram")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Item{
        id : graphBg
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: labelTitle.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 80
        Item{
            id: yAxis
            width: 70
            anchors.top: parent.top
            anchors.bottom: yLineArea.bottom
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            UiLabel {
                id: yAxis10
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis09
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 1 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis08
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 2 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis07
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 3 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis06
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 4 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis05
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 5 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis04
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 6 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis03
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 7 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis02
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 8 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                id: yAxis01
                text: "999,999"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 9 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

            UiLabel {
                text: "0"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: parent.height - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                horizontalAlignment: Text.AlignRight
            }

        }

        Item{
            id: yLineArea
            anchors.left: yAxis.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: xAxis.top
            anchors.bottomMargin: 10
            anchors.leftMargin: 10

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 0 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 1 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 2 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 3 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 4 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 5 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 6 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 7 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 8 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.1) * 9 - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

            Rectangle {
                height: 2
                color: "#59ffffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: (parent.height) - (height / 2)
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }

        }

        RowLayout {
            id: barArea
            anchors.left: yLineArea.left
            anchors.right: yLineArea.right
            anchors.top: yLineArea.top
            anchors.bottom: yLineArea.bottom
            anchors.rightMargin: 30
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0

            clip: true

            Item {
                width: 200
                height: 200
                Layout.preferredHeight: 1
                Layout.preferredWidth: 50
                Layout.fillHeight: true
                Layout.fillWidth: true

                Rectangle {
                    id : xBarBg01
                    width: 30
                    color: "#59000000"
                    radius: 15
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -15
                    anchors.topMargin: 0
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        id: xBar01
                        width: parent.width - 4
                        height: 50
                        color: "#0085ff"
                        radius: 15
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        anchors.horizontalCenter: parent.horizontalCenter


                    }

                    UiLabel{
                        id: yValue01
                        width: 100
                        color: "#FFFFFF"
                        text: "999,999"
                        anchors.top: parent.top
                        horizontalAlignment: Text.AlignRight
                        anchors.topMargin: 60
                        anchors.horizontalCenter: parent.horizontalCenter
                        rotation: 270
                    }
                }
            }

            Item {
                width: 200
                height: 200
                Layout.preferredWidth: 30
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            RowLayout {
                width: 200
                height: 200
                Layout.preferredWidth: 480
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar02
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue02
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar03
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue03
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar04
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue04
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar05
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue05
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar06
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue06
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar07
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue07
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar08
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue08
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar09
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue09
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar10
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue10
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        width: 30
                        color: "#59000000"
                        radius: 15
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -15
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            id: xBar11
                            width: parent.width - 4
                            height: 50
                            color: "#0085ff"
                            radius: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 0
                            anchors.horizontalCenter: parent.horizontalCenter


                        }

                        UiLabel{
                            id: yValue11
                            width: 100
                            color: "#FFFFFF"
                            text: "999,999"
                            anchors.top: parent.top
                            horizontalAlignment: Text.AlignRight
                            anchors.topMargin: 60
                            anchors.horizontalCenter: parent.horizontalCenter
                            rotation: 270
                        }
                    }
                }
            }

            Item {
                width: 200
                height: 200
                Layout.preferredWidth: 30
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Item {
                width: 200
                height: 200
                Layout.preferredWidth: 50
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    width: 30
                    color: "#59000000"
                    radius: 15
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -15
                    anchors.topMargin: 0
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        id: xBar12
                        width: parent.width - 4
                        height: 50
                        color: "#0085ff"
                        radius: 15
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter


                    }

                    UiLabel{
                        id: yValue12
                        width: 100
                        color: "#FFFFFF"
                        text: "999,999"
                        anchors.top: parent.top
                        horizontalAlignment: Text.AlignRight
                        anchors.topMargin: 60
                        anchors.horizontalCenter: parent.horizontalCenter
                        rotation: 270
                    }
                }
            }
        }

        RowLayout
        {
            id: xAxis
            y: 391
            height: 84
            anchors.left: barArea.left
            anchors.right: barArea.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            clip: false

            Item {
                id: item1
                width: 200
                height: 200
                Layout.preferredHeight: 1
                Layout.preferredWidth: 50
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiLabel{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    text: qsTr("Under")
                    rotation: 0
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.topMargin: 0

                }
            }

            Item {
                id: item2
                width: 200
                height: 200
                Layout.preferredWidth: 30
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                UiLabel{
                    text: "..."
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignLeft
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0

                }
            }

            RowLayout {
                width: 200
                height: 200
                Layout.preferredWidth: 480
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis01
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                        anchors.verticalCenterOffset: 0

                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis02
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)

                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis03
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis04
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis05
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis06
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis07
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis08
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis09
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }

                Item {
                    width: 200
                    height: 200
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    UiLabel{
                        id: xAXis10
                        text: "99,999.9"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.height
                        height: parent.width
                        rotation: 270
                        horizontalAlignment: Text.AlignRight
                        anchors.horizontalCenterOffset: (-1 * height * 0.5)
                    }
                }
            }

            Item {
                id: item3
                width: 200
                height: 200
                Layout.preferredWidth: 30
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                UiLabel{
                    id: xAXis11
                    text: "99,999.9"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    rotation: 270
                    horizontalAlignment: Text.AlignRight
                    anchors.horizontalCenterOffset: (-1 * height * 0.5)
                }

                UiLabel{
                    text: "..."
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignRight
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0

                }

            }

            Item {
                id: item4
                width: 200
                height: 200
                Layout.preferredWidth: 50
                Layout.preferredHeight: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                UiLabel{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.height
                    height: parent.width
                    text: qsTr("Over")
                    rotation: 0
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.topMargin: 0

                }
            }
        }
        UiLabel{
            text: "[g]"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.rightMargin: 15

        }
    }

    DoubleValidator{
            id : floatExpValidator
            bottom: 0
            top : 100000
            decimals: 1
            //regExp : /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
    }

    UiInputText {
        id: inputGMin
        x: 507
        width: 250
        height: 42
        anchors.right: inputGMax.left
        anchors.top: parent.top
        labelText: qsTr("Graph min")
        anchors.rightMargin: 20
        anchors.topMargin: 20
        labelWidth: 130
        validator : floatExpValidator

        onSignalEventChangedInputFocus: {
            if(value === true)
            {
                inputText = inputText.replace(",","")
                inputText = inputText.replace(" g","")
            }
            else
            {
                inputText = (parseFloat(inputText)).toLocaleString(ViewManager.locale, 'f', 1) + " g";
            }
        }
    }

    UiInputText {
        id: inputGMax
        x: 507
        width: 250
        height: 42
        anchors.right: btnApply.left
        anchors.top: parent.top
        inputText: "99,999.9 g"
        anchors.topMargin: 20
        anchors.rightMargin: 20
        labelText: qsTr("Graph max")
        labelWidth: 130
        validator : floatExpValidator

        onSignalEventChangedInputFocus: {
            if(value === true)
            {
                inputText = inputText.replace(",","")
                inputText = inputText.replace(" g","")
            }
            else
            {
                inputText = (parseFloat(inputText)).toLocaleString(ViewManager.locale, 'f', 1) + " g";
            }
        }
    }

    UiButton{
        id : btnApply
        width: 120
        height: 42
        colType: EnumDefine.BTN_COLOR_TYPE_BLUE
        isTextBtn: true
        text : qsTr("Apply")

        anchors.top: parent.top
        fontColor: "#ffffff"
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        onSignalEventClicked: {
            var strMin = inputGMin.inputText.replace(",","")
            strMin = strMin.replace(" g","")
            var minValue = (parseFloat(strMin) * 1000) + 0.5
            var strMax = inputGMax.inputText.replace(",","")
            strMax = strMax.replace(" g","")
            var maxValue = (parseFloat(strMax) * 1000) + 0.5

            model.onCommandSetRange(minValue, maxValue)
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:16}D{i:35}
}
##^##*/
