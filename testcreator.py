import json
import os
#OTHER THINGS TO CONSIDER THIS CAN BE AUTOMATED TO READ N FILES WITH DIFFERENT SETUPS
def runtest():
	inputjson=readjson()
	command="./arguments h {} w {} fv {} sh {} fl {} fr {} pr {} v{} o {} fm {} {} {}".format(
												inputjson['resolution']['height'],
												inputjson['resolution']['width'],
												inputjson['camera']['fieldview'],
												inputjson['shades'],
												inputjson['reflect'],
												inputjson['refract'],
												inputjson['precision'],
												inputjson['neon'],
												inputjson['objects'],
												inputjson['camera']['from'][0],
												inputjson['camera']['from'][1],
												inputjson['camera']['from'][2],
												inputjson['camera']['to'][0],
												inputjson['camera']['to'][1],
												inputjson['camera']['to'][2],
												inputjson['camera']['up'][0],
												inputjson['camera']['up'][1],
												inputjson['camera']['up'][2],

												)
	os.system(command)
	print("call to c binary")

def readjson():
	with open('setup.json') as json_file:
		data = json.load(json_file)
	return data

runtest()