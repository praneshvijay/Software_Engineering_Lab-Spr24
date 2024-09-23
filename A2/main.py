import tkinter as tk
import tkinter.messagebox as messagebox
import sqlite3
import re

class person:
    def __init__(self, userid, password, name, dob, stype) :
        self._userid = userid
        self._password = password
        self._name = name
        self._dob = dob
        self._stype = stype
        
class student(person):
    def __init__(self, userid, password, name, dob, stype, rollno, grad):
        super().__init__(userid, password, name, dob, stype)
        self._grad = grad
        self._rollno = rollno
        
class teacher(person):
    def __init__(self, userid, password, name, dob, stype, empid):
        super().__init__(userid, password, name, dob, stype)
        self._empid = empid
        
class ugstudent(student):
    def __init__(self, userid, password, name, dob, stype, rollno, grad, hall):
        super().__init__(userid, password, name, dob, stype, rollno, grad)
        self._hall = hall
        
class pgstudent(student):
    def __init__(self, userid, password, name, dob, stype, rollno, grad):
        super().__init__(userid, password, name, dob, stype, rollno, grad)
        
#Create database with tables
conn = sqlite3.connect("database.db")
c = conn.cursor()
c.execute("CREATE TABLE IF NOT EXISTS users (userid TEXT PRIMARY KEY, password TEXT, name TEXT, dob TEXT, type TEXT, attempts INTEGER)")
c.execute("CREATE TABLE IF NOT EXISTS ugstudents (userid TEXT PRIMARY KEY, rollno TEXT, grad TEXT, hall TEXT)")
c.execute("CREATE TABLE IF NOT EXISTS pgstudents (userid TEXT PRIMARY KEY, rollno TEXT, grad TEXT)")
c.execute("CREATE TABLE IF NOT EXISTS teachers (userid TEXT PRIMARY KEY, empid TEXT)")
conn.commit()
conn.close()
        
class registerframe():
    def __init__(self, master):
        #Based on _register
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Register", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "User ID", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._userid = tk.Entry(self._frame, font = ("Times New Roman", 15))
        self._userid.grid(row = 1, column = 1, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
        self._password = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._password.grid(row = 2, column = 1, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "Confirm Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 3, column = 0, padx = 10, pady = 10)
        self._cpassword = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._cpassword.grid(row = 3, column = 1, padx = 10, pady = 10)
        #Type Dropdown
        self._label = tk.Label(self._frame, text = "Type", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 4, column = 0, padx = 10, pady = 10)
        self._type = tk.StringVar()
        self._type.set("Select")
        self._dropdown = tk.OptionMenu(self._frame, self._type, "UG Student", "PG Student", "Teacher")
        self._dropdown.config(font = ("Times New Roman", 15))
        self._dropdown.grid(row = 4, column = 1, padx = 10, pady = 10)
        
        self._button = tk.Button(self._frame, text = "Register", font = ("Times New Roman", 15), command = self._register)
        self._button.grid(row = 5, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
        self._button.grid(row = 6, column = 0, columnspan = 2, padx = 10, pady = 10)
        
        
    def _register(self):
        #Common registerframes for all types of users, only userid, password, type
        if self._userid.get() == "" or self._password.get() == "" or self._cpassword.get() == "" or self._type.get() == "Select":
            messagebox.showerror("Error", "Please fill all the fields")
            return
        
        #Validate userid as valid email
        if not re.search("[a-zA-Z0-9]+@[a-zA-Z]+\.[a-zA-Z]+", self._userid.get()):
            messagebox.showerror("Error", "Invalid email id")
            return
        
        if self._password.get() != self._cpassword.get():
            messagebox.showerror("Error", "Passwords do not match")
            return
        
        #Validate password as strong
        if len(self._password.get()) < 8 or len(self._password.get()) > 12:
            messagebox.showerror("Error", "Password must be between 8 and 12 characters")
            return
        if not re.search("[a-z]", self._password.get()):
            messagebox.showerror("Error", "Password must contain at least one lowercase letter")
            return
        if not re.search("[A-Z]", self._password.get()):
            messagebox.showerror("Error", "Password must contain at least one uppercase letter")
            return
        if not re.search("[0-9]", self._password.get()):
            messagebox.showerror("Error", "Password must contain at least one digit")
            return
        if not re.search("[!@#$%^&*]", self._password.get()):
            messagebox.showerror("Error", "Password must contain at least one special character")
            return
        
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE userid = ?", (self._userid.get(),))
        if c.fetchone() != None:
            messagebox.showerror("Error", "User ID already exists")
            conn.close()
            return

        c.execute("INSERT INTO users VALUES (?, ?, ?, ?, ?, ?)", (self._userid.get(), self._password.get(), "", "", self._type.get(),0))
        if self._type.get() == "UG Student":
            c.execute("INSERT INTO ugstudents VALUES (?, ?, ?, ?)", (self._userid.get(), "", "", ""))
        elif self._type.get() == "PG Student":
            c.execute("INSERT INTO pgstudents VALUES (?, ?, ?)", (self._userid.get(), "", ""))
        else:
            c.execute("INSERT INTO teachers VALUES (?, ?)", (self._userid.get(), ""))
        conn.commit()
        conn.close()
        
        messagebox.showinfo("Success", "User registered successfully")
        #Go back to login page
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = loginframe(self._master)
        self._master.mainloop()
        return
    
    def _back(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = mainframe(self._master)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
    
class loginframe():
    
    #Login frame, no need to show register option, show back option to go back to main page
    def __init__(self, master):
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Login", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "User ID", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._userid = tk.Entry(self._frame, font = ("Times New Roman", 15))
        self._userid.grid(row = 1, column = 1, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
        self._password = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._password.grid(row = 2, column = 1, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Login", font = ("Times New Roman", 15), command = self._login)
        self._button.grid(row = 3, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
        self._button.grid(row = 4, column = 0, columnspan = 2, padx = 10, pady = 10)
        
    def _login(self):
        if self._userid.get() == "" or self._password.get() == "":
            messagebox.showerror("Error", "Please fill all the fields")
            return
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE userid = ?", (self._userid.get(),))
        user = c.fetchone()
        if user == None:
            messagebox.showerror("Error", "User ID does not exist")
            conn.close()
            return
        c.execute("SELECT * FROM users WHERE userid = ? AND password = ?", (self._userid.get(), self._password.get()))
        user = c.fetchone()
        if user == None:
            c.execute("UPDATE users SET attempts = attempts + 1 WHERE userid = ?", (self._userid.get(),))
            conn.commit()
            #If attempts > 3, deactivate account
            c.execute("SELECT * FROM users WHERE userid = ?", (self._userid.get(),))
            user = c.fetchone()
            if user[5] > 2:
                c.execute("SELECT * FROM users WHERE userid = ?", (self._userid.get(),))
                user = c.fetchone()     
                type = user[4]
                c.execute("DELETE FROM users WHERE userid = ?", (self._userid.get(),))
                if type == "UG Student":
                    c.execute("DELETE FROM ugstudents WHERE userid = ?", (self._userid.get(),))
                elif type == "PG Student":
                    c.execute("DELETE FROM pgstudents WHERE userid = ?", (self._userid.get(),))
                else:
                    c.execute("DELETE FROM teachers WHERE userid = ?", (self._userid.get(),))
                conn.commit()
                conn.close()
                messagebox.showinfo("Success", "User deactivated due to multiple incorrect attempts")
                self._master.destroy()
                self._master = tk.Tk()
                self._frame = loginframe(self._master)
                self._master.mainloop()
                return
            
            c.execute("SELECT * FROM users WHERE userid = ?", (self._userid.get(),))
            user = c.fetchone()
            messagebox.showerror("Error", "Incorrect password! Attempts remaining: " + str(3 - user[5]))
            
            conn.close()
            return
        
        #Reset attempts
        c.execute("UPDATE users SET attempts = 0 WHERE userid = ?", (self._userid.get(),))
        conn.commit()
        conn.close()
        
        user_id = self._userid.get()
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, user_id)
        self._master.mainloop()
        return
    
    def _back(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = mainframe(self._master)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
     
class dashboardframe():
    #Have features like edit profile, deactivate account, logout, change password
    def __init__(self, master, userid):
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._userid = userid
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Dashboard", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Edit Profile", font = ("Times New Roman", 15), command = self._editprofile)
        self._button.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Deactivate Account", font = ("Times New Roman", 15), command = self._deactivateaccount)
        self._button.grid(row = 2, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Change Password", font = ("Times New Roman", 15), command = self._changepassword)
        self._button.grid(row = 3, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Logout", font = ("Times New Roman", 15), command = self._logout)
        self._button.grid(row = 4, column = 0, padx = 10, pady = 10)  
        
    def _editprofile(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = editprofileframe(self._master, self._userid)
        self._master.mainloop()
        return
    
    def _deactivateaccount(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = deactivateaccountframe(self._master, self._userid)
        self._master.mainloop()
        return
    
    def _logout(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = loginframe(self._master)
        self._master.mainloop()
        return
    
    def _changepassword(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = changepasswordframe(self._master, self._userid)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
    
class editprofileframe():
    #Edit profile is different for different types of users, the aldready filled fields should be displayed and be editable
    def __init__(self, master, userid):
        self._master = master
        self._master.title("AcAdemic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._userid = userid
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE userid = ?", (self._userid,))
        user = c.fetchone()
        if user[4] == "UG Student":
            c.execute("SELECT * FROM ugstudents WHERE userid = ?", (self._userid,))
            user = user + c.fetchone()
        elif user[4] == "PG Student":
            c.execute("SELECT * FROM pgstudents WHERE userid = ?", (self._userid,))
            user = user + c.fetchone()
        else:
            c.execute("SELECT * FROM teachers WHERE userid = ?", (self._userid,))
            user = user + c.fetchone()
        self._type = tk.StringVar()
        self._type.set(user[4])
        conn.close()
        self._label = tk.Label(self._frame, text = "Edit Profile", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "User ID", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._userid = tk.Entry(self._frame, font = ("Times New Roman", 15))
        self._userid.insert(0, user[0])
        self._userid.config(state = "disabled")
        self._userid.grid(row = 1, column = 1, padx = 10, pady = 10)
        
        if user[4] == "UG Student":
            self._label = tk.Label(self._frame, text = "Name", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
            self._name = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._name.insert(0, user[2])
            self._name.grid(row = 2, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Date of Birth", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 3, column = 0, padx = 10, pady = 10)
            self._dob = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._dob.insert(0, user[3])
            self._dob.grid(row = 3, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Roll No.", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 4, column = 0, padx = 10, pady = 10)
            self._rollno = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._rollno.insert(0, user[7])
            self._rollno.grid(row = 4, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Graduation Year", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 5, column = 0, padx = 10, pady = 10)
            self._grad = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._grad.insert(0, user[8])
            self._grad.grid(row = 5, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Hall", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 6, column = 0, padx = 10, pady = 10)
            self._hall = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._hall.insert(0, user[9])
            self._hall.grid(row = 6, column = 1, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Save", font = ("Times New Roman", 15), command = self._save)
            self._button.grid(row = 7, column = 0, columnspan = 2, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
            self._button.grid(row = 8, column = 0, columnspan = 2, padx = 10, pady = 10)
            
        elif user[4] == "PG Student":
            self._label = tk.Label(self._frame, text = "Name", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
            self._name = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._name.insert(0, user[2])
            self._name.grid(row = 2, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Date of Birth", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 3, column = 0, padx = 10, pady = 10)
            self._dob = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._dob.insert(0, user[3])
            self._dob.grid(row = 3, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Roll No.", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 4, column = 0, padx = 10, pady = 10)
            self._rollno = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._rollno.insert(0, user[7])
            self._rollno.grid(row = 4, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Graduation Year", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 5, column = 0, padx = 10, pady = 10)
            self._grad = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._grad.insert(0, user[8])
            self._grad.grid(row = 5, column = 1, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Save", font = ("Times New Roman", 15), command = self._save)
            self._button.grid(row = 7, column = 0, columnspan = 2, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
            self._button.grid(row = 8, column = 0, columnspan = 2, padx = 10, pady = 10)
            
        else:
            self._label = tk.Label(self._frame, text = "Name", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
            self._name = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._name.insert(0, user[2])
            self._name.grid(row = 2, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Date of Birth", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 3, column = 0, padx = 10, pady = 10)
            self._dob = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._dob.insert(0, user[3])
            self._dob.grid(row = 3, column = 1, padx = 10, pady = 10)
            self._label = tk.Label(self._frame, text = "Employee ID", font = ("Times New Roman", 15), bg = "#ffffff")
            self._label.grid(row = 4, column = 0, padx = 10, pady = 10)
            self._empid = tk.Entry(self._frame, font = ("Times New Roman", 15))
            self._empid.insert(0, user[7])
            self._empid.grid(row = 4, column = 1, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Save", font = ("Times New Roman", 15), command = self._save)
            self._button.grid(row = 5, column = 0, columnspan = 2, padx = 10, pady = 10)
            self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
            self._button.grid(row = 6, column = 0, columnspan = 2, padx = 10, pady = 10)
            
    def _save(self):
        
        if self._name.get() == "" or self._dob.get() == "":
            messagebox.showerror("Error", "Please fill all the fields")
            return
        
        if self._dob.get() != "":
            try:
                dob = self._dob.get().split("/")
                if len(dob) != 3:
                    messagebox.showerror("Error", "Invalid date of birth")
                    return
                if int(dob[0]) < 1 or int(dob[0]) > 31 or int(dob[1]) < 1 or int(dob[1]) > 12 or int(dob[2]) < 1900 or int(dob[2]) > 2020:
                    messagebox.showerror("Error", "Invalid date of birth")
                    return
            except:
                messagebox.showerror("Error", "Invalid date of birth")
                return
        
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
        c.execute("UPDATE users SET name = ?, dob = ? WHERE userid = ?", (self._name.get(), self._dob.get(), self._userid.get()))
        if c.rowcount == 0:
            messagebox.showerror("Error", "User ID does not exist")
            conn.close()
            return
        if self._type.get() == "UG Student":
            c.execute("UPDATE ugstudents SET rollno = ?, grad = ?, hall = ? WHERE userid = ?", (self._rollno.get(), self._grad.get(), self._hall.get(), self._userid.get()))
        elif self._type.get() == "PG Student":
            c.execute("UPDATE pgstudents SET rollno = ?, grad = ? WHERE userid = ?", (self._rollno.get(), self._grad.get(), self._userid.get()))
        else:
            c.execute("UPDATE teachers SET empid = ? WHERE userid = ?", (self._empid.get(), self._userid.get()))
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "User updated successfully")
        #While going back, keep the userid same
        user_id = self._userid.get()
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, user_id)
        self._master.mainloop()
        return

    def _back(self):
        #While going back, keep the userid same
        user_id = self._userid.get()
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, user_id)
        self._master.mainloop()
        return

    def _close(self):
        self._master.destroy()
        return
    
class deactivateaccountframe():
    def __init__(self, master, userid):
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._userid = userid
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Are you sure you want to deactivate your account?", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Yes", font = ("Times New Roman", 15), command = self._yes)
        self._button.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "No", font = ("Times New Roman", 15), command = self._no)
        self._button.grid(row = 1, column = 1, padx = 10, pady = 10)
        
    def _yes(self):
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE userid = ?", (self._userid,))
        user = c.fetchone()
        type = user[4]
        c.execute("DELETE FROM users WHERE userid = ?", (self._userid,))
        if type == "UG Student":
            c.execute("DELETE FROM ugstudents WHERE userid = ?", (self._userid,))
        elif type == "PG Student":
            c.execute("DELETE FROM pgstudents WHERE userid = ?", (self._userid,))
        else:
            c.execute("DELETE FROM teachers WHERE userid = ?", (self._userid,))
        if c.rowcount == 0:
            messagebox.showerror("Error", "User ID does not exist")
            conn.close()
            return
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "User deactivated successfully")
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = loginframe(self._master)
        self._master.mainloop()
        return
    
    def _no(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, self._userid)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
  
class changepasswordframe():
    def __init__(self, master, userid):
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._userid = userid
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Change Password", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "Old Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._oldpassword = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._oldpassword.grid(row = 1, column = 1, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "New Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 2, column = 0, padx = 10, pady = 10)
        self._newpassword = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._newpassword.grid(row = 2, column = 1, padx = 10, pady = 10)
        self._label = tk.Label(self._frame, text = "Confirm New Password", font = ("Times New Roman", 15), bg = "#ffffff")
        self._label.grid(row = 3, column = 0, padx = 10, pady = 10)
        self._cnewpassword = tk.Entry(self._frame, font = ("Times New Roman", 15), show = "*")
        self._cnewpassword.grid(row = 3, column = 1, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Change Password", font = ("Times New Roman", 15), command = self._changepassword)
        self._button.grid(row = 4, column = 0, columnspan = 2, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Back", font = ("Times New Roman", 15), command = self._back)
        self._button.grid(row = 5, column = 0, columnspan = 2, padx = 10, pady = 10)
        
    def _changepassword(self):
        if self._oldpassword.get() == "" or self._newpassword.get() == "" or self._cnewpassword.get() == "":
            messagebox.showerror("Error", "Please fill all the fields")
            return
        
        conn = sqlite3.connect("database.db")
        c = conn.cursor()
            
        #Check if old pawssword is correct
        c.execute("SELECT * FROM users WHERE userid = ? AND password = ?", (self._userid, self._oldpassword.get()))
        if c.fetchone() == None:
            messagebox.showerror("Error", "Old password is incorrect")
            conn.close()
            return
        
        if self._newpassword.get() != self._cnewpassword.get():
            messagebox.showerror("Error", "Passwords do not match")
            return
        
        #Validate password as strong
        if len(self._newpassword.get()) < 8 or len(self._newpassword.get()) > 12:
            messagebox.showerror("Error", "Password must be between 8 and 12 characters")
            return
        if not re.search("[a-z]", self._newpassword.get()):
            messagebox.showerror("Error", "Password must contain at least one lowercase letter")
            return
        if not re.search("[A-Z]", self._newpassword.get()):
            messagebox.showerror("Error", "Password must contain at least one uppercase letter")
            return
        if not re.search("[0-9]", self._newpassword.get()):
            messagebox.showerror("Error", "Password must contain at least one digit")
            return
        if not re.search("[!@#$%^&*]", self._newpassword.get()):
            messagebox.showerror("Error", "Password must contain at least one special character")
            return
        
        c.execute("SELECT * FROM users WHERE userid = ? AND password = ?", (self._userid, self._oldpassword.get()))
        if c.fetchone() == None:
            messagebox.showerror("Error", "Old password is incorrect")
            conn.close()
            return
        c.execute("UPDATE users SET password = ? WHERE userid = ?", (self._newpassword.get(), self._userid))
        conn.commit()
        conn.close()
        messagebox.showinfo("Success", "Password changed successfully")
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, self._userid)
        self._master.mainloop()
        return  
    
    def _back(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = dashboardframe(self._master, self._userid)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
       
class mainframe():
    def __init__(self, master):
        self._master = master
        self._master.title("Academic Management System")
        self._master.geometry("500x500")
        self._master.resizable(False, False)
        self._master.configure(background = "#ffffff")
        #self._master.iconbitmap("icon.ico")
        self._master.protocol("WM_DELETE_WINDOW", self._close)
        self._frame = tk.Frame(self._master, bg = "#ffffff")
        self._frame.pack()
        self._label = tk.Label(self._frame, text = "Welcome to Academic Management", font = ("Times New Roman", 20), bg = "#ffffff")
        self._label.grid(row = 0, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Login", font = ("Times New Roman", 15), command = self._login)
        self._button.grid(row = 1, column = 0, padx = 10, pady = 10)
        self._button = tk.Button(self._frame, text = "Register", font = ("Times New Roman", 15), command = self._register)
        self._button.grid(row = 2, column = 0, padx = 10, pady = 10)
        #CLose Button
        self._button = tk.Button(self._frame, text = "Close", font = ("Times New Roman", 15), command = self._close)
        self._button.grid(row = 3, column = 0, padx = 10, pady = 10)
        
    def _login(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = loginframe(self._master)
        self._master.mainloop()
        return
    
    def _register(self):
        self._master.destroy()
        self._master = tk.Tk()
        self._frame = registerframe(self._master)
        self._master.mainloop()
        return
    
    def _close(self):
        self._master.destroy()
        return
    
if __name__ == "__main__":
    root = tk.Tk()
    app = mainframe(root)
    root.mainloop()
    
          