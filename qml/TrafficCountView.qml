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
		//source: "background.png"
	}

	Rectangle
	{
		id: startSessionButton
		color: "blue"
		radius: 5
		border.width: 4
		border.color: "gold"
		width: parent.width * 0.33
		height: parent.height * 0.15
		anchors.bottom: reviewSessionsButton.top
		anchors.bottomMargin: parent.height * 0.1
		anchors.right: parent.right
		anchors.rightMargin: 10

		Text
		{
			anchors.centerIn: parent
			text: "Start Session"
			font.pixelSize: parent.height * 0.8
		}

		NumberAnimation
		{
			id: startAnimationUp
			property: startSessionButton.y
			duration: 500
			easing.type: Easing.OutBounce
		}
	}

	Rectangle
	{
		id: reviewSessionsButton
		color: "red"
		radius: 5
		border.width: 4
		border.color: "yellow"
		width: parent.width * 0.33
		height: parent.height * 0.15
		anchors.bottom: toolbarContainer.top
		anchors.bottomMargin: parent.height * 0.1
		anchors.right: parent.right
		anchors.rightMargin: 10

		Text
		{
			anchors.centerIn: parent
			text: "Review Session"
			font.pixelSize: parent.height * 0.8
		}

		NumberAnimation
		{
			id: reviewAnimationUp
			property: reviewSessionsButton.y
			duration: 500
			easing.type: Easing.OutBounce
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
			text: "Toolbar"
			font.pixelSize: parent.height * 0.8
		}

		NumberAnimation
		{
			id: toolbarAnimationUp
			property: toolbarContainer.y
			duration: 500
			easing.type: Easing.OutBounce
		}
	}
}
