import threading

balance = 1000

thread = threading.Lock()

def update_bal(val):
    global balance
    thread.acquire()
    print("Amount to be withdrawn/deposited :", val)
    if(balance + val < 1000):
        print("Cannot withdraw as balance too low")
    else:
        balance = balance + val
        print("Updated balance is ",balance)
    thread.release()

if __name__ == "__main__":
    print("Current balance before threads start: ",balance)
    x = []
    for i in range(1,11):
        if(random.randint(0,2) == 1):
            x.append(threading.Thread(target=update_bal,args=(200,)))
        else:
            x.append(threading.Thread(target=update_bal,args=(-200,)))

    for i in x:
        i.start()