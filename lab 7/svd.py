import numpy as np
import matplotlib.pyplot as plt


def perform_svd():
    """Perform Singular Value Decomposition on a matrix."""

    # Create sample matrix
    matrix = np.array([
        [4, 0, 0],
        [0, 3, 0],
        [0, 0, 2],
        [1, 1, 1]
    ], dtype=float)

    print("Original Matrix:")
    print(matrix)

    # Apply SVD
    U, S, VT = np.linalg.svd(matrix, full_matrices=False)

    print("\nMatrix U:")
    print(U)

    print("\nSingular Values:")
    print(S)

    print("\nMatrix VT:")
    print(VT)

    # Reconstruct matrix
    reconstructed = U @ np.diag(S) @ VT

    print("\nReconstructed Matrix:")
    print(np.round(reconstructed, 2))

    # Low-rank approximation
    k = 2
    reduced = U[:, :k] @ np.diag(S[:k]) @ VT[:k, :]

    print("\nRank-2 Approximation:")
    print(np.round(reduced, 2))

    # Visualize singular values
    plt.figure(figsize=(7, 5))
    plt.bar(range(1, len(S) + 1), S)
    plt.xlabel("Singular Value Index")
    plt.ylabel("Singular Value")
    plt.title("SVD Singular Values")
    plt.savefig("svd_visualization.png")
    plt.show()


if __name__ == "__main__":
    perform_svd()