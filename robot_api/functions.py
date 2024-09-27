import sqlite3
import messages as msg
from tkinter import *
import requests

def launch_gui(root): # launches the tkinter window using mainloop
    root.mainloop()

def connect_to_db(): # establishes connection to database + creates the cursor object
    conn = sqlite3.connect('userinfo.db')
    cursor = conn.cursor() 
    return conn, cursor

def commit_n_close(conn): # saves changes and connects to database
    conn.commit() 
    conn.close() 

def create_db(): # creates database if not existing already 
    conn, cursor = connect_to_db()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            password TEXT NOT NULL
        )
    ''') 
    # primary key makes it so that the id auto increments, ensuring a unique id for every user
    commit_n_close(conn)

def print_db() : # prints info in database (mainly for debugging)
    conn, cursor = connect_to_db()

    cursor.execute('SELECT * FROM users')
    rows = cursor.fetchall() 

    for x in rows:
        print(x)

    commit_n_close(conn)

def insert_db(the_user, the_pw): # inserts username and password into database
    conn, cursor = connect_to_db()

    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (the_user, the_pw))

    commit_n_close(conn)

def existing_user(the_user): # checks if the username already exists in database
    conn, cursor = connect_to_db()

    cursor.execute('SELECT id FROM users WHERE username = ?', (the_user,))

    result = cursor.fetchone()

    commit_n_close(conn)

    return result is not None # false if user doesn't exist already, true if it does
    
def get_password(the_user): 
    conn, cursor = connect_to_db()

    cursor.execute('SELECT id FROM users WHERE username = ?', (the_user,)) # gets id corresponding to username
    id_number = cursor.fetchone()[0] 
    cursor.execute('SELECT password FROM users WHERE id = ?', (id_number,)) # gets password corresponding to id
    password = cursor.fetchone()[0]

    commit_n_close(conn)
    return password
    
def login_button_func(user, pw): 
    if not user or not pw: # makes sure entry fields are not blank
        msg.blank_entry()
        return
    exists = existing_user(user) # checks if user exists in database
    if not exists:
        msg.invalid_user()
        return
    password = get_password(user) # checks if password is correct 
    if pw != password: 
        msg.wrong_pw()
        return
    else: 
        msg.login(user) # successful login!
        create_robot_gui() # launches robot remote control window

def create_acc_button_func(user, pw): 
    if not user or not pw: # makes sure entries are not empty
        msg.blank_entry()
        return
    exists = existing_user(user) # check if user alr exists
    if exists:
        msg.user_exists() # if user alr exists, login instead of create acc 
        return
    insert_db(user, pw) # insert user and pw into database
    msg.create_acc()

def post_direction(direction):
    try:
        url = "http://127.0.0.1:5000/moving"
        data = {'direction': direction}
        req = requests.post(url, json=data)
        print('command sent successfully')
    except:
        print('something happened; error')

def create_login_page(): # sets up the tkinter window for logging in
    login_page = Tk() 
    login_page.title('user login')
    login_page.geometry('320x150')

    user_entry_text = StringVar()
    pw_entry_text = StringVar()

    entries_panel = Frame(login_page)
    entries_panel.grid(row=1, column=1, rowspan=3,padx=10,pady=5,sticky='NWSE')

    username_entry_label = Label(entries_panel, text='username: ')
    username_entry_label.grid(row=1, column=1, padx=5, pady=5)

    username_entry = Entry(entries_panel, textvariable=user_entry_text)
    username_entry.grid(row=1, column=2, padx=5, pady=5)

    password_entry_label = Label(entries_panel, text='password: ')
    password_entry_label.grid(row=2, column=1, padx=5, pady=5)

    password_entry = Entry(entries_panel, textvariable=pw_entry_text)
    password_entry.grid(row=2, column=2, padx=5, pady=5)

    buttons_panel = Frame(login_page)
    buttons_panel.grid(row=5, column=1, rowspan=1, padx=45, pady=5, sticky='NWSE')

    login_button = Button(buttons_panel, text='login', command=lambda: login_button_func(user_entry_text.get(), pw_entry_text.get())) 
    login_button.grid(row=1, column=1, ipadx=3, ipady=2, padx=5, pady=5)

    create_acc_button = Button(buttons_panel, text='create account', command=lambda: create_acc_button_func(user_entry_text.get(), pw_entry_text.get())) 
    create_acc_button.grid(row=1, column=2, ipadx=3, ipady=2, padx=5, pady=5)
    
    return login_page

def create_robot_gui(): # sets up tkinter window for controlling robot if login is successful
    robot_gui = Toplevel()
    robot_gui.title('robot gui')
    robot_gui.geometry('500x220')

    buttons_panel = Frame(robot_gui)
    buttons_panel.grid(row=5, column=1, rowspan=1, padx=60, pady=30, sticky='NWSE')

    forward = Button(buttons_panel,text='move forward', command = lambda: post_direction('forward'))
    forward.grid(row=1, column=2, padx=5, pady=5, ipadx=5, ipady=5,sticky='we')

    left = Button(buttons_panel, text='move left',command = lambda: post_direction('left'))
    left.grid(row=2, column=1,padx=2.5, pady=5, ipadx=5, ipady=5)

    stop = Button(buttons_panel, text='stop', command = lambda: post_direction('stop'))
    stop.grid(row=2, column=2, padx=2.5, pady=5, ipadx=5, ipady=5,sticky='we')

    right = Button(buttons_panel, text='move right', command = lambda: post_direction('right'))
    right.grid(row=2, column=3,padx=2.5, pady=5, ipadx=5, ipady=5,sticky='we')

    backward = Button(buttons_panel, text='move backward', command = lambda: post_direction('backward'))
    backward.grid(row=3, column=2, padx=2.5, pady=5, ipadx=5, ipady=5, sticky='we')