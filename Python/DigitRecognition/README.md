# DigitRecognition

A CNN-based handwritten digit recognition system trained on the MNIST dataset using TensorFlow/Keras.

## How It Works

Loads MNIST (60k training, 10k test images), normalizes pixels, and trains a convolutional neural network:
- Two Conv2D blocks (32 → 32, 64 → 64) with BatchNorm, MaxPool, Dropout
- Dense layer (256) + BatchNorm + Dropout → 10-class softmax output

If a saved model (`model_cnn.h5`) exists, it loads that instead of retraining. Then it reads 28×28 grayscale images from `digits/`, inverts colors (MNIST convention), and predicts each digit with confidence scores. Displays results with matplotlib.

## Usage

```bash
pip install tensorflow opencv-python numpy matplotlib
python main.py
```

Place 28×28 grayscale digit images in `digits/` for prediction.
