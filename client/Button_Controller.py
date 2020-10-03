import json

from PySide2.QtCore import QObject, Slot

from ServerConection import ServerConnection


class Button_Controller(QObject):
    @Slot(str, str, str, str, result=str)
    def complete_registration(self, login, email, password, confirm_password) -> str:
        if password != confirm_password:
            return
        if login == "" or email == "" or password == "":
            return

        register_data = {"target": "reg", "login": login, "email": email, "password": password}
        json_data = json.dumps(register_data).encode("utf-8")

        with open("/home/frotos/Desktop/data.json", "w+") as file:
            json.dump(register_data, file)

        server_conection = ServerConnection()
        server_answer: dict = json.loads(server_conection.pool.apply(server_conection.send_data, (json_data,)))

        print(server_answer)
        
        if server_answer["target"] == "reg":
            if server_answer["email"] == "ok" and server_answer["login"] == "ok":
                return "OK"
            elif server_answer["email"] == "bad" and server_answer["login"] == "bad":
                return "both"
            elif server_answer["email"] == "bad":
                return "email"
            elif server_answer["login"] == "bad":
                return "login"
            else:
                print(server_answer)

    @Slot(str, str, result=str)
    def complete_logging(self, login, password) -> str:
        if login == "" or password == "":
            return

        login_data = {"target": "log", "login" : login, "password" : password}
        json_data = json.dumps(login_data).encode("utf-8")

        with open("/home/frotos/Desktop/data.json", "w+") as file:
            json.dump(login_data, file)

        server_conection = ServerConnection()
        server_answer: dict = json.loads(server_conection.pool.apply(server_conection.send_data, (json_data,)))

        print(server_answer)

        if server_answer["target"] == "log":
            if server_answer["login"] == "ok" and server_answer["pass"] == "ok":
                return "OK"
            elif server_answer["login"] == "bad" and server_answer["pass"] == "bad":
                return "both"
            elif server_answer["login"] == "bad":
                return "login"
            elif server_answer["pass"] == "bad":
                return "pass"
            else:
                print(server_answer)
