public class p4 extends Thread {

    public static void main(String[] args) {
        p4 thread1 = new p4();
        p4 thread2 = new p4();

        thread1.start(); // interrupted thread
        thread2.start(); // uninterrupted thread

        System.out.println("Is thread1 interrupted:" + thread1.isInterrupted());
        System.out.println("Is thread2 interrupted:" + thread2.isInterrupted());


        thread1.interrupt();
        System.out.println("\nIs thread1 interrupted:" + thread1.isInterrupted());
        System.out.println("Is thread2 interrupted:" + thread2.isInterrupted());


    }


    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            try {
                Thread.sleep(2000);
                System.out.println(i);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }




}