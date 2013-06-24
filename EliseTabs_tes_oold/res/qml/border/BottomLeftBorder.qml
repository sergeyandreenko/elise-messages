import QtQuick 2.0

MouseArea {
    width: 5
    height: 5
    anchors {
        left: parent.left;
        bottom: parent.bottom;
    }
    hoverEnabled: true
    property point clickPos

    onEntered: _window.setCursorShape(Qt.SizeBDiagCursor)
    onExited: _window.setCursorShape(Qt.ArrowCursor)

    onPressed: clickPos = Qt.point(mouse.x, mouse.y)

    onPositionChanged:
    {
        if (pressedButtons & Qt.LeftButton) {
            _window.moveBottomLeft(Qt.point(mouse.x, mouse.y), clickPos)
        }
    }

}
