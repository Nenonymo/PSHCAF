import matplotlib.pyplot as plt


heuristic = ["FCFS","LCFS","SJF","LJF","RR","LBW","WS"]
variances = ["0.000", "0.010", "0.018", "0.031", "0.056", "0.100", "0.180", "0.310", "0.560", "1.000"]

with open("wtlist.txt", mode="r") as f:
    lines = f.readlines()

file1 = open("wOver.csv", mode="w")
file2 = open("wTask.csv", mode="w")

for h in range(7): #Split by heuristic
    data = []
    for v in range(10): #Split by variance
        line1 = f"{heuristic[h]},{variances[v]}"
        line2 = f"{heuristic[h]},{variances[v]}"
        for l in range(6): #Split by worker
            (o, t) = lines[h*7 + v].split(";")[2][1:-2].split(", ")[l*2:l*2+2]
            (o, t) = (float(o[1:]), float(t[:-1]))
            line1 += f",{o}"
            line2 += f",{t}"
        file1.write(line1 + "\n")
        file2.write(line2 + "\n")

file1.close()
file2.close()