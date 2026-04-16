import matplotlib.pyplot as plt
import pandas as pd
class plotter:
    def __init__(self, filename='log.csv'):
        self.filename = filename
    def plot(self):
        df = pd.read_csv(self.filename)
        plt.figure(figsize=(10, 10))
        plt.subplot(3, 1, 1)
        plt.plot(df['timestamp'], df['temp'], label='Temperature (°C)')
        plt.plot(df['timestamp'], df['hum'], label='Humidity (%)')
        plt.legend()
        plt.title('Temperature and Humidity Over Time')
        plt.subplot(3, 1, 2)
        plt.plot(df['timestamp'], df['light'], label='Light Intensity (Lux)', color='orange')
        plt.legend()
        plt.title('Light Intensity Over Time')
        plt.subplot(3,1,3)
        plt.plot(df['dist'], label='Distance (cm)')
        plt.title('Distance over time')
        plt.legend()
        plt.tight_layout()
        plt.show()
plot = plotter()
plot.plot()
