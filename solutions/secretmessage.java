/*
https://open.kattis.com/problems/secretmessage
Note that since it is always a square, the indexes are just going column wise from left to right
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class secretmessage{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
		StringBuilder sb; 
		int t = Integer.parseInt(br.readLine());
		String temp;
		int n;
		char[] arr;
		while (t-- >0){
			temp = br.readLine();
			n=(int)Math.ceil(Math.sqrt(temp.length()));
			arr=temp.toCharArray();
			sb=new StringBuilder();
			for (int i=(n*n)-n;i<(n*n);i++){
				for (int j=i;j>=0;j-=n){
					if (j>arr.length-1){continue;}
					else {sb.append(arr[j]);}
				}
			}
			pw.println(sb);
		}
		pw.flush();
		pw.close();
	}
}