import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Rectangle {


    ListView {
        z:parent + 2
        id: videoView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: statusBarConnect.top
        orientation: ListView.Vertical
        flickableDirection: Flickable.VerticalFlick
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
            ListElement {
                name: "Orange"
                colorCode: "orange"
            }

            ListElement {
                name: "White"
                colorCode: "white"
            }
            ListElement {
                name: "Black"
                colorCode: "black"
            }

            ListElement {
                name: "Teal"
                colorCode: "teal"
            }
        }
        highlightFollowsCurrentItem: true
        focus: true
        delegate: Rectangle {
            id: delItem
            width: parent.width
            border.color: "steelblue"
            border.width: 4
            color: "transparent"
            radius: parent.width/32
            clip: true
            anchors.margins: 4
            height: index == videoView.currentIndex ? parent.width * .25:parent.width * .125
            MouseArea
            {
                anchors.fill: parent
                onClicked: {
                    videoView.currentIndex = index;
                }
            }
            Row {
                id: row1
                width:parent.width
                height:parent.height
                anchors.margins: 4
                anchors.horizontalCenter: delItem.horizontalCenter
                Rectangle {
                    x: parent.width/3
                    id: itemRect
                    height:delItem.height
                    width: height
                    anchors.margins: 4
                    color: colorCode
                }

                Text {
                    anchors.verticalCenter: itemRect.verticalCenter
                    anchors.left: itemRect.right
                    text: name
                    font.bold: true
                    font.pixelSize: (delItem.width - itemRect.height) / (text.length+10)
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                spacing: 2
            }

        }
    }
    StatusBar{
        id:statusBarConnect
        height:80
        width:parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}
