/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package aoc;

import java.io.FileNotFoundException;

public class App {
    public static void main(String[] args) throws FileNotFoundException, Exception{
        long res = new DayEleven(new Reader(null).read()).p2();
        System.out.println("res: " + res);
    }
}
