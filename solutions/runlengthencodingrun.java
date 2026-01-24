
/*
https://open.kattis.com/problems/runlengthencodingrun

This version has been changed to accept integers (more than 1-9)
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class runlengthencodingrun{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		StringBuilder sb = new StringBuilder();
		String[] temp= br.readLine().split(" ");
		char[] arr= temp[1].toCharArray();
		int idx=0;int ctr=0;int prev=0;
		if (temp[0].equals("E")){
			while (idx <= arr.length-1){
				sb.append(arr[idx]);
				idx++;
				ctr=1;
				if (idx ==arr.length){break;}
				while (arr[idx]==arr[idx-1] ){
					ctr++;
					idx++;
					if (idx ==arr.length){break;}
				}
				sb.append(String.valueOf(ctr));
			}
			if (ctr==1){sb.append(String.valueOf(ctr));}
			pw.println(sb.toString());
		}
		else{
			while (idx <= arr.length-1){
				// System.out.println("idx is "+idx);
				sb.append(arr[idx]);
				prev=idx;
				idx++;
				if (idx ==arr.length){break;}
				if (Character.isDigit(arr[idx])){
					ctr=Character.getNumericValue(arr[idx]);
					// System.out.println("cntr is "+ctr);
					idx++;
					if (idx ==arr.length){break;}
					while (Character.isDigit(arr[idx])) {
						ctr*=10;
						ctr+=Character.getNumericValue(arr[idx]);
						// System.out.println(ctr);
						idx++;
						if (idx ==arr.length){break;}
					}
				}

				ctr--;
				while(ctr>0){
					// System.out.println(ctr);
					ctr--;
					sb.append(arr[prev]);
				}
			}
			ctr--;
			while(ctr>0){
				// System.out.println(ctr);
				ctr--;
				sb.append(arr[prev]);
			}
			pw.println(sb.toString());
		}
		pw.flush();
		pw.close();
	}
}