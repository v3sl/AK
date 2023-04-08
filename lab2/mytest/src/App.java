import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Random;

public class App {

    public static ArrayList<Integer> randomCyclicPermutation(int length) {
        ArrayList<Integer> result = new ArrayList<>(length);
        ArrayList<Integer> unusedIndexes = new ArrayList<>(length - 1);
        for (int i = 0; i < length; ++i) {
            result.add(0);
        }
        for (int i = 0; i < length - 1; ++i) {
            unusedIndexes.add(i + 1);
        }
        int currentIndex = 0;
        for (int i = 0; i < length - 1; ++i) {
            Random rand = new Random();
            int r = Math.abs(rand.nextInt()) % unusedIndexes.size();
            int nextInd = unusedIndexes.get(r);
            remove(unusedIndexes, r);
            result.set(currentIndex, nextInd);
            currentIndex = nextInd;
        }
        return result;
    }

    public static void remove(ArrayList<Integer> s, int i) {
        s.set(i, s.get(s.size() - 1));
        s.remove(s.size() - 1);
    }

    public static double benchmarkLatency(int sizeBytes, int iterations) {
        ArrayList<Integer> array = randomCyclicPermutation(sizeBytes / 4);
        int pointer = 0;
        long time = System.currentTimeMillis();
        for (int i = 0; i < iterations; ++i) {
            pointer = array.get(pointer);
        }
        return (System.currentTimeMillis() - time) * 1000000 / iterations;
    }

    public static void main(String[] args) throws Exception {
        FileWriter writer = new FileWriter("data1.txt");
        for (double i = 5000.0; i <= 20_000_000.0; i *= 1.2) {
            double time = benchmarkLatency((int) (i), 100_000_000);
            String str = Integer.toString((int) i) + ' ' + Double.toString(time) + '\n';
            writer.write(str);
            System.out.println(i);
        }
        writer.close();
    }
}
