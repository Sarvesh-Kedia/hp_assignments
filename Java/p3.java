public class p3 {

    public static void main(String[] args) {

        Thread main_thread = Thread.currentThread();
        System.out.println("this is main thread");

        Thread child_thread = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("this is child thread");
            }
        });

        
        child_thread.start();
    }

}