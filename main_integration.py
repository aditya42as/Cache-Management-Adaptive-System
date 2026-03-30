import subprocess
import threading
import sys
import time
from dashboard.ui_main import DashboardApp

def run_cpp_backend(app):
    # gonna run the cpp exe here later with popen
    time.sleep(2)
    
    # dummy outputs for now to test ui
    fake_cpp_stdout = [
        '{"event": "access", "address": 1000, "hit": false, "stride_info": {"stride": 0, "predicted_next": 1000}}',
        '{"event": "access", "address": 1008, "hit": false, "stride_info": {"stride": 8, "predicted_next": 1016}}',
        '{"event": "access", "address": 1016, "hit": true, "stride_info": {"stride": 8, "predicted_next": 1024}}',
        '{"event": "access", "address": 1024, "hit": true, "stride_info": {"stride": 8, "predicted_next": 1032}}'
    ]
    
    for line in fake_cpp_stdout:
        app.update_cache_status(line)
        time.sleep(3)

def main():
    app = DashboardApp()
    
    # put the cpp listener on diff thread so window doesn't crash
    backend_thread = threading.Thread(target=run_cpp_backend, args=(app,), daemon=True)
    backend_thread.start()
    
    app.mainloop()

if __name__ == "__main__":
    main()
