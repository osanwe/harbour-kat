/*
  Copyright (C) 2015 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of vkFish.

  vkFish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Foobar is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0
import "../js/auth.js" as AuthJS
import "../js/storage.js" as StorageJS


Dialog {
    id: loginPage

    function checkUrl(url) {
        if (AuthJS.checkUrl(url) !== 1) {
            console.log(AuthJS.accessToken)
            StorageJS.storeSettingsValue("access_token", AuthJS.accessToken)
            StorageJS.storeSettingsValue("user_id", AuthJS.userId)
            loginView.stop()
            loginPage.close()
        }
    }

    SilicaWebView {
        id: loginView
        anchors.fill: parent
        url: "https://oauth.vk.com/authorize?" +
             "client_id=4803503" +
             "&scope=messages,offline" +
             "&redirect_uri=https://oauth.vk.com/blank.html" +
             "&display=mobile" +
             "&response_type=token"

        onUrlChanged: checkUrl(url)
    }
}





