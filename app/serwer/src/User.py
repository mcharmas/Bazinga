import socket
import time

class User():
    def __init__(self, login, password, group, host, socket):
        self.login = login
        self.password = password
        self.group = group
        self.host = host
        self.socket = socket
        self.timestamp = time.localtime()
        
    def sendData(self, data):
        self.socket.sendto(data, self.host)
        
    def update(self):
        self.timestamp = time.localtime()
        