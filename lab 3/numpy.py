import numpy as np


def numpy_operations():
    """Demonstrate basic NumPy array operations."""

    arr = np.array([10, 20, 30, 40, 50])

    print("Original Array:", arr)
    print("Array Dimensions:", arr.ndim)
    print("Array Shape:", arr.shape)
    print("Array Size:", arr.size)
    print("Sum:", np.sum(arr))
    print("Mean:", np.mean(arr))
    print("Maximum:", np.max(arr))
    print("Minimum:", np.min(arr))
    print("Standard Deviation:", np.std(arr))


if __name__ == "__main__":
    numpy_operations()