import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd


for i in range(9):
    df = pd.read_csv(
        f"results/{i}.txt",
        sep=";",
        engine="python",
        names=["runtime", "EstimatedCost"], usecols=[0, 1],)
    df["runtime"] = pd.to_numeric(df["runtime"], errors="coerce")
    df["EstimatedCost"] = pd.to_numeric(df["EstimatedCost"], errors="coerce")
    df = df.dropna()
    summary = df.agg(["mean", "std"])
    print(summary)


# Combine all max_iter values into long-form dataframe
records = []
variances = ["0.010", "0.018", "0.031", "0.056", "0.100", "0.180", "0.310", "0.560", "1.000"]

lookingAt = "EstimatedCost"

for i, v in enumerate(variances):
    df = pd.read_csv(
        f"tasks/{i}.txt",
        sep=r"\s+",
        engine="python",
        skiprows=1,
        skipfooter=1,
        names=["Delay", "Zoom", "MaxIter", "Resolution", "EstimatedCost"]
    )
    for val in df[lookingAt]:
        records.append({"Variance": float(v), lookingAt: val})

    summary = df.agg(["mean", "std"])
    #print(f"Variance {v}:\n", summary)

df_long = pd.DataFrame(records)

# Compute mean values for each variance
means = df_long.groupby("Variance")[lookingAt].mean().reset_index()

# Plot violin plot
plt.figure(figsize=(10, 6))
sns.violinplot(x="Variance", y=lookingAt, data=df_long, inner="box", scale="width")

# Add mean dots
plt.scatter(
    x=range(len(means)),  # x-coordinates aligned with violinplot x-axis
    y=means[lookingAt],
    color='red',
    marker='o',
    zorder=5,
    label='Mean',
    alpha=0.5
)

plt.xlabel("Variance (v)", fontsize=14)
plt.ylabel("Estimated cost", fontsize=14)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
