import User
import time
from threading import Timer
from Logger import *

class Group():
    """Grupa przechowujaca userow.
    Posiada timer sprawdzajacy co timeout bezczynnosc userow po ich timestampach
    po bezczynnosci user jest usuwany
    
    TODO: wysylac odnowienie polaczenia    
    """
    def __init__(self, manager, id=0):
        """Konstruktor"""
        ##Tablica uzytkownikow
        self.users = []
        ##Manager danej grupy
        self.manager = manager
        ##Timeout po ktorym uzytkownik jest rozlaczany
        self.timeout = 30
        ##Id grupy
        self.id = id
        ##Nazwa potrzebna do debugowania
        self.name = "Group("+str(id)+")"
        ##Timer wywolujacy funkcje czyszczenia grupy z bezczynnych uzytkownikow
        self.timer = Timer(self.timeout, self.checkTimeouts)        
        self.timer.start()
        
    def sendData(self,data):
        """Funkcja wysylajaca dane do wszystkich z grupy."""
        Logger.log(self.name, "sendData()", "Wysylanie danych.")
        for u in self.users:
            u.sendData(data)
            
    def checkTimeouts(self):
        """Funkcja wywolywana cyklicznie, sprawdzajaca bezczynnosci uzytkownikow."""
        Logger.log(self.name, "checkTimeouts()", "Sprawdzanie bezczynnosci.")
        t = time.localtime()
        for u in self.users:            
            if  time.mktime(t) - time.mktime(u.timestamp) >= self.timeout:            
                Logger.log(self.name, "checkTimeouts()", "Usuwanie uzytkownika z powodu bezczynnosci " + u.login)
                self.manager.delUser(u.id)
                self.users.remove(u)
        self.timer.cancel()
        self.timer = Timer(self.timeout, self.checkTimeouts)
        if len(self.users):            
            self.timer.start()
               
                
    def addUser(self, user):
        """Dodaje usera do grupy."""        
        Logger.log(self.name, "addUser()", "Dodawanie uzytkownika " + user.login)
        self.users.append(user)
        if not self.timer.isAlive():
            self.timer.start()
        
    def delUser(self, user):
        """Usuwa usera z grupy."""
        Logger.log(self.name, "delUser()", "Usuwanie uzytkownika bo sam tego chce " + user.login)
        self.manager.delUser(user.id)
        self.users.remove(user)
        
    def isEmpty(self):
        """Zwraca czy grupa jest pusta."""
        if len(self.users):
            return True
        return False
        
if __name__ == "__main__":
    g = Group()
    u1 = User.User(0, "dupa", "Jasio", g, ('localhost',1234), None)
    u2 = User.User(1, "dupa1", "Jasio1", g, ('localhost',1234), None)
    u1.update()
    g.addUser(u1)
    time.sleep(5)    
    u2.update()  
    g.addUser(u2)
    time.sleep(2)
