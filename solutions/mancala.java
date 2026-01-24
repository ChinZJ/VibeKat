/*
https://open.kattis.com/problems/mancala
The upper bound is 80 bins, we can brute force a solution
For every counter we add to a higher bin, we subtract one from the previous bins to simulate how the counters are being played out
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class mancala{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String[] temp;
		int n,ctr,idx=0,high;
		int[] state;
		while (t-- >0){
			temp = br.readLine().split(" ");
			n=Integer.parseInt(temp[0]);
			ctr=Integer.parseInt(temp[1]);
			state = new int[80]; idx=0; high=0;
			while (ctr != 0){
				while (state[idx]!=0){
					idx++;
				}
				high=Math.max(high,idx);
				state[idx]=idx+1;
				ctr=ctr-idx-1;
				while (idx!=0){
					idx--;
					state[idx]--;
					ctr++;
				}
			}
			pw.println(n + " "+ (high+1));
			for (int i=0;i<high+1;i++){
				pw.print(state[i] + " ");
			}
			pw.println();
		}
		pw.flush();
		pw.close();
	}
}
