import json

from PySide2.QtCore import QObject, Slot


class Button_Controller(QObject):
    @Slot(str, str, str, str)
    def complete_registration(self, login, email, password, confirm_password):
        if password != confirm_password:
            return
        if login == "" or email == "" or password == "":
            return

        register_data = {"login" : login, "email" : email, "password" : password}
        print(json.dumps(register_data))

    @Slot(str, str)
    def login_button_complete(self, login, password):
        if login == "" or password == "":
            return

        login_data = {"login" : login, "password" : password}
        print(json.dumps(login_data))
