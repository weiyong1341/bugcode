import torch
import clip
from PIL import Image
import torch.nn.functional as F
import torch.nn as nn

device = "cuda" if torch.cuda.is_available() else "cpu"
model, preprocess = clip.load("ViT-B/32", device=device)


image1 = preprocess(Image.open("15.png")).unsqueeze(0).to(device)
image2 = preprocess(Image.open("0120.png")).unsqueeze(0).to(device)


image = preprocess(Image.open("CLIP.png")).unsqueeze(0).to(device)
text = clip.tokenize(["a diagram", "a dog", "a cat"]).to(device)


cos = nn.CosineSimilarity(dim=1, eps=1e-6)

with torch.no_grad():
    
    # image1_features = model.encode_image(image1).float()
    # image2_features = model.encode_image(image2).float()
    
    # print(image1_features.max())
    # print(image2_features.min())
    
    # similarity = cos(image1_features, image2_features)
    # print(similarity)
    

    image_features = model.encode_image(image).float()
    text_features = model.encode_text(text)
    
    logits_per_image, logits_per_text = model(image, text)
    probs = logits_per_image.softmax(dim=-1).cpu().numpy()

print("Label probs:", probs)  # prints: [[0.9927937  0.00421068 0.00299572]]


