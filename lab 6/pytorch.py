import torch


def pytorch_basics():
    """Demonstrate basic PyTorch tensor operations."""

    # Create tensors
    a = torch.tensor([10, 20, 30])
    b = torch.tensor([1, 2, 3])

    print("Tensor A:", a)
    print("Tensor B:", b)

    # Tensor operations
    print("\nAddition:", a + b)
    print("Subtraction:", a - b)
    print("Multiplication:", a * b)
    print("Division:", a / b)

    # Matrix operations
    matrix = torch.tensor([
        [1, 2],
        [3, 4]
    ])

    print("\nMatrix:")
    print(matrix)

    print("\nMatrix Transpose:")
    print(matrix.T)

    print("\nMean:", torch.mean(a.float()))
    print("Sum:", torch.sum(a))


if __name__ == "__main__":
    pytorch_basics()