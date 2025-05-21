import torch
import timm

models = timm.list_models("*")
# print(models)

model = timm.create_model("vit_base_patch16_224")
img = torch.randn((1, 3, 224, 224))
model(img)