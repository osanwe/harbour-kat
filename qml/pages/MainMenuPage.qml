import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        anchors.fill: parent

        header: PageHeader { title: "Kat 0.1.4" }

        model: ListModel {
            ListElement {
                icon: "image://theme/icon-l-message"
                name: "Новости"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-redirect"
                name: "Ответы"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-email"
                name: "Сообщения"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-people"
                name: "Друзья"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-people"
                name: "Группы"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-image"
                name: "Фотографии"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-video"
                name: "Видеозаписи"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-music"
                name: "Аудиозаписи"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-favorite"
                name: "Закладки"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-document"
                name: "Документы"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-cover-search"
                name: "Поиск"
                counter: ""
            }
        }

        delegate: BackgroundItem {
            id: menuItem
            height: Theme.itemSizeSmall

            Item {
                anchors.fill: parent
                anchors.rightMargin: Theme.paddingLarge
                anchors.leftMargin: Theme.paddingLarge

                Image {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                    source: icon
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: name
                }

                Label {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: counter
                }
            }

            onClicked: {
                switch (index) {
                case 0:
                    break

                case 1:
                    break

                case 2:
                    pageStack.push(Qt.resolvedUrl("MessagesPage.qml"))
                    break;

                case 3:
                    break

                case 4:
                    break

                case 5:
                    break

                case 6:
                    break

                case 7:
                    break

                case 8:
                    break

                case 9:
                    break

                case 10:
                    break
                }
            }
        }
    }
}
