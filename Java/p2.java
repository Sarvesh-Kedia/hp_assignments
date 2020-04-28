public class p2 {

    public static void main(String[] args) {

        Thread mainThread = Thread.currentThread();
        System.out.println("Main thread details:");
        System.out.println("name: " + mainThread.getName());
        System.out.println("id:" + mainThread.getId());
        System.out.println("status:" + mainThread.getState());
        System.out.println("priority:" + mainThread.getPriority());
        System.out.println("Thread Group: " + mainThread.getThreadGroup().getName());

        ChildThread ct = new ChildThread();
        ct.start();
    }

    private static class ChildThread extends Thread {

        @Override
        public void run() {

            Thread childThread = new Thread();
            System.out.println("\n\nChild thread details:");
            System.out.println("name: " + childThread.getName());
            System.out.println("id:" + childThread.getId());
            System.out.println("status:" + childThread.getState());
            System.out.println("priority:" + childThread.getPriority());
            System.out.println("Thread Group: " + childThread.getThreadGroup().getName());

        }


    }

}
