import QtQuick 2.0

Rectangle {
    id: droneItem
    width: parent.width
    border.color: "white"
    border.width: 4
    color: "black"
    radius: parent.width/32
    clip: true
    // anchors.margins: 4
    height: index == parent.currentIndex ? parent.width * .25:parent.width * .125
    Rectangle{
        color: "white"
        id: typeImage
        height: parent.height* .9
        width: height
        anchors.left: parent.left
        anchors.leftMargin: width/6
        anchors.verticalCenter: parent.verticalCenter
        radius:8
        clip: true
        Image{
            anchors.fill: parent
            anchors.margins: 4
            source: "qrc:/images/" + model.modelData.drone_type + ".png"
        }
    }
    Text{
        id: nameText
        height: parent.height/4
        width: parent.width/2
        text: "Drone Name: " + model.modelData.drone_name
        color: "yellow"
        anchors.top: parent.top
        anchors.left: typeImage.right
        anchors.leftMargin: parent.width/16
        font.pixelSize: height*.85
    }
    Text{
        id: ipText
        height: parent.height/4
        width: parent.width/2
        text: "Drone IP: " + model.modelData.drone_ip
        color: "white"
        anchors.top: nameText.bottom
        anchors.left: typeImage.right
        anchors.leftMargin: parent.width/16
        font.pixelSize: height*.85
    }
    Text{
        id: ownerText
        height: parent.height/4
        width: parent.width/2
        text: "Drone Owner: " + model.modelData.drone_owner
        color: "white"
        anchors.top: ipText.bottom
        anchors.left: typeImage.right
        anchors.leftMargin: parent.width/16
        font.pixelSize: height*.85
    }
    Text{
        id: typeText
        height: parent.height/4
        width: parent.width/2
        text: "Drone Type: " + model.modelData.drone_type
        color: "white"
        anchors.top: ownerText.bottom
        anchors.left: typeImage.right
        anchors.leftMargin: parent.width/16
        font.pixelSize: height*.85
    }


}
