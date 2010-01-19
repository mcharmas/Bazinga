from Packet import *
from Logger import *
from User import User 
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
        self.dataSenderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #wszystko idzie przez ten socket... to chyba nie do konca dorbze
    
    """
    to handluje date jak nazwa wskazduje (wywoluje inne funkcje dla poszczegolnych komunikatow i zrodel)
    """
    def handleData(self,data, client):
        try:                 
            p = Packet(data)            
        except:
            SLogger.log(self.classname, "handleData", "Cos poszlo nie tak z parsowanie pakietu. Olewamy! (Kochamy UDP:P)")
            
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
    
    """
    oblsuguje logowanie sterownika w bardzo skomplikowany i zawily sposob...
    1) sprawdza czy dobry login i haslo
    2) jesli tak - dadaje sie do listy driverow (oczekujace na polaczenie klienta)
    3) jesli nie to olewa, olewanie jest dobrze
    TODO: mozna by sprawdzac czy przypadkiem user nie jest zalogowany bo takie cyrki moga sie zdazyc...
    """                                                       
    def loginDriver(self, packet, client):
        SLogger.log(self.classname, "loginDriver", "Dostalem dane do logowania sterownika.")
        try:
            user,passwd = packet.content.split(':')
        except ValueError:
            SLogger.log(self.classname, "loginDriver", "Blad zawartosci pakietu, olewam")
            return
                    
        correct = self.authenticator.checkUser(user, passwd)
        if correct:
            SLogger.log(self.classname, "loginDriver", "Fpytke haslo i login, dodaje do driverow.")
            self.groupManager.addDriver(user)            
        else:
            SLogger.log(self.classname, "loginDriver", "Zle haslo i/lub login... Olewam sprawe.")
            
    
    """
    obsluguje logowanie klienta w jeszcze bardziej skomplikowany sposob:
    1)sprawdza login i haslo
    2)jesli ok:
            3)sprawdza czy user ma drivera, jesli ok:
                dodaje do grupy, nadaje sid i wysyla ACK
              nie ok:
                wysyla SDEN z info "NO DRIVER" (sprawdzajac czy przypadkiem wczesniej nie byl zalogowany)
    4) jesli dupne login i haslo to wysyla SDEN z info "BAD CREDENTIALS"
    """                        
    def loginApplication(self, packet, client):
        SLogger.log(self.classname, "loginApplication", "Dostalem dane do logowania aplikacji.")
        try:
            user,passwd,port,token = packet.content.split(':')        
            client = (client[0], int(port))
        except:
            SLogger.log(self.classname, "loginApplication", "Blad zawartosci pakietu. Olewam.")
            return            
                
        correct = self.authenticator.checkUser(user, passwd)
        if correct:
            if self.groupManager.hasDriver(user):
                SLogger.log(self.classname, "loginApplication", "Wszystko fpyte, jest driver, odsylam info ze spoko")
                u = User.User(0, user, passwd, client, self.dataSenderSocket)
                sid = self.groupManager.addUser(u, token)
                u.sendData(Packet.packetFromContent(sid, Packet.Sources.SERVER, 0, Packet.Communicates.SACK, str(sid)).toString())
            else:
                #moze jest juz zalogowany?
                id = self.groupManager.getUserByLogin(user)
                if id: #o kurde... jest juz zalogowany
                    u = User.User(id, user, passwd, client, self.dataSenderSocket)
                    u.sendData(Packet.packetFromContent(id, Packet.Sources.SERVER, 0, Packet.Communicates.SACK, str(id)).toString())
                    SLogger.log(self.classname, "loginApplication", "User byl juz zalogowany! Wyslalem jeszcze raz SACK")
                else:
                    SLogger.log(self.classname, "loginApplication", "Dupa... nie ma drivera.")
                    u = User.User(0, None, None, client, self.dataSenderSocket)                        
                    u.sendData(Packet.packetFromContent(0, Packet.Sources.SERVER, 0, Packet.Communicates.SDEN, "NO DRIVER").toString())
        else:
                SLogger.log(self.classname, "loginApplication", "Dupa... zle credentiale.")
                u = User.User(0, user, passwd, client, self.dataSenderSocket)
                u.sendData(Packet.packetFromContent(sid, Packet.Sources.SERVER, 0, Packet.Communicates.SDEN, "BAD CREDENTIALS").toString())
    
    
    def check(self, packet, client):
        SLogger.log(self.classname, "check", "Dostalem request do synchronizacji sesji.")
        try:
            self.groupManager.getUser(packet.id).update()
            p = Packet.packetFromContent(packet.id, Packet.Sources.SERVER, 0, Packet.Communicates.CONFIRM, "")
            self.groupManager.getUser(packet.id).sendData(p.toString())
            SLogger.log(self.classname, "check", "Zupdatowalem i wyslalem confirma...")
        except:
            SLogger.log(self.classname, "check", "Ups... nie ma takiego  klienta.")
        
    
    def close(self, packet, client):
        SLogger.log(self.classname, "close", "Dostalem request do zakonczenia sesji.")
        try:
            self.groupManager.getUser(packet.id).grup.delUser(self.groupManager.getUser(packet.id)) #to jest brzyyyyyyydkie
        except KeyError:
            SLogger.log(self.classname, "close", "UPS Najwyrazniej nie ma takiego  klienta.")
        SLogger.log(self.classname, "close", "I po krzyku.")
    
    def normalContent(self, packet, client):
        SLogger.log(self.classname, "normalContent", "Dostalem normalne dane do popchniecia dalej.")
        try:
            packet.source = Packet.Sources.SERVER
            self.groupManager.getUser(packet.id).group.sendData(packet)
        except KeyError:
            SLogger.log(self.classname, "normalContent", "UPS Najwyrazniej nie ma takiego klienta.")
        SLogger.log(self.classname, "normalContent", "Polecialo...")
    
        
    
    