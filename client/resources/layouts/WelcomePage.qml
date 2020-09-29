import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    id: columnLayout
    
    Image {
        id: logo_image
        source: "../icons/logo.png"
        Layout.alignment: Qt.AlignHCenter
        sourceSize.width: 200
    }
    
    ButtonGroup {
        buttons: welcome_button_column.children
    }
    
    Column {
        id: welcome_button_column
        Layout.alignment: Qt.AlignHCenter
        spacing: 20
        
        RoundButton {
            id: register_button
            objectName: "register_button"
            width: 120
            text: qsTr("Registration")
            font.pointSize: 12
            Layout.alignment: Qt.AlignHCenter
            
            palette {
                button:button_color
                buttonText: button_text_color
            }
            onClicked: stack_view.push(registration_page)
        }
        
        RoundButton {
            id: login_button
            objectName: "login_button"
            width: 120
            text: qsTr("Login")
            font.pointSize: 12
            Layout.alignment: Qt.AlignHCenter
            palette {
                button: "#262626"
                buttonText: "#b4b4b4"
            }
            onClicked: stack_view.push(login_page)
        }
    }
}
