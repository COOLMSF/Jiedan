/* This test writes smiling faces and santa clauses out in mostly
 * random order.  In UTF-16, smiling faces can be represented with
 * a single 16-bit value, but santa clauses require a surrogate pair.
 *
 * This test may require special attention in languages that internally
 * represent strings as UTF-16 sequences, such as Java.
 *
 * @author godmar
 * Spring '22
 */
import java.util.*;
import java.io.*;

public class SurrogateTest
{
    public static void main(String []av) {
        var howmany = Integer.parseInt(av[0]);
        var MSIZE = 1<<17;
        var rnd = new Random(42);
        var out = new PrintWriter(System.out, false);
        var santaClaus = "\uD83C\uDF85";
        var smilingFace = "\u263A";
        for (int i = 0; i < howmany; i++) {
            if (rnd.nextInt() % 2 == 0 || i > howmany - MSIZE)
                out.print(santaClaus);
            else
                out.print(smilingFace);
        }
        out.close();
    }
}