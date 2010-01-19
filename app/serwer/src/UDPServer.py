# -*- coding: UTF-8 -*-   

#import socket
import threading
import SocketServer
from Logger import SLogger
from Parser import *

class ThreadedUDPRequestHandler(SocketServer.BaseRequestHandler):
    """
    klasa odpowiedzialna za obsługiwanie requestów serwera UDP
    """
    
    parser = Parser()
    
    def handle(self):        
        """
        funkcja obslugujaca request serwera UDP
        """
        data = self.request[0]
        SLogger.log("ThreadedUDPRequestHandler", "handle", "Cos dostalem i daje parserowi.")        
        ThreadedUDPRequestHandler.parser.handleData(data, self.client_address)                                        
                
                   

class ThreadedUDPServer(SocketServer.ThreadingMixIn, SocketServer.UDPServer):
    """
    klasa utworzona sztucznie zeby wymusic serwer na watkach
    """
    pass


class UDPServer:
    """
    klasa przetrzymująca serwer i główny wątek
    """
    def __init__(self, host, port):
        self.name = "UDPServer"
        self.addr = (host,port)
        self.server = ThreadedUDPServer(self.addr, ThreadedUDPRequestHandler)
        self.server_thread = None
        SLogger.log(self.name, "__init__", "utworzono serwer")
        

    def start(self):
        """
        startuje serwer, w przypadku gdy juz byl uruchomiony wyrzuca wyjatek Exception("Already started")
        """
        if self.server_thread:
            SLogger.log(self.name, "start", "startowanie nie udane, serwer juz dzialal")
            raise Exception("Already started")
        self.server_thread = threading.Thread(target = self.server.serve_forever())
        self.server_thread.start()
        SLogger.log(self.name, "start", "serwer wystartowany")
        
    
    def shutdown(self):
        """
        wyłącza serwer (jezeli był uruchomiony)
        """
        if self.server_thread:            
            self.server.shutdown()
            self.server_thread = None
            SLogger.log(self.name, "shutdown", "serwer wylaczony")        
        SLogger.log(self.name, "shutdown", "serwer wczesniej nie dzialal")

if __name__ == "__main__":
    """
    testuje sam serwer
    """
    try:
        s = UDPServer('', 1234)
        s.start()
    except KeyboardInterrupt:
        s.shutdown()