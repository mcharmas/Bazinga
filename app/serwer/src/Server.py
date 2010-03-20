from Serv.ConfigReader import ConfigReader
from Serv.UDPServer import UDPServer
from Serv.UDPServer import ThreadedUDPRequestHandler
from Serv.Logger import Logger


c = ConfigReader('settings.conf')
port = int(c.getConfigItem('port'))
Logger.verbose = int(c.getConfigItem('debug'))

print "Uruchamiam serwer na porcie " + str(port) +'.'
if Logger.verbose:
    print "Tryb debug jest wlaczony."

try:
    s = UDPServer('', port)
    s.start()
except KeyboardInterrupt:
    ThreadedUDPRequestHandler.parser.groupManager.timer.cancel()
    ThreadedUDPRequestHandler.parser.groupManager.closeAllGroups()
    s.shutdown()

