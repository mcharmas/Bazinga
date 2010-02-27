import struct

class Sources:
    """Klasa trzymajaca ENUM z typami zrodel.
    DRIVER, APPLICATION, SERVER
    """                
    DRIVER, APPLICATION, SERVER = range(3)
    
class Communicates:
    """Klasa trzymajca ENUM z typami komunikatow.
    SREQ, SACK, SDEN,CHECK, CONFIRM, UPDATE, CLOSE, OBJECT, OTHER, ERROR
    """     
    SREQ, SACK, SDEN,CHECK, CONFIRM, UPDATE, CLOSE, OBJECT, OTHER, ERROR = range(10)

class Packet:
    """Klasa trzymajaca pakiet podzielony na czesci."""    

    ##Format danych przesnylanych przez siec: int(id), (byte)source, int(timestamp), byte(command),short(length),dane
    #int(id), (byte)source, int(timestamp), byte(command),short(length)
    fmt = "ibibh" 
            
    def __init__(self, data=""):
        """Konstruktor ktory jak dostanie dane rozklada pakiet na czesci."""            
        ##Niesformatowany pakiet
        self.data = data
        
        ##Id sesji
        self.id = ""
        
        ##Zrodlo (DRIVER, APPLICATION, SERVER)
        self.source = ""
        
        ##Timestamp wyslania pakietu
        self.timestamp = ""
        
        ##Komenda (SREQ, SACK, SDEN,CHECK, CONFIRM, UPDATE, CLOSE, OBJECT, OTHER, ERROR)
        self.command = ""
        
        ##Wielkosc pakietu
        self.length = ""
        
        ##Zawartosc pakietu
        self.content = ""
        if data:
            self.id,self.source,self.timestamp,self.command, self.length = struct.unpack(Packet.fmt,data[0:struct.calcsize(Packet.fmt)])
            self.content =  data[struct.calcsize(Packet.fmt):]
        
    def packetFromCont(id,source,timestamp,command,content):
        """Statyczna metoda ktora jest mapowana na funkcje statyczna (packetFromContent)
        podajemy jej wszystkie pola pakietu a ona generuje pakiet na ich podstawie.
        """
        p = Packet()
        p.id = id
        p.source = source
        p.timestamp = timestamp
        p.command = command
        p.length = len(content)        
        p.content =  content     
        p.repack()
        return p
    
    ##Metoda statyczna, zobacz packetFromCont
    packetFromContent = staticmethod(packetFromCont)
        
    def repack(self):
        """Funkcja sluzaca do ponownego zapakowania wszystkich danych."""
        self.data = struct.pack(Packet.fmt,self.id,self.source,self.timestamp,self.command,len(self.content))+self.content
        
    def debug(self):
        return str(self.id)+" "+str(self.source)+" "+str(self.timestamp)+" "+str(self.command)+" "+str(self.length)+" "+self.content
        
    def toString(self):
        """Funckcja zwracajaca zapakowany pakiet."""
        self.repack()
        return self.data

if __name__ == "__main__":    
    dataToSend = "to jest test"
    p = Packet.packetFromContent(1,2,3,4,dataToSend)
    p1 = Packet(p.toString())
    p1.debug()
    