from Logger import *

class UserDBReader:
    """Klasa zczytuje z pliku baze danych z uzytkownikami
    format linii:   user;;haslo
    Plik musi znajdowac sie w katalogu z ktorego odpalamy serwer.
    TODO: dodac mozliwosc przekazania pliku konfiguracyjnego jako parametr i zmienic domysle polozenie
    
    """
    
    def __init__(self):
        """Konstruktor."""
        ##Mapa uzytkownikow z haslami
        self.userList={}
        self.getUserList('users.conf')

    def getUserList(self,file):
        """Pobiera z pliku liste uzytkownikow."""
        try:
            lines=open(file).readlines()
            for line in lines:
                if line.startswith("\n"):
                    pass
                else:
                    self.userList[line.partition(";;")[0]]=line.partition(";;")[2].replace('\n','')
        except IOError:
            Logger.log("UserDBReader", "getUserList()", "IOError podczas czytania pliku")            
            raise IOError

    def checkUser(self,user,passwd):
        """Sprawdza czy login i haslo uzytkownika sie zgadzaja oraz pod warunkiem ze uzytkownik istnieje."""        
        Logger.log("UserDBReader", "checkUser()", "sprawdzam usera: " + user + " haslo: ***")
        if self.userExists(user):
            if self.getUserPasswd(user,passwd):
                Logger.log("UserDBReader", "checkUser()", "Wow! Jest OK!")
                return True
            else:
                Logger.log("UserDBReader", "checkUser()", "Eee... Zle!")
                return False
        else:
            return False

    def userExists(self,user):
        """Sprwadza czy uzytkownik w bazie istnieje."""
        if user in self.userList:
            return True
        else:
            return False

    def getUserPasswd(self,user,passwd):
        """Sprawdza czy nazwa uzytkownika i haslo zgadzaja sie bez kontroli czy uzytkownik istnieje."""
        if self.userList[user]==passwd:
            return True
        else:
            return False

