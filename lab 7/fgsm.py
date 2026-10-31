import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt


# Create sample dataset
torch.manual_seed(42)

X = torch.randn(200, 2)
y = (X[:, 0] + X[:, 1] > 0).float().unsqueeze(1)


# Define neural network
class SimpleModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.network = nn.Sequential(
            nn.Linear(2, 8),
            nn.ReLU(),
            nn.Linear(8, 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        return self.network(x)


def evaluate_accuracy(model, inputs, labels):
    with torch.no_grad():
        predictions = (model(inputs) >= 0.5).float()
        return (predictions == labels).float().mean().item()


def fgsm_defensive_demo():
    model = SimpleModel()

    criterion = nn.BCELoss()
    optimizer = optim.Adam(model.parameters(), lr=0.01)

    # Train model
    for epoch in range(300):
        predictions = model(X)
        loss = criterion(predictions, y)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    # Evaluate clean inputs
    clean_accuracy = evaluate_accuracy(model, X, y)

    # Demonstrate bounded input perturbation
    test_inputs = X.clone().detach().requires_grad_(True)

    model.zero_grad()
    predictions = model(test_inputs)
    loss = criterion(predictions, y)
    loss.backward()

    epsilon = 0.05

    perturbed_inputs = (
        test_inputs.detach()
        + epsilon * test_inputs.grad.detach().sign()
    )

    # Evaluate perturbed inputs
    perturbed_accuracy = evaluate_accuracy(
        model, perturbed_inputs, y
    )

    print("FGSM Defensive Evaluation")
    print("-------------------------")
    print("Clean Accuracy:", clean_accuracy)
    print("Perturbed Accuracy:", perturbed_accuracy)
    print("Perturbation Epsilon:", epsilon)

    # Plot comparison
    plt.bar(
        ["Clean", "Perturbed"],
        [clean_accuracy, perturbed_accuracy]
    )

    plt.ylabel("Accuracy")
    plt.title("Model Robustness Evaluation")
    plt.savefig("fgsm_evaluation.png")
    plt.show()


if __name__ == "__main__":
    fgsm_defensive_demo()