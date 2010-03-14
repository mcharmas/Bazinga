from Group import *
from Logger import * 
"""
TODO: wypierdzielac puste grupy!
TODO: wypierdzielac drivery po jakims czasie!
"""
class UserGroupManager:
    """Klasa ta jest menagerem uzytkownikow, grup i sterownikow. Gdy uzytkownik jest podlaczany ta klasa zarzadza do jakiej grupy idzie.
    Klasa dba tez o to aby puste grupy byly usuwane.    
    """
    def __init__(self):
        """Konstruktor"""
        ##Drivery ktore jeszcze nie maja klientow.
        self.drivers = {}
        
        ##Zalogowani uzytkownicy po session ID
        self.users = {}
        
        ##Tablica grup po tokenie
        self.groups = {}
        
        ##Ostatni uzyty SID, za kazdym razem przyznawany jest kolejny
        self.lastSid = 1
        
        ##Nazwa klasy potrzeban do logowania
        self.name = "UserGroupManager"
        
    def addDriver(self,username, host):
        """Dodaje sterownik uzytkownika"""
        Logger.log(self.name, "addDriver", "Dodaje driver "+username)
        sid = self.lastSid;
        self.lastSid+=1        
        self.drivers[username] = (sid,host)
        return sid
        
        
    def hasDriver(self, username):
        """Zwraca czy dany username ma zalogowany sterownik."""
        if username in self.drivers.keys():
            id,_ = self.drivers[username]
            return id
        return None
    
    def driverSessionExists(self, id1):
        for id2, host in self.drivers.values():
            if id2 == id1:
                return host
        return False
    
    def addUser(self, user, token):
        """Dodaje uzytkownika do grupy z danym tokienem o ile taka grupa istnieje."""
        Logger.log(self.name, "addUser", "Dodaje usera: "+user.login+" do grupy:"+token)        
        user.id,user.driverHost = self.drivers.pop(user.login)         
        
        if not self.groups.has_key(token):
            self.groups[token] = Group(self)
        user.group = self.groups[token]      
        
        self.users[user.id] = user       
        self.groups[token].addUser(user)
        Logger.log(self.name, "addUser", "Nadany sid to: "+user.login+":"+str(self.lastSid-1))
        return user.id
    
    def delUser(self, user):
        """Usuwa uzytkownika z grupy oraz grupe jezeli jest pusta."""
        Logger.log(self.name, "addUser", "Usuwamm usera: "+str(user))
        del self.users[user]
        for k in self.groups.keys():
            if self.groups[k].isEmpty():
                Logger.log(self.name, "addUser", "Usuwam pusta grupe: "+k)
                del self.groups[k]
            
        
    def getUser(self, id):
        """Zwraca uzytkownika o danym ID."""
        try:
            return self.users[id]
        except:
            return None
            
    def getUserByLogin(self, login):
        """Zwraca uzytkownika o danym loginie"""
        for u in self.users.values():
            if u.login == login:
                return u.id
            
        return None
