import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    id: columnLayout

    function reset_fields() {
        logging_login_field.text = ""
        logging_password_field.text = ""
    }

    function complete_logginin(result) {
        if (result === "OK") {
            reset_fields();
        }
        else if (result === "both") {
            logging_login_popup.open()
            logging_password_popup.open()
        }
        else if (result === "login") {
            logging_login_popup.open()
        }
        else if (result === "pass") {
            logging_password_popup.open()
        }
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

            Popup {
                id: logging_login_popup

                parent: logging_login_field
                x: parent.width - width
                y: parent.height - 2
                width: parent.width
                height: 18

                background: RoundedErrorRectangle {
                    id: logging_login_popup_rect
                    error_text: "Username is incorrect"
                }
            }
        }

        Item {
            height: 10
        }
        TextField {
            id: logging_password_field
            objectName: "logging_password_field"
            placeholderText: "Enter your password"
            selectByMouse: true
            width: parent.width / 2
            echoMode: TextInput.Password

            Popup {
                id: logging_password_popup

                parent: logging_password_field
                x: parent.width - width
                y: parent.height - 2
                width: parent.width
                height: 18

                background: RoundedErrorRectangle {
                    id: logging_password_popup_rect
                    error_text: "Password is incorrect"
                }
            }
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

                Component.onCompleted: function() {
                    ButtonController.loginSignal.connect(complete_logginin);
                }

                onClicked: {
                    ButtonController.complete_logging(logging_login_field.text, logging_password_field.text)
                }
            }
        }
    }
}
