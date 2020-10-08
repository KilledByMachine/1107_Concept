import json

from PySide2.QtCore import QObject, Signal, Slot
from PySide2.QtQml import QQmlApplicationEngine

from ServerConection import ServerConnection
from UserAuthorization import UserAuthorization


class Button_Controller(QObject):
    def __init__(self, parent=None):
        super(Button_Controller, self).__init__(parent)
        self.user = UserAuthorization(self)

    registerSignal = Signal(str, name="registerSignal")
    loginSignal = Signal(str, name="loginSignal")

    @Slot(str, str, str, str, result=str)
    def complete_registration(self, login, email, password, confirm_password) -> str:
        if password != confirm_password:
            return
        if login == "" or email == "" or password == "":
            return

        register_data = {"rarget": "reg", "login": login, "email": email, "password": password}
        json_data = json.dumps(register_data).encode("utf-8")

        with open("/home/frotos/Desktop/data.json", "w+") as file:
            json.dump(register_data, file)

        self.user.pool.apply(self.user.register, (json_data,))

    @Slot(str, str, result=str)
    def complete_logging(self, login, password) -> str:
        if login == "" or password == "":
            return

        login_data = {"target": "log", "login" : login, "password" : password}
        json_data = json.dumps(login_data).encode("utf-8")

        with open("/home/frotos/Desktop/data.json", "w+") as file:
            json.dump(login_data, file)

        self.user.pool.apply(self.user.login, (json_data,))
