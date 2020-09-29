import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Window {
    width: 400
    height: 480
    visible: true
    title: qsTr("**Program name**")

    property color primary_color: "#2f2f2f"
    property color button_color: "#262626"
    property color button_text_color: "#b4b4b4"

    color: primary_color

    RowLayout {
        ToolButton {
            text: "<"
            Layout.alignment: Qt.AlignVCenter
            visible: stack_view.depth > 1

            onClicked: {
                registration_page.reset_fields()
                login_page.reset_fields()
                stack_view.pop()
            }
        }

        Item {
            Layout.fillWidth: true
        }
    }

    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: welcome_page
    }

    WelcomePage {
        id: welcome_page
    }

    RegistrationPage {
        visible: false
        id: registration_page
    }

    LoginPage {
        visible: false
        id: login_page
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
