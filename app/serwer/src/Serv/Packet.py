import struct


class Packet:
    """
    klasa trzymajaca pakiet podzielony na czesci
    
    """    
    
    class Sources:
        """
        klasa trzymajaca ENUM z typami zrodel
        
        """
        DRIVER, APPLICATION, SERVER = range(3)
       
    class Communicates:
        """
        klasa trzymajca ENUM z typami komunikatow
        
        """     
        SREQ, SACK, SDEN,CHECK, CONFIRM, UPDATE, CLOSE, OBJECT, OTHER, ERROR = range(10)

    """
    format danych przesnylanych przez siec: int(id), (byte)source, int(timestamp), byte(command),short(length),dane
    """
    fmt = "!ibibh" #int(id), (byte)source, int(timestamp), byte(command),short(length)
            
    def __init__(self, data=""):
        """
        konstruktor ktory jak dostanie dane rozklada pakiet na czesci
            
        """            
        self.data = data
        self.id = ""
        self.source = ""
        self.timestamp = ""
        self.command = ""
        self.length = ""
        self.content = ""
        if data:
            self.id,self.source,self.timestamp,self.command, self.length = struct.unpack(Packet.fmt,data[0:struct.calcsize(Packet.fmt)])
            self.content =  data[struct.calcsize(Packet.fmt):]
        
    def packetFromCont(id,source,timestamp,command,content):
        """
        statyczna metoda ktora jest mapowana na funkcje statyczna (packetFromContent)
        podajemy jej wszystkie pola pakietu a ona generuje pakiet na ich podstawie
        
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
        
    def repack(self):
        """
        funkcja sluzaca do ponownego zapakowania wszystkich danych
            
        """

        self.data = struct.pack(Packet.fmt,self.id,self.source,self.timestamp,self.command,len(self.content))+self.content
        
    def debug(self):
        return str(self.id)+" "+str(self.source)+" "+str(self.timestamp)+" "+str(self.command)+" "+str(self.length)+" "+self.content
        
    def toString(self):
        """
        funckcja zwracajaca zapakowany pakiet

        """
        self.repack()
        return self.data
    
    packetFromContent = staticmethod(packetFromCont)
  
if __name__ == "__main__":    
    dataToSend = "to jest test"
    p = Packet.packetFromContent(1,2,3,4,dataToSend)
    p1 = Packet(p.toString())
    p1.debug()
    