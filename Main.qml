import QtQuick
import QtMultimedia
import QtQuick.Controls

ApplicationWindow {
    id: root
    width: windowWidth
    height: windowHeight
    visible: true
    color: "#303030"
    title: qsTr("Test bench - SIP")

    Item {
        id: videoContainer
        width: containerWidth
        height: containerHeight

        transform: [
            Rotation {
                angle: flip ? 180 : 0
                origin.x: width / 2
                origin.y: height / 2
            },
            Scale {
                xScale: mirror ? -1 : 1
            }
        ]

        anchors.horizontalCenter: parent.horizontalCenter

        anchors.top: if (containerAlignment === "top")
            parent.top
        anchors.bottom: if (containerAlignment === "bottom")
            parent.bottom
        anchors.verticalCenter: if (containerAlignment === "center")
            parent.verticalCenter
        anchors.left: if (containerAlignment === "left")
            parent.left
        anchors.right: if (containerAlignment === "right")
            parent.right

        Grid {
            id: videoGrid
            anchors.fill: parent
            columns: gridCols
            rows: gridRows

            Repeater {
                model: videoSources
                delegate: Video {
                    width: videoContainer.width / gridCols
                    height: videoContainer.height / gridRows
                    source: modelData
                    autoPlay: true
                    fillMode: VideoOutput.PreserveAspectCrop
                }
            }
        }
    }
}
