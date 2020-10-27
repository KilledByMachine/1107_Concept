import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Rectangle {
    color: "red"
    radius: 2
    property alias error_text: text_error.text
    
    Text {
        id: text_error
        leftPadding: 5
        anchors.verticalCenter: parent.verticalCenter
    }
}
