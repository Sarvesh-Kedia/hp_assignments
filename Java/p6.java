public class p6 {

    public static int balance_amount = 1000;

    public static class Deposit implements Runnable {

        @Override
        public void run() {
            System.out.println("deposits:");

            synchronized (this) {
                balance_amount += 200;
            }
            System.out.println(balance_amount);
        }
    }

    public static class Withdraw implements Runnable {

        @Override
        public void run() {
            System.out.println("withdrawals:");

            synchronized (this) {
                if (balance_amount-200 < 1000) {
                    System.out.println("cannot withdraw (minimum balance needs to be 1000)");
                }
                else{
                    balance_amount -= 200;
                }

            }

            System.out.println(balance_amount);
        }
    }

    public static void main(String[] args) throws InterruptedException {

        int threadnum = 20;
        Thread[] threads = new Thread[threadnum];
        Random random = new Random();

        for (int i = 0; i < threadnum; i++) {
            int val = random.nextInt(2);
            if (val == 1) {
                threads[i] = new Thread(new Withdraw());
            } else {
                threads[i] = new Thread(new Deposit());

            }
            threads[i].start();
            threads[i].join();
        }

    }
}