import matplotlib.pyplot as plt
import pandas as pd

heuristic = ["FCFS","LCFS","SJF","LJF","RR","LBW","WS"]
variance = [.0, .01, .018, .031, .056, .1, .18, .31, .56, 1.0]

for hid in range(7):
    for tset in range(10):
        with open(f"results/{hid}_{tset}.txt", mode="r") as f:
            raw = f.readlines()
    
        data = []
        for line in raw:
            if line[0] == "W":
                data.append(line)

        data.sort()

        for i in range(6):
            line = data[i].split(sep=";")
            overhead = float(line[1][2:])
            task=float(line[2][2:].strip("\n"))
            data[i]=(overhead, task)



        
        print(f"{heuristic[hid]};{variance[tset]};{data}")