import struct

"""klasa trzymajaca pakiet podzielony na czesci"""
class Packet:
    
    """
    klasa trzymajaca ENUM z typami zrodel
    """
    class Sources:
        DRIVER, APPLICATION, SERVER = range(3)
       
    """
    klasa trzymajca ENUM z typami komunikatow
    """ 
    class Communicates:
        SREQ, SACK, SDEN,CHECK, CONFIRM, UPDATE, CLOSE, OBJECT, OTHER, ERROR = range(10)

    """
    format danych przesnylanych przez siec: int(id), (byte)source, int(timestamp), byte(command),short(length),dane
    """
    fmt = "!ibibh" #int(id), (byte)source, int(timestamp), byte(command),short(length)
            
    """
    konstruktor ktory jak dostanie dane rozklada pakiet na czesci
    """
    def __init__(self, data=""):                
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
        
    """
    metoda ktora jest mapowana na funkcje statyczna (packetFromContent)
    podajemy jej wszystkie pola pakietu a ona generuje pakiet na ich podstawie
    """
    def packetFromCont(id,source,timestamp,command,content):
        p = Packet()
        p.id = id
        p.source = source
        p.timestamp = timestamp
        p.command = command
        p.length = len(content)        
        p.content =  content     
        p.repack()
        return p
        
    """
    funkcja sluzaca do ponownego zapakowania wszystkich danych
    """
    def repack(self):
        self.data = struct.pack(Packet.fmt,self.id,self.source,self.timestamp,self.command,len(self.content))+self.content
        
    def debug(self):
        return str(self.id)+" "+str(self.source)+" "+str(self.timestamp)+" "+str(self.command)+" "+str(self.length)+" "+self.content
        
    """
    funckcja zwracajaca zapakowany pakiet
    """
    def toString(self):
        self.repack()
        return self.data
    
    packetFromContent = staticmethod(packetFromCont)
                
    
dataToSend = "to jest test"
p = Packet.packetFromContent(1,2,3,4,dataToSend)
p1 = Packet(p.toString())
p1.debug()