
/*
https://open.kattis.com/problems/ordinals

We can run memoisation
If you really want to be lazy since n<=8 you can hardcode the answer
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class ordinals{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int t = Integer.parseInt(br.readLine());
		if (t==0){pw.println("{}");}
		else if (t==1){pw.println("{{}}");}
		else{
			HashMap<Integer,String> hm=new HashMap<>();
			hm.put(0,"{}");
			hm.put(1,"{{}}");
			int idx=2;
			while(idx<=t){
				StringBuilder sb=new StringBuilder("{}");
				for (int i=0;i<idx;i++){
					sb.insert(sb.length()-1, hm.get(i));
					if (i!=idx-1){sb.insert(sb.length()-1,",");}
				}
				
				hm.put(idx,sb.toString());
				idx++;
			}
			pw.println(hm.get(t));
		}
		pw.flush();
		pw.close();
	}
}