import java.util.concurrent.*;

public class TreeCalculation {
    // tree level to go parallel
    int levelParallel;
    // total number of generated tasks
    long totalTasks;
    // current number of open tasks
    long nTasks;
    // total height of tree
    int height;

    TreeCalculation(int height, int levelParallel) {
	this.height = height;
	this.levelParallel = levelParallel;
    }

    void incrementTasks() {
	++nTasks;
	++totalTasks;
    }

    void decrementTasks() {
	--nTasks;
    }

    long getNTasks() {
	return nTasks;
    }

    void preProcess(int threadCount) {
	// ???
	// insert/modify here
    }

    long postProcess() {
	// ???
	// insert/modify here
	return 0;
    }

    public static void main(String[] args) {
	if (args.length != 3) {
	    System.out.println("usage: java Tree treeHeight levelParallel nthreads\n");
	    return;
	}
	int height = Integer.parseInt(args[0]);
	int levelParallel = Integer.parseInt(args[1]);
	int threadCount = Integer.parseInt(args[2]);

	TreeCalculation tc = new TreeCalculation(height, levelParallel);

	// generate balanced binary tree
	Tree t = Tree.genTree(height, height);

	//System.gc();

	// traverse sequential
	long t0 = System.nanoTime();
	long p1 = t.processTree();
	double t1 = (System.nanoTime() - t0) * 1e-9;

	t0 = System.nanoTime();
	tc.preProcess(threadCount);
	long p2 = t.processTreeParallel(tc);
	p2 += tc.postProcess();
	double t2 = (System.nanoTime() - t0) * 1e-9;

	long ref = (Tree.counter * (Tree.counter + 1)) / 2;
	if (p1 != ref)
	    System.out.printf("ERROR: sum %d != reference %d\n", p1, ref);
	if (p1 != p2)
	    System.out.printf("ERROR: sum %d != parallel %d\n", p1, p2);
	if (tc.totalTasks != (2 << levelParallel)) {
	    System.out.printf("ERROR: ntasks %d != %d\n", 2 << levelParallel, tc.totalTasks);
	}

	// print timing
	System.out.printf("tree height: %2d sequential: %.6f parallel with %3d threads and %6d tasks: %.6f  speedup: %.3f count: %d\n",
			  height, t1, threadCount, tc.totalTasks, t2, t1 / t2, ref);
    }
}

// ==============================================================================

class Tree {

    static long counter; // counter for consecutive node numbering

    int level; // node level
    long value; // node value
    Tree left; // left child
    Tree right; // right child

    // constructor
    Tree(long value) {
	this.value = value;
    }

    // generate a balanced binary tree of depth k
    static Tree genTree(int k, int height) {
	if (k < 0) {
	    return null;
	} else {
	    Tree t = new Tree(++counter);
	    t.level = height - k;
	    t.left = genTree(k - 1, height);
	    t.right = genTree(k - 1, height);
	    return t;
	}
    }

    // ==============================================================================
    // traverse a tree sequentially

    long processTree() {
	return value
	    + ((left == null) ? 0 : left.processTree())
	    + ((right == null) ? 0 : right.processTree());
    }

    // ==============================================================================
    // traverse a tree parallel
    
    long processTreeParallel(TreeCalculation tc) {
	// ???
	// insert/modify here
	return processTree();
    }
}

//==============================================================================
