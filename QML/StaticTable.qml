import QtQuick 2.0

Rectangle {
    property int rowHeight: 30
    property real rowTitleRatio: 0.4
    width: 600
    color: "transparent"

    function addData(tableData) {
        var rowLength = tableData[0]

        hSeparator.createObject(table)

        for (var i = 1; i < tableData.length;) {
            if (i + rowLength > tableData.length) {
                console.log("Malformed table row", tableData)
                break
            }

            var component = row.createObject(table)

            vClosedSeparator.createObject(component)
            addRow(component, tableData.slice(i, i + rowLength))
            vClosedSeparator.createObject(component)

            hSeparator.createObject(table)
            i += rowLength
        }
    }

    function addRow(component, rowData) {
        cell.createObject(component, {
                              "height": rowHeight, "width": width * rowTitleRatio,
                              "cellValue": rowData[0]
                          })
        vSeparator.createObject(component)

        var widthRemaining = width - width * rowTitleRatio - 2

        for (var i = 1; i < rowData.length; ++i) {
            cell.createObject(component, {
                                  "width": widthRemaining / (rowData.length - 1) - 1,
                                  "cellValue": rowData[i]
                              })

            if (i < (rowData.length - 1)) {
                vSeparator.createObject(component)
            }
        }
    }

    function clearTable() {
        for (var rowIndex = table.children.length; rowIndex > 0; --rowIndex) {
            for (var cellIndex = table.children[rowIndex - 1].children.length; cellIndex > 0; --cellIndex) {
                table.children[rowIndex - 1].children[cellIndex -1].destroy()
            }
            table.children[rowIndex - 1].destroy()
        }
    }

    Component {
        id: vSeparator

        Rectangle {
            width: 1
            height: rowHeight - 8
            y: 4

            color: root.darkGray
        }
    }

    Component {
        id: vClosedSeparator

        Rectangle {
            width: 1
            height: rowHeight

            color: root.darkGray
        }
    }

    Component {
        id: hSeparator

        Rectangle {
            width: parent.width
            height: 1

            color: root.darkGray
        }
    }

    Component {
        id: cell

        Rectangle {
            property string cellValue: "Missing value!"
            height: rowHeight
            color: root.darkDarkGray

            Text {
                text: parent.cellValue
                anchors.fill: parent
                font {
                    family: "Arial"
                    pointSize: 9
                }

                wrapMode: Text.WordWrap
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Component {
        id: row

        Row {
            anchors.left: parent.left
            anchors.right: parent.right
            height: rowHeight
        }
    }

    Column {
        id: table

        anchors.fill: parent
    }
}
