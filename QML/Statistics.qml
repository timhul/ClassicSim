import QtQuick 2.0

Rectangle {
    id: statisticsRect
    anchors.fill: parent

    color: "transparent"

    Component.onCompleted: updateStatistics()

    Connections {
        target: statistics
        onStatisticsCleared: clearStatistics()
        onStatisticsReady: updateStatistics()
    }

    function updateStatistics() {
        if (statisticsColumn.children.length !== 0) {
            console.log("children non-zero, will fail to update chart, delaying update")
            timer.start()
            return
        }

        for (var i = 0; i < statistics.getNumStatisticsRows(); ++i) {
            var component = Qt.createComponent("StatisticEntry.qml")
            if (component.status !== Component.Ready) {
                console.log("Created component not ready!", component.errorString())
                continue
            }
            var entry = component.createObject(statisticsColumn)
            entry.imageSource = statistics.getEntryIcon(i)

            var tableInfo = statistics.getTableInfo(i)
            entry.addTable(tableInfo)

            var chartInfo = statistics.getChartInfo(i)
            if (chartInfo.length < 2)
                console.log("Malformed chart info", chartInfo)
            else if (chartInfo[1] === "PIE")
                createPieChart(chartInfo, entry)
            else
                console.log("Unhandled chart type", chartInfo[1])
        }
    }

    function clearStatistics() {
        for (var i = statisticsColumn.children.length; i > 0; --i) {
            statisticsColumn.children[i - 1].clearTable()
            statisticsColumn.children[i - 1].destroy()
        }
    }

    function createPieChart(chartInfo, entry) {
        entry.chartTitle = chartInfo[0]

        var i = 2
        for (; i + 2 < chartInfo.length;) {
            entry.addSlice(chartInfo[i], chartInfo[i + 1], chartInfo[i + 2])
            i += 3
        }
    }

    Timer {
        id: timer
        interval: 500
        running: false
        repeat: false
        onTriggered: updateStatistics()
    }

    Column {
        id: statisticsColumn

        anchors.fill: parent
    }

//    ChartView {
//        width: 400
//        height: 300
//        theme: ChartView.ChartThemeDark
//        antialiasing: true
//        animationOptions: ChartView.NoAnimation
//        backgroundColor: root.darkDarkGray
//        title: "Heroic Strike"

//        PieSeries {
//            id: pieSeries

//            function updateSlices() {
//                pieSeries.clear()
//                var slices = pieChart.getSlices()

//                console.log(slices)

//                var i = 0
//                for (; i < slices.length;) {
//                    pieSeries.append(slices[i], slices[i + 1])
//                    console.log(slices[i], slices[i + 1])
//                    i += 2
//                }
//            }


//            Component.onCompleted: updateSlices()
//        }

//        PieSeries {
//            id: pieSeries

//            VPieModelMapper {
//                model: pieChartModel
//                labelsColumn: 0
//                valuesColumn: 1
//            }
//        }
//    }
}
