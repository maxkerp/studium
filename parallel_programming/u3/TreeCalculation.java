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
    // the executionService managaging the threadpool
    ExecutorService es;
    // the completionService managing the cumputation of results
    CompletionService<Long> cs;

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

    void submitSubTree(Tree t){
     cs.submit(t);
     incrementTasks();
    }

    void preProcess(int threadCount) {
	// ???
	// insert/modify here
      es = Executors.newFixedThreadPool(threadCount);
      cs = new ExecutorCompletionService<Long>(es);
    }

    long postProcess() {
	// ???
	// insert/modify here
      long sum = 0;
      try{
        while (!(getNTasks() == 0)){
          sum += cs.take().get();
          decrementTasks();
        }
      } catch (InterruptedException e) {}
        catch (ExecutionException e) {}
      es.shutdown();
	    return sum;
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
	System.out.printf("tree height: %2d\nSequential: %.6f\nParallel: %3d threads, %6d tasks: %.6f\nspeedup: %.3f\ncount: %d\n",
			  height, t1, threadCount, tc.totalTasks, t2, t1 / t2, ref);
    }
}

// ==============================================================================

class Tree implements Callable<Long> {

    static long counter; // counter for consecutive node numbering

    int level; // node level
    long value; // node value
    Tree left; // left child
    Tree right; // right child

    // constructor
    Tree(long value) {
	this.value = value;
    }

    public Long call(){
      return this.processTree();
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
      if( this.level == tc.levelParallel){
        tc.submitSubTree(this.left);
        tc.submitSubTree(this.right);

        return this.value;
      } else

        return this.value + this.left.processTreeParallel(tc) + this.right.processTreeParallel(tc);
    }
}

//==============================================================================
