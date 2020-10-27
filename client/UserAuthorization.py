import json
import time
from datetime import datetime, timedelta
from multiprocessing.pool import ThreadPool

from ServerConection import ServerConnection


class UserAuthorization:
    def __init__(self, button_controller=None):
        super().__init__()
        self.pool = ThreadPool(processes=1)
        self.controller = button_controller

    def register(self, register_data: bytes) -> str:
        server_conection = ServerConnection()
        server_answer = server_conection.pool.apply_async(
            server_conection.send_data, (register_data,)
        )
        send_time = datetime.now()

        while not server_answer.ready():
            if datetime.now().strftime("%H:%M:%S") == (
                send_time + timedelta(seconds=1)
            ).strftime("%H:%M:%S"):
                server_conection.client_sock.close()
                return False

            time.sleep(0.1)

        answer = ""
        received_data = server_answer.get()
        if received_data:
            answer_data: dict = json.loads(received_data)

            if answer_data["target"] == "reg":
                if answer_data["email"] == "ok" and answer_data["login"] == "ok":
                    answer = "OK"
                elif answer_data["email"] == "bad" and answer_data["login"] == "bad":
                    answer = "both"
                elif answer_data["email"] == "bad":
                    answer = "email"
                elif answer_data["login"] == "bad":
                    answer = "login"
                else:
                    print(answer_data)
        else:
            answer = "Connection error"

        self.controller.registerSignal.emit(answer)

    def login(self, login_data: bytes) -> str:
        server_conection = ServerConnection()
        server_answer = server_conection.pool.apply_async(
            server_conection.send_data, (login_data,)
        )
        send_time = datetime.now()

        while not server_answer.ready():
            if datetime.now().strftime("%H:%M:%S") == (
                send_time + timedelta(seconds=1)
            ).strftime("%H:%M:%S"):
                server_conection.client_sock.close()
                return False

            time.sleep(0.1)

        answer = ""
        received_data = server_answer.get()
        print(received_data)
        if received_data:
            answer_data: dict = json.loads(received_data)

            if answer_data["target"] == "log":
                if answer_data["login"] == "ok" and answer_data["pass"] == "ok":
                    answer = "OK"
                elif answer_data["login"] == "bad" and answer_data["pass"] == "bad":
                    answer = "both"
                elif answer_data["login"] == "bad":
                    answer = "login"
                elif answer_data["pass"] == "bad":
                    answer = "pass"
                else:
                    print(answer_data)

        self.controller.loginSignal.emit(answer)
