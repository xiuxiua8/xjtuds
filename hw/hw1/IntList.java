public class IntList {

    private int first;
    private IntList rest;

    /** A List with first FIRST0 and rest REST0. */
    public IntList(int first0, IntList rest0) {
        first = first0;
        rest = rest0;
    }

    /** A List with null rest, and first = 0.*/
    public IntList() {
        /* NOTE: public IntList () { }  would also work. */
        this(0, null);
    }

    
    /**
    * Returns a list consisting of the elements of A followed by the
    * *  elements of B.  May modify items of A.
    */

    public static IntList dmerge(IntList A, IntList B) {
        if (A == null) {
            A = B;
            return A;
        }
        IntList prt = A;
        while (prt.rest != null) {
            prt = prt.rest;
        }
        prt.rest = B;
        return A;
    }

    /**
    * Returns a list consisting of the elements of A followed by the
    * * elements of B.  May NOT modify items of A. 
    */

    public static IntList merge(IntList A, IntList B) {
        if (A == null) {
            return B;
        }
        if (A.rest == null) {
            return new IntList(A.first, B);
        }
        return new IntList(A.first, merge(A.rest, B));
    }
}