import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0


Rectangle
{
	id: trafficView
	color: "purple"

	property int touchStartY: 0
	property int toolbarExpandedHeight: trafficView.height * 0.4
	property int toolbarClosedHeight: trafficView.height * 0.15

	MultiPointTouchArea
	{
		id: touchController
		anchors.fill: parent
		touchPoints:
		[//add more touch points here to reference for complex touch commands
			TouchPoint { id: point1 }
		]

		onPressed:
		{
			touchStartY = point1.y;
		}

		onReleased:
		{
			if (touchStartY > point1.y)
			{
				startSessionButton.y -= toolbarExpandedHeight;
				reviewSessionsButton.y -= toolbarExpandedHeight;
				toolbarContainer.height = toolbarExpandedHeight;
				toolbarContainer.y -= toolbarExpandedHeight;
			}
			else if (touchStartY < point1.y)
			{
				startSessionButton.y += toolbarExpandedHeight;
				reviewSessionsButton.y += toolbarExpandedHeight;
				toolbarContainer.height = toolbarClosedHeight;
				toolbarContainer.y += toolbarExpandedHeight;
			}
		}
	}

	Image
	{
		id: background
		anchors.centerIn: parent
		anchors.fill: parent
		height: parent.height
		width: parent.width
        source: "qrc:/images/TrafficBackground.png"
	}

    Rectangle{
        id:startSessionButton
        width:  parent.width/3
        height: parent.height/10
        anchors.bottom: reviewSessionsButton.top
        anchors.bottomMargin: parent.height * .1
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: "blue"
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        visible: true
        MouseArea{
            anchors.fill: parent
            onPressed: {

            }
            onReleased: {

            }
        }

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .8
            color: "yellow"
            text: "Start Session"
        }
    }

    Rectangle{
        id:reviewSessionsButton
        width:  parent.width/3
        height: parent.height/10
        anchors.bottom: toolbarContainer.top
        anchors.bottomMargin: parent.height * 0.1
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: "blue"
        border.width: 2
        border.color: "black"
        anchors.margins: 4
        radius: 2
        visible: true
        MouseArea{
            anchors.fill: parent
            onPressed: {

            }
            onReleased: {

            }
        }

        Text{
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.height * .8
            color: "yellow"
            text: "Review Sessions"
        }
    }


	Rectangle
	{
		id: toolbarContainer
		color: "dark green"
		radius: 5
		border.width: 4
		border.color: "green"
		width: parent.width
		height: parent.height * 0.15
		anchors.bottom: parent.bottom
		anchors.horizontalCenter: parent.horizontalCenter

		Text
		{
			anchors.centerIn: parent
            text: "I am Broken"
            font.pixelSize: parent.height *.9
		}


	}
}
