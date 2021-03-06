from Packet import *
from Logger import *
from User import User 
from UserAuthenticator import *
from UserGroupManager import *
from threading import Timer
import socket



class Parser:
    """Klasa parsujaca dane przychodzace do servera."""
    
    def __init__(self):
        """Konstruktor."""
        Logger.log("Parser", "INIT", "Jestem tworzony.")
        
        ##Nazwa klasy potrzebna do loggera
        self.classname = "Parser"
        
        ##Manager grup
        self.groupManager = UserGroupManager()
        
        ##Authenticator
        self.authenticator = UserAuthenticator()
        
        ##Socket ktorym sa wysylane dane do userow
        self.dataSenderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #wszystko idzie przez ten socket... to chyba nie do konca dorbze
    
    def handleData(self,data, client):
        """Dokonuje podstawowego podzialu danych do przetworzenia dalej. Tutaj wykonywany jest poczatek parsowania pakietu."""

        try:                 
            p = Packet(data)            
        except:
            Logger.log(self.classname, "handleData", "Blad podczas parsowania pakietu. pakiet zignorowany.")
            
        if p.command == Communicates.SREQ:
            if p.source == Sources.DRIVER:
                self.loginDriver(p, client)
            elif p.source == Sources.APPLICATION:
                self.loginApplication(p, client)
        elif p.command == Communicates.CHECK:
            if p.source == Sources.DRIVER:
                self.checkDriver(p, client)
            elif p.source == Sources.APPLICATION:
                self.checkApplication(p, client)
            #self.check(p, client)
        elif p.command == Communicates.CLOSE:
            if p.source == Sources.APPLICATION:
                self.closeApplication(p, client)
            elif p.source == Sources.DRIVER:
                self.closeDriver(p, client)
        elif p.command == Communicates.OBJECT or p.command == Communicates.OTHER:
            self.normalContent(p, client)
    
    def loginDriver(self, packet, client):
        """Oblsuguje logowanie sterownika w bardzo skomplikowany i zawily sposob...
        1) sprawdza czy dobry login i haslo
        2) jesli tak - dadaje sie do listy driverow (oczekujace na polaczenie klienta)
        3) jesli nie to olewa, olewanie jest dobre        
        """                                                       

        Logger.log(self.classname, "loginDriver", "Otrzymano dane do logowania sterownika.")
        try:
            user,passwd,port = packet.content.split(':')
            port = int(port)
        except ValueError:
            Logger.log(self.classname, "loginDriver", "Blad zawartosci pakietu. Pakiet porzucony.")
            return
        
        id = self.groupManager.getUserByLogin(user)
        if id:
            self.loginApplication(packet, client)
            return
         
        correct = self.authenticator.checkUser(user, passwd)
        h = (client[0], port)
        if correct:
            Logger.log(self.classname, "loginDriver", "haslo i login poprawne,")            
            id = self.groupManager.hasDriver(user) 
            if not id:                
                Logger.log(self.classname, "loginDriver", "Ten driver nie jest zarejestrowany. Dodaje do driverow.")
                id = self.groupManager.addDriver(user, h)
            else:
                Logger.log(self.classname, "loginDriver", "Ten driver byl juz zarejestrowany. Wysylam ACK.")
                                
            p = Packet.packetFromContent(id, Sources.SERVER, 0, Communicates.SACK, str(0)).toString()   
            self.dataSenderSocket.sendto(p, h)       
        else:
            Logger.log(self.classname, "loginDriver", "Zle haslo i/lub login... User zignorowany.")
            p = Packet.packetFromContent(0, Sources.SERVER, 0, Communicates.SDEN, str(0)).toString()   
            self.dataSenderSocket.sendto(p, h)       
            
    
    def loginApplication(self, packet, client):
        """Obsluguje logowanie klienta w jeszcze bardziej skomplikowany sposob:
        1)sprawdza login i haslo
        2)jesli ok:
                3)sprawdza czy user ma drivera, jesli ok:
                    dodaje do grupy, nadaje sid i wysyla ACK
                  nie ok:
                    wysyla SDEN z info "NO DRIVER" (sprawdzajac czy przypadkiem wczesniej nie byl zalogowany)
        4) jesli dupne login i haslo to wysyla SDEN z info "BAD CREDENTIALS"        
        """                        
        Logger.log(self.classname, "loginApplication", "Dostalem dane do logowania aplikacji.")
        try:
            user,passwd,port,token = packet.content.split(':')        
            client = (client[0], int(port))
        except:
            Logger.log(self.classname, "loginApplication", "Blad zawartosci pakietu. Pakiet porzucony.")
            return            
                
        correct = self.authenticator.checkUser(user, passwd)
        if correct:
            if self.groupManager.hasDriver(user):
                Logger.log(self.classname, "loginApplication", "Dane OK. odsylam potwierdzenie...")
                u = User.User(0, user, passwd, client, self.dataSenderSocket)
                sid = self.groupManager.addUser(u, token)
                p = Packet.packetFromContent(sid, Sources.SERVER, 0, Communicates.SACK, str(sid)).toString()
                u.sendData(p)
            else:
                #moze jest juz zalogowany?
                id = self.groupManager.getUserByLogin(user)
                if id: #o kurde... jest juz zalogowany
                    u = User.User(id, user, passwd, client, self.dataSenderSocket)
                    u.sendData(Packet.packetFromContent(id, Sources.SERVER, 0, Communicates.SACK, str(id)).toString())
                    Logger.log(self.classname, "loginApplication", "User byl juz zalogowany! Wyslalem jeszcze raz SACK")
                else:
                    Logger.log(self.classname, "loginApplication", "Dupa... nie ma drivera.")
                    u = User.User(0, None, None, client, self.dataSenderSocket)                        
                    u.sendData(Packet.packetFromContent(0, Sources.SERVER, 0, Communicates.SDEN, "NO DRIVER").toString())
        else:
                Logger.log(self.classname, "loginApplication", "Dupa... zle credentiale.")
                u = User.User(0, user, passwd, client, self.dataSenderSocket)                
                p = Packet.packetFromContent(0, Sources.SERVER, 0, Communicates.SDEN, "BAD CREDENTIALS").toString()
                u.sendData(p)

    def checkDriver(self, packet, client):
        """ASDF, Szymon napisal, Szymon wie co to robi, pytac Szymona"""
        Logger.log(self.classname, "checkDriver", "Dostalem request do synchronizacji sesji drivera.")
        dhost = self.groupManager.driverSessionExists(packet.id)
        p = None
        if dhost:
            Logger.log(self.classname, "checkDriver", "Odsylam driverowi CONFIRM i robie UPDATE")
            p = Packet.packetFromContent(packet.id, Sources.SERVER, 0, Communicates.CONFIRM, "").toString()
            h = dhost
            self.groupManager.updateDriver(packet.id)
            self.dataSenderSocket.sendto(p, dhost)
        else:
            self.checkApplication(packet, client)
        
    
    def checkApplication(self, packet, client):
        """Obsluguje rzadnie check. Aktualizuje klienta w grupie zeby potwierdzic ciaglosc polaczenia oraz odsyla confirm do klienta."""
        Logger.log(self.classname, "check", "Dostalem request do synchronizacji sesji klienta.")
        
        u = self.groupManager.getUser(packet.id)
        if u:
            u.update()
            p = Packet.packetFromContent(packet.id, Sources.SERVER, 0, Communicates.CONFIRM, "")
            u.sendData(p.toString())
            u.sendDataToDriver(p.toString())
            Logger.log(self.classname, "check", "Zupdatowalem i wyslalem confirma...")
        else:     
            Logger.log(self.classname, "check", "Ups... nie ma takiego  klienta.")
    
    def closeApplication(self, packet, client):
        """Konczy sesje z uzytkownikiem usuwajac go rowniez z grupy."""
        Logger.log(self.classname, "closeApplication", "Dostalem request do zakonczenia sesji.")
        try:
            u = self.groupManager.getUser(packet.id)
            if u:
                #u.group.delUser(self.groupManager.getUser(packet.id)) #to jest brzyyyyyyydkie
                self.groupManager.delUser(u)
        except KeyError:
            Logger.log(self.classname, "closeApplication", "UPS Najwyrazniej nie ma takiego  klienta.")
        Logger.log(self.classname, "closeApplication", "I po krzyku.")
        
    def closeDriver(self, packet, client):
        """Zamyka sesje drivera zamykajac wczesniej sesje aplikacji."""
        Logger.log(self.classname, "closeApplication", "Dostalem request do zakonczenia sesji drivera.")
        self.closeApplication(packet, client)
        self.groupManager.delDriver(packet.id)
        p = Packet.packetFromContent(packet.id, Sources.SERVER, 0, Communicates.CONFIRM, "")
        Logger.log(self.classname, "closeApplication", "Dostalem request do zakonczenia sesji drivera.")
    
    def normalContent(self, packet, client):
        """Obslugiwanie pakietow z normalna zawartoscia czyli do rozeslania dalej.
        Rozsyla dane po uzytkownikach grupy nadawcy pakietu oraz uaktualnia timestamp z ostatnia aktywnoscia uzytkownika.         
        """        
        Logger.log(self.classname, "normalContent", "Dostalem normalne dane do popchniecia dalej.")
        u = self.groupManager.getUser(packet.id)
        if u:
            u.update()
            packet.source = Sources.SERVER
            packet.repack()
            u.group.sendData(packet.toString())
            Logger.log(self.classname, "normalContent", "Polecialo...")
        else:
            Logger.log(self.classname, "normalContent", "UPS Najwyrazniej nie ma takiego klienta.")

    
        
    
    
