import tkinter as tk
import requests 
import time
window = tk.Tk()
window.title('IoT and sensors fusion')
window.geometry('400x600')

var1 = tk.StringVar()
var2 = tk.StringVar()
var3 = tk.StringVar()
l1 = tk.Label(window, textvariable=var1, font=('Arial', 20), width=30,height=2).place(x=200,y=200,anchor='center')
#l.pack()
l2 = tk.Label(window, textvariable=var2,font=('Arial', 20), width=30,height=2).place(x=200,y=300,anchor='center')
l2 = tk.Label(window, textvariable=var3,font=('Arial', 20), width=30,height=2).place(x=200,y=100,anchor='center')
#l2 = tk.Label(window, textvariable=var2, bg='red', font=('Arial', 12), width=15,height=2).place(x=200,y=80,anchor='center')
var1.set("Is it raining now?")
var2.set("update thingspeak and arduino")
var3.set("Iot and Sensors Fusion")

'''
on_hit = False

def hit_me():
    global on_hit
    if on_hit == False:
        on_hit = True
        var1.set('no func')
        a=11

    else:
        on_hit = False
        var1.set('no func')
        a=10
'''
def hit_button_raining():
    var2.set('It\'s raining now.')
    a=11
    update_ts_arduino(a)
def hit_button_notraining():
    var2.set('It isn\'t raining now.')
    a=10
    update_ts_arduino(a)

  
button1 = tk.Button(window, text='yes', width=10,height=2, command=hit_button_raining).place(x=100,y=350,anchor='center')
#b.pack()
button2=tk.Button(window, text='no', width=10,height=2, command=hit_button_notraining).place(x=300,y=350,anchor='center')
button3 = tk.Button(window, text='shower', width=10,height=2, command=hit_button_raining).place(x=100,y=400,anchor='center')
#b.pack()
button4=tk.Button(window, text='heavy rain', width=10,height=2, command=hit_button_notraining).place(x=300,y=400,anchor='center')


def update_ts_arduino(a):
    string=''
    string =str(a)
    r = requests.get('https://api.thingspeak.com/update?api_key=7WGCAERVOGIX1J5Y&field5='+string)
    #r=requests.get('https://api.thingspeak.com/channels/437741/feeds.json?results=1')
    print(r.status_code)

window.mainloop()
