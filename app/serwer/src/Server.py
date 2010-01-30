from Serv.ConfigReader import ConfigReader
from Serv.UDPServer import UDPServer
from Serv.Logger import SLogger


c = ConfigReader('settings.conf')
port = int(c.getConfigItem('port'))
SLogger.verbose = int(c.getConfigItem('debug'))

print "Uruchamiam serwer na porcie " + str(port) +'.'
if SLogger.verbose:
    print "Tryb debug jest wlaczony."

try:
    s = UDPServer('', port)
    s.start()
except KeyboardInterrupt:
    s.shutdown()