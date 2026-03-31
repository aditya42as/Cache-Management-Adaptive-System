import subprocess
import threading
import sys
import time
from dashboard.ui_main import DashboardApp

def run_cpp_backend(app):
    try:
        print("Starting C++ Backend...")
        
        process = subprocess.Popen(
            ["backend_main.exe"],                  
            stdout=subprocess.PIPE,                
            text=True,                             
            bufsize=1,                             
            universal_newlines=True
        )
        
        print("C++ Backend launched successfully!")
        
        for line in process.stdout:
            line = line.strip()
            if line:                               
                app.update_cache_status(line)      
                
        process.wait()
        
    except FileNotFoundError:
        print("ERROR: Could not find 'backend_main.exe'")
        print("Make sure backend_main.exe is in the same folder as this Python file.")
        print("You can also run build.bat first to generate it.")
        
    except Exception as e:
        print(f"Unexpected error: {e}")

def main():
    app = DashboardApp()
    
    backend_thread = threading.Thread(target=run_cpp_backend, args=(app,), daemon=True)
    backend_thread.start()
    
    app.mainloop()

if __name__ == "__main__":
    main()