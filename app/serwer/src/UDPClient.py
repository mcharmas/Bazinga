'''
Created on 2009-12-14

@author: orbit
'''
import sys
import socket

if __name__ == "__main__":
    HOST, PORT = "localhost", 1234
    data = " ".join(sys.argv[1:])
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(data + "\n", (HOST, PORT))
    
    print "Data send...."
    data = ""
    while 1:
        d = sock.recv(1024)
        if not d:
            break
        data += d 
    print data
