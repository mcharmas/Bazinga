class Logger:
    '''Klasa logujaca.'''
    
    ##Zmienna statyczna wskazujaca czy logger jest wlaczony (1 - tak, 0 - nie)
    verbose = 1
    
    def log(classname, methodname, data):
        """Metoda sluzaca do logowania danych na standardowe wyjscie.
        Przyjmuje nazwe klasy i nazwe metody oddzielnie zeby ladnie sformatowac wyjscie.
        """
        if Logger.verbose:
            print classname + ":" + methodname + " message: " + data
    
    ##Statyczna metoda logujaca        
    log = staticmethod(log)