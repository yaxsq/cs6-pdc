import java.util.Random;

public class Main {
    static final int N = 1000;
    static int[][] M1 = new int[N][N];
    static int[][] M2 = new int[N][N];
    static int[][] M3 = new int[N][N];

    // Function to initialize matrices with random values
    static void initialize() {
        Random rand = new Random();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                M1[i][j] = rand.nextInt(100);
                M2[i][j] = rand.nextInt(100);
            }
    }

    // Row-major addition
    static void addRowMajor() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                M3[i][j] = M1[i][j] + M2[i][j];
    }

    // Column-major addition
    static void addColumnMajor() {
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++)
                M3[i][j] = M1[i][j] + M2[i][j];
    }

    public static void main(String[] args) {
        initialize();

        long startTime, endTime;

        // Measure row-major execution time
        startTime = System.nanoTime();
        addRowMajor();
        endTime = System.nanoTime();
        System.out.println("Row Major Execution Time: " + (endTime - startTime) / 1e6 + " ms");

        // Measure column-major execution time
        startTime = System.nanoTime();
        addColumnMajor();
        endTime = System.nanoTime();
        System.out.println("Column Major Execution Time: " + (endTime - startTime) / 1e6 + " ms");
    }
}
