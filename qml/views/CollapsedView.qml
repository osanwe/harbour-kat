/*
  Copyright (C) 2016 Petr Vytovtov
                The element is based on from Jolla Store client.
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: detailsBackground

    property var bdate: ""
    property var relation: ""
    property var relationPartnerId: ""
    property var relationPartnerName: ""
    property var occupationId: ""
    property var occupationType: ""
    property var occupationName: ""

    property var sex: ""
    property var city: ""
    property var country: ""
    property var homeTown: ""
    property var mobilePhone: ""
    property var homePhone: ""
    property var site: ""

    property var description: ""

    property int horizontalMargin: Theme.horizontalPageMargin

    property real _ellipsisDisplacement: detailsBox.opened ? 0 : Theme.paddingLarge
    Behavior on _ellipsisDisplacement {
        NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
    }

    width: parent.width
    height: detailsBox.height + detailsBox.y + Theme.paddingMedium + _ellipsisDisplacement
    highlighted: down && !highlightDelayTimer.running
    _showPress: highlighted

    onPressedChanged: {
        if (pressed) {
            highlightDelayTimer.restart()
        }
    }

    Timer {
        id: highlightDelayTimer
        interval: 50
    }

    Item {
        id: detailsBox

        property bool opened: false

        y: Theme.paddingMedium
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: horizontalMargin
            rightMargin: horizontalMargin
        }
        clip: true

        height: opened
                ? expandedDetails.height
                : descriptionLabel.visible ? (3 * Theme.fontSizeMedium)
                                           : (birthdayInfo.height + relationshipInfo.height + occupationInfo.height)

        Behavior on height {
            NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
        }

        Column {
            id: expandedDetails

            width: parent.width
            anchors.top: lblSummary.bottom

            Label {
                id: descriptionLabel
                width: parent.width
                visible: description !== ""
                wrapMode: Text.WordWrap
                text: description
            }

            Row {
                id: birthdayInfo
                width: parent.width
                spacing: Theme.paddingSmall
                visible: bdate !== ""

                Label {
                    font.bold: true
                    text: qsTr("Birthday:")
                }

                Label {
                    text: bdate
                }
            }

            Row {
                id: relationshipInfo
                width: parent.width
                spacing: Theme.paddingSmall
                visible: relation !== 0

                Label {
                    font.bold: true
                    text: switch (relation) {
                          case 1:
                              return qsTr("Single")

                          case 2:
                              return qsTr("In a relationship")

                          case 3:
                              return qsTr("Engaged")

                          case 4:
                              return qsTr("Married")

                          case 5:
                              return qsTr("It's complicated")

                          case 6:
                              return qsTr("Actively searching")

                          case 7:
                              return qsTr("In love")
                          }
                }

                Label {
                    font.underline: true
                    color: Theme.highlightColor
                    text: relationPartnerName

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            pageContainer.replace(Qt.resolvedUrl("../pages/ProfilePage.qml"),
                                                  { profileId: relationPartnerId } )
                        }
                    }
                }
            }

            Row {
                id: occupationInfo
                width: parent.width
                visible: occupationName !== ""

                Label {
                    width: parent.width
                    text: occupationName
                    truncationMode: TruncationMode.Fade
                }
            }

            // --------------

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: sex !== 0 && sex !== ""

                Label {
                    font.bold: true
                    text: qsTr("Gender:")
                }

                Label {
                    text: sex === 1 ? qsTr("Female") : qsTr("Male")
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: city !== ""

                Label {
                    font.bold: true
                    text: qsTr("City:")
                }

                Label {
                    text: city
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: country !== ""

                Label {
                    font.bold: true
                    text: qsTr("Country:")
                }

                Label {
                    text: country
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: homeTown !== ""

                Label {
                    font.bold: true
                    text: qsTr("Home town:")
                }

                Label {
                    text: homeTown
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: mobilePhone !== ""

                Label {
                    font.bold: true
                    text: qsTr("Mobile phone:")
                }

                Label {
                    text: mobilePhone
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: homePhone !== ""

                Label {
                    font.bold: true
                    text: qsTr("Home phone:")
                }

                Label {
                    text: homePhone
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: site !== ""

                Label {
                    font.bold: true
                    text: qsTr("Site:")
                }

                Label {
                    text: site
                }
            }
        }

    }

    Item {
        x: detailsBox.x
        y: detailsBox.y
        OpacityRampEffect {
            sourceItem: detailsBox
            enabled: !detailsBox.opened
            direction: OpacityRamp.TopToBottom
            slope: 1.6
            offset: 4 / 7
            width: detailsBox.width
            height: detailsBox.height
            anchors.fill: null
        }
    }

    Image {
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: horizontalMargin
        }
        source: "image://theme/icon-lock-more"
    }

    onClicked: {
        detailsBox.opened = !detailsBox.opened
    }
}
