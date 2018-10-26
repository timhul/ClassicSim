import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Controls 2.2

Rectangle {
    id: statisticsRect
    anchors.fill: parent

    color: "transparent"

    state: "DAMAGE_BREAKDOWN"

    Row {
        id: changeStatistics
        height: 30

        anchors {
            top: parent.top
            topMargin: 15
            left: parent.left
            leftMargin: 30
            right: parent.right
        }

        spacing: 5

        RectangleBorders {
            height: 30
            width: 150
            property string activeState: "DAMAGE_BREAKDOWN"

            TextSmall {
                text: "Damage Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onRectangleClicked: statisticsRect.state = activeState
            onRectangleRightClicked: statisticsRect.state = activeState

            rectColor: statisticsRect.state === activeState ? "#42d4f4" : root.darkDarkGray
        }

        RectangleBorders {
            height: 30
            width: 150
            property string activeState: "BUFF_BREAKDOWN"

            TextSmall {
                text: "Buff Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onRectangleClicked: statisticsRect.state = activeState
            onRectangleRightClicked: statisticsRect.state = activeState

            rectColor: statisticsRect.state === activeState ? "#42d4f4" : root.darkDarkGray
        }

        RectangleBorders {
            height: 30
            width: 150
            property string activeState: "PROC_BREAKDOWN"

            TextSmall {
                text: "Proc Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onRectangleClicked: statisticsRect.state = activeState
            onRectangleRightClicked: statisticsRect.state = activeState

            rectColor: statisticsRect.state === activeState ? "#42d4f4" : root.darkDarkGray
        }

        RectangleBorders {
            height: 30
            width: 150
            property string activeState: "RESOURCE_BREAKDOWN"

            TextSmall {
                text: "Resource Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onRectangleClicked: statisticsRect.state = activeState
            onRectangleRightClicked: statisticsRect.state = activeState

            rectColor: statisticsRect.state === activeState ? "#42d4f4" : root.darkDarkGray
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "DAMAGE_BREAKDOWN"

        StatisticsHeader {
            id: headerOutcomes
            title: "Ability Outcomes"
        }

        StatisticsMeleeDamageAvoidanceBreakdownSorting {
            id: damageBreakdownSorting
            anchors.top: headerOutcomes.bottom
        }

        ListView {
            id: damageAvoidanceBreakdownTable
            anchors {
                top: damageBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: meleeAvoidanceBreakdownModel
            delegate: StatisticsEntryMeleeDamageAvoidanceBreakdown {
                name: _name
                iconurl: _icon
                totalattempts: _totalattempts
                numhits: _numhits
                hitpercent: _hitpercent
                numcrits: _numcrits
                critpercent: _critpercent
                numglances: _numglances
                glancepercent: _glancepercent
                nummisses: _nummisses
                misspercent: _misspercent
                numdodges: _numdodges
                dodgepercent: _dodgepercent
                numparries: _numparries
                parrypercent: _parrypercent
            }
        }

        StatisticsHeader {
            id: headerMeleeDmgBreakdown
            title: "Ability Damage Breakdown"

            anchors.top: damageAvoidanceBreakdownTable.bottom
        }

        StatisticsMeleeDamageBreakdownSorting {
            id: meleeDamageBreakdownSorting
            anchors {
                top: headerMeleeDmgBreakdown.bottom
                left: parent.left
                right: parent.right
            }
        }

        ListView {
            id: damageBreakdownTable
            anchors {
                top: meleeDamageBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: meleeDamageBreakdownModel
            delegate: StatisticsEntryMeleeDamageBreakdown {
                name: _name
                iconurl: _icon
                totaldmgabsolute: _totaldmgabsolute
                totaldmgpercentage: _totaldmgpercent
                minhit: _minhit
                avghit: _avghit
                maxhit: _maxhit
                mincrit: _mincrit
                avgcrit: _avgcrit
                maxcrit: _maxcrit
                minglance: _minglance
                avgglance: _avgglance
                maxglance: _maxglance
                mindpr: _mindpr
                avgdpr: _avgdpr
                maxdpr: _maxdpr
                mindpet: _mindpet
                avgdpet: _avgdpet
                maxdpet: _maxdpet
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "BUFF_BREAKDOWN"

        StatisticsHeader {
            id: headerBuffUptimes
            title: "Buff Uptimes"
        }

        StatisticsBuffBreakdownSorting {
            id: buffBreakdownSorting
            anchors.top: headerBuffUptimes.bottom
        }

        ListView {
            id: buffBreakdownTable
            anchors {
                top: buffBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: buffBreakdownModel
            delegate: StatisticsEntryBuffBreakdown {
                name: _name
                iconurl: _icon
                avguptime: _avguptime
                minuptime: _minuptime
                maxuptime: _maxuptime
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "PROC_BREAKDOWN"

        StatisticsHeader {
            id: headerProc
            title: "Proc information"
        }

        StatisticsProcBreakdownSorting {
            id: procBreakdownSorting
            anchors.top: headerProc.bottom
        }

        ListView {
            id: procBreakdownTable
            anchors {
                top: procBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: procBreakdownModel
            delegate: StatisticsEntryProcBreakdown {
                name: _name
                iconurl: _icon
                avgprocrate: _avgprocrate
                numprocs: _numprocs
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "RESOURCE_BREAKDOWN"

        StatisticsHeader {
            id: headerResource
            title: "Resource information"
        }

        StatisticsResourceBreakdownSorting {
            id: resourceBreakdownSorting
            anchors.top: headerResource.bottom
        }

        ListView {
            id: resourceBreakdownTable
            anchors {
                top: resourceBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: resourceBreakdownModel
            delegate: StatisticsEntryResourceBreakdown {
                name: _name
                iconurl: _icon
                mp5: _mp5
                rp5: _rp5
                ep5: _ep5
            }
        }
    }

    /*
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
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ListView {
            clip: true
            model: objectModel
            boundsBehavior: Flickable.StopAtBounds
        }
    }*/
}
