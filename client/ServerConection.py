import socket

from settings.server_settings import SERVER_IP, SERVER_PORT


class ServerConnection:
    def __init__(self):
        self.client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def send_data(self, data: bytes) -> str:
        self.client_sock.connect((SERVER_IP, SERVER_PORT))
        self.client_sock.sendall(data)
        received_data = self.client_sock.recv(1024)
        self.client_sock.close()

        return received_data
