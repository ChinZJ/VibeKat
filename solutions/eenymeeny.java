
/*
https://open.kattis.com/problems/eenymeeny

*/
import java.util.*;
import java.io.*;
import java.math.*;

public class eenymeeny{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		int rot=br.readLine().split(" ").length-1;
		int n=Integer.parseInt(br.readLine());
		ArrayList<String> names=new ArrayList<String>();
		ArrayList<String> arr1=new ArrayList<String>();
		ArrayList<String> arr2=new ArrayList<String>();
		boolean alt=true;
		for (int i=0;i<n;i++){
			names.add(br.readLine());
		}
		int idx=0;
		while (!names.isEmpty()){
			idx=(idx+rot)%names.size();
			// System.out.println("idx is "+idx);
			if (alt){arr1.add(names.get(idx));alt=false;}
			else{arr2.add(names.get(idx));alt=true;}
			// System.out.println("current idx is "+names.get(idx));
			names.remove(idx);
			// System.out.println("after idx is "+names.get(idx));
		}
		pw.println(arr1.size());
		for (int i=0;i<arr1.size();i++){
			pw.println(arr1.get(i));
		}
		pw.println(arr2.size());
		for (int i=0;i<arr2.size();i++){
			pw.println(arr2.get(i));
		}


		pw.flush();
		pw.close();
	}
}