
/*
https://open.kattis.com/problems/kcuddlanod

numbers in reversed order
2=5, 5=2
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class kcuddlanod{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp=br.readLine().split(" ");
		String bag1=temp[0];
		String bag2=temp[1];
		int idx,val1,val2;
		//Either bag bigger than the other by length, else compare lexicographically backwards
		if (bag1.length()>bag2.length()){pw.println(1);}
		else if (bag2.length()>bag1.length()){pw.println(2);}
		else{
			boolean swap1=false;
			boolean swap2=false;
			char[] arr1=bag1.toCharArray();
			char[] arr2=bag2.toCharArray();
			idx=bag1.length()-1;
			while (true){
				swap1=false;swap2=false;
				val1=Character.getNumericValue(arr1[idx]);
				val2=Character.getNumericValue(arr2[idx]);
				if (!swap1&&val1==2){val1=5;swap1=true;}
				if (!swap1&&val1==5){val1=2;swap1=true;}
				if (!swap2&&val2==2){val2=5;swap2=true;}
				if (!swap2&&val2==5){val2=2;swap2=true;}
				if (val1>val2){pw.println(1);break;}
				else if (val2>val1){pw.println(2);break;}
				idx--;
			}
		}
		pw.flush();
		pw.close();
	}
}