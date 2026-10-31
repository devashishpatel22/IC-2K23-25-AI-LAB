import pandas as pd


def perform_eda():
    """Perform basic exploratory data analysis."""

    data = {
        "Name": ["Aman", "Riya", "Karan", "Neha", "Rahul"],
        "Age": [20, 21, 19, 22, 20],
        "Marks": [85, 90, 78, 92, 88],
        "Attendance": [85, 90, 75, 95, 80]
    }

    df = pd.DataFrame(data)

    print("Dataset:")
    print(df)

    print("\nDataset Information:")
    df.info()

    print("\nStatistical Summary:")
    print(df.describe())

    print("\nAverage Marks:", df["Marks"].mean())
    print("Highest Marks:", df["Marks"].max())
    print("Lowest Marks:", df["Marks"].min())

    print("\nCorrelation Matrix:")
    print(df[["Age", "Marks", "Attendance"]].corr())


if __name__ == "__main__":
    perform_eda()