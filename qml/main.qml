import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import "qrc:/qml"
ApplicationWindow {
    id: appWindow
    width: ScreenWidth
    height: ScreenHeight
    visible: true

    visibility: DisplayMode

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

                Rectangle {
                    id: greenScreen
                    height: appWindow.height
                    width: appWindow.width
                    color: "green"
                    anchors.verticalCenter: parent.verticalCenter
                }
        }
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
        NumberAnimation on contentX { running:false; id:slideRight; to: greenScreen.x; duration: 200  }
        NumberAnimation on contentX { running:false; id:slideLeft; to: 0; duration: 200  }
    }

}
