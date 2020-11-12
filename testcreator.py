import json
import os
import time
#OTHER THINGS TO CONSIDER THIS CAN BE AUTOMATED TO READ N FILES WITH DIFFERENT SETUPS
def runtest():
	for index in range(1):
		os.system("rm -rf results")
		os.system("mkdir results")
		inputjson=readjson(6)
		os.system("rm -rf out.ppm")
		os.system("g++ main.cpp -pthread -lm -o main")
		command="./main h {} w {} fv {} sh {} rl {} rf {} pr {} v{} o {} a {} fm {} {} {} to {} {} {} up {} {} {} >> out.ppm".format(
													inputjson['resolution']['height'],
													inputjson['resolution']['width'],
													inputjson['camera']['fieldview'],
													inputjson['shades'],
													inputjson['reflect'],
													inputjson['refract'],
													inputjson['precision'],
													inputjson['neon'],
													inputjson['objects'],
													inputjson['aliasing'],
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
		print(command)
		command_out="height,width,shades,reflect,refract,precision,neon,objects,aliasing,iteration,elapsed"
		os.system("echo "+command_out+" >> results/results.csv")
		for iteration in range(5):
			path="h_{}_w_{}_fv_{}_sh_{}_rl_{}_rf_{}_pr_{}_v{}_o_{}_a_{}_fm_{}_{}_{}_to_{}_{}_{}_up_{}_{}_{}_{}".format(
													inputjson['resolution']['height'],
													inputjson['resolution']['width'],
													inputjson['camera']['fieldview'],
													inputjson['shades'],
													inputjson['reflect'],
													inputjson['refract'],
													inputjson['precision'],
													inputjson['neon'],
													inputjson['objects'],
													inputjson['aliasing'],
													inputjson['camera']['from'][0],
													inputjson['camera']['from'][1],
													inputjson['camera']['from'][2],
													inputjson['camera']['to'][0],
													inputjson['camera']['to'][1],
													inputjson['camera']['to'][2],
													inputjson['camera']['up'][0],
													inputjson['camera']['up'][1],
													inputjson['camera']['up'][2],
													iteration
													)
			os.system("mkdir results/"+path)
			os.system(" echo 3 > /proc/sys/vm/drop_caches && swapoff -a && swapon -a && printf '\n%s\n' 'Ram-cache and Swap Cleared'")
			time.sleep(5)
			start = time.time()
			os.system(command)
			end = time.time()
			print(end - start)
			time.sleep(5)
			f = open("result.txt", "r")
			os.system("mv result.txt results/"+path)
			os.system("mv out.ppm results/"+path)
			command_out="{},{},{},{},{},{},{},{},{},{},{}".format(
													inputjson['resolution']['height'],
													inputjson['resolution']['width'],
													inputjson['shades'],
													inputjson['reflect'],
													inputjson['refract'],
													inputjson['precision'],
													inputjson['neon'],
													inputjson['objects'],
													inputjson['aliasing'],
													iteration,
													f.read()
													)
			os.system("echo "+command_out+" >> results/results.csv")
			f.close() 

def readjson(index):
	with open('configuration_files/setup'+str(index)+'.json') as json_file:
		data = json.load(json_file)
	return data

runtest()
