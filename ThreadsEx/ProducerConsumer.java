import java.util.Random;

public class ProducerConsumer {

    public static void main(String[] args) throws InterruptedException {
        //Class for all methods
        final PC pc = new PC();

        // Create producer thread
        Thread Produce = new Thread(new Runnable() {
            @Override
            public void run()
            {
                try
                {
                    pc.produce();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });

        // Create consumer thread
        Thread Consume = new Thread(new Runnable() {
            @Override
            public void run()
            {
                try
                {
                    pc.consume();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });

        //Start both threads
        Produce.start();
        Consume.start();

        //End of threads
        Produce.join();
        Consume.join();

        System.out.println("Exiting!");
    }

    //Class contains producer consumer and buffer
    public static class PC {
        //Buffer
        double[] buffer = new double[1000];
        //Prodcer Funct.
        public void produce() throws InterruptedException {
            int bufferValueCounter = 0;
            int itemsProduced = 0;
            while (itemsProduced != 1000000) {
                synchronized (this) {
                    //Producer waits while buffer is full
                    while (buffer[999] != 0) {
                        wait();
                    }
                    //Producer produces
                    for (int i = 0; i < buffer.length; i++){
                        Random random = new Random();
                        double randy = random.nextDouble() * 100.0;
                        bufferValueCounter += randy;
                        buffer[i] = randy;
                        itemsProduced++;
                        if (itemsProduced % 100000 == 0){
                            System.out.println("Producer: Generated " + itemsProduced + " items, Cumulative value of generated items=" + bufferValueCounter);
                        }
                    }

                    //Notifies consumer
                    notify();

                }
            }
            System.out.println("Producer: Finished generating " + itemsProduced + " items");
        }

        // Function called by consumer thread
        public void consume() throws InterruptedException {
            int bufferValueCounter = 0;
            int itemsProduced = 0;
            while (itemsProduced != 1000000){
                synchronized (this) {
                    //Consumer waits while buffer is empty
                    while (buffer[999] == 0) {
                        wait();
                    }
                    //Consumer consumes
                    for (int i = 0; i < buffer.length; i++){
                        double val = buffer[i];
                        bufferValueCounter += val;
                        itemsProduced++;
                        if (itemsProduced % 100000 == 0){
                            System.out.println("Consumer: Generated " + itemsProduced + " items, Cumulative value of generated items=" + bufferValueCounter);
                        }
                        buffer[i] = 0;
                    }

                    // Notify producer
                    notify();


                }
            }
            System.out.println("Consumer: Finished generating " + itemsProduced + " items");

        }
    }
}
