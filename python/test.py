import csv

listx = [["hi", 2, 3], ["there", 4, 5], ["world", 6, 7]]

with open('main.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    cash = 100.50
    writer.writerow([cash])
    for item in listx:
        writer.writerow([item[0], item[1], item[2]])