import socket
import time

class User:
    def __init__(self, id, login, password, host, socket):
        self.id = id
        self.login = login
        self.password = password
        self.group = None        
        self.host = host
        self.socket = socket
        self.timestamp = time.localtime()        
        
    def sendData(self, data):
        if self.socket:
            self.socket.sendto(data, self.host)
        
    def update(self):
        self.timestamp = time.localtime()
        