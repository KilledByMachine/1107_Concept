import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

TextField {
    id: root

    property color border_color: secondary_color

    function change_border_color(color){
        border_color = color
    }

    background: Rectangle{
        implicitWidth: 200
        implicitHeight: 40
        border.width: 2
        border.color: root.focus ? border_color : "transparent"
    }
    selectByMouse: true
}
