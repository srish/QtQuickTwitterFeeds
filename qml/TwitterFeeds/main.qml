// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 540

    Rectangle {
        id: twitterHandle
        color: "purple"
        width: parent.width
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: user
            text: "@paraskuhad"
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 10
            color: "white"
            font.pixelSize: 24
        }
    }

    ListView {
        id: listView
        height: parent.height
        width: parent.width
        anchors.top: twitterHandle.bottom
        model: xmlModel

        delegate: Rectangle {
            id: tweetBox
            width: parent.width
            height: 60
            border.width: 1
            border.color: "gray"

            Text {
                id: tweet
                anchors.left: tweetBox.left
                anchors.leftMargin: 10
                anchors.right: tweetBox.right
                anchors.rightMargin: 10
                anchors.verticalCenter: tweetBox.verticalCenter
                text: statusText
                font.pixelSize: 16
                color: "black"
                wrapMode: Text.WordWrap
                width: parent.width
                clip: true
            }
        }
    }

    Timer {
        id: timer
        interval: 2000
        onTriggered: {
            xmlParser.parseTweets("paraskuhad")
        }
    }

    Component.onCompleted: timer.start()

    XmlListModel {
        id: xmlModel
        source: "http://api.twitter.com/1/statuses/user_timeline.xml?screen_name=paraskuhad"
        query: "/statuses/status"
        XmlRole { name: "statusText"; query: "text/string()" }
    }
}

