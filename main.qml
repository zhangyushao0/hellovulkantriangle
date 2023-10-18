import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id: window
    visible: true
    width: 1024
    height: 768
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"
        Button {
            id: button
            text: qsTr("Click me")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                vulkanWindow.addSpeed(0.15);
            }
        }
    }

    Connections {
        target: vulkanWindow
        function onWindowResized(width, height) {
            window.width = width;
            window.height = height;
        }
    }
    Connections {
        target: vulkanWindow
        function onWindowMoved(x, y) {
            window.x = x;
            window.y = y;
        }
    }
    Connections {
        target: vulkanWindow
        function onWindowActivated() {
            window.raise();
        }
    }
    Connections {
        target: vulkanWindow
        function onWindowStateChanged(state) {
            if (state === Qt.WindowMinimized) {
                window.hide();
            } else {
                window.show();
            }
        }
    }
    Connections {
        target: vulkanWindow
        function onWindowClosed() {
            window.close();
        }
    }
}
