import tkinter as tk
import serial
import keyboard

ser = serial.Serial('COM3', 9600)

def send_keyboard_input(key):
    keyboard.press(key)
    keyboard.release(key)

def set_button_function(button_number, function):
    if button_number == 1:
        global button1_function
        button1_function = function
    elif button_number == 2:
        global button2_function
        button2_function = function
    elif button_number == 3:
        global button3_function
        button3_function = function
    elif button_number == 4:
        global button4_function
        button4_function = function

def call_button_function(button_number):
    if button_number == 1:
        function = button1_function
    elif button_number == 2:
        function = button2_function
    elif button_number == 3:
        function = button3_function
    elif button_number == 4:
        function = button4_function
    else:
        return
    ser.write(str(button_number).encode('utf-8') + b'\n')
    if function == "a":
        send_keyboard_input('a')
    elif function == "b":
        send_keyboard_input('b')
    elif function == "c":
        send_keyboard_input('c')
    elif function == "d":
        send_keyboard_input('d')

root = tk.Tk()
root.title("Button Control")

config_frame = tk.Frame(root)
config_frame.pack(side=tk.TOP, padx=10, pady=10)

button1_label = tk.Label(config_frame, text="Button 1:")
button1_label.grid(row=0, column=0, padx=10, pady=10)
button1_entry = tk.Entry(config_frame)
button1_entry.grid(row=0, column=1, padx=10, pady=10)
button2_label = tk.Label(config_frame, text="Button 2:")
button2_label.grid(row=1, column=0, padx=10, pady=10)
button2_entry = tk.Entry(config_frame)
button2_entry.grid(row=1, column=1, padx=10, pady=10)
button3_label = tk.Label(config_frame, text="Button 3:")
button3_label.grid(row=2, column=0, padx=10, pady=10)
button3_entry = tk.Entry(config_frame)
button3_entry.grid(row=2, column=1, padx=10, pady=10)
button4_label = tk.Label(config_frame, text="Button 4:")
button4_label.grid(row=3, column=0, padx=10, pady=10)
button4_entry = tk.Entry(config_frame)
button4_entry.grid(row=3, column=1, padx=10, pady=10)

def save_button_configurations():
    set_button_function(1, button1_entry.get())
    set_button_function(2, button2_entry.get())
    set_button_function(3, button3_entry.get())
    set_button_function(4, button4_entry.get())

save_button = tk.Button(config_frame, text="Save", command=save_button_configurations)
save_button.grid(row=4, column=0, pady=10)
button_frame = tk.Frame(root)
button_frame.pack(side=tk.TOP, padx=10, pady=10)

button1 = tk.Button(button_frame, text="Button 1", command=lambda: call_button_function(1))
button1.pack(side=tk.LEFT, padx=10, pady=10)
button2 = tk.Button(button_frame, text="Button 2", command=lambda: call_button_function(2))
button2.pack(side=tk.LEFT, padx=10, pady=10)
button3 = tk.Button(button_frame, text="Button 3", command=lambda: call_button_function(3))
button3.pack(side=tk.LEFT, padx=10, pady=10)
button4 = tk.Button(button_frame, text="Button 4", command=lambda: call_button_function(4))
button4.pack(side=tk.LEFT, padx=10, pady=10)

root.mainloop()
