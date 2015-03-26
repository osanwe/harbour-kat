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

SOURCES += \
    src/harbour-kat.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    translations/*.ts \
    qml/pages/LoginPage.qml \
    qml/auth.js \
    qml/storage.js \
    src/js/auth.js \
    js/auth.js \
    js/storage.js \
    js/api/messages.js \
    qml/js/auth.js \
    qml/js/storage.js \
    qml/js/api/messages.js \
    qml/js/api/users.js \
    qml/pages/MessagesPage.qml \
    qml/pages/DialogPage.qml \
    qml/views/MessageItem.qml \
    qml/pages/AboutPage.qml \
    qml/pages/NewMessagePage.qml \
    LICENSE \
    README.md \
    .gitignore \
    qml/harbour-kat.qml \
    harbour-kat.desktop \
    rpm/harbour-kat.yaml \
    rpm/harbour-kat.spec \
    rpm/harbour-kat.changes.in \
    qml/pages/ChatUsersPage.qml \
    qml/views/UserItem.qml

# to disable building translations every time, comment out the
# following CONFIG line
#CONFIG += sailfishapp_i18n
#TRANSLATIONS += translations/vkFish-de.ts

HEADERS +=

