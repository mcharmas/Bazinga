'''
Created on 2010-01-20

@author: orbit
'''
import socket, traceback
from Packet import *

if __name__ == '__main__':
    host = 'localhost'
    port = 9999

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((host, port))

    while 1:
        try:
            message, address = s.recvfrom(8192)
            print "Got data from", address
            p = Packet(message)
            print p.debug()
        except (KeyboardInterrupt, SystemExit):
            raise
        except:
            traceback.print_exc()    