import QtQuick 2.0

Rectangle {
    width: 600
    height: 30

    color: "transparent"

    property url iconurl
    property string name
    property string totalthrtabsolute
    property string totalthrtpercentage
    property string minhitthrt
    property string avghitthrt
    property string maxhitthrt
    property string mincritthrt
    property string avgcritthrt
    property string maxcritthrt
    property string minglancethrt
    property string avgglancethrt
    property string maxglancethrt
    property string mintpr
    property string avgtpr
    property string maxtpr
    property string mintpet
    property string avgtpet
    property string maxtpet

    Row {
        anchors.fill: parent

        property int threatWidth: 80

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
            width: 120

            TextSmall {
                text: totalthrtabsolute
            }
        }

        RectangleBorders {
            height: parent.height
            width: 70

            TextSmall {
                text: totalthrtpercentage
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: minhitthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: avghitthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: maxhitthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: mincritthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: avgcritthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: maxcritthrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: minglancethrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: avgglancethrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: maxglancethrt
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: mintpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: avgtpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: maxtpr
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: mintpet
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: avgtpet
            }
        }

        RectangleBorders {
            height: parent.height
            width: parent.threatWidth

            TextSmall {
                text: maxtpet
            }
        }
    }
}
