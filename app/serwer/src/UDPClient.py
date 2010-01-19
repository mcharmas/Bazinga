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
    
    loginDriverPacket = Packet.packetFromContent(0, Packet.Sources.DRIVER, 0, Packet.Communicates.SREQ, "dupa:jasio")
    loginAppPacket = Packet.packetFromContent(0, Packet.Sources.APPLICATION, 0, Packet.Communicates.SREQ, "dupa:jasio:9999:test")
    
        
    #sock.sendto(loginDriverPacket.toString(), (HOST, PORT))
    sock.sendto(loginAppPacket.toString(), (HOST, PORT))
