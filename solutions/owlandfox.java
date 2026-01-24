/*
https://open.kattis.com/problems/owlandfox
Look digit wise until first non zero and subtract 1 from that
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class owlandfox{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
		
		int t = Integer.parseInt(br.readLine());
		String str;
		int val,idx,mag,ans;
		while (t-- >0){
			str=br.readLine();
			idx=str.length()-1;
			mag=1;ans=0;
			while (idx>=0){
				if (str.charAt(idx)=='0'){idx--;mag*=10;}
				else {
					ans+=(Character.getNumericValue(str.charAt(idx))-1) * mag;
					idx--;
					mag*=10;
					break;
				}
			}
			while (idx >=0){
				ans+= (Character.getNumericValue(str.charAt(idx)))*mag;
				mag*=10;
				idx--;
			}
			pw.println(ans);
		}
		pw.flush();
		pw.close();
	}
}