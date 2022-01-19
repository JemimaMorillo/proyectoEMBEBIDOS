# !/usr/bin/env python3
# Generated by Proteus Visual Designer for Raspberry Pi

# Modules
import requests
import math
import random
from time import sleep
import threading
from wiringpi import Serial
import RPi.GPIO as GPIO
####
   
TOKEN = "BBFF-4LbxOyprgewS770K934gLGJbxTodrS"  # Put your TOKEN here
DEVICE_LABEL = "PROYECTO"  # Put your device label here 
VARIABLE_LABEL_1 = "temperature"  # Put your first variable label here
VARIABLE_LABEL_2 = "humidity"  # Put your second variable label here
VARIABLE_LABEL_3 = "estado"
led=5
#####



baud = 9600
ser  = Serial("/dev/serial0",baud)
sleep(0.3)
def peripheral_setup():
 GPIO.setmode(GPIO.BCM)
 GPIO.setup(led, GPIO.OUT)
 GPIO.output(led,True)
 #######

def recibir(echo = True):
 data = ""
 while True:
  input = ser.getchar()
  if echo:
   ser.putchar(input)
  if input == "\r":
   return (data)
  data += input
 sleep(0.2)
  #################
def printsln(menss):
 ser.puts(menss+"\r")
 sleep(0.2)
##################3
def prints(menss):
 ser.puts(menss)
 sleep(0.2)
##################
def build_payload(variable_1, variable_2, variable_3,dato1,dato2,dato3):
    # Creates two random values for sending data
    
    value_1 = dato1
    value_2 = dato2
    value_3=  dato3
    print ("CONECTADO...")  
    

    # Creates a random gps coordinates
   

    payload = {variable_1: value_1,
              variable_2: value_2,
              variable_3: value_3}

    return payload


def post_request(payload):
    # Creates the headers for the HTTP requests
    url = "http://industrial.api.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, DEVICE_LABEL)
    headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}

    # Makes the HTTP requests
    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, json=payload)
        status = req.status_code
        attempts += 1
        sleep(1)

    # Processes results
    if status >= 400:
        print("[ERROR] Could not send data after 5 attempts, please check \
            your token credentials and internet connection")
        return False

    print("[INFO] request made properly, your device is updated")
    return True

#####################
peripheral_setup()

# Main function
def main () :
# Infinite loop
 while True :
 

  mensaje = recibir()
  vals = mensaje.split(',')
  
  
  
  try:
    print(len(vals))
    if (len(vals)==3    ):

       print("----------------")
       print(mensaje)
       payload = build_payload(VARIABLE_LABEL_1, VARIABLE_LABEL_2, VARIABLE_LABEL_3,float(vals[0]),float(vals[1]),int(vals[2]))
       print("[INFO] Attemping to send data")
       post_request(payload)
       print("[INFO] finished")
       
  except:
   print("error")
   pass
  sleep(0.2)
 
 
  
# Command line execution
if __name__ == '__main__' :
 main()