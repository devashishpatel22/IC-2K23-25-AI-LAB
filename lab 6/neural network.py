import torch
import torch.nn as nn
import torch.optim as optim


class NeuralNetwork(nn.Module):
    """Define a simple feedforward neural network."""

    def __init__(self):
        super().__init__()

        self.layers = nn.Sequential(
            nn.Linear(2, 8),
            nn.ReLU(),
            nn.Linear(8, 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        return self.layers(x)


def train_neural_network():
    """Train the neural network on sample binary data."""

    X = torch.tensor([
        [0.0, 0.0],
        [0.0, 1.0],
        [1.0, 0.0],
        [1.0, 1.0]
    ])

    y = torch.tensor([
        [0.0],
        [1.0],
        [1.0],
        [1.0]
    ])

    model = NeuralNetwork()

    criterion = nn.BCELoss()
    optimizer = optim.Adam(model.parameters(), lr=0.01)

    for epoch in range(1000):
        predictions = model(X)
        loss = criterion(predictions, y)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    print("Neural Network Training Completed")
    print("Final Loss:", loss.item())

    with torch.no_grad():
        predictions = model(X)
        print("\nPredictions:")
        print(predictions)
        print("\nPredicted Classes:")
        print((predictions >= 0.5).int())


if __name__ == "__main__":
    train_neural_network()