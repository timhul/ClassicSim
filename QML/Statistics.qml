import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Controls 2.2

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

    ObjectModel {
        id: objectModel
    }

    Rectangle {
        id: tmpStorage
        visible: false
    }

    function updateStatistics() {
        for (var i = 0; i < statistics.getNumStatisticsRows(); ++i) {
            var entry = root.createNewObject(tmpStorage, "StatisticEntry.qml")
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

            objectModel.append(entry)
        }
    }

    function clearStatistics() {
        for (var i = objectModel.count; i > 0; --i) {
            objectModel.get(i - 1).clearTable()
            //tmpStorage.children[i - 1].destroy()
        }
        objectModel.clear()
    }

    function createPieChart(chartInfo, entry) {
        entry.chartTitle = chartInfo[0]

        var i = 2
        for (; i + 2 < chartInfo.length;) {
            entry.addSlice(chartInfo[i], chartInfo[i + 1], chartInfo[i + 2])
            i += 3
        }
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            clip: true
            model: objectModel
            boundsBehavior: Flickable.StopAtBounds
        }
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
