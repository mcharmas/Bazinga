import sys
from Logger import SLogger

class ConfigReader():
"""
format pliku konfiguracyjnego: 
         klucz;;wartosc         

przed rozpoczeciem czytania, nalezy ustawic plik konfiguracyjny!

"""

    def __init__(self,name):
        self.fileName=name        #nazwa pliku konfiguracyjnego
        self.dataArray={}
        self.lines=""
        self.readFromFile()

    
    def readFromFile(self):
        """odczyt z podanego pliku
        
        """
        try:
            lines=open(self.fileName).readlines()
            for line in lines:
                if line.startswith("\n"):
                    pass
                else:
                    self.dataArray[line.partition(";;")[0]]=line.partition(";;")[2].replace('\n','')
        except IOError:
            SLogger.log("ConfigReader", "readFromFile()", "IOError podczas czytania pliku")
            raise IOError


    def getdataArray(self):
        return self.dataArray

    def setConfigItem(self,key,value):
        """ustawia zadana wartosc dla klucza.
        jesli klucz istnial wczesniej, zostanie nadpisany, jesli nie zostanei utworzony
        po tej operacji, plik konfiguracyjny zostanie nadpisany
        
        """
        print"SET: ", key,"=>", value
        if key in self.dataArray:
            self.dataArray[key]=value
        else:
            self.dataArray[key]=value
        self.saveToFile()

    
    def saveToFile(self):
        """zapis stanu tablicy do pliku
        
        """
        try:
            file=open(self.fileName, 'w')
            for k,v in self.dataArray.items():
                #print "pozycja:" , k,v
                file.write(k+";;"+v+"\n")
        except IOError:
            SLogger.log("ConfigReader", "saveToFile()", "IOError podczas zapisu do pliku")
            raise IOError
        file.close()
    
    def getConfigItem(self, key):
        """zwraca wartosc dla zadanego klucza, badz False, jesli taki klucz nie istnieje
        
        """
        if key in self.dataArray:
            return self.dataArray[key]
        else:
            return False