import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    id: columnLayout

    function reset_fields() {
        register_login_field.text = ""
        register_email_field.text = ""
        register_pass_field.text = ""
        register_pass_confirm_field.text = ""
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter

        Label {
            text: "Registration"
            font.bold: true
            font.pointSize: 14
            color: button_text_color
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            height: 20
        }

        TextField {
            id: register_login_field
            objectName: "register_login_field"
            placeholderText: "Enter your login"
            selectByMouse: true
            width: parent.width / 2
        }

        Item {
            height: 10
        }

        TextField {
            id: register_email_field
            objectName: "register_email_field"
            placeholderText: "Enter your email"
            selectByMouse: true
            width: parent.width / 2
        }

        Item {
            height: 10
        }

        TextField {
            id: register_pass_field
            objectName: "register_pass_field"
            placeholderText: "Enter your password"
            selectByMouse: true
            width: parent.width / 2
            echoMode: TextInput.Password
        }

        Item {
            height: 5
        }

        TextField {
            id: register_pass_confirm_field
            objectName: "register_pass_confirm_field"
            placeholderText: "Confirm your password"
            selectByMouse: true
            width: parent.width / 2
            echoMode: TextInput.Password
        }

        Item {
            height: 20
        }

        Column {
            RoundButton {
                id: register_button_confirm
                objectName: "register_button_confirm"
                width: columnLayout.width / 2
                text: qsTr("Registrer")
                font.pointSize: 12
                Layout.alignment: Qt.AlignHCenter

                palette {
                    button:button_color
                    buttonText: button_text_color
                }
                onClicked: button_controller.complete_registration(register_login_field.text, register_email_field.text,
                                                                   register_pass_field.text, register_pass_confirm_field.text)
            }
        }
    }
}
