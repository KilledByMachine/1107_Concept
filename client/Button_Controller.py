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
        server_answer = server_conection.pool.apply_async(server_conection.send_data, (json_data,))
        if server_answer.ready():
            answer_data: dict = json.loads(server_answer.get())

            print(answer_data)
            
            if answer_data["target"] == "reg":
                if answer_data["email"] == "ok" and answer_data["login"] == "ok":
                    return "OK"
                elif answer_data["email"] == "bad" and answer_data["login"] == "bad":
                    return "both"
                elif answer_data["email"] == "bad":
                    return "email"
                elif answer_data["login"] == "bad":
                    return "login"
                else:
                    print(answer_data)

    @Slot(str, str, result=str)
    def complete_logging(self, login, password) -> str:
        if login == "" or password == "":
            return

        login_data = {"target": "log", "login" : login, "password" : password}
        json_data = json.dumps(login_data).encode("utf-8")

        with open("/home/frotos/Desktop/data.json", "w+") as file:
            json.dump(login_data, file)

        server_conection = ServerConnection()
        server_answer = server_conection.pool.apply_async(server_conection.send_data, (json_data,))
        if server_answer.ready():
            answer_data: dict = json.loads(server_answer.get())

            print(answer_data)

            if answer_data["target"] == "log":
                if answer_data["login"] == "ok" and answer_data["pass"] == "ok":
                    return "OK"
                elif answer_data["login"] == "bad" and answer_data["pass"] == "bad":
                    return "both"
                elif answer_data["login"] == "bad":
                    return "login"
                elif answer_data["pass"] == "bad":
                    return "pass"
                else:
                    print(answer_data)
