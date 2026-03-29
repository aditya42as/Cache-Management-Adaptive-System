import customtkinter as ctk
import psutil
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import threading
import json
import random 

# trying out this dark theme, looks way better
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("blue")

class DashboardApp(ctk.CTk):
    def __init__(self):
        super().__init__()
        self.title("Adaptive Predictiveness - Cache Monitor")
        self.geometry("1100x700")
        
        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(0, weight=1)
        
        self.setup_sidebar()
        self.setup_main_view()
        
        self.update_telemetry()
        
    def setup_sidebar(self):
        # side panel for hardware stats
        self.sidebar_frame = ctk.CTkFrame(self, width=250, corner_radius=0, fg_color="#1a1a1a")
        self.sidebar_frame.grid(row=0, column=0, sticky="nsew")
        
        self.title_label = ctk.CTkLabel(self.sidebar_frame, text="HP Victus Vitals", font=ctk.CTkFont(size=24, weight="bold"))
        self.title_label.pack(pady=30, padx=20)
        
        self.cpu_label = ctk.CTkLabel(self.sidebar_frame, text="CPU Usage: 0%", font=ctk.CTkFont(size=18), text_color="#00ffcc")
        self.cpu_label.pack(pady=10, padx=20)
        
        self.ram_label = ctk.CTkLabel(self.sidebar_frame, text="RAM Usage: 0%", font=ctk.CTkFont(size=18), text_color="#ff00cc")
        self.ram_label.pack(pady=10, padx=20)
        
        self.temp_label = ctk.CTkLabel(self.sidebar_frame, text="CPU Temp: N/A", font=ctk.CTkFont(size=18), text_color="#ff3333")
        self.temp_label.pack(pady=10, padx=20)

    def setup_main_view(self):
        # center area for cache logs
        self.main_frame = ctk.CTkFrame(self, fg_color="#262626")
        self.main_frame.grid(row=0, column=1, sticky="nsew", padx=20, pady=20)
        
        self.status_header = ctk.CTkLabel(self.main_frame, text="Cache Event Monitor", font=ctk.CTkFont(size=28, weight="bold"))
        self.status_header.pack(pady=10)
        
        # indicator text that changes color on hits
        self.hit_miss_indicator = ctk.CTkLabel(self.main_frame, text="WAITING", font=ctk.CTkFont(size=22, weight="bold"), 
                                               text_color="gray", corner_radius=10, fg_color="#333333")
        self.hit_miss_indicator.pack(pady=20, ipadx=20, ipady=10)
        
        self.log_box = ctk.CTkTextbox(self.main_frame, width=700, height=300, font=ctk.CTkFont(family="Consolas", size=14))
        self.log_box.pack(pady=10, padx=20, expand=True, fill="both")
        
    def update_telemetry(self):
        # pull live cpu/ram usage from psutil
        cpu_percent = psutil.cpu_percent()
        ram_percent = psutil.virtual_memory().percent
        
        temp_val = "N/A"
        if hasattr(psutil, "sensors_temperatures") and psutil.sensors_temperatures():
            temps = psutil.sensors_temperatures()
            if 'coretemp' in temps:
                temp_val = f"{temps['coretemp'][0].current}°C"
                
        self.cpu_label.configure(text=f"CPU Usage: {cpu_percent}%")
        self.ram_label.configure(text=f"RAM Usage: {ram_percent}%")
        self.temp_label.configure(text=f"CPU Temp: {temp_val}")
        
        # loop this every 2 secs
        self.after(2000, self.update_telemetry)
        
    def update_cache_status(self, json_data):
        try:
            data = json.loads(json_data)
            status_text = f"EVENT: Address {data.get('address')} "
            
            # toggle green/red based on cache hit
            if data.get("hit"):
                self.hit_miss_indicator.configure(text="CACHE HIT", text_color="#00ffcc", fg_color="#004d40")
                status_text += "[HIT]"
            else:
                self.hit_miss_indicator.configure(text="CACHE MISS", text_color="#ff3333", fg_color="#4d0000")
                status_text += "[MISS]"
                
            stride_info = data.get("stride_info", {})
            status_text += f"\nPredicted Next: {stride_info.get('predicted_next', 'N/A')} (Stride: {stride_info.get('stride', 0)})\n"
            
            self.log_box.insert("end", status_text + "-"*40 + "\n")
            self.log_box.see("end")
            
        except json.JSONDecodeError:
            self.log_box.insert("end", f"RAW C++: {json_data}\n")
            self.log_box.see("end")

if __name__ == "__main__":
    app = DashboardApp()
    app.mainloop()
