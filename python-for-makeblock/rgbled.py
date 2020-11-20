from lib.mBot import *

if __name__ == '__main__':
	bot = mBot()
	# bot.startWithSerial("COM5")
	bot.startWithHID()
	while(1):
		print("hi1")
		bot.doRGBLedOnBoard(0, 0,0,255)
		sleep(0.5)
		print("hi2")
		bot.doRGBLedOnBoard(0, 0,255,0)
		sleep(0.5)
		print("hi3")
		bot.doRGBLedOnBoard(0, 255,0,0)
		sleep(0.5)