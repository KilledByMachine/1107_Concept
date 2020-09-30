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

        CustomTextField {
            id: register_login_field
            objectName: "register_login_field"
            placeholderText: "Enter your login"
            selectByMouse: true
            width: parent.width / 2

            Popup {
                id: register_login_popup

                parent: register_login_field
                x: parent.width - width
                y: parent.height - 2
                width: parent.width
                height: 18

                background: RoundedErrorRectangle {
                    id: register_login_popup_rect
                    error_text: "Username is not available"
                }
            }
        }

        Item {
            height: 10
        }

        CustomTextField {
            id: register_email_field
            objectName: "register_email_field"
            placeholderText: "Enter your email"
            width: parent.width / 2

            validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }
            onTextChanged: {
                if (text.length == 0) {
                    change_border_color(secondary_color)
                }
                else if (acceptableInput) {
                    change_border_color("green")
                }
                else {
                    change_border_color("red")
                }
            }

            Popup {
                id: register_email_popup

                parent: register_email_field
                x: parent.width - width
                y: parent.height - 2
                width: parent.width
                height: 18

                background: RoundedErrorRectangle {
                    id: register_email_popup_rect
                    error_text: "Email is not available"
                }
            }
        }

        Item {
            height: 10
        }

        CustomTextField {
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

        CustomTextField {
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
                onClicked: {
                    var result = button_controller.complete_registration(register_login_field.text, register_email_field.text,
                                                                   register_pass_field.text, register_pass_confirm_field.text)
                    if (result === "OK") {
                        reset_fields();
                        stack_view.push(login_page)
                    }
                    else if (result === "both") {
                        register_login_popup.open()
                        register_email_popup.open()
                    }
                    else if (result === "login") {
                        register_login_popup.open()
                    }
                    else if (result === "email") {
                        register_email_popup.open()
                    }
                }
            }
        }
    }
}

