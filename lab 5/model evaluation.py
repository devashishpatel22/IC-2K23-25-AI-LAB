from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    confusion_matrix,
    classification_report
)
import matplotlib.pyplot as plt
import seaborn as sns
import time


def evaluate_model():
    """Evaluate the Decision Tree Classifier."""

    iris = load_iris()
    X = iris.data
    y = iris.target

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    model = DecisionTreeClassifier(random_state=42)

    start_time = time.perf_counter()
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    execution_time = time.perf_counter() - start_time

    print("Model Evaluation Results")
    print("------------------------")

    print("Accuracy:", accuracy_score(y_test, y_pred))

    print(
        "Precision:",
        precision_score(y_test, y_pred, average="weighted")
    )

    print(
        "Recall:",
        recall_score(y_test, y_pred, average="weighted")
    )

    print(
        "F1 Score:",
        f1_score(y_test, y_pred, average="weighted")
    )

    print("\nClassification Report:")
    print(classification_report(
        y_test, y_pred, target_names=iris.target_names
    ))

    print("Execution Time:", execution_time, "seconds")

    # Confusion Matrix
    cm = confusion_matrix(y_test, y_pred)

    plt.figure(figsize=(7, 5))
    sns.heatmap(
        cm,
        annot=True,
        fmt="d",
        cmap="Blues",
        xticklabels=iris.target_names,
        yticklabels=iris.target_names
    )

    plt.title("Confusion Matrix")
    plt.xlabel("Predicted Labels")
    plt.ylabel("Actual Labels")
    plt.savefig("confusion_matrix.png")
    plt.show()


if __name__ == "__main__":
    evaluate_model()