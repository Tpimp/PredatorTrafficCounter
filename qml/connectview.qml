import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Rectangle {
    color: "#3d3d3e"
    property bool connectedToCopter: false
    Text{
        id:titleText
        anchors.bottom: inputRect.top
        anchors.horizontalCenter: inputRect.horizontalCenter
        anchors.bottomMargin: 4
        anchors.topMargin:  20
        color: "white"
        font.pixelSize: 36
        visible: !connectedToCopter
        text: "Please Connect to a Predator QuadCopter..."
    }

    Image
    {
        id: droneImage
        width: parent.width * .40
        height: width * .8
        smooth: true
        visible: !connectedToCopter
        x:15
        y:-80
        //anchors.margins: -10
        //anchors.topMargin: -80
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/predatordrone.png"
    }
    Rectangle
    {
        id:inputRect
        anchors.top: droneImage.bottom
        anchors.left: parent.left
        width: parent.width * .45
        height: parent.height/12
        radius: 10
        color: white
        border.color: "yellow"
        border.width: 2
        clip: true
        anchors.topMargin: -40
        TextInput{
            id: ipString
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignBottom
            font.family: "Niagara Engraved"
            font.pixelSize: parent.height * .85
        }
    }
    Rectangle{
        id:addRect
        anchors.left: inputRect.right
        width:inputRect.width/2
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        MouseArea{
            anchors.fill: parent
        }

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .65
            color: "yellow"
            text: "Add To List"
        }
    }
    Rectangle{
        anchors.left: addRect.right
        anchors.right: parent.right
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        MouseArea{
            anchors.fill: parent
            onClicked: {
                VideoTransferManager.attemptConnectionToHost(ipString.text);
            }
        }

                Text{
                    anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .65
            color: "yellow"
            text: "Connect"
        }
    }

    ListView {
        z:parent + 2
        id: videoView
        visible: connectedToCopter
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
        Text{
            anchors.fill: parent
            text:"Currently Disconnected..."
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:  Text.AlignBottom
            font.pixelSize: parent.height * .8
        }
    }
}
