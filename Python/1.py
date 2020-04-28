import threading
import time

def thread_func(name, delay):
    time.sleep(delay)
    print("Thread ", name,"running after delay of ", delay, " second(s)")



a = threading.Thread(target=thread_func,args=(1,1))
b = threading.Thread(target=thread_func,args=(2,2))

a.start()
b.start()