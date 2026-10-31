import torch
import torch.nn.functional as F
import torchvision.models as models
import torchvision.transforms as transforms
import matplotlib.pyplot as plt

from PIL import Image
import numpy as np


def generate_grad_cam(image_path):
    """Generate a Grad-CAM visualization using ResNet18."""

    # Load pretrained ResNet18 model
    weights = models.ResNet18_Weights.DEFAULT
    model = models.resnet18(weights=weights)
    model.eval()

    # Store feature maps and gradients
    activations = []
    gradients = []

    target_layer = model.layer4[-1]

    def forward_hook(module, input, output):
        activations.append(output)

    def backward_hook(module, grad_input, grad_output):
        gradients.append(grad_output[0])

    target_layer.register_forward_hook(forward_hook)
    target_layer.register_full_backward_hook(backward_hook)

    # Load and preprocess image
    image = Image.open(image_path).convert("RGB")

    preprocess = weights.transforms()
    input_tensor = preprocess(image).unsqueeze(0)

    # Forward pass
    output = model(input_tensor)
    predicted_class = output.argmax(dim=1).item()

    # Backward pass
    model.zero_grad()
    output[0, predicted_class].backward()

    # Calculate Grad-CAM
    feature_maps = activations[0]
    grads = gradients[0]

    weights_cam = grads.mean(dim=(2, 3), keepdim=True)

    cam = (weights_cam * feature_maps).sum(dim=1)
    cam = F.relu(cam)

    cam = F.interpolate(
        cam.unsqueeze(1),
        size=(224, 224),
        mode="bilinear",
        align_corners=False
    )

    cam = cam.squeeze().detach().numpy()

    # Normalize heatmap
    cam = cam - cam.min()
    cam = cam / (cam.max() + 1e-8)

    # Display original image and heatmap
    original = image.resize((224, 224))

    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(original)
    plt.title("Original Image")
    plt.axis("off")

    plt.subplot(1, 2, 2)
    plt.imshow(original)
    plt.imshow(cam, cmap="jet", alpha=0.5)
    plt.title("Grad-CAM Visualization")
    plt.axis("off")

    plt.savefig("grad_cam_output.png")
    plt.show()

    print("Predicted Class Index:", predicted_class)
    print("Grad-CAM visualization generated successfully.")


if __name__ == "__main__":
    generate_grad_cam("cat.jpeg")