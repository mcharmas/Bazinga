from Packet import *
from Logger import *
from User import * 
from UserAuthenticator import *
from UserGroupManager import *
import socket


"""
klasa parsujaca dane przychodzace do servera
"""
class Parser:
    def __init__(self):        
        self.classname = "Parser"
        self.groupManager = UserGroupManager()
        self.authenticator = UserAuthenticator()
        self.dataSenderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
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
        user,passwd,port,token = packet.content.split(':')
        client[1] = int(port)
        SLogger.log(self.classname, "loginApplication", "Dostalem dane do logowania aplikacji: " + user + ' ' + passwd)        
        correct = self.authenticator.checkUser(user, passwd)
        if correct:
            if self.groupManager.hasDriver(user):
                u = User(0, user, passwd, client, self.dataSenderSocket)
                sid = self.groupManager.addUser(u, token)
                u.sendData(Packet.packetFromContent(sid, Packet.Sources.SERVER, 0, Packet.Communicates.SACK, str(sid)).toString())
            else:
                u = User(0, user, passwd, client, self.dataSenderSocket)
                u.sendData(Packet.packetFromContent(sid, Packet.Sources.SERVER, 0, Packet.Communicates.SDEN, "NO DRIVER").toString())
        else:
                u = User(0, user, passwd, client, self.dataSenderSocket)
                u.sendData(Packet.packetFromContent(sid, Packet.Sources.SERVER, 0, Packet.Communicates.SDEN, "BAD CREDENTIALS").toString())
    
    def check(self, packet, client):
        SLogger.log(self.classname, "check", "Dostalem request do synchronizacji sesji.")
    
    def close(self, packet, client):
        SLogger.log(self.classname, "close", "Dostalem request do zakonczenia sesji.")
    
    def normalContent(self, packet, client):
        SLogger.log(self.classname, "close", "Dostalem normalne dane do popchniecia dalej.")
    
        
    
    