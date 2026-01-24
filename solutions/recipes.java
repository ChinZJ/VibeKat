/*
https://open.kattis.com/problems/recipes
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class recipes{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String[] temp;
		int n,idx,ctr=1;
		double mnwght,sc;
		node[] arr;
		while (t-- >0){
			temp = br.readLine().split(" ");
			n=Integer.parseInt(temp[0]);
			sc=Double.parseDouble(temp[2])/Double.parseDouble(temp[1]);
			arr=new node[n];idx=0;mnwght=0;
			for (int i=0;i<n;i++){
				temp = br.readLine().split(" ");
				if (Double.parseDouble(temp[2])==100.0){idx=i;mnwght=Double.parseDouble(temp[1]);}
				arr[i]=new node(temp[0], Double.parseDouble(temp[1]), Double.parseDouble(temp[2]));
			}
			pw.println("Recipe # "+ctr);
			for (int i=0;i<n;i++){
				pw.println(arr[i].self+" "+(sc*mnwght*arr[i].pctg/100));
			}
			ctr++;
			pw.println("----------------------------------------");
		}
		pw.flush();
		pw.close();
	}
}
class node{
	public String self;
	public double weight;
	public double pctg;
	public node(String self,double weight, double pctg){
		this.self=self;
		this.weight=weight;
		this.pctg=pctg;
	}
}