from lib.mBot import *

def onLight(value):
	print("light = ",value)
	
if __name__ == '__main__':
	bot = mBot()
	bot.startWithSerial("COM5")
	# bot.startWithHID()
	while(1):
		bot.requestLightOnBoard(1,onLight)
		bot.requestLightOnBoard(2,onLight)
		sleep(0.5)