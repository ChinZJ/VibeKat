/*
First input is number of test case

Format of test case
number of dominoes, number of lines
x knocks down y

We use modified kosaraju's algorithm here*/
import java.util.*;
import java.io.*;

public class Dominos {
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		//Initializing loop
		int no_case = Integer.parseInt(br.readLine());
		while (no_case > 0) {
			//Initialisation of each test case
			String[] temp = br.readLine().split(" ");
			int no_dom = Integer.parseInt(temp[0]);
			int line = Integer.parseInt(temp[1]);

			//Initialising variables
			int counter = 0;
			Boolean[] visit = new Boolean[no_dom+1];
			Boolean[] topple = new Boolean[no_dom+1];
			visit[0] = true;
			topple[0] = true;
			ArrayList<Node> dominos = new ArrayList<Node>();
			dominos.add(new Node());
			for (int i = 1; i < no_dom+1; i++) {
				visit[i] = false;
				topple[i] = false;
				dominos.add(new Node());
			}
			for (int i = 0; i < line; i++) {
				
				temp = br.readLine().split(" ");
				Node domino = dominos.get(Integer.parseInt(temp[0]));
				Node domino2 = dominos.get(Integer.parseInt(temp[1]));
				domino2.prev.add(Integer.parseInt(temp[0]));
				domino.next.add(Integer.parseInt(temp[1]));
				topple[Integer.parseInt(temp[1])] = true;

			}

			//Iterate throught topple, for each topple that is false, they are definitely a source, perform DFS from there
			for (int i = 1; i < no_dom+1; i++) {
				if (!topple[i]) {DFS(i, dominos, visit); counter++;}
			}
			//Iterate through visit, for each visit that is still false, there is a cycle, run DFS on it
			//The issue with the cycle is that I can have another cycle that leads to the toppling of this cycle
			//Thus, cycles become bidirectional (I will topple front and back)
			for (int i = 1; i < no_dom+1; i++) {
				if (!visit[i]) {DFS_cyc(i, dominos, visit); counter++;}
			}
			pw.println(counter);
			no_case--;
		}
		pw.flush();
		pw.close();
	}

	public static void DFS(int i, ArrayList<Node> dominos, Boolean[] visit) {
		Node temp = dominos.get(i);
		if (!visit[i]) {
			visit[i] = true;
			if (!temp.next.isEmpty()){
				for (int j = 0; j < temp.next.size(); j++){
					DFS(temp.next.get(j), dominos, visit);
				}
			}
		}
	}

	public static void DFS_cyc(int i, ArrayList<Node> dominos, Boolean[] visit) {
		Node temp = dominos.get(i);
		if (!visit[i]) {
			visit[i] = true;
			if (!temp.next.isEmpty()){
				for (int j = 0; j < temp.next.size(); j++){
					DFS_cyc(temp.next.get(j), dominos, visit);
				}
			}

			if (!temp.prev.isEmpty()){
				for (int j = 0; j < temp.prev.size(); j++){
					DFS_cyc(temp.prev.get(j), dominos, visit);
				}
			}
		}
	}
}

class Node {
	ArrayList<Integer> prev = new ArrayList<Integer>();
	ArrayList<Integer> next = new ArrayList<Integer>();
	public Node() {}
}