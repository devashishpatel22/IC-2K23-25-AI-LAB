import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt


def train_linear_regression():
    """Train a simple linear regression model."""

    # Training data
    X = torch.tensor(
        [[1.0], [2.0], [3.0], [4.0], [5.0]]
    )

    y = torch.tensor(
        [[3.0], [5.0], [7.0], [9.0], [11.0]]
    )

    # Define model
    model = nn.Linear(1, 1)

    # Loss function and optimizer
    criterion = nn.MSELoss()
    optimizer = optim.SGD(model.parameters(), lr=0.01)

    # Training
    losses = []

    for epoch in range(1000):
        predictions = model(X)
        loss = criterion(predictions, y)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        losses.append(loss.item())

    print("Training Completed")
    print("Final Loss:", loss.item())

    # Prediction
    test = torch.tensor([[6.0]])

    with torch.no_grad():
        prediction = model(test)

    print("Prediction for X = 6:", prediction.item())

    # Plot loss
    plt.plot(losses)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.title("Linear Regression Training Loss")
    plt.savefig("linear_regression_loss.png")
    plt.show()


if __name__ == "__main__":
    train_linear_regression()