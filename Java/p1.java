public class p1 {

    public static void main(String[] args) {

        Thread mainThread = Thread.currentThread();
        System.out.println("Main thread details:");
        System.out.println("name: " + mainThread.getName());
        System.out.println("id:" + mainThread.getId());
        System.out.println("status:" + mainThread.getState());
        System.out.println("priority:" + mainThread.getPriority());
        System.out.println("Thread Group: " + mainThread.getThreadGroup().getName());
    }

}