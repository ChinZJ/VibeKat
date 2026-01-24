
/*
https://open.kattis.com/problems/treirad

Binary search, the upper bound is 999
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class treirad{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		int left=1,right=999,mid=0;
		while (left<=right){
			mid=(left+right) / 2;
			if ((mid*(mid+1)*(mid+2))<t){
				if ((mid+1)*(mid+2)*(mid+3) >t){break;}
				else{left=mid+1;}
			}
			else{
				if (((mid-1)*mid*(mid+1))<t){mid--;break;}
				else{right=mid-1;}
			}
		}
		pw.println(mid);
		pw.flush();
		pw.close();
	}
}