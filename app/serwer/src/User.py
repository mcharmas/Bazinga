import socket
import time

class User:
    def __init__(self, id, login, password, group, host):
        self.id = id
        self.login = login
        self.password = password
        self.group = group        
        self.host = host
        self.socket = None
        self.timestamp = time.localtime()        
        
    def sendData(self, data):
        if self.socket:
            self.socket.sendto(data, self.host)
        
    def update(self):
        self.timestamp = time.localtime()
        