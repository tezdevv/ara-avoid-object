import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

X_train = np.array([
    [80, 85, 90, 95, 100, 120, 120, 100, 95, 90, 85, 80],
    [30, 35, 40, 45, 50, 60, 100, 120, 130, 140, 150, 160],
    [140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30],
    [20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20],
    [100, 100, 100, 100, 100, 50, 50, 50, 100, 100, 100, 100],
], dtype=np.float32)

Y_train = np.array([0, 2, 1, 3, 0], dtype=np.uint8)
X_train = X_train / 200.0

model = keras.Sequential([
    layers.Input(shape=(12,)),
    layers.Dense(16, activation='relu'),
    layers.Dense(12, activation='relu'),
    layers.Dense(4, activation='softmax') 
])

model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

model.fit(X_train, Y_train, epochs=500, verbose=1)

mapPredict = (np.array( [140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30]))/200
resultPredict = model.predict(np.array([mapPredict]))

print("Hasil Prediksi : ", resultPredict)
print("Arah : ", np.argmax(resultPredict))

# model.save("model_robot.h5")

# converter = tf.lite.TFLiteConverter.from_keras_model(model)
# tflite_model = converter.convert()
# with open("model_robot.tflite", "wb") as f:
#     f.write(tflite_model)


import math

# Data sensor dari kiri ke kanan (0° ke 180°, setiap 15°)
sensor_data = [80, 85, 90, 95, 100, 120, 120, 100, 95, 90, 85, 80]

# Ambil titik paling panjang (terbuka lebar)
max_index = sensor_data.index(max(sensor_data))
max_jarak = sensor_data[max_index]

# Hitung sudut relatif terhadap tengah (index ke-5 dan 6 adalah 90°)
sudut_per_index = 15  # derajat
relatif_index = max_index - 5.5  # dari pusat robot (tengah-tengah antara index 5 dan 6)
sudut_dari_tengah = relatif_index * sudut_per_index
sudut_radian = math.radians(abs(sudut_dari_tengah))

# Hitung jarak depan (proyeksi ke depan)
jarak_depan = math.cos(sudut_radian) * max_jarak
jarak_samping = math.sin(sudut_radian) * max_jarak

# Sudut belok robot
sudut_belok = abs(sudut_dari_tengah)  # arah berdasarkan max_index kiri/kanan
arah = "kanan" if max_index > 5.5 else "kiri" if max_index < 5.5 else "maju"

print(f"Arah: {arah}")
print(f"Belok {sudut_belok:.2f} derajat")
print(f"Proyeksi ke depan: {jarak_depan:.2f} cm")
print(f"Proyeksi samping: {jarak_samping:.2f} cm")
