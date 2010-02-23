# -*- coding: UTF-8 -*-   

#import socket
import threading
import SocketServer
from Logger import *
from Parser import *

class ThreadedUDPRequestHandler(SocketServer.BaseRequestHandler):
    """Klasa odpowiedzialna za obsługiwanie requestów serwera UDP."""
    
    ##Statyczny parser uzywany do parsowania wszystkich danych.
    parser = Parser()
    
    def handle(self):        
        """Funkcja obslugujaca request serwera UDP.
        Popycha dane dalej do parsera ktory sie zajmuje reszta.
        """
        data = self.request[0]
        Logger.log("ThreadedUDPRequestHandler", "handle", "Dane otrzymane o przekazane do Parsera.")
        ThreadedUDPRequestHandler.parser.handleData(data, self.client_address)                                        
                
                   

class ThreadedUDPServer(SocketServer.ThreadingMixIn, SocketServer.UDPServer):
    """Klasa utworzona sztucznie zeby wymusic serwer na watkach."""
    pass


class UDPServer:
    """Klasa przetrzymująca serwer i główny wątek."""
    def __init__(self, host, port):
        """Konstruktor przyjmujacy host i port na ktorym serwer ma nasluchiwac."""
        ##Nazwa klasy uzywana do logowania
        self.name = "UDPServer"
        
        ##Adres i port na ktorym serwer ma sluchac.
        self.addr = (host,port)
        
        ##Serwer
        self.server = ThreadedUDPServer(self.addr, ThreadedUDPRequestHandler)
        
        ##Watek serwera
        self.server_thread = None
        
        Logger.log(self.name, "__init__", "utworzono serwer")
        

    def start(self):
        """Startuje serwer, w przypadku gdy juz byl uruchomiony wyrzuca wyjatek Exception("Already started")."""
        if self.server_thread:
            Logger.log(self.name, "start", "startowanie nie udane, serwer juz dzialal")
            raise Exception("Already started")
        self.server_thread = threading.Thread(target = self.server.serve_forever())
        self.server_thread.start()
        Logger.log(self.name, "start", "serwer wystartowany")
        
    
    def shutdown(self):
        """Wyłącza serwer (jezeli był uruchomiony).
        TODO: To jest do poprawienia. Zawsze wydaje mu sie ze serwer nie dziala...
        """
        if self.server_thread:            
            self.server.shutdown()
            self.server_thread = None
            Logger.log(self.name, "shutdown", "serwer wylaczony")        
        Logger.log(self.name, "shutdown", "serwer wczesniej nie dzialal")
