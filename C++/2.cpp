#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

const int n = 5;

int flag = 0;

std::thread *philosopher[n];
std::mutex forks[n], actionmtx;





int pickupfork(int left, int right) {
    if (forks[left].try_lock()) {
        if (forks[right].try_lock()) {
            return 1;
        }
        else {
            forks[left].unlock();
        }
    }
    return 0;
}


void function(int philID) {
    int leftIndex = philID-1;
    int rightIndex = (philID) % (n-1);

    while (1) {
        if (pickupfork(leftIndex, rightIndex)) {
            actionmtx.lock();
               std::cout << "philosopher " << philID << " is eating.\n";
               flag++;
               if(flag==5){
                  break;
               }
            actionmtx.unlock();


            forks[leftIndex].unlock();
            forks[rightIndex].unlock();


            sleep(1000); //cannot acquire again right away
        }
        else {
            actionmtx.lock();
               std::cout << "philosopher " << philID << " is thinking.\n";
            actionmtx.unlock();
        }

    }

   std::cout << "all philosophers have eaten\n";

}


int main() {

    for (int i = 1; i < n+1; i++) {
        philosopher[i-1] = new std::thread(function, i);

    }


    for (int i = 0; i < n; i++) {
         philosopher[i]->join();
    }

    return 0;
}