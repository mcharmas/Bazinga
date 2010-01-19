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
    def __init__(self, manager, id=0):
        self.users = []
        self.manager = manager
        self.timeout = 1
        self.id = id
        self.name = "Group("+str(id)+")"
        self.timer = Timer(self.timeout, self.checkTimeouts)        
        self.timer.start()
        
    def sendData(self,data):
        SLogger.log(self.name, "checkTimeouts()", "Wysylanie danych.")
        for u in self.users:
            u.sendData(data)
            
    def checkTimeouts(self):
        SLogger.log(self.name, "checkTimeouts()", "Sprawdzanie bezczynnosci.")
        t = time.localtime()
        for u in self.users:            
            if  time.mktime(t) - time.mktime(u.timestamp) >= self.timeout:            
                SLogger.log(self.name, "checkTimeouts()", "Usuwanie uzytkownika z powodu bezczynnosci " + u.login)
                self.manager.delUser(u.id)
                self.users.remove(u)
        self.timer.cancel()
        self.timer = Timer(self.timeout, self.checkTimeouts)
        self.timer.start()
               
                
    def addUser(self, user):
        SLogger.log(self.name, "addUser()", "Dodawanie uzytkownika " + user.login)
        self.users.append(user)
        
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
      