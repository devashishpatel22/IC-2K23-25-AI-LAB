import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA


def perform_pca():
    """Apply PCA to reduce the Iris dataset to two dimensions."""

    # Load dataset
    iris = load_iris()
    X = iris.data
    y = iris.target

    # Standardize the data
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    # Apply PCA
    pca = PCA(n_components=2)
    X_pca = pca.fit_transform(X_scaled)

    print("Original Dataset Shape:", X.shape)
    print("Reduced Dataset Shape:", X_pca.shape)

    print("\nExplained Variance Ratio:")
    print(pca.explained_variance_ratio_)

    print(
        "\nTotal Explained Variance:",
        pca.explained_variance_ratio_.sum()
    )

    # Visualize reduced dimensions
    plt.figure(figsize=(8, 6))

    for i, name in enumerate(iris.target_names):
        plt.scatter(
            X_pca[y == i, 0],
            X_pca[y == i, 1],
            label=name
        )

    plt.xlabel("Principal Component 1")
    plt.ylabel("Principal Component 2")
    plt.title("PCA - Iris Dataset")
    plt.legend()

    plt.savefig("pca_visualization.png")
    plt.show()


if __name__ == "__main__":
    perform_pca()