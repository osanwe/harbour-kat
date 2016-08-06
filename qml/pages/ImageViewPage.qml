import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: imageViewPage

    property var photoSource

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        contentWidth: window.width
        contentHeight: window.height
        clip: true

        PinchArea {

            property real initialWidth
            property real initialHeight

            width: Math.max(flick.contentWidth, flick.width)
            height: Math.max(flick.contentHeight, flick.height)

            Rectangle {
                width: flick.contentWidth
                height: flick.contentHeight
                color: "#00000000"

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: photoSource

                    MouseArea {
                        anchors.fill: parent

                        onDoubleClicked: {
                            flick.contentWidth = window.width
                            flick.contentHeight = window.height
                        }
                    }
                }
            }

            onPinchStarted: {
                initialWidth = flick.contentWidth
                initialHeight = flick.contentHeight
            }

            onPinchUpdated: {
                flick.contentX += pinch.previousCenter.x - pinch.center.x
                flick.contentY += pinch.previousCenter.y - pinch.center.y
                flick.resizeContent(Math.max(window.width, initialWidth * pinch.scale),
                                    Math.max(window.height, initialHeight * pinch.scale),
                                    pinch.center)
            }

            onPinchFinished: flick.returnToBounds()
        }
    }
}

