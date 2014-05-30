import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Rectangle {
    color: "#3d3d3e"
    id:connectView
    property bool connectedToCopter: false
    property string currentConnection: ""
    Image
    {
        anchors.fill: parent
        source:"qrc:/images/ConnectBackground.png"
        id: backgroundImage
        smooth: true
        visible: !connectedToCopter
        fillMode: Image.Stretch

    }

    // Define Connections to C++ objects
    Connections {
            target: VideoTransferManager
            onConnectedForTransfer:{
                statusText.text = ("Now Connected to " + currentConnection);
                connectedToCopter = true;
                VideoTransferManager.fetchVideoListFromServer();
            }
            onConnectionFailed:{
                statusText.text = ("Connection to " + currentConnection + " has failed.");
                //connectedToCopter = false;
            }

        }
    Connections
    {
        target: VideoManager
        onVideoInfoUpdated:{
            videoView.currentIndex = index;
            statusText.text = "Fetched info " + (index+1) + " of " + videoView.count;
        }
        onVideoObjectsChanged:{
            VideoManager.fetchAllVideoInfo();
        }
    }

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
        color: "white"
        border.color: "yellow"
        border.width: 2
        clip: true
        visible: !connectedToCopter
        anchors.topMargin: -40
        TextInput{
            id: ipString
            anchors.fill: parent
            text:"192.168.3.115"
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
        visible: !connectedToCopter
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        MouseArea{
            anchors.fill: parent
            onPressed:{
                addRect.color = "orange";
            }
            onReleased: {
                addRect.color = "blue";
            }
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
        visible: !connectedToCopter
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        MouseArea{
            anchors.fill: parent
            onPressed: {
                    VideoTransferManager.attemptConnectionToHost(ipString.text);
                    currentConnection = ipString.text;
            }
            onReleased: {
                addRect.color = "blue";
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
        id: videoView
        visible: connectedToCopter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: statusBarConnect.top
        orientation: ListView.Vertical
        flickableDirection: Flickable.VerticalFlick
        model: videoList
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
           // anchors.margins: 4
            height: index == videoView.currentIndex ? parent.width * .25:parent.width * .125
            MouseArea
            {
                anchors.fill: parent
                onClicked: {
                    videoView.currentIndex = index;
                }
            }
            // TODO: Turn download button into "Action Menu" - provide interface for video actions
            Rectangle{
                id:downloadButton
                color: "brown"
                width: parent.width/6
                height: parent.height/10
                radius:16
                visible: model.modelData.videoinfo === ""
                border.color: "black"
                border.width: 1
                anchors.top: locationRect.bottom
                anchors.horizontalCenter: locationRect.horizontalCenter
                anchors.margins: 10
                MouseArea{
                    anchors.fill: parent
                    onPressed:{
                        VideoTransferManager.fetchVideoInfoFromServer(model.modelData.videoname);
                    }
                }
                Text{
                    text:"Download Video"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height*.75
                    color: "black"
                }

            }
            // TODO: Fix display of video info (Flow work well here?)
            Rectangle{
                anchors.right: locationRect.left
                anchors.top: videoNameText.bottom
                color: "transparent"
                width:parent.width/4
                height: parent.height*.8 - videoNameText.height
                visible: index == videoView.currentIndex ? true:false
                border.width: 2
                clip: true
                border.color: "white"
                Text{
                    color:"white"
                    wrapMode: Text.WordWrap
                    anchors.fill: parent
                    text: model.modelData.videoinfo
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                }
            }
            Text {
                // anchors.verticalCenter: itemRect.verticalCenter
                id: videoNameText
                text: model.modelData.videoname
                anchors.top: parent.top
                anchors.right: locationRect.left
                anchors.left: parent.left
                anchors.leftMargin: 4
                font.bold: true
                color: "white"
                font.pixelSize: (delItem.width - locationRect.height) / text.length + 2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Rectangle{
                id: locationRect
                height:delItem.height * .6
                width:delItem.width/3
                anchors.top: parent.top
                anchors.right: parent.right
                radius: width/16
                anchors.topMargin: 6
                anchors.rightMargin: 6
                gradient: Gradient {
                    GradientStop {
                        position: 0.00;
                        color: "#006aff";
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#1500ff";
                    }
                }
                border.width: 1
                border.color: "white"
                Rectangle{
                    width: parent.width*.8
                    height: parent.height/3
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins:parent.height/12
                    id:onServer
                    Text{
                        text: "On Server"
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        font.pixelSize: parent.height*.75
                        color: "yellow"
                    }

                    gradient: Gradient {
                        GradientStop {
                            position: 0.00;
                            color: "#5d84ee";
                        }
                        GradientStop {
                            position: 0.86;
                            color: "#494be6";
                        }
                    }
                    border.color: "#00ddff"
                    Rectangle{
                        anchors.right: parent.right
                        width: parent.width/12
                        anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        height: width
                        radius:height/2
                        color: servable ? "#00ff08":"red"
                        border.width: 1
                        border.color: "black"
                    }
                }
                Rectangle{
                    width: parent.width*.8
                    height: parent.height/3
                    anchors.top: onServer.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: onClient
                    anchors.margins:parent.height/12
                    Text{
                        text: "On Client"
                        anchors.left: parent.left
                        anchors.leftMargin: 4
                        font.pixelSize: parent.height*.75
                        color: "yellow"
                    }

                    gradient: Gradient {
                        GradientStop {
                            position: 0.00;
                            color: "#5d84ee";
                        }
                        GradientStop {
                            position: 0.86;
                            color: "#494be6";
                        }
                    }
                    border.color: "#00ddff"
                    Rectangle{
                        anchors.right: parent.right
                        width: parent.width/12
                        anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        height: width
                        radius:height/2
                        color: local ? "#00ff08":"red"
                        border.width: 1
                        border.color: "black"
                    }
                }
            }

        }
    }
    StatusBar{
        id:statusBarConnect
        height:80
        anchors.left: parent.left
        anchors.right: parent.right
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        Text{
            id:statusText
            anchors.fill: parent
            text:"Currently Disconnected..."
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:  Text.AlignBottom
            font.pixelSize: parent.height * .8
        }
    }
}
