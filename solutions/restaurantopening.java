
/*
https://open.kattis.com/problems/restaurantopening

Brute force each coordinate
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class restaurantopening{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp= br.readLine().split(" ");
		int row=Integer.parseInt(temp[0]);
		int col=Integer.parseInt(temp[1]);
		int[][] arr=new int[row][col];
		for (int i=0;i<row;i++){
			temp= br.readLine().split(" ");
			for (int j=0;j<col;j++){
				arr[i][j]=Integer.parseInt(temp[j]);
			}
		}
		int ans=Integer.MAX_VALUE;
		int cost=0;
		for (int i=0;i<row;i++){
			for (int j=0;j<col;j++){
				for (int k=0;k<row;k++){
					for (int l=0;l<col;l++){
						// System.out.println(k+" "+l);
						cost+=arr[k][l]*(Math.abs(i-k)+Math.abs(j-l));
						// System.out.println(cost);
					}
				}
				ans=Math.min(ans,cost);
				cost=0;
			}
		}
		pw.println(ans);

		pw.flush();
		pw.close();
	}
}