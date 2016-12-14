import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    property int groupId
    property var stats: []

    function draw() {
        var context = graph.getContext("2d")
        context.clearRect(0, 0, graph.width, graph.height)
        context.lineWidth = 3

        context.strokeStyle = "gray"
        context.beginPath()
        context.moveTo(0, 0)
        context.lineTo(0, graph.height)
        context.lineTo(graph.width, graph.height)
        context.stroke()

        if (stats.length <= 1) return

        var maximum = stats[0]
        for (var index in stats) if (stats[index] > maximum) maximum = stats[index]
        var verticalStep = graph.height / maximum
        var horizontalStep = graph.width / (stats.length / 2 - 1)

        context.fillStyle = "gray"
        context.font = "12pt sans-serif"
        context.fillText(maximum, 10, 20)
        context.fillText("1", 10, graph.height - verticalStep)

        index = 0
        context.strokeStyle = "rgb(255, 0, 0)"
        context.beginPath()
        context.moveTo(0, graph.height - verticalStep * stats[index])
        while (index < stats.length-2) {
            index += 2
            context.lineTo(horizontalStep * (index / 2), graph.height - verticalStep * stats[index])
        }
        context.stroke()

        index = 0
        context.strokeStyle = "rgb(0, 0, 255)"
        context.beginPath()
        context.moveTo(0, graph.height - verticalStep * stats[index+1])
        while (index < stats.length-1) {
            index += 2
            context.lineTo(horizontalStep * (index / 2), graph.height - verticalStep * stats[index+1])
        }
        context.stroke()
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        Column {
            id: content
            width: parent.width

            PageHeader {
                title: qsTr("Statistics")
            }

            ValueButton {
                id: dateFromButton
                width: parent.width
                label: qsTr("Date from:")

                onClicked: {
                    var dialog = pageStack.push(datePicker, { date: new Date(dateFromButton.value) })
                    dialog.accepted.connect(function() {
                        var day = dialog.day
                        if (day < 10) day = "0" + day
                        var month = dialog.month
                        if (month < 10) month = "0" + day
                        var year = dialog.year
                        dateFromButton.value = year + "-" + month + "-" + day
                        vksdk.stats.get(groupId, dateFromButton.value, dateToButton.value)
                    })
                }
            }

            ValueButton {
                id: dateToButton
                width: parent.width
                label: qsTr("Date to:")

                onClicked: {
                    var dialog = pageStack.push(datePicker, { date: new Date(dateToButton.value) })
                    dialog.accepted.connect(function() {
                        var day = dialog.day
                        if (day < 10) day = "0" + day
                        var month = dialog.month
                        if (month < 10) month = "0" + day
                        var year = dialog.year
                        dateToButton.value = year + "-" + month + "-" + day
                        vksdk.stats.get(groupId, dateFromButton.value, dateToButton.value)
                    })
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            Canvas {
                id: graph
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.rightMargin: Theme.horizontalPageMargin
                height: width / 3 * 2
                onPaint: draw()
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingLarge

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.paddingLarge
                    height: Theme.paddingLarge
                    color: "#F00"
                }

                Label {
                    text: qsTr("Total views")
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingLarge

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.paddingLarge
                    height: Theme.paddingLarge
                    color: "#00F"
                }

                Label {
                    text: qsTr("Uniqual visitors")
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Component {
        id: datePicker
        DatePickerDialog {}
    }

    Connections {
        target: vksdk
        onGotStats: {
            stats = data
            graph.requestPaint()
        }
    }

    Component.onCompleted: {
        var date = new Date()
        var day = date.getDate()
        if (day < 10) day = "0" + day
        var month = date.getMonth() + 1
        if (month < 10) month = "0" + day
        var year = date.getFullYear()
        var currentDate = year + "-" + month + "-" + day
        dateFromButton.value = currentDate
        dateToButton.value = currentDate
        vksdk.stats.get(groupId, currentDate, currentDate)
    }
}

