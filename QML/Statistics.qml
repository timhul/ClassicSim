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

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "DISTRIBUTIONS"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Distributions"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "DAMAGE_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Damage Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "THREAT_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Threat Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "BUFF_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Buff Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "PROC_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Proc Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "RESOURCE_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Resource Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "ROTATION_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Rotation Breakdown"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }

        GradientSelectedButton {
            height: 30
            width: 150
            property string activeState: "ENGINE_BREAKDOWN"
            selected: statisticsRect.state === activeState

            TextSmall {
                text: "Internal Engine"
                color: statisticsRect.state === parent.activeState ? "black" : "white"
            }

            onSelectButtonClicked: statisticsRect.state = activeState
            onSelectButtonRightClicked: statisticsRect.state = activeState

            gradientSelectedFrom: "#42d4f4"
            gradientSelectedTo: "#37b3ce"
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "DISTRIBUTIONS"

        StatisticsHeader {
            id: headerDistribution
            title: "DPS Distribution"
        }

        Row {
            id: dpsDistributionDesc

            height: 30
            width: parent.width

            anchors.top: headerDistribution.bottom

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: "Min DPS"
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: "Max DPS"
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: "Standard Deviation"
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: "± (95% CI)"
                }
            }
        }

        Row {
            id: dpsDistribution
            height: 30
            width: parent.width

            anchors.top: dpsDistributionDesc.bottom

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: settings.minDps
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: settings.maxDps
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: settings.dpsStdDev
                }
            }

            RectangleBorders {
                height: parent.height
                width: 150

                TextSmall {
                    text: settings.dpsConfInterval
                }
            }
        }

        StatisticsHeader {
            id: dpsStatWeightHeader
            title: "DPS Stat Weights"

            anchors.top: dpsDistribution.bottom
            anchors.topMargin: 20
        }

        StatisticsScaleResultSorting {
            id: dpsScaleResultSorting
            anchors.top: dpsStatWeightHeader.bottom
            scaleResultModel: dpsScaleResultModel
        }

        ListView {
            id: dpsScaleResultTable
            anchors {
                top: dpsScaleResultSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: dpsScaleResultModel
            delegate: StatisticsEntryScaleResult {
                name: _name
                absvalue: _absvalue
                relvalue: _relvalue
                standarddev: _standarddev
                confidenceinterval: _confidenceinterval
            }
        }

        StatisticsHeader {
            id: tpsStatWeightHeader
            title: "TPS Stat Weights"

            anchors.top: dpsScaleResultTable.bottom
            anchors.topMargin: 20
        }

        StatisticsScaleResultSorting {
            id: tpsScaleResultSorting
            anchors.top: tpsStatWeightHeader.bottom
            scaleResultModel: tpsScaleResultModel
        }

        ListView {
            id: tpsScaleResultTable
            anchors {
                top: tpsScaleResultSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: tpsScaleResultModel
            delegate: StatisticsEntryScaleResult {
                name: _name
                absvalue: _absvalue
                relvalue: _relvalue
                standarddev: _standarddev
                confidenceinterval: _confidenceinterval
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "DAMAGE_BREAKDOWN"

        StatisticsHeader {
            id: headerMeleeDmgBreakdown
            title: "Ability Damage Breakdown"
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

        StatisticsHeader {
            id: headerOutcomes
            title: "Ability Outcomes"

            anchors.top: damageBreakdownTable.bottom
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
                numpartial25: _numpartial25
                partial25percent: _partial25percent
                numpartial50: _numpartial50
                partial50percent: _partial50percent
                numpartial75: _numpartial75
                partial75percent: _partial75percent
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "THREAT_BREAKDOWN"

        StatisticsHeader {
            id: headerThreatBreakdown
            title: "Ability Threat Breakdown"
        }

        StatisticsThreatBreakdownSorting {
            id: threatBreakdownSorting
            anchors {
                top: headerThreatBreakdown.bottom
                left: parent.left
                right: parent.right
            }
        }

        ListView {
            id: threatBreakdownTable
            anchors {
                top: threatBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: threatBreakdownModel
            delegate: StatisticsEntryThreatBreakdown {
                name: _name
                iconurl: _icon
                totalthrtabsolute: _totalthrtabsolute
                totalthrtpercentage: _totalthrtpercent
                minhitthrt: _minhitthrt
                avghitthrt: _avghitthrt
                maxhitthrt: _maxhitthrt
                mincritthrt: _mincritthrt
                avgcritthrt: _avgcritthrt
                maxcritthrt: _maxcritthrt
                minglancethrt: _minglancethrt
                avgglancethrt: _avgglancethrt
                maxglancethrt: _maxglancethrt
                mintpr: _mintpr
                avgtpr: _avgtpr
                maxtpr: _maxtpr
                mintpet: _mintpet
                avgtpet: _avgtpet
                maxtpet: _maxtpet
            }
        }

        // StatisticsHeader {
        //     id: headerOutcomes
        //     title: "Ability Outcomes"

        //     anchors.top: threatBreakdownTable.bottom
        // }

        // StatisticsThreatAvoidanceBreakdownSorting {
        //     id: damageBreakdownSorting
        //     anchors.top: headerOutcomes.bottom
        // }

        // ListView {
        //     id: damageAvoidanceBreakdownTable
        //     anchors {
        //         top: damageBreakdownSorting.bottom
        //         left: parent.left
        //         right: parent.right
        //     }

        //     boundsBehavior: Flickable.StopAtBounds

        //     implicitHeight: contentHeight

        //     model: meleeAvoidanceBreakdownModel
        //     delegate: StatisticsEntryMeleeDamageAvoidanceBreakdown {
        //         name: _name
        //         iconurl: _icon
        //         totalattempts: _totalattempts
        //         numhits: _numhits
        //         hitpercent: _hitpercent
        //         numcrits: _numcrits
        //         critpercent: _critpercent
        //         numglances: _numglances
        //         glancepercent: _glancepercent
        //         nummisses: _nummisses
        //         misspercent: _misspercent
        //         numdodges: _numdodges
        //         dodgepercent: _dodgepercent
        //         numparries: _numparries
        //         parrypercent: _parrypercent
        //         numpartial25: _numpartial25
        //         partial25percent: _partial25percent
        //         numpartial50: _numpartial50
        //         partial50percent: _partial50percent
        //         numpartial75: _numpartial75
        //         partial75percent: _partial75percent
        //     }
        // }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
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

        StatisticsHeader {
            id: headerDebuffUptimes
            title: "Debuff Uptimes"
            anchors.top: buffBreakdownTable.bottom
        }

        StatisticsBuffBreakdownSorting {
            id: debuffBreakdownSorting
            anchors.top: headerDebuffUptimes.bottom
        }

        ListView {
            id: debuffBreakdownTable
            anchors {
                top: debuffBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: debuffBreakdownModel
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
            leftMargin: 30
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
                effectiveppm: _effectiveppm
                numprocs: _numprocs
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
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

    ScrollView {
        id: rotationScrollView
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
            bottom: parent.bottom
        }
        width: 200

        clip: true

        visible: parent.state === "ROTATION_BREAKDOWN"

        StatisticsHeader {
            id: headerRotation
            title: "Rotation information"
        }

        ListView {
            id: rotationList
            anchors {
                top: headerRotation.bottom
                topMargin: 10
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: rotationExecutorListModel
            delegate: StatisticsEntryExecutorList {
                name: _name
                selected: _selected
                index: _index
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: rotationScrollView.right
            leftMargin: 30
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "ROTATION_BREAKDOWN"

        StatisticsHeader {
            id: headerRotationExecutor
            title: "Executor Breakdown"
        }

        StatisticsExecutorBreakdownSorting {
            id: executorBreakdownSorting
            anchors.top: headerRotationExecutor.bottom
            anchors.topMargin: 10
        }

        ListView {
            id: rotationExecutorTable
            anchors {
                top: executorBreakdownSorting.bottom
                topMargin: 10
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: rotationExecutorBreakdownModel
            delegate: StatisticsEntryExecutorBreakdown {
                executor: _executor
                spellstatus: _spellstatus
                value: _value
            }
        }
    }

    ScrollView {
        anchors {
            top: changeStatistics.bottom
            left: parent.left
            leftMargin: 30
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        visible: parent.state === "ENGINE_BREAKDOWN"

        StatisticsHeader {
            id: headerEngine
            title: "Engine information"
        }

        TextSmall {
            id: eventsHandledPerSecondText
            anchorParent: false
            pointSize: 15

            anchors {
                top: headerEngine.bottom
                topMargin: 15
                left: parent.left
            }

            text: statistics.engineHandledEventsPerSecond + " events handled / second"
        }

        StatisticsEngineBreakdownSorting {
            id: engineBreakdownSorting
            anchors.top: eventsHandledPerSecondText.bottom
            anchors.topMargin: 10
        }

        ListView {
            id: engineBreakdownTable
            anchors {
                top: engineBreakdownSorting.bottom
                left: parent.left
                right: parent.right
            }

            boundsBehavior: Flickable.StopAtBounds

            implicitHeight: contentHeight

            model: engineBreakdownModel
            delegate: StatisticsEntryEngineBreakdown {
                event: _event
                percentage: _percentage
                total: _total
                permin: _permin
            }
        }
    }
}
