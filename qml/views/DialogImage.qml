import QtQuick 2.0

Item {
    property var src

    function calculateWidth(counter, parentWidth) {
        switch (src.length) {
        case 1:
            if (counter === 1) return parentWidth
            else return 0

        case 2:
            if (counter === 1 || counter === 2) return parentWidth / 2
            else return 0

        case 3:
            if (counter === 1 || counter === 2 || counter === 3) return parentWidth / 2
            else return 0

        default:
            return parentWidth / 2
        }
    }

    function calculateHeight(counter, parentHeight) {
        switch (src.length) {
        case 1:
            if (counter === 1) return parentHeight
            else return 0

        case 2:
            if (counter === 1 || counter === 2) return parentHeight
            else return 0

        case 3:
            if (counter === 1 || counter === 2 || counter === 3) return parentHeight / 2
            else return 0

        default:
            return parentHeight / 2
        }
    }

    Grid {
        anchors.fill: parent
        columns: 2
        rows: 2

        Image {
            width: calculateWidth(1, parent.width)
            height: calculateHeight(1, parent.height)
            source: src[0]
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 2 ? src[1] : ""
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 3 ? src[2] : ""
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 4 ? src[3] : ""
        }
    }
}
