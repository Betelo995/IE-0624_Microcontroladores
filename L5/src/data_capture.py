import sys
import serial
import time
import csv

#Encabezado del documento para sustituir el del arduino que no siempre sale bien
header = ['aX', 'aY', 'aZ', 'gX', 'gY', 'gZ']
#Determinamos la cantidad de datos que se quieren muestrear
samples = 3000
#Flag en 0 para el conteo de datos
counter = 0
#Para poder determinar los datos que se están capturando
filename = sys.argv[1]

#En caso de que no se conecte de forma adecuada se tiene un manejo de errores:
try:
    ser = serial.Serial(port = '/dev/ttyACM0', baudrate=9600, timeout=1) 
    print("Conectado!")
except serial.SerialException as e:
    print("Fallo al conectar con la placa en el puerto: " + str(e))
    sys.exit(1)

#f = open(filename, 'w', encoding='UTF8')
with open(filename, 'w', encoding='UTF8') as f:
    writer = csv.writer(f)
    print(header)
    writer.writerow(header)

    while(counter < samples):
        
        data = ser.readline().decode('utf-8').replace('\r', "").replace('\n', "")
        data = data.split(',')

        if(len(data) == 6):    
            writer.writerow(data)
            print(data) #Únicamente para poder ver los datos en consola mientras se capturan
            counter+=1
ser.close()