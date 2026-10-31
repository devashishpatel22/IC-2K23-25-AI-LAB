from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from sklearn.tree import plot_tree
import matplotlib.pyplot as plt


def train_decision_tree():
    """Train and visualize a Decision Tree Classifier."""

    # Load Iris dataset
    iris = load_iris()
    X = iris.data
    y = iris.target

    # Split dataset
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    # Create and train model
    model = DecisionTreeClassifier(
        criterion="gini",
        random_state=42
    )

    model.fit(X_train, y_train)

    # Make predictions
    y_pred = model.predict(X_test)

    # Calculate accuracy
    accuracy = accuracy_score(y_test, y_pred)

    print("Decision Tree Classifier")
    print("Accuracy:", accuracy)

    # Visualize decision tree
    plt.figure(figsize=(15, 10))

    plot_tree(
        model,
        feature_names=iris.feature_names,
        class_names=iris.target_names,
        filled=True
    )

    plt.title("Decision Tree Visualization")
    plt.savefig("decision_tree.png")
    plt.show()


if __name__ == "__main__":
    train_decision_tree()