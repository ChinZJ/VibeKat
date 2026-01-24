/*
Run 5m/s
Cannons takes 2s to launch 50m in any direction
Cannons are not obstacles

INPUTS
X Y coordinate of location
X Y location to reach

number of cannons available
X Y coordinates of the cannons

First thing we need is magnitude
(this will give you straight line distance)
sqrt( (x1-x2)^2 + (y1-y2)^2)

Run original Dijkstras algorithm on time
*/
import java.io.*;
import java.util.*;
import java.lang.Math;

public class cannon {
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		//Constants and variables
		int RUN_TIME = 5;
		int CANNON_DISTANCE = 50;
		int CANNON_TIME = 2;
		Double time;
		Double time2;
		IntegerTriple temp_trip;
		IntegerTriple temp_trip2;

		//Storage variables
		ArrayList<coordinate> coord_lst = new ArrayList<coordinate>();
		ArrayList<ArrayList<IntegerTriple>> adjlst = new ArrayList<ArrayList<IntegerTriple>>();
		PriorityQueue<IntegerTriple> dijkstra = new PriorityQueue<IntegerTriple>(new TimeComparator());

		//Initializing variables
		String[] temp = br.readLine().split(" ");
		coordinate start = new coordinate(Double.parseDouble(temp[0]), Double.parseDouble(temp[1]));
		coord_lst.add(start);
		temp = br.readLine().split(" ");
		coordinate end = new coordinate(Double.parseDouble(temp[0]), Double.parseDouble(temp[1]));
		coord_lst.add(end);

		int no_cannon = Integer.parseInt(br.readLine());
		//Create my time array
		Double[] fin_time = new Double[no_cannon + 2];
		fin_time[0] = 0.0;

		//Adding cannon coordinates
		for (int i = 0; i < no_cannon; i++) {
			temp = br.readLine().split(" ");
			coordinate temp_cannon = new coordinate(Double.parseDouble(temp[0]), Double.parseDouble(temp[1]));
			coord_lst.add(temp_cannon);
		}

		//Creating adjacent list
		for (int i = 0; i < no_cannon + 2; i++) {
			ArrayList<IntegerTriple> to_add = new ArrayList<IntegerTriple>();
			coordinate source = coord_lst.get(i);
			for (int j = 0; j <no_cannon + 2; j++) {
				//Base case, same node do not bother
				if (i == j) {continue;}

				coordinate dst = coord_lst.get(j);
				Double distance = magnitude(source.x, dst.x, source.y, dst.y);
				//If i is either start or end, achieved by running
				if (i == 0 || i == 1) {
					time = distance / RUN_TIME;
					to_add.add(new IntegerTriple(i, j, time));
				}
				//This is a cannon, we subtract 50m from the distance
				else {
					//If the distance is shorter than 50m, our cannon will overshoot
					//The shortest distance is always its straight line
					if (distance < CANNON_DISTANCE) {
						time = (CANNON_DISTANCE - distance) / RUN_TIME + CANNON_TIME;
					}
					else {
						time = ((distance - CANNON_DISTANCE) / RUN_TIME) + CANNON_TIME;
					}

					//Manual running might be faster
					time2 = distance/RUN_TIME;
					if (time < time2) {to_add.add(new IntegerTriple(i, j, time));}
					else {to_add.add(new IntegerTriple(i, j, time2));}
				}
			}
			//Store our neighbors pair
			adjlst.add(to_add);
		}

		// for (int i = 0; i < no_cannon+2; i++) {
		// 	for (int j = 0; j < adjlst.get(i).size(); j++) {
		// 		System.out.println("Source " + adjlst.get(i).get(j).source + " connects to " + adjlst.get(i).get(j).dst + " with time " + adjlst.get(i).get(j).time);
		// 	}
		// }

		//With our graph, we can now run Dijkstras algorithm
		//Always start with SOURCE = 0
		for (int i = 0; i < adjlst.get(0).size(); i++) {
			temp_trip = adjlst.get(0).get(i);
			fin_time[temp_trip.dst] = temp_trip.time;
			dijkstra.add(temp_trip);
		}

		while (!dijkstra.isEmpty()) {
			//Take shortest
			temp_trip = dijkstra.poll();
			// System.out.println("Looking at " + temp_trip.source + " to " + temp_trip.dst + " with time " + temp_trip.time);
			// System.out.println("old is " + fin_time[temp_trip.dst]);
			// System.out.println("new is " + (fin_time[temp_trip.source] + temp_trip.time));
			//if value inside fin_time is smaller, this is a duplicated node
			if (fin_time[temp_trip.dst] < fin_time[temp_trip.source] + temp_trip.time) {continue;}

			else{
				//System.out.println("Running else!");
				fin_time[temp_trip.dst] = fin_time[temp_trip.source] + temp_trip.time;
				//Look through all its nodes
				for (int i = 0; i < adjlst.get(temp_trip.dst).size(); i++) {
					temp_trip2 = adjlst.get(temp_trip.dst).get(i);
					dijkstra.add(temp_trip2);
					//If we have a shorter time path, we update it
					if (fin_time[temp_trip2.source] + temp_trip2.time < fin_time[temp_trip2.dst]) {
						fin_time[temp_trip2.dst] = fin_time[temp_trip2.source] + temp_trip2.time;
						//System.out.println("Setting " + fin_time[temp_trip2.dst] + " to " + (fin_time[temp_trip.source] + temp_trip2.time));
					}
					
				}
			}
		}

		pw.println(fin_time[1]);
		pw.flush();
		pw.close();


	}

	//Additional methods
	public static Double magnitude(Double x1, Double x2, Double y1, Double y2) {
		return Math.sqrt(Math.pow(x1-x2, 2) + Math.pow(y1-y2, 2));
	}
}

class coordinate{
	double x;
	double y;

	public coordinate (double x, double y) {
		this.x = x;
		this.y = y;
	}
}

class IntegerTriple{
	int source;
	int dst;
	double time;
	public IntegerTriple(int source, int dst, double time) {
		this.source = source;
		this.dst = dst;
		this.time = time;
	}
}

class TimeComparator implements Comparator<IntegerTriple> {

	public int compare(IntegerTriple v1, IntegerTriple v2) {
		// Returns the difference:
		Double result = v1.time - v2.time;
		// if positive, age of p1 is greater than p2
		if (result< 0) {return -1;}
		// if zero, the ages are equal
		else if (result == 0) {return 0;}
		// if negative, age of p1 is less than p2
		else {return 1;}
	}
}