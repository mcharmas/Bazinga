'''
Created on 2009-12-14

@author: orbit
'''

from Packet import *
import sys
import socket

if __name__ == "__main__":
    HOST, PORT = "localhost", 1234    
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    loginDriverPacket = Packet.packetFromContent(0, Packet.Sources.DRIVER, 0, Packet.Communicates.SREQ, "dupa:jasio:9999")
    loginAppPacket = Packet.packetFromContent(0, Packet.Sources.APPLICATION, 0, Packet.Communicates.SREQ, "dupa:jasio:9999:test")
    checkPacket = Packet.packetFromContent(2, Packet.Sources.APPLICATION, 0, Packet.Communicates.CHECK, "")
    normalContent = Packet.packetFromContent(2, Packet.Sources.DRIVER, 0, Packet.Communicates.OBJECT, "to sa jakies pierdoly.... i jeszcze wieksze peirdoly")
    
        
    #sock.sendto(loginDriverPacket.toString(), (HOST, PORT))
    #sock.sendto(loginAppPacket.toString(), (HOST, PORT))
    #sock.sendto(checkPacket.toString(), (HOST, PORT))
    sock.sendto(normalContent.toString(), (HOST, PORT))
