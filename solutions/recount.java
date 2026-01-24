/*
https://open.kattis.com/problems/recount

Counting sort
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class recount{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		HashMap<String, node> hm=new HashMap<>();
		PriorityQueue<node> pq=new PriorityQueue<node>( (x,y) -> (y.cnt - x.cnt));
		node nde;
		String temp;
		while (!(temp=br.readLine()).equals("***")){
			if (!hm.containsKey(temp)){
				nde= new node(temp);
				hm.put(temp,nde);
				pq.add(nde);
			}
			else{
				nde=hm.get(temp);
				nde.cnt++;
			}
		}
		Collection<node> cllc=hm.values();
		node[] arr=cllc.toArray(new node[0]);
		Arrays.sort(arr, Comparator.comparingInt(node -> node.cnt));
		if (arr[arr.length-1].cnt > arr[arr.length-2].cnt){pw.println(arr[arr.length-1].self);}
		else{pw.println("Runoff!");}
		pw.flush();
		pw.close();
	}
}
class node{
	//This stores the individual data of runners
	public String self;
	public int cnt=1;

	//Constructor
	public node(String self) { 
    	this.self=self;
	}
}