import QtQuick 2.0
import QtCharts 2.2

Rectangle {
    anchors.fill: parent

    color: "transparent"

    ChartView {
        width: 400
        height: 300
        theme: ChartView.ChartThemeDark
        antialiasing: true
        animationOptions: ChartView.NoAnimation
        backgroundColor: root.darkDarkGray
        title: "Heroic Strike"

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

        PieSeries {
            id: pieSeries

            VPieModelMapper {
                model: pieChartModel
                labelsColumn: 0
                valuesColumn: 1
            }
        }
    }
}
