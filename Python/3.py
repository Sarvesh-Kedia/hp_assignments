from threading import Thread, currentThread, Lock
from random import randint
import queue


class mpq:
    def __init__(self):
        self.queue = queue.Queue()
        self.lock = Lock()

    def get(self):
        if (self.empty()==False):
            self.lock.acquire()
            i= self.queue.get()
            print("Thread no", currentThread().getName(),"getting",i)
            self.lock.release()
            return i
        return None

    def put(self,item):
        self.lock.acquire()
        i = self.queue.put(item)
        print("Thread no", currentThread().getName(),"putting",item)
        self.lock.release()
        return i

    def empty(self):
        self.lock.acquire()
        i = self.queue.empty()
        self.lock.release()
        return i



if __name__ == '__main__':

    mpq = mpq()
    threads = []

    for i in range(1,12):
        
        if (randint(1, 10)%2):
            threads.append(Thread(None, mpq.put, i,(randint(5,200),)))
        else:
            threads.append(Thread(None, mpq.get, i, ))

    for i in range(len(threads)):
        threads[i].start()

    for i in range(len(threads)):
        threads[i].join()

