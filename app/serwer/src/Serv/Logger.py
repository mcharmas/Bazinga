'''
Created on 2009-12-14

@author: orbit
'''

class SLogger(object):
    '''
    Klasa logujaca...
    '''
    verbose = 1
    
    def log(classname, methodname, data):
        """ metoda sluzaca do logowania danych na standardowe wyjscie
        przyjmuje nazwe klasy i nazwe metody oddzielnie zeby ladnie sformatowac wyjscie
        
        """
        if SLogger.verbose:
            print classname + ":" + methodname + " message: " + data
            
    log = staticmethod(log)