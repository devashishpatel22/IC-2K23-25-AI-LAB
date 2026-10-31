import pandas as pd


def pandas_operations():
    """Demonstrate basic Pandas operations."""

    data = {
        "Name": ["Aman", "Riya", "Karan", "Neha", "Rahul"],
        "Age": [20, 21, 19, 22, 20],
        "Marks": [85, 90, 78, 92, 88]
    }

    df = pd.DataFrame(data)

    print("Original DataFrame:")
    print(df)

    print("\nFirst Two Records:")
    print(df.head(2))

    print("\nStatistical Summary:")
    print(df.describe())

    print("\nStudents with Marks Greater than 85:")
    print(df[df["Marks"] > 85])

    print("\nSorted DataFrame:")
    print(df.sort_values(by="Marks", ascending=False))


if __name__ == "__main__":
    pandas_operations()