from Packet import *
from Logger import *
from User import * 
from UserAuthenticator import *
from UserGroupManager import *


"""
klasa parsujaca dane przychodzace do servera
"""
class Parser:
    def __init__(self):        
        self.classname = "Parser"
        self.groupManager = UserGroupManager()
        self.authenticator = UserAuthenticator()
    
    def handleData(self,data, client):
        p = Packet(data)
        if p.command == Packet.Communicates.SREQ:
            if p.source == Packet.Sources.DRIVER:
                self.loginDriver(p, client)
            elif p.source == Packet.Sources.APPLICATION:
                self.loginApplication(p, client)
        elif p.command == Packet.Communicates.CHECK:
            self.check(p, client)
        elif p.command == Packet.Communicates.CLOSE:
            self.close(p, client)
        elif p.command == Packet.Communicates.OBJECT or p.command == Packet.Communicates.OTHER:
            self.normalContent(p, client) 
                                                           
    def loginDriver(self, packet, client):
        SLogger.log(self.classname, "loginDriver", "Dostalem dane do logowania sterownika.")
    
    def loginApplication(self, packet, client):
        user,passwd = packet.content.split(':')
        SLogger.log(self.classname, "loginApplication", "Dostalem dane do logowania aplikacji: " + user + ' ' + passwd)        
        correct = self.authenticator.checkUser(user, passwd)
        
    
    def check(self, packet, client):
        SLogger.log(self.classname, "check", "Dostalem request do synchronizacji sesji.")
    
    def close(self, packet, client):
        SLogger.log(self.classname, "close", "Dostalem request do zakonczenia sesji.")
    
    def normalContent(self, packet, client):
        SLogger.log(self.classname, "close", "Dostalem normalne dane do popchniecia dalej.")
    
        
    
    