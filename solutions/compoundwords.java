/*
https://open.kattis.com/problems/compoundwords
Add all permutations into a list and use a treeset to permutate all combinations
Then iterate the treeset to print it out
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class compoundwords {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
        
        TreeSet<String> ts = new TreeSet<String>();
        ArrayList<String> temp = new ArrayList<>();
        String[] tmp;
        String s;
        while ( (s=br.readLine()) != null){
            tmp=s.split(" ");
            for (int i=0;i<tmp.length;i++){
                temp.add(tmp[i]);
            }
        }
        for (int i=0;i<temp.size();i++){
            for (int j=0;j<temp.size();j++){
                if (i!=j){
                    ts.add(temp.get(i)+temp.get(j));
                }
            }
        }
        for (String ans: ts) {pw.println(ans);} 
        pw.flush();
        pw.close();
    }
}
