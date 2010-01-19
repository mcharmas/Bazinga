import socket
import time

class User:
    def __init__(self, id, login, password, host, sock):
        self.id = id
        self.login = login
        self.password = password
        self.group = None        
        self.host = host
        self.driverHost = None
        #self.socket = socket
        self.sock = sock
        self.timestamp = time.localtime()        
        
    def sendData(self, data):
        if self.sock:                        
            self.sock.sendto(data, self.host)
            
    def sendDataToDriver(self, data):
        if self.sock:
            self.sock.sendto(data, self.driverHost)
        
    def update(self):
        self.timestamp = time.localtime()
        