/*
https://open.kattis.com/problems/arrivingontime

Input
First line
	n [1, 10^5]   : Number of tram stops
	m [1, 2x10^5] : Numebr of tram lines
	s [1, 10^9]   : Time at which meeting starts in seconds from now

m tram lines
	u [0, n)     : Depart stop
	v [0, n)     : Arritve stop
	t0 [0, 10^9] : First departure (First tram)
	p [1, 10^9]  : Departs every p (Each subsequent tram)
	d [1, 10^9]  : d seconds from departure to arrival (travel time)

Start from 0
Get to n - 1
	Latest time which you can leave hotel in seconds from now
	Else, "impossible"

The idea I would like to try intuitively is to find the shortest path from the back and take whatever is left
*/

import java.util.*;
import java.io.*;
import java.math.*;

public class ArrivingOnTime{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		// Retrieving variables first
		String[] temp;
		temp = br.readLine().split(" ");
		MainNode mainNode, tempNode;
		SubNode subNode;
		int n, m, source, dest, s, dist, diff;
		n = Integer.parseInt(temp[0]); // number of tram stops
		m = Integer.parseInt(temp[1]); // number of tram lines
		s = Integer.parseInt(temp[2]); // meeting time from now

		// Setting up required data structures
		boolean solve = false;
		PriorityQueue<MainNode> pq = new PriorityQueue<MainNode>((x, y) -> Integer.compare(y.score, x.score));
		boolean[] visit = new boolean[n];
		MainNode[] nodeLst = new MainNode[n];
		// Initialize home node because it will now have no outgoing edges
		nodeLst[0] = new MainNode(0);

		while (m-- >0){
			temp = br.readLine().split(" ");
			source = Integer.parseInt(temp[1]); // Recall we are "reversing" the edges
			dest = Integer.parseInt(temp[0]);
			subNode = new SubNode(dest,
									Integer.parseInt(temp[2]),
									Integer.parseInt(temp[3]),
									Integer.parseInt(temp[4]));	
			// Check if new
			if (nodeLst[source] == null) {
				mainNode = new MainNode(source);		
				mainNode.neighbor.add(subNode);
				nodeLst[source] = mainNode;	
			} else {
				mainNode = nodeLst[source];
				mainNode.neighbor.add(subNode);
			}


			if (source == n-1) {
				// Recall we are starting from the back
				// Initialize its weight to s
				mainNode.score = s;
				// Put into priority queue
				pq.add(mainNode);
			}
			
		}

		// Initialize modiied dijkstras
		while (!pq.isEmpty()) {
			mainNode = pq.poll();
			// If source node, we can terminate
			if (mainNode.u == 0)  {solve = true; break;}
			else if (visit[mainNode.u]) continue;
			else {
				// Add stop to visited set
				visit[mainNode.u] = true;
				// For all neighboring stops
				for (SubNode sub : mainNode.neighbor) {
					// Calculate new distance
					dist = mainNode.score - sub.d;
					// Check first if dist is 0, because sub.t will need to be 0
					// dist == 0 is a special case
					if (dist < 0) continue;
					else if (dist == 0) {
						if (sub.t != 0) continue; // Not a solution
						// else no operations required
					} else {
						// if dist > zero, need to align with waiting time if any
						diff = (dist - sub.t) % sub.p;
						dist -= diff;
					}
					// If score smaller than 0, discard: no solution
					if (dist < 0) continue;
					else {
						// Extract node of interest
						tempNode = nodeLst[sub.v];
						// Check for cheeky case where we have a disconnected train
						// This is likely the reason for run time error
						if (tempNode == null) continue;
						tempNode.score = Math.max(tempNode.score, dist);
						// Enqueue 
						pq.add(tempNode);
					}
				}
			}
		}

		// Check if solved
		if (solve) pw.println(nodeLst[0].score);
		else pw.println("impossible");


		pw.flush();
		pw.close();
	}
}

class MainNode{
	// This stores the information of the main node, that may have multiple neighbors
	public int u, score;
	public ArrayList<SubNode> neighbor;

	//Constructor
	public MainNode(int u) { 
    	this.u = u;
    	this.score = Integer.MIN_VALUE; // negative infinite weight, we are doing max heap
    	this.neighbor = new ArrayList<SubNode>();
	}	
}

class SubNode{
	//This stores the individual data of each station
	public int v, t, p, d;

	//Constructor
	public SubNode(int v, int t, int p, int d) { 
    	this.v = v;
    	this.t = t;
    	this.p = p;
    	this.d = d;
	}
}