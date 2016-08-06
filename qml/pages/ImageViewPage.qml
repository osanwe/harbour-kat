import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: imageViewPage

    property var photoSource

    Image {
        id: imageView
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: photoSource
    }

    PinchArea {
        anchors.fill: parent
        pinch {
            target: imageView
            minimumScale: 1
            maximumScale: 4
            dragAxis: Pinch.XAndYAxis
        }
    }
}

