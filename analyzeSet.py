import pandas as pd

series = "tasks"

for set in range(0, 11):
    filename = f"{series}/{set}.txt"

    df = pd.read_csv(filename, sep=" ", engine="python", skiprows=1, skipfooter=1, names=["Delay","Zoom","MaxIter","Resolution","EstimatedCost"])

    summary = df.agg(["mean", "std"])

    print(f"\n{filename}")

    print(summary)