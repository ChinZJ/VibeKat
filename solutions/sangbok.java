
/*
https://open.kattis.com/problems/sangbok

Minimal number of seconds to sing the most amount of songs possible
Can greedily take the shortest
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class sangbok{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		
		String[] temp= br.readLine().split(" ");
		int t = Integer.parseInt(temp[0])*60;
		int n=Integer.parseInt(temp[1]);
		int[] arr=new int[n];
		int total,idx;
		temp=br.readLine().split(" ");
		for (int i=0;i<n;i++){
			arr[i]=Integer.parseInt(temp[i]);
		}
		idx=0;total=0;
		Arrays.sort(arr);
		while (total<=t){
			if (idx==n){break;}
			if (total+arr[idx]<=t){total+=arr[idx];}
			else{break;}
			idx++;
		}
		pw.println(total);
		pw.flush();
		pw.close();
	}
}