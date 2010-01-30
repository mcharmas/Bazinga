from UserDBReader import *
"""
 autoryzacja uzytkownika
"""

class UserAuthenticator():

    def __init__(self):
        self.user=UserDBReader()

    def checkUser(self,user,passwd):
        return self.user.checkUser(user,passwd)

