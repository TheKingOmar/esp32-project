import csv
class Summary:
    def __init__(self):
        self.summary = {}
    def summarize(self):
        total_rows = 0
        empty_rows_temp = 0
        empty_rows_hum = 0
        total_sum_light = 0
        total_sum_temp = 0
        total_sum_hum = 0
        min_light = float('inf')
        min_temp= float('inf')
        min_hum = float('inf')
        max_light =0
        max_temp = 0
        max_hum = 0
        with open('log.csv', mode='r', newline='', encoding='utf-8') as file:
                reader = csv.DictReader(file)
                for row in reader:
                   total_rows +=1
                   if row['temp'] == '':
                      empty_rows_temp +=1
                   if row['hum'] == '':
                      empty_rows_hum +=1
                   light = int(row['light'])
                   if row.get('temp'):
                      temp = float(row['temp'])
                      min_temp = min(temp, min_temp)
                      max_temp = max(temp, max_temp)
                      total_sum_temp += temp
                   if row.get('hum'):
                      hum = float(row['hum']) 
                      min_hum = min(hum, min_hum)
                      max_hum = max(hum, max_hum)
                      total_sum_hum += hum
                   min_light= min(light, min_light)
                   max_light= max(light, max_light)
                   total_sum_light += light
        self.summary['total_rows'] = total_rows
        self.summary['empty_temp'] = empty_rows_temp
        self.summary['empty_hum'] = empty_rows_hum
        self.summary['max_temp'] = max_temp
        self.summary['max_light'] = max_light
        self.summary['max_hum'] = max_hum
        self.summary['min_temp'] = min_temp
        self.summary['min_light'] = min_light
        self.summary['min_hum'] = min_hum
        if total_rows != 0:
            self.summary['avg_light'] = total_sum_light/total_rows
            if (total_rows-empty_rows_temp) != 0:
               self.summary['avg_temp'] = total_sum_temp/(total_rows-empty_rows_temp)
            if (total_rows-empty_rows_hum) != 0:
               self.summary['avg_hum'] = total_sum_hum/(total_rows-empty_rows_hum)
    def result(self):
        print(f"""
              Rows: {self.summary['total_rows']}
              Missing temp: {self.summary['empty_temp']}
              Missing hum: {self.summary['empty_hum']}
              Temp min/max/avg: {self.summary['min_temp']}/{self.summary['max_temp']}/{round(self.summary['avg_temp'], 1)}
              Hum min/max/avg: {self.summary['min_hum']}/{self.summary['max_hum']}/{round(self.summary['avg_hum'], 1)}
              Light min/max/avg: {self.summary['min_light']}/{self.summary['max_light']}/{round(self.summary['avg_light'])}"""
              )
summarize = Summary()
summarize.summarize()
summarize.result()