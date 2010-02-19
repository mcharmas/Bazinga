from UserDBReader import *
"""
 autoryzacja uzytkownika
"""

class UserAuthenticator():
    """Klasa autentykujaca uzytkownika po loginie i hasle."""

    def __init__(self):
        """Konstruktor."""
        ##Obiekt czytajacy z bazy danych
        self.user=UserDBReader()

    def checkUser(self,user,passwd):
        """Sprawdza czy nazwa uzytkownika i haslo sie zgadzaja."""
        return self.user.checkUser(user,passwd)

