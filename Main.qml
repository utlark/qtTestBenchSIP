import QtQuick
import QtQuick.Controls

import qtTestBenchSIP

ApplicationWindow {
    id: root
    width: viewModel.windowWidth
    height: viewModel.windowHeight
    visible: true
    color: "#303030"
    title: "Test bench - SIP"

    MainViewModel {
        id: viewModel
    }

    Rectangle {
        id: videoContainer
        width: viewModel.containerWidth
        height: viewModel.containerHeight
        color: "#202020"

        transform: [
            Rotation {
                angle: viewModel.flip ? 180 : 0
                origin.x: videoContainer.width / 2
                origin.y: videoContainer.height / 2
            }
        ]

        LayoutMirroring.enabled: viewModel.mirror
        LayoutMirroring.childrenInherit: viewModel.mirror

        anchors.horizontalCenter: parent.horizontalCenter

        states: [
            State {
                name: "top"
                when: viewModel.containerAlignment === "top"
                AnchorChanges {
                    target: videoContainer
                    anchors.top: root.contentItem.top
                }
            },
            State {
                name: "bottom"
                when: viewModel.containerAlignment === "bottom"
                AnchorChanges {
                    target: videoContainer
                    anchors.bottom: root.contentItem.bottom
                }
            },
            State {
                name: "center"
                when: viewModel.containerAlignment === "center"
                AnchorChanges {
                    target: videoContainer
                    anchors.verticalCenter: root.contentItem.verticalCenter
                }
            },
            State {
                name: "left"
                when: viewModel.containerAlignment === "left"
                AnchorChanges {
                    target: videoContainer
                    anchors.left: root.contentItem.left
                }
            },
            State {
                name: "right"
                when: viewModel.containerAlignment === "right"
                AnchorChanges {
                    target: videoContainer
                    anchors.right: root.contentItem.right
                }
            }
        ]

        Grid {
            id: videoGrid
            anchors.fill: parent
            columns: viewModel.gridCols
            rows: viewModel.gridRows

            Component.onCompleted: viewModel.populateVideoGrid(videoGrid)
        }
    }
}
