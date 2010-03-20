from Group import *
from Logger import * 
import time
from threading import Timer

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
        
        #Interwal z jakim wywolywane jest sprawdzanie bezczynnosci driverow
        self.timeout = 30
        
        #Timer wywolujacy funkcje sprawdzania bezczynnosci
        self.timer = Timer(self.timeout, self.checkDriverTimeouts)        
        self.timer.start()
        
    def addDriver(self,username, host):
        """Dodaje sterownik uzytkownika."""
        Logger.log(self.name, "addDriver", "Dodaje driver "+username)
        sid = self.lastSid;
        self.lastSid+=1        
        self.drivers[username] = (sid,host,time.localtime())
        return sid
       
    def delDriver(self, id):
        """Usuwa sterownik uzytkownika."""
        Logger.log(self.name, "delDriver", "Usuwam drivera: "+str(id))
        user = self.getDriverUsername(id)
        if user:
            self.drivers.pop(user)
        
    def hasDriver(self, username):
        """Zwraca czy dany username ma zalogowany sterownik."""
        if username in self.drivers.keys():
            id,_,_ = self.drivers[username]
            return id
        return None
    
    def driverSessionExists(self, id1):
        """Zwraca hosta drivera o ile ostnieje"""
        for id2,host,_ in self.drivers.values():
            if id2 == id1:
                return host
        return False
    
    def getDriverUsername(self, id):    
        """Zwraca username drivera o danym ID sesji"""
        for username in self.drivers.keys():
            if self.drivers[username][0] == id:
                return username            
        return None
      
    def addUser(self, user, token):
        """Dodaje uzytkownika do grupy z danym tokienem o ile taka grupa istnieje."""
        Logger.log(self.name, "addUser", "Dodaje usera: "+user.login+" do grupy:"+token)        
        #user.id,user.driverHost = self.drivers.pop(user.login)         
        user.id,user.driverHost,_ = self.drivers[user.login]
        
        if not self.groups.has_key(token):
            self.groups[token] = Group(self)
        user.group = self.groups[token]      
        
        self.users[user.id] = user       
        self.groups[token].addUser(user)
        Logger.log(self.name, "addUser", "Nadany sid to: "+user.login+":"+str(self.lastSid-1))
        return user.id
    
    def delUser(self, user):
        """Usuwa uzytkownika z grupy oraz grupe jezeli jest pusta."""
        Logger.log(self.name, "delUser", "Usuwam usera: "+str(user))
        try:
            del self.users[user]
        except:
            Logger.log(self.name, "delUser", "Nie bylo usera do usuniecia.")
        
        for k in self.groups.keys():
            if self.groups[k].isEmpty():
                Logger.log(self.name, "delUser", "Usuwam pusta grupe: "+k)
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
    
    def updateDriver(self, id):
        """Updatuje timestamp drivera. Potrzebne do sprawdzania bezczynnosci."""
        username = self.getDriverUsername(id)        
        if username:
            id,host,_ = self.drivers[username]
            self.drivers[username]=(id,host,time.localtime())
    
    def checkDriverTimeouts(self):
        """Funkcja wywolywana cyklicznie, sprawdzajaca bezczynnosci sterownikow."""
        Logger.log(self.name, "checkDriverTimeouts()", "Sprawdzanie bezczynnosci.")
        t = time.localtime()
        for u in self.drivers.keys():
            id,_,timestamp = self.drivers[u]  
            self.delUser(u)
            self.delDriver(id)      
            if  time.mktime(t) - time.mktime(timestamp) >= self.timeout:            
                Logger.log(self.name, "checkTimeouts()", "Usuwanie sterownika z powodu bezczynnosci: "+u)
                
        self.timer.cancel()
        self.timer = Timer(self.timeout, self.checkDriverTimeouts)                
        self.timer.start()
        
    def closeAllGroups(self):
        """Funkcja zatrzymuje wszystkie timery, potrzebna zeby ladnie zamknac serwer."""
        for g in self.groups.keys():
            self.groups[g].timer.cancel()
            

