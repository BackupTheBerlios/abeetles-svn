**************************************************
Usage of scripts in application Abeetles:
**************************************************

Script file is a text file and abeetles must be run with parametr -s <name of cript> so as to start with the script.

In script file must be placed one or more individual runs of Abeetles simulator. One run is described by a paragraph like following:

run=env3 //name of the run and name of directory that will be results written to.
map=env_cfg.bmp //name of bmp picture of map that should be used. Must be present at current directory
beetles=random,200,20 //starting set of beetles can be either random or can be read from a file. If it is random, it must be set by word "random", then the seed for generator of pseudorandom numbers "200" and then number of beetles to be initially placed into the map "20". Both numbers can be -1, which means time-based seed and default number of beetles.
eff=EnergyFromFlower.bmp //name of bmp file that describes function of beetles energy exploited from eaten flowers.
costs=1,1,2,0 //cost of actions of a beetle: step, rotation, mating, waiting
endtime=199000 // number of turn of simulator
aggrstatfn=aggr.txt //name of files where aggregated statistics should be written
histstatfn=hist.csv //the same for histogram statistics
timestatfn=time.csv //the same for time statistics
savetimeaggrreg=150 //every 150 turns will be aggregated statistics saved to file <time><aggrstatfn>
savetimehistreg=200 //the same for histogram statistics


run=env4
map=env_cfg.bmp
beetles="beetles.txt"//name of file of beetles
eff=EnergyFromFlower.bmp
costs=1,1,2,0
endtime=1000
aggrstatfn=aggr.txt
histstatfn=hist.csv
timestatfn=time.csv
savetimeaggrreg=100
savetimeshist=70,500,1000 //enumeration of turns, when histogram statistics should be saved. 
savetimesaggr=70,500,1000 //the same for aggregated statistics
