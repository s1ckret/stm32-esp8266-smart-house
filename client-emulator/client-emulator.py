import time

fileRoot = "../webpage/"

def updateFile(f_name, value):
    f = open(fileRoot + f_name, "w")
    f.write(str(value))
    f.close()

def main():
    temperature = "temperature.txt"
    led = "ledStatus.txt"
    while True:
        updateFile(temperature, 21.46)
        updateFile(led, 1)
        time.sleep(0.5)
        updateFile(temperature, 22.1)
        updateFile(led, 0)
        time.sleep(0.5)


if __name__ == "__main__":
    main()