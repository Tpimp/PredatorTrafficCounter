import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.1

import "qrc:/qml"
Rectangle {
    color: "#3d3d3e"
    id:connectView
    property bool connectedToCopter: false
    property string currentConnection: ""
    property bool attemptingToConnect: false
    property alias statusBar: statusBarConnect

    function showVideoView(){
        backgroundImage.visible = false;
        connectMessage.visible = false;
        droneImage.visible = false;
        addToListButton.visible = false;
        droneView.visible = false;
        connectButton.visible = false;
        inputRect.visible = false;
        videoView.visible = true

    }
    function showConnectView(){
        backgroundImage.visible = true;
        connectMessage.visible = true;
        droneImage.visible = true;
        connectButton.visible = true;
        inputRect.visible = true;
        addToListButton.visible = true;
        videoView.visible = false;
        droneView.visible = true;

    }

    function disableInputConnectView(){
        connectView.enabled = false;
    }
    function enableInputConnectView(){
        connectView.enabled = true;
    }

    function checkIfConfigurationSuccessful()
    {
        if(SettingsManager.drone_list == "" ||
           SettingsManager.video_directory == "")
            return false;
        return true;
    }

    // Define Connections to C++ objects
    Connections {
            target: VideoTransferManager
            onConnectedForTransfer:{
                statusText.text = ("Now Connected to " + currentConnection);
                connectedToCopter = true;
                showVideoView();
                attemptingToConnect = false;
                disableInputConnectView();
                busyIndicator.source = "qrc:/images/busy.gif";
                VideoTransferManager.fetchVideoListFromServer();
            }
            onConnectionFailed:{
                if(attemptingToConnect)
                {
                    statusText.text = ("Connection attempt failed");
                }
                else
                {
                    statusText.text = ("Connection to " + currentConnection + " failed.");
                }

                attemptingToConnect = false;
                enableInputConnectView();
                busyRect.visible = false;
                connectedToCopter = false;
                showConnectView();

            }
            onDownloadPercentChanged:{ // (QString name,int percent)
               // videoView
            }

        }
    Connections
    {
        target: VideoManager
        onVideoInfoUpdated:{
            videoView.currentIndex = index;
            statusText.text = "Fetching info " + (index) + " of " + videoView.count;
            if((videoView.currentIndex + 1) == videoView.count )
            {
                statusText.text = "All Video Info Fetched";
                enableInputConnectView();
                //VideoTransferManager.
                busyRect.visible = false;
            }
        }
        onVideoObjectsChanged:{
            statusText.text = "Fetching video info for all videos...";
            VideoManager.fetchAllVideoInfo();
        }
    }

    Image
    {
        anchors.fill: parent
        source:"qrc:/images/ConnectBackground.png"
        id: backgroundImage
        smooth: true
        visible: true
        fillMode: Image.Stretch

    }
    Text{
        id:connectMessage
        anchors.bottom: inputRect.top
        anchors.bottomMargin: 4
        anchors.topMargin:  20
        anchors.left: parent.left
        anchors.right: addToListButton.left
        color: "white"
        font.pixelSize: (width / text.length) +8
        visible: true
        horizontalAlignment: Text.AlignHCenter
        text: "Please Connect to a Predator QuadCopter..."
    }

    Image
    {
        id: droneImage
        width: parent.width * .40
        height: width * .8
        smooth: true
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
        visible: true
        anchors.topMargin: -40
        TextInput{
            id: ipString
            anchors.fill: parent
            anchors.margins: 2
            text:"192.168.3.115"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .85
        }
    }
    Rectangle{
        id:addToListButton
        anchors.left: inputRect.right
        width:inputRect.width/2
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        visible: true
        MouseArea{
            anchors.fill: parent
            onPressed:{
                addToListButton.color = "orange";
            }
            onReleased: {
                addToListButton.color = "blue";
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
        id:connectButton
        anchors.left: addToListButton.right
        anchors.right: parent.right
        anchors.verticalCenter: inputRect.verticalCenter
        color: "blue"
        height: inputRect.height
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        visible: true
        MouseArea{
            anchors.fill: parent
            onPressed: {
                    if(checkIfConfigurationSuccessful())
                    {
                        statusText.text = "Attempting to connect to " + ipString.text;
                        attemptingToConnect = true;
                        disableInputConnectView();
                        busyIndicator.source = "qrc:/images/busy1.gif";
                        busyRect.visible = true;
                        VideoTransferManager.attemptConnectionToHost(ipString.text);
                        currentConnection = ipString.text;
                    }
                    else
                    {

                    }
            }
            onReleased: {
                connectButton.color = "blue";
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
        id: droneView
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: connectButton.bottom
        anchors.bottom: statusBarConnect.top
        orientation: ListView.Vertical
        flickableDirection: Flickable.VerticalFlick
        model: knownDrones
        highlightFollowsCurrentItem: true
        focus: true
        delegate: DroneItem{}
    }
    ListView {
        id: videoView
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: statusBarConnect.top
        orientation: ListView.Vertical
        flickableDirection: Flickable.VerticalFlick
        model: videoList
        highlightFollowsCurrentItem: true
        focus: true
        section.property: "videoname"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        delegate: Rectangle {
            id: delItem
            width: parent.width
            border.color: "steelblue"
            border.width: 4
            color: "transparent"
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
                id:actionButton
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
                anchors.top: parent.top
                color: "transparent"
                width:parent.width/4
                height: parent.height*.8
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
            ProgressBar{
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: locationRect.left
                visible: downloading
                style:ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "darkblue"
                        border.color: "gray"
                        border.width: 2
                    }
                    progress: Rectangle {
                                color: "lightsteelblue"
                                border.color: "steelblue"
                            }
                }
                maximumValue: 100
                minimumValue: 0
                value: amountcomplete

            }

        }
        section {
            property: "videoname"
            criteria: ViewSection.FullString

            delegate: Rectangle {
                id: sectionHeading
                width: parent.width
                height: videoView.height * .125
                color: "lightsteelblue"
                radius: width *.25
                border.width: 2
                border.color:"steelblue"
                Text { anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: parent.height *.8
                    text: section
                }
            }
        }
    }
    Rectangle{
        id:busyRect
        color: "black"
        opacity: 0.85
        anchors.top: parent.top
        anchors.bottom: statusBarConnect.top
        anchors.left: parent.left
        anchors.right: parent.right
        z: parent.z + 5
        AnimatedImage{
            id: busyIndicator
            width: parent.width/6
            height: width
            playing: busyRect.visible
            source: "qrc:/images/busy1.gif"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
        antialiasing: true
        FastBlur {
            anchors.fill: busyRect
            source: busyRect
            radius: 32
        }
        visible: false

    }

    StatusBar{
        id:statusBarConnect
        height:80
        anchors.left: parent.left
        anchors.right: parent.right
        property alias text: statusText
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        Text{
            id:statusText
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width * .75
            text:"Currently Disconnected..."
            horizontalAlignment: Text.AlignLeft
            verticalAlignment:  Text.AlignBottom
            font.pixelSize: parent.height * .8
        }

        ProgressBar {
            id: progressConnecting
            anchors.left: statusText.right
            height : 20
            anchors.right: parent.right
            style:ProgressBarStyle {
                background: Rectangle {
                    radius: 2
                    color: "darkblue"
                    border.color: "gray"
                    border.width: 2
                }
                progress: Rectangle {
                    color: "lightsteelblue"
                    border.color: "steelblue"
                    Item {
                            anchors.fill: parent
                            anchors.margins: 1
                            visible: control.indeterminate
                            clip: true
                            Row {
                                Repeater {
                                    Rectangle {
                                        color: index % 2 ? "steelblue" : "lightsteelblue"
                                        width: 20 ; height: control.height
                                    }
                                    model: control.width / 20 + 2
                                }
                                XAnimator on x {
                                    from: 0 ; to: -40
                                    loops: Animation.Infinite
                                    running: control.indeterminate
                                }
                            }
                        }
                }
            }
            indeterminate: true
            visible: busyRect.visible
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
