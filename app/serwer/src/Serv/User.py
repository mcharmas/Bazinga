import socket
import time

class User:
    """Klasa trzymajaca informacje o danym uzytkowniku."""
    
    def __init__(self, id, login, password, host, sock):
        """Konstruktor."""
        ##Id sesji uzytkownika
        self.id = id
        
        ##Login uzytkownika        
        self.login = login
        
        ##Haslo uzytkownika
        self.password = password
        
        ##Grupa w ktorej uzytkownik aktualnie sie znajduje
        self.group = None        
        
        ##Host uzytkownika
        self.host = host
        
        ##Host drivera uzytkownika        
        self.driverHost = None
        
        ##Socket przez ktory wysylane sa dane do uzytkownika
        self.sock = sock
        
        ##Ostatnia aktywnosc uzytkownika
        self.timestamp = time.localtime()        
        
    def sendData(self, data):
        """Wysyla dane do aplikacji klienckiej."""
        if self.sock:                        
            self.sock.sendto(data, self.host)
            
    def sendDataToDriver(self, data):
        """Wysyla dane do aplikacji sterownika."""
        if self.sock:
            self.sock.sendto(data, self.driverHost)
        
    def update(self):
        """Aktualizuje ostatnia aktywnosc uzytkownika."""        
        self.timestamp = time.localtime()
        