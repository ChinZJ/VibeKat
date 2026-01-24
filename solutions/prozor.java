/*
https://open.kattis.com/problems/prozor

Brute force scanning
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class prozor{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[]tmp;
		String temp;
		int row,col,len,crow,ccol,brow=0,bcol=0,ctr,bctr=0;
		char[][] arr;
		
		tmp = br.readLine().split(" ");
		row=Integer.parseInt(tmp[0]);
		col=Integer.parseInt(tmp[1]);
		len=Integer.parseInt(tmp[2]);
		arr=new char[row][col];
		for (int i=0;i<row;i++){
			temp = br.readLine();
			for (int j=0;j<col;j++){
				arr[i][j]=temp.charAt(j);
			}
		}
		crow=0;ccol=0;
		while (ccol+len <= col){
			while (crow+len <= row){
				ctr=0;
				for (int i=1;i<=len-2;i++){
					for (int j=1;j<=len-2;j++){
						if (arr[crow+i][ccol+j]=='*'){
							ctr++;
							// System.out.println("hit at "+ (crow+i) + " " + (ccol+j) );
						}
					}
				}
				// System.out.println("row "+crow+" and col "+ccol+" has count "+ctr);
				if (ctr > bctr){bctr=ctr;brow=crow;bcol=ccol;}
				crow++;
			}
			crow=0;
			ccol++;
		}
		for (int i=0;i<len;i++){
			if (i==0 || i==len-1) {arr[brow][bcol+i]='+';arr[brow+len-1][bcol+i]='+';}
			else {arr[brow][bcol+i]='-';arr[brow+len-1][bcol+i]='-';arr[brow+i][bcol]='|';arr[brow+i][bcol+len-1]='|';}
		}
		pw.println(bctr);
		for (int i=0;i<row;i++){
			for (int j=0;j<col;j++){
				pw.print(arr[i][j]);
			}
			pw.println();
		}
		
		pw.flush();
		pw.close();
	}
}