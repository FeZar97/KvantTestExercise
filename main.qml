import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import KvantTableModel 0.1

Window {
    width: cellWidth * 3 + spacing * 2
    height: 400
    visible: true

    property var cellWidth: 150
    property var spacing: 2

    Connections {
        target: kvantTableModel

        onShowMessage: {
            popup.contentItem.text = message
            popup.open()
        }

        onUpdateTable: {
            tableView.model = []
            tableView.model = kvantTableModel
        }
    }

    FileDialog {
        id: fileDialog
        title: "Choose input file"
        folder: shortcuts.home
        onAccepted: {
            kvantTableModel.importFile(fileDialog.fileUrls)
        }
    }

    Popup {
        id: popup
        parent: Overlay.overlay
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentItem: Text {}
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        RowLayout {
            Layout.margins: 6
            Button {
                id: fileChooseButton
                text: "Import file"
                onClicked: {
                    fileDialog.open()
                }
            }

            Button {
                id: clearButton
                text: "Clear data"
                onClicked: kvantTableModel.clearModel()
            }
        }

        RowLayout {
            TableView {
                id: tableView
                Layout.fillWidth: true
                Layout.fillHeight: true
                columnSpacing: spacing
                rowSpacing: 1
                clip: true

                delegate: Rectangle {
                    implicitHeight: 50
                    implicitWidth: cellWidth
                    border.width: 2
                    Text {
                        anchors.centerIn: parent
                        text: tabledata
                        font.pointSize: 12
                    }
                }
            }
        }
    }
}
