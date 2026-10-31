def visualize_data():
    """Generate different visualizations using student data."""

    data = {
        "Name": ["Aman", "Riya", "Karan", "Neha", "Rahul"],
        "Marks": [85, 90, 78, 92, 88],
        "Attendance": [85, 90, 75, 95, 80]
    }

    df = pd.DataFrame(data)

    # Bar Chart
    plt.figure(figsize=(8, 5))
    plt.bar(df["Name"], df["Marks"])
    plt.title("Student Marks")
    plt.xlabel("Students")
    plt.ylabel("Marks")
    plt.savefig("student_marks.png")
    plt.show()

    # Histogram
    plt.figure(figsize=(8, 5))
    plt.hist(df["Marks"], bins=5, edgecolor="black")
    plt.title("Distribution of Student Marks")
    plt.xlabel("Marks")
    plt.ylabel("Frequency")
    plt.savefig("marks_histogram.png")
    plt.show()

    # Scatter Plot
    plt.figure(figsize=(8, 5))
    plt.scatter(df["Attendance"], df["Marks"])
    plt.title("Attendance vs Marks")
    plt.xlabel("Attendance")
    plt.ylabel("Marks")
  plt.savefig("outputs/student_marks.png")
plt.savefig("outputs/marks_histogram.png")
plt.savefig("outputs/attendance_vs_marks.png")
plt.savefig("outputs/correlation_heatmap.png")
    plt.show()

    # Correlation Heatmap
    plt.figure(figsize=(6, 4))
    sns.heatmap(
        df[["Marks", "Attendance"]].corr(),
        annot=True,
        cmap="coolwarm"
    )
    plt.title("Correlation Heatmap")
    plt.savefig("correlation_heatmap.png")
    plt.show()


if __name__ == "__main__":
    visualize_data()