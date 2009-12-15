import User
import time

class Group():
    def __init__(self):
        self.users = []
        self.timeout = 500
        
    def sendData(self,data):
        for u in self.users:
            u.sendData(data)
            
    def checkTimeouts(self):
        time = time.localtime()
        for u in self.users:
            if time.mktime(u.timestamp) - time.mktime(time) > self.timeout:
                del u