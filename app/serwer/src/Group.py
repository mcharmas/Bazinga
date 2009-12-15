import User
import time
from threading import Timer
from Logger import SLogger

class Group():
    """
    grupa przechowujaca userow
    posiada timer sprawdzajacy co timeout bezczynnosc userow po ich timestampach
    po bezczynnosci user jest usuwany (TODO: wysylac odnowienie polaczenia)
    """
    def __init__(self, id=0):
        self.users = []
        self.timeout = 500
        self.id = id
        self.name = "Group("+str(id)+")"
        self.timer = Timer(self.timeout, self.checkTimeouts)
        
    def sendData(self,data):
        SLogger.log(self.name, "checkTimeouts()", "Wysylanie danych.")
        for u in self.users:
            u.sendData(data)
            
    def checkTimeouts(self):
        SLogger.log(self.name, "checkTimeouts()", "Sprawdzanie bezczynnosci.")
        time = time.localtime()
        for u in self.users:
            if time.mktime(u.timestamp) - time.mktime(time) > self.timeout:
                SLogger.log(self.name, "checkTimeouts()", "Usuwanie " + u.login)
                del u
                
    def addUser(self, user):
        SLogger.log(self.name, "addUser()", "Dodawanie uzytkownika " + user.login)
        self.users.append(user)