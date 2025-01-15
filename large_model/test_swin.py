
import torch
import timm

model = timm.create_model('swin_base_patch4_window7_224', pretrained=False)
img = torch.randn(1, 3, 224, 224)
prob = model(img)
print(prob)

