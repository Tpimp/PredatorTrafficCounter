import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.1
Rectangle {
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#646464";
        }
        GradientStop {
            position: 1.00;
            color: "#000000";
        }
    }
    anchors.fill: parent
    // Define the Wireless Video Transfer settings
    Rectangle{
        id: titleTextRect
        border.color: "white"
        border.width: 2
        Text{
            id: wirelessTitleText
            anchors.rightMargin: 4
            color: "white"
            font.pixelSize: parent.height * .9
            text: "Drone Wireless Transfer Settings"
        }
        anchors.top: parent.top
        anchors.rightMargin: 4
        anchors.right: videoDirectoryRect.right
    }

    Rectangle
    {
        id:videoDirectoryRect
        anchors.top: titleTextRect.bottom
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.topMargin: parent.height/12
        radius: 10
        color: "white"
        border.color: "blue"
        border.width: 2
        width: parent.width * .4
        height: parent.height/8
        clip: true
        TextInput{
            id: video_directoryString
            anchors.fill: parent
            anchors.margins: 2
            text:"/Video_directory"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .65
        }
    }
    Button{
        text:"..."
        anchors.left: videoDirectoryRect.right
        height: videoDirectoryRect.height
        anchors.margins: 8
        anchors.right: parent.horizontalCenter
        anchors.verticalCenter: videoDirectoryRect.verticalCenter
        onClicked:{
            fileDialog.open();

        }
    }
    FileDialog{
        id: fileDialog
        visible: false
        //modality: Qt.Modal
        width: parent.width
        height: parent.height
        title: "Video Directory Location"
        selectExisting: true
        selectFolder:true
        selectMultiple: false
        onAccepted:  {
            var output = fileDialog.folder.toString();
            var index = 8;
            var directory_str = "";
            while(index < output.length)
            {
                directory_str += (output[index]);
                index++;
            }

            video_directoryString.text =directory_str;
        }
    }

    // Define the Traffic Counter Settings
}
