import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd



# Combine all max_iter values into long-form dataframe
records = []
variances = [str(v) for v in [0.0000, 0.0010, 0.0017, 0.0030, 0.0044, 0.0065, 0.0095, 0.0138, 0.0201, 0.0292, 0.0425, 0.0619, 0.0901, 0.1311, 0.1908, 0.2772, 0.4026, 0.5848, 0.8496, 1.0000]]

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
    print(f"Variance {v}:\n", summary)

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

xticks = [v for i, v in enumerate(variances) if i % 2 == 0]

plt.xlabel("Variance (v)", fontsize=14)
plt.ylabel("Estimated cost", fontsize=14)
plt.xticks(ticks=range(len(variances)), labels=variances, rotation=45)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
