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

QT += multimedia

include("vksdk/vksdk.pri")

SOURCES += \
    src/harbour-kat.cpp \
    src/settingswrapper.cpp \
    src/mediaplayerwrapper.cpp \
    src/playlistmodel.cpp

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
    src/mediaplayerwrapper.h \
    src/playlistmodel.h

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
    qml/views/GeoItem.qml \
    qml/views/PhotosView.qml \
    qml/views/VideosView.qml \
    qml/views/AudiosView.qml \
    qml/views/DocumentsView.qml \
    qml/views/NewsView.qml \
    qml/pages/WallPostPage.qml \
    qml/views/WallPostView.qml \
    qml/views/RepostView.qml \
    qml/pages/NewsfeedPage.qml \
    qml/views/DialogImage.qml \
    qml/pages/AudioPlayerPage.qml \
    qml/pages/VideoPlayerPage.qml \
    qml/pages/AboutPage.qml

