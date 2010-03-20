from Serv.ConfigReader import ConfigReader
from Serv.UDPServer import UDPServer
from Serv.UDPServer import ThreadedUDPRequestHandler
from Serv.Logger import Logger
from Serv.UserDBReader import UserDBReader
import getopt
import sys

def printHelp():
    print "Serwer projektu Bazinga. Sposob uruchamiania:"
    print "python " + sys.argv[0] + " [opcje]"
    print "Opcje:"
    print "--help - wyswietla pomoc"
    print "-u sciezka - sciezka do pliku z baza uzytkownikow (domyslna ./users.conf)"
    print "-c sciezka - sciezka do pliku konfiguracyjnego (domysla ./settings.conf)\n"

try:
    optlist,args = getopt.gnu_getopt(sys.argv, 'hu:c:', ['help'])
except:
    sys.stderr.write('Blad parametrow programu.\n')
    sys.exit(1)
    
config = 'settings.conf'
users = 'users.conf'

for opt,param in optlist:
    if opt == '--help':
        printHelp()
        sys.exit(0)
    if opt == '-c':
        config = param
    if opt == '-u':
        UserDBReader.path = param

try:
    c = ConfigReader(config)
    port = int(c.getConfigItem('port'))
    Logger.verbose = int(c.getConfigItem('debug'))
except IOError:
    sys.stderr.write('Nie znaleziono pliku konfiguracyjnego.\n')
    sys.exit(1)

print "Uruchamiam serwer na porcie " + str(port) +'.'
if Logger.verbose:
    print "Tryb debug jest wlaczony."

try:
    s = UDPServer('', port)
    s.start()
except KeyboardInterrupt:    
    UDPServer.parser.groupManager.timer.cancel()
    UDPServer.parser.groupManager.closeAllGroups()
    s.shutdown()
except IOError:
    sys.stderr.write('Blad czytania pliku z uzytkownikami.\n')
    sys.exit(1)
    

