import serial as ser
import csv
from datetime import datetime
import time
class Logger:
    def __init__(self, port, baudrate,timeout=1):
        try:
           self.serial_port = ser.Serial(port, baudrate, timeout=timeout)
           time.sleep(2)
        except Exception as e:
           print(f"Error opening serial port: {e}")
           raise
        finally:
              pass
    def read(self):
        return self.serial_port.readline().decode(errors="ignore").strip()
    def parse(self, data):
        parsed_data = {}
        for item in data.split(','):
            if '=' in item:
                key, value = item.split('=', 1)
                key = key.strip()
                value = value.strip()
                if value =='?':
                    value = None
                elif key in ('temp' , 'hum'):
                    try:
                        value = float(value)
                    except ValueError:
                        value = None
                elif key == 'light':
                    try:
                        value = int(value)
                    except ValueError:
                        value = None
                elif key == 'dist':
                    try:
                        value = float(value)
                    except ValueError:
                        value = None
                
                parsed_data[key] = value
        if not parsed_data:
            return None
        return parsed_data
    def csv_init(self, filename='log.csv'):
        self.file = open(filename, mode='a', newline='', encoding='utf-8')
        self.writer = csv.DictWriter(self.file, fieldnames=['timestamp', 'temp', 'hum', 'light','dist'])
        if self.file.tell() == 0:
           self.writer.writeheader()
    def csv_log(self, data):
        timestamp = datetime.now().isoformat()
        row = {'timestamp': timestamp, 'temp': data.get('temp'), 'hum': data.get('hum'), 'light': data.get('light'), 'dist':data.get('dist')}
        self.writer.writerow(row)
        self.file.flush()
    def close(self):
        if hasattr(self, 'serial_port') and self.serial_port.is_open:
            self.serial_port.close()
        if hasattr(self, 'file') and not self.file.closed:
            self.file.close()
log = Logger('COM6', 115200)
log.csv_init()
try:
  while True:
    data = log.read()
    parsed_data = log.parse(data)
    if not parsed_data:
      continue
    log.csv_log(parsed_data)
except KeyboardInterrupt:
  pass
finally:
   log.close()
