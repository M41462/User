# Digit Recognition

A CNN-based handwritten digit recognition project using TensorFlow/Keras trained on the MNIST dataset.

## Usage

Run the script to train the model (if no saved model exists) and predict digits from `digits/` folder:

```bash
python main.py
```

Place `1.jpg`, `2.jpg`, etc. (28×28 grayscale) in `digits/` for prediction. The first time it runs, it trains a CNN on MNIST and saves the model to `model_cnn.h5`.

## Model Architecture

- Conv2D(32→32) + BatchNorm + MaxPool + Dropout(0.25)
- Conv2D(64→64) + BatchNorm + MaxPool + Dropout(0.25)
- Dense(256) + BatchNorm + Dropout(0.5) → Dense(10) softmax

## Dependencies

`tensorflow`, `opencv-python`, `numpy`, `matplotlib`
