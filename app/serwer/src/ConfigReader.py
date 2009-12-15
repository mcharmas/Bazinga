import sys
from Logger import SLogger
"""
format pliku konfiguracyjnego: 
         klucz;;wartosc         

przed rozpoczeciem czytania, nalezy ustawic plik konfiguracyjny!
"""
class ConfigReader():


    def __init__(self,name):
        self.fileName=name        #nazwa pliku konfiguracyjnego
        self.dataArray={}
        self.lines=""

    #odczyt z podanego pliku
    def readFromFile(self):
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

    #ustawia zadana wartosc dla klucza.
    #jesli klucz istnial wczesniej, zostanie nadpisany, jesli nie zostanei utworzony
    #po tej operacji, plik konfiguracyjny zostanie nadpisany
    def setConfigItem(self,key,value):
        print"SET: ", key,"=>", value
        if key in self.dataArray:
            self.dataArray[key]=value
        else:
            self.dataArray[key]=value
        self.saveToFile()

    #zapis stanu tablicy do pliku
    def saveToFile(self):
        try:
            file=open(self.fileName, 'w')
            for k,v in self.dataArray.items():
                #print "pozycja:" , k,v
                file.write(k+";;"+v+"\n")
        except IOError:
            SLogger.log("ConfigReader", "saveToFile()", "IOError podczas zapisu do pliku")
            raise IOError
        file.close()

    #zwraca wartosc dla zadanego klucza, badz False, jesli taki klucz nie istnieje
    def getConfigItem(self, key):
        if key in self.dataArray:
            return self.dataArray[key]
        else:
            return False