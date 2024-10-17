import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.animation 1.0
import Forms 1.0

Item {
    id: root
    anchors.fill: parent

    CalculateForm {
        id: calculateFormGeneric
    }

    ListModel {
        id: modelButton
        ListElement {
            contentButton: "("
            colorButton: "#652580"
        }
        ListElement {
            contentButton: ")"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "C"
            colorButton: "#3c388d"
        }
        ListElement {
            contentButton: "Del"
            colorButton: "#3c388d"
        }
        ListElement {
            contentButton: "1/x"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "^"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "sqrt"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "%"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "7"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "8"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "9"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "/"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "4"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "5"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "6"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "*"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "1"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "2"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "3"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "-"
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "."
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "0"
            colorButton: "#9ce551"
        }
        ListElement {
            contentButton: "="
            colorButton: "#652580"
        }
        ListElement {
            contentButton: "+"
            colorButton: "#652580"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20

        RowLayout {
            id: labelLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            Layout.maximumHeight: 250

            Text {
                id: textInput
                text: calculateFormGeneric.textInput
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 80
                anchors.rightMargin: root.width - gridButton.width
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.pointSize: 40
            }
            Text {
                id: textOutput
                text: calculateFormGeneric.textOutput
                font.pointSize: 35
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: textInput.bottom
                anchors.rightMargin: root.width - gridButton.width
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
            }
        }

        GridLayout {
            id: gridButton
            anchors.top: labelLayout.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            Layout.maximumWidth: 1000
            Layout.maximumHeight: 800
            columns: 4
            rows: 6

            Repeater {
                anchors.fill: parent
                model: modelButton

                property string contentButton
                property string colorButton

                Button {
                    id: operationsButton
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: 125

                    contentItem: {

                    }
                    background: Rectangle {
                        anchors.fill: parent
                        color: colorButton
                        radius: 10
                    }

                    Text {
                        anchors.fill: parent
                        text: contentButton
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 20
                        color: "white"
                    }
                    onClicked: {
                        calculateFormGeneric.operations(contentButton)
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

