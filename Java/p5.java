public class p5 extends Thread {

    public static void main(String[] args) {

        ThreadJoin thread1 = new ThreadJoin();
        ThreadJoin thread2 = new ThreadJoin();

        thread1.start();

        try {
            System.out.println("Current Thread: "+ Thread.currentThread().getName());
            thread1.join();
        } catch (Exception ex) {
            System.out.println("Error");
        }

        thread2.start();

        try {
            System.out.println("Current Thread: "+ Thread.currentThread().getName());
            thread2.join();
        } catch (Exception ex) {
            System.out.println("Error");
        }

    }
}

class ThreadJoin extends Thread {
    @Override
    public void run() {
        for (int i = 0; i < 2; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("(inside function)Current Thread: "+ Thread.currentThread().getName());
            } catch (Exception ex) {
                System.out.println("Error");
            }
        }
    }
}