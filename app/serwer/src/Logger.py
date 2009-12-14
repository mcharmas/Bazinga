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
        if SLogger.verbose:
            print classname + ":" + methodname + " message: " + data
            
    log = staticmethod(log)