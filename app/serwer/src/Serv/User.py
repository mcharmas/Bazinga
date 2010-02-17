import socket
import time

class User:
    """Klasa trzymajaca informacje o danym uzytkowniku
    
    """
    
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
        """Wysyla dane do aplikacji klienckiej
        
        """
        if self.sock:                        
            self.sock.sendto(data, self.host)
            
    def sendDataToDriver(self, data):
        """Wysyla dane do aplikacji sterownika
        
        """
        if self.sock:
            self.sock.sendto(data, self.driverHost)
        
    def update(self):
        """Aktualizuje ostatnia aktywnosc uzytkownika
        
        """        
        self.timestamp = time.localtime()
        