import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtCharts 2.2

RectangleBorders {
    property url imageSource
    property int entryHeight: 300
    height: entryHeight
    color: "transparent"

    anchors {
        left: parent.left
        right: parent.right
    }

    property string chartTitle

    function addSlice(label, value, color) {
        var slice = pieSeries.append(label, value)
        slice.color = color
        slice.labelVisible = true
        slice.borderColor = root.darkGray
        slice.borderWidth = 2
    }

    function addTable(tableInfo) {
        table.addData(tableInfo)
    }

    function clearTable() {
        table.clearTable()
    }

    Row {
        anchors.fill: parent
        padding: 5

        Image {
            height: 60
            width: 60

            source: imageSource
        }

        StaticTable {
            id: table
            width: 600
            height: entryHeight
        }

        ChartView {
            width: 400
            height: entryHeight
            theme: ChartView.ChartThemeDark
            antialiasing: true
            animationOptions: ChartView.NoAnimation
            backgroundColor: root.darkDarkGray
            legend.visible: false

            title: chartTitle

            PieSeries {
                id: pieSeries
            }
        }
    }
}
