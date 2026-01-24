import java.util.*;
import java.io.*;

class idk {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String temp = br.readLine();
		char prev = temp.charAt(0);
		StringBuilder str = new StringBuilder("");
		str.append(prev);
		char newchar;
		for (int i = 1; i < temp.length(); i++) {
			newchar = temp.charAt(i);
			if (prev != newchar) {
				str.append(newchar);
				prev = newchar;
			}
		}
		pw.println(str);
		pw.flush();
		pw.close();
	}
}