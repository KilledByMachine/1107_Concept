import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    id: columnLayout

    function reset_fields() {
        logging_login_field.text = ""
        loggin_password_field.text = ""
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter

        Label {
            text: "Logging in"
            font.bold: true
            font.pointSize: 14
            color: button_text_color
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            height: 20
        }

        TextField {
            id: logging_login_field
            objectName: "logging_field"
            placeholderText: "Enter your login"
            selectByMouse: true
            width: parent.width / 2
        }

        Item {
            height: 10
        }
        TextField {
            id: loggin_password_field
            objectName: "loggin_password_field"
            placeholderText: "Enter your password"
            selectByMouse: true
            width: parent.width / 2
            echoMode: TextInput.Password
        }

        Item {
            height: 20
        }

        Column {
            RoundButton {
                id: login_button_confirm
                objectName: "login_button_confirm"
                width: columnLayout.width / 2
                text: qsTr("Log in")
                font.pointSize: 12
                Layout.alignment: Qt.AlignHCenter

                palette {
                    button:button_color
                    buttonText: button_text_color
                }
                onClicked: button_controller.login_button_complete(logging_login_field.text, loggin_password_field.text)
            }
        }
    }
}
