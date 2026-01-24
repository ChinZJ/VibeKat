
/*
https://open.kattis.com/problems/polymul1

Basic sum of multiplication table
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class polymul1{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		String[] temp,temp2;
		int[][] mtx;
		int first,second,sum,row,col,coldum,tot;
		while (t-- >0){
			first=Integer.parseInt(br.readLine());
			temp = br.readLine().split(" ");
			second=Integer.parseInt(br.readLine());
			temp2 = br.readLine().split(" ");
			pw.println(first+second);
			sum=first+second+1;
			mtx=new int[1][sum];
			col=sum-1;
			for (int i=second;i>=0;i--){
				coldum=col;
				col--;
				for (int j=first;j>=0;j--){
					// System.out.println("coldum is "+coldum+" and col is "+col);
					mtx[0][coldum]+=Integer.parseInt(temp[j])*(Integer.parseInt(temp2[i]));
					coldum--;
				}
			}
			for (int i=0;i<sum;i++){
				pw.print(mtx[0][i]+" ");
			}
			pw.println();
		}
		pw.flush();
		pw.close();
	}
}