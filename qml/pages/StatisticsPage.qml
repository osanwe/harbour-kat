import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    property int groupId

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        Column {
            id: content
            width: parent.width

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
        }

        VerticalScrollDecorator {}
    }

    Component {
        id: datePicker
        DatePickerDialog {}
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

