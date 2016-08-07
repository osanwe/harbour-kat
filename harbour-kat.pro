# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-kat

CONFIG += sailfishapp
greaterThan(QT_VERSION, 5.5) {
    CONFIG += C++11
} else {
    QMAKE_CXXFLAGS += -std=gnu++11
}

SOURCES += \
    src/harbour-kat.cpp \
    src/settingswrapper.cpp \
    src/vk/authorization.cpp \
    src/vk/vksdk.cpp \
    src/vk/apirequest.cpp \
    src/vk/messages.cpp \
    src/vk/longpoll.cpp \
    src/vk/objects/message.cpp \
    src/vk/objects/dialog.cpp \
    src/vk/users.cpp \
    src/vk/objects/chat.cpp \
    src/vk/objects/user.cpp \
    src/vk/friends.cpp \
    src/vk/objects/friend.cpp

OTHER_FILES += \
    qml/harbour-kat.qml \
    qml/cover/*.qml \
    qml/pages/*.qml \
    qml/views/*.qml \
    translations/*.ts \
    rpm/harbour-kat.yaml \
    rpm/harbour-kat.spec \
    rpm/harbour-kat.changes.in \
    LICENSE \
    README.md

#CONFIG += sailfishapp_i18n
#TRANSLATIONS += \
#    translations/harbour-kat-en.ts

HEADERS += \
    src/settingswrapper.h \
    src/vk/authorization.h \
    src/vk/vksdk.h \
    src/vk/apirequest.h \
    src/vk/messages.h \
    src/vk/longpoll.h \
    src/vk/objects/message.h \
    src/vk/objects/dialog.h \
    src/vk/users.h \
    src/vk/objects/chat.h \
    src/vk/objects/user.h \
    src/vk/friends.h \
    src/vk/objects/friend.h

DISTFILES += \
    qml/pages/MainMenuPage.qml \
    qml/pages/LoginPage.qml \
    qml/pages/DialogsListPage.qml \
    qml/pages/ProfilePage.qml \
    qml/pages/ImageViewPage.qml \
    qml/pages/FriendsListPage.qml \
    qml/views/UserListItem.qml \
    qml/pages/DialogPage.qml \
    qml/views/MessageItem.qml \
    qml/views/FwdMessages.qml \
    qml/views/AttachmentsView.qml \
    qml/views/GeoItem.qml
