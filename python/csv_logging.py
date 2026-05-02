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
                else:
                    try:
                        value = float(value)
                    except ValueError:
                        value = value
                parsed_data[key] = value
        if not parsed_data:
            return None
        return parsed_data
    def csv_init(self, fields, filename='log.csv',):
        self.fields = fields
        self.file = open(filename, mode='a', newline='', encoding='utf-8')
        self.writer = csv.DictWriter(self.file, fieldnames=fields)
        if self.file.tell() == 0:
           self.writer.writeheader()
    def csv_log(self, data):
        timestamp = datetime.now().isoformat()
        row = {}
        for key in self.fields:
            if key == "timestamp":
                row["timestamp"] = timestamp
            else:
                row[key] = data.get(key)
        self.writer.writerow(row)
        self.file.flush()
    def close(self):
        if hasattr(self, 'serial_port') and self.serial_port.is_open:
            self.serial_port.close()
        if hasattr(self, 'file') and not self.file.closed:
            self.file.close()
log = Logger('COM6', 115200)
fields1 = ['timestamp', 'temp', 'hum', 'light','dist']
fields2 = ['timestamp', 'dist', 'angle', 'mode']
log.csv_init(fields2)
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
