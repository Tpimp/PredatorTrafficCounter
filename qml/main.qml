import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import "qrc:/qml"
ApplicationWindow {
    id: appWindow
    width: ScreenWidth
    height: ScreenHeight
    visible: true


    title: qsTr("Predator Traffic Counter")

    Flickable{

        anchors.fill: parent
        contentWidth: parent.width*2
        contentHeight: parent.height

        Row {
            anchors.fill: parent
                ConnectView{
                    id: connectView
                    height: appWindow.height
                    width: appWindow.width
                    anchors.verticalCenter: parent.verticalCenter
                }

				TrafficCountView {
					id: trafficView
                    height: appWindow.height
					width: appWindow.width
                    anchors.verticalCenter: parent.verticalCenter
                }
        }
        SettingsView{
            id: settingsView
            anchors.top: parent.top
            anchors.bottom: parent.top
            anchors.bottomMargin: connectView.statusBar.height
            anchors.left: parent.left
            anchors.right: parent.right
            z: parent.z + 10
            visible: false
        }

        // snap to the module current most visible
        onMovementEnded:  {
            if(visibleArea.xPosition > .24)
            {

                slideRight.start()
            }
            else
            {
                slideLeft.start()
            }

        }
        // perform animation on x
		NumberAnimation on contentX { running:false; id:slideRight; to: trafficView.x; duration: 200  }
        NumberAnimation on contentX { running:false; id:slideLeft; to: 0; duration: 200  }
    }

}
