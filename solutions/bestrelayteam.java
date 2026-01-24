/*
INPUTS
integer n
number of runners to choose from
name (maximum 20 characters in upper case), run first leg, run others
(there are two digits after a decimal point)

OUTPUT
time (float)
first runner
all other runners */

/*
No need to check for name length by perfoming negative indexing
time2 = temp[-1:-4:-1]; time3 = temp[-6:-9:-1]; name = temp[-11::-1]

We will need to perform sorting twice.
First we extract out the first 3 other runners in order
Next, we find the shortest first runner out of the rest.
Perform a comparison within the 4 selected runners.
*/

/*
FORMULA: P2-P1 positive = slower, negative = faster
(P2-P1)_1 + (P1-P2)_2: positive = slower, negative = faster
Looking at the provided sample outputs
CARTER 9.78 8.93
BOLT 9.58 8.43
(diff -0.20, 0.5 --> net 0.3 which means time increase)
POWELL 9.72 8.61
(diff -0.06, 0.32 --> net 0.26 which means time increase)
BLAKE 9.69 8.72
(diff -0.09, 0.21 --> net 0.12 which means time increase)

MARDELL 13.36 13.20
POLACEK 13.05 12.55
(diff -0.31, 0.75 net 0.44)
SODERMAN 13.99 12.57
(diff -0.63, 0.63, net 0)
DRANGE 15.14 14.19
(diff cant be asked) */



//Import
import java.util.*;
import java.io.*;

//main class
public class ProblemBRT{

	public static void main(String[] args) throws IOException {
		int no_case; //Creates my loop
		int first_idx = 4; //This is for me to find my fastest first runner.
		int slowest_idx = 1; 
		double final_time = 0; //This will give me my final time
		int iter = 4;
		ArrayList<String> final_lst = new ArrayList<String>(); //This will give me my final list of names
		ArrayList<Runner> runner_lst = new ArrayList<Runner>(); //Stores my list of runners

		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out)); //Writing
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); //Reading

		no_case = Integer.parseInt(br.readLine());
		for (int i = 0; i < no_case; i++) { //This loops through all of my runners
			//I am going to utilise this loop to help me find the fastest first runner as well
			String[] inpt = br.readLine().split(" "); //Gives me a size 3 array
			Runner temp = new Runner(Double.parseDouble(inpt[1]), Double.parseDouble(inpt[2]), inpt[0]);
			runner_lst.add(temp);
		}

		//If the number of cases is exactly 4, we can skip to the final swap check step

		if (no_case != 4){
			iter = 5;
			//Accounting when no_case > 4
			quicksort(runner_lst, 0, no_case-1);
			//Run through the loop to find my fastest first runner.
			for (int i = 4; i < no_case; i++) {
				if ((runner_lst.get(i)).get_first() < (runner_lst.get(first_idx)).get_first()) {
					first_idx = i;
				}
			}
			swap(runner_lst, first_idx, 4);
		}
		

		final_time += (runner_lst.get(0)).get_first();
		final_lst.add((runner_lst.get(0)).get_name());
		for (int i = 1; i < iter; i++) {
			final_time += (runner_lst.get(i)).get_second();
			final_lst.add((runner_lst.get(i)).get_name());
		}

		//Brute force combination
		for (int i = 0; i < iter; i++){
			double temp_time = (runner_lst.get(i)).get_first(); //Rereshing my temp time
			ArrayList<String> temp_lst = new ArrayList<String>(); //This will give me my final list of names
			temp_lst.add((runner_lst.get(i)).get_name());
			for(int j = 0; j<iter; j++){
				if (i != j) {
					temp_time += (runner_lst.get(j)).get_second();
					temp_lst.add((runner_lst.get(j)).get_name());
				}
				if (temp_lst.size() == 4) {break;}
			}
			if (temp_time < final_time){
				final_time = temp_time;
				final_lst = temp_lst;
			}
		}

		pw.println(final_time);
		for (int i = 0; i<4; i++) {
			pw.println(final_lst.get(i));
		}
		pw.flush();
		pw.close();
	}

	public static void quicksort(ArrayList<Runner> runner_lst, int start, int end) {
		//My goal is actually to find partition 4
		if (start < end) {
			int pivot_pt = partition(runner_lst, start, end); //runs my first sort and gives me a pivot
			if (pivot_pt < 3) {
				//If it is less than 2, I only need to sort those above the pivot point
				quicksort(runner_lst, pivot_pt+1, end);
			}
			if (pivot_pt > 3) {
				//If it is more than 2,, I only need to sort those behind the pivot point
				quicksort(runner_lst, start, pivot_pt-1);
			}
			//If pivot_pt is at 2, I can move on to find the fastest first runner and put them at position 5
			//This will be done in the main code.
		}
	}

	public static void swap(ArrayList<Runner> runner_lst, int pos1, int pos2){
		//Takes in 2 indexes and swaps their position
		Runner temp = runner_lst.get(pos1);
		runner_lst.set(pos1, runner_lst.get(pos2));
		runner_lst.set(pos2, temp);
	}

	public static int partition(ArrayList<Runner> runner_lst, int start, int end){
		//Use start as my pivot, sort runner_lst to the left and to the right of my pivot item
		Runner pivot = runner_lst.get(start);
		double pvt_val = pivot.get_second(); //Sorting based on t2
		int counter = start;

		for (int i = start+1; i <= end; i++) {
			//If value >= pivot, do nothing
			if ((runner_lst.get(i)).get_second() < pvt_val) {
				//If value < pivot, shift pivot position forward by 1.
				counter++;
				swap(runner_lst, i, counter);
			}
		}
		swap(runner_lst,start,counter); // put the pivot at the right place
		return counter;    // counter is the pivot's final position
	}

	public static void printArray(ArrayList<Runner> runner_lst, int len) {
		System.out.println("The runners prior to final check are:");
		for (int i = 0; i < len; i++)
			System.out.print((runner_lst.get(i)).get_first() + " "+(runner_lst.get(i)).get_name() +" " +(runner_lst.get(i)).get_second() + " ");
		System.out.println();
	}
}


class Runner{
	//This stores the individual data of runners
	public double t1,t2;
	public String name;

	//Constructor
	public Runner(double first, double second, String iName) { 
    	t1 = first;
    	t2 = second;
    	name = iName;
	}
	//get methods
	public String get_name() {return name;}
	public double get_first() {return t1;}
	public double get_second() {return t2;}
}