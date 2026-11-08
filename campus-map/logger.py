import serial, csv, time

# Spots:(name, latitude, longitude). Replace with gps coords and add spots for how many i would like
SPOTS = {
    '1': ('Spot A', 43.0000, -80.0000),
    '2': ('Spot B', 43.0000, -80.0000),
    '3': ('Spot C', 43.0000, -80.0000),
}

# Open the ESP32's serial port, match the com4 of my esp32 and the baud rate (115200)
ser = serial.Serial('COM4', 115200, timeout=2)

def read_avg(n=5):
    # n valid readings and average, 
    rows = []
    while len(rows) < n:
        try:
            # Turn a line like "22.41,310.0,18" into [22.41, 310.0, 18.0]
            vals = [float(x) for x in ser.readline().decode(errors='ignore').split(',')]
            if len(vals) == 3:          # keep only complete lines
                rows.append(vals)
        except ValueError:
            pass                        # skip broken lines
    return [sum(c) / n for c in zip(*rows)]   # average temp, lux, sound

# Append to data.csv so old data isn't erased
with open('data.csv', 'a', newline='') as f:
    w = csv.writer(f)
    # Keep asking for a spot until you type q
    while (key := input("Spot (q to quit): ")) != 'q':
        if key in SPOTS:
            ser.reset_input_buffer()    # throw away old buffered readings
            name, lat, lon = SPOTS[key]
            row = read_avg()
            # Save: timestamp, spot name, lat, lon, temp, lux, sound
            w.writerow([time.time(), name, lat, lon, *row])
            f.flush()                   # write to disk immediately
            print(name, [round(x, 1) for x in row])   # show temp, lux, sound