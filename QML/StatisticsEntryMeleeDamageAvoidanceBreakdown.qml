import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property url iconurl
    property string name
    property string totaldmgabsolute
    property string totaldmgpercentage
    property string totalattempts
    property string numhits
    property string hitpercent
    property string numcrits
    property string critpercent
    property string numglances
    property string glancepercent
    property string nummisses
    property string misspercent
    property string numdodges
    property string dodgepercent
    property string numparries
    property string parrypercent

    Row {
        anchors.fill: parent

        property int attemptsWidth: 80
        property int percentageWidth: 70

        RectangleBorders {
            height: parent.height
            width: height

            Image {
                height: parent.height - 6
                width: height
                x: 3
                y: 3

                source: iconurl
            }
        }

        RectangleBorders {
            height: parent.height
            width: 200

            TextSmall {
                text: name
                anchors.leftMargin: 10

                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: totalattempts
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: numhits
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: hitpercent
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: numcrits
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: critpercent
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: numglances
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: glancepercent
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: nummisses
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: misspercent
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: numdodges
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: dodgepercent
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.attemptsWidth

            TextSmall {
                text: numparries
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.percentageWidth

            TextSmall {
                text: parrypercent
            }
        }
    }
}
