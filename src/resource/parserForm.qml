import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.animation 1.0
import Forms 1.0

Item {
    id: root

    ParserForm {
        id: parserGeneric
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        RowLayout {
            id: textInputLayout
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            Rectangle {
                color: "#3c388d"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 50
                border.width: 0
                radius: 10
                TextField {
                    id: textInput
                    background: Rectangle {
                        anchors.fill: parent
                        color: "#00000000"
                    }
                    color: "white"
                    placeholderTextColor: "white"
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    font.pointSize: 12
                    placeholderText: "Введите математическое выражение"
                    onFocusChanged: {
                        parserGeneric.setTextInput(textInput.text)
                    }
                }
            }
        }
        RowLayout {
            id: textResultLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: textInputLayout.bottom
            anchors.topMargin: 20

            Text {
                anchors.fill: parent
                color: "black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 12
                text: parserGeneric.textOutput
            }
        }
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: textResultLayout.bottom
            anchors.topMargin: 20

            Button {
                anchors.fill: parent
                implicitHeight: 50
                text: "Расчитать математическое выражение"

                contentItem: Text {}
                onClicked: parserGeneric.calculate()
                background: Rectangle {
                    anchors.fill: parent
                    color: "#8330a6"
                    border.width: 0
                    radius: 10
                }
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    text: parent.text
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pointSize: 12
                    color: "white"
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

