import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.animation 1.0
import Forms 1.0

ApplicationWindow {
    id: root
    width: 700
    height: 600
    title: "О программе Formula Plus"

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        RowLayout {
            id: titleLayout
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            Image {
                id: titleImage
                source: "qrc:/images/logotype.png"
                Layout.preferredWidth: 120
                Layout.preferredHeight: 100
            }

            Text {
                anchors.left: titleImage.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 5
                anchors.topMargin: 10
                id: title
                font.pointSize: 45
                color: "#8330a6"
                text: "Formula Plus"
            }
        }
        RowLayout {
            id: descriptionLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: titleLayout.bottom
            anchors.topMargin: 10

            Text {
                anchors.fill: parent
                anchors.rightMargin: 100
                id: description
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pointSize: 16
                text: "TUSUR Formula Plus (64 разрядная версия)
Текущая версия приложения 1.0.11 \n
© Разработано командой ГПО шокльникой,
под руководством Дмитрия Михайловича Мочалова,
при содействие с TUSUR University, при поддержки
Bunch Software, 2022-2024 г. Все права защищены. \n
Программа основана на Qt 6.7.2 (MSVC 64-bit) \n
Собрано 19 октября в 21:07 \n
Данное приложение распространяется под
свободной лицензией Apache License 2.0 2004 г. "
            }
        }
        RowLayout {
            id: buttonLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: descriptionLayout.bottom
            anchors.topMargin: 20

            Button {
                id: buttonOk
                implicitWidth: 150
                Layout.fillHeight: true
                anchors.right: parent.right
                Layout.maximumHeight: 50

                background: Rectangle {
                    anchors.fill: parent
                    color: colorButton
                    radius: 10
                }

                Text {
                    anchors.fill: buttonOk
                    text: "OK"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 20
                    color: "black"
                }
                onClicked: {
                    root.close()
                }
            }
        }
    }
}
