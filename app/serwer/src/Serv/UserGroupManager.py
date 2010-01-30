from Group import *
from Logger import * 
"""
TODO: wypierdzielac puste grupy!
TODO: wypierdzielac drivery po jakims czasie!
"""
class UserGroupManager:
    def __init__(self):
        self.drivers = {} #drivery bez klientow...
        self.users = {} #userzy po sidach
        self.groups = {} #grupy po tokenie
        self.lastSid = 1
        self.name = "UserGroupManager"
        
    def addDriver(self,username, host):
        SLogger.log(self.name, "addDriver", "Dodaje driver "+username)
        self.drivers[username] = host
        
    def hasDriver(self, username):
        if username in self.drivers.keys():
            return self.drivers[username]
        return None
    
    def addUser(self, user, token):
        SLogger.log(self.name, "addUser", "Dodaje usera: "+user.login+" do grupy:"+token)        
        driverHost = self.drivers.pop(user.login)
        user.driverHost = driverHost
        user.id = self.lastSid
        self.lastSid+=1 
        
        if not self.groups.has_key(token):
            self.groups[token] = Group(self)
        user.group = self.groups[token]      
        
        self.users[user.id] = user       
        self.groups[token].addUser(user)
        SLogger.log(self.name, "addUser", "Nadany sid to: "+user.login+":"+str(self.lastSid-1))
        return self.lastSid-1
    
    def delUser(self, user):
        SLogger.log(self.name, "addUser", "Wywalam usera: "+str(user))
        del self.users[user]
        for k in self.groups.keys():
            if self.groups[k].isEmpty():
                SLogger.log(self.name, "addUser", "Wywalam grupe: "+k+" bo jest pusta.")
                del self.groups[k]
            
        
    def getUser(self, id):
        try:
            return self.users[id]
        except:
            return None
            
    def getUserByLogin(self, login):
        for u in self.users.values():
            if u.login == login:
                return u.id
            
        return None
            
        
    
        