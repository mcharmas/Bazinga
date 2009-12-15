import sys
from Logger import SLogger
"""
klasa zczytuje z pliku baze danych z uzytkownikami
           format linii:   user;;haslo
"""
class UserDBReader():

    userList={}

    def __init__(self):
        pass

    def getUserList(self,file):
        try:
            lines=open(file).readlines()
            for line in lines:
                if line.startswith("\n"):
                    pass
                else:
                    self.userList[line.partition(";;")[0]]=line.partition(";;")[2].replace('\n','')
        except IOError:
            SLogger.log("UserDBReader", "getUserList()", "IOError podczas czytania pliku")            
            raise IOError

    def checkUser(self,user,passwd):
        if self.userExists(user):
            if self.getUserPasswd(user,passwd):
                return True
            else:
                return False
        else:
            return False

    def userExists(self,user):
        if user in self.userList:
            return True
        else:
            return False

    def getUserPasswd(self,user,passwd):
        if self.userList[user]==passwd:
            return True
        else:
            return False

    def createUser(self,user,passwd):
        pass

    def setUserPasswd(self,user,passwd):
        pass

