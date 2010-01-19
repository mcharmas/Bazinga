from Group import *

class UserGroupManager:
    def __init__(self):
        self.drivers = [] #drivery bez klientow...
        self.users = {} #userzy po sidach
        self.groups = {} #grupy po tokenie
        self.lastSid = 1
        
    def addDriver(self,username):
        self.drivers.append(username)
        
    def hasDriver(self, username):
        if username in self.drivers:
            return True
        return False
    
    def addUser(self, user, token):
        self.drivers.remove(user.login)
        user.id = self.lastSid
        self.lastSid+=1 
        
        if not self.groups.has_key(token):
            self.groups[token] = Group(self)
        user.group = self.groups[token]        
        
        self.users[user.id] = user       
        self.groups[token].addUser(user)
        return self.lastSid-1
    
    def delUser(self, user):
        del self.users[user]
        
    def getUser(self, id):
        return self.user[id]
    
            
        
    
        