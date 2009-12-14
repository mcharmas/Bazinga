

class ConfigReader():

    file=None


    def __init__(self,file):
        self.readFromFile(file)

    def readFromFile(self,file):
        self.file=open(file, "r")

        self.file.close()
