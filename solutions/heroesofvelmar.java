
/*
https://open.kattis.com/problems/heroesofvelmar

ThunderHeart 6 if location at least 3more, double power
Zenith 4 if played center +5
Seraphina 1 +1 to everyone excluding herself
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class heroesofvelmar{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		HashMap<String,Integer> hm=new HashMap<>();
		hm.put("Shadow", 6);
		hm.put("Gale", 5);
		hm.put("Ranger", 4);
		hm.put("Anvil", 7);
		hm.put("Vexia", 3);
		hm.put("Guardian", 8);
		hm.put("Thunderheart", 6);
		hm.put("Frostwhisper", 2);
		hm.put("Voidclaw", 3);
		hm.put("Ironwood", 3);
		hm.put("Zenith", 4);
		hm.put("Seraphina", 1);

		String[] temp1,temp2;
		int s1=0;
		int s2=0;
		int round=1;
		int t1,t2;
		int total1=0;
		int total2=0;
		while (round<=3){
			t1=0;t2=0;
			temp1 = br.readLine().split(" ");
			temp2 = br.readLine().split(" ");
			if (Integer.parseInt(temp1[0])>0){
				if (Integer.parseInt(temp1[0])==4){
					for (int i=1;i<temp1.length;i++){
						if (temp1[i].equals("Thunderheart")){t1+=6;}
						if (temp1[i].equals("Seraphina")){t1+= (temp1.length-2);}
						if (temp1[i].equals("Zenith") && round==2){t1+=5;}
						t1+=hm.get(temp1[i]);
					}
				}
				else{
					for (int i=1;i<temp1.length;i++){
						if (temp1[i].equals("Seraphina")){t1+= (temp1.length-2);}
						if (temp1[i].equals("Zenith") && round==2){t1+=5;}
						t1+=hm.get(temp1[i]);
					}
				}
			}
			if (Integer.parseInt(temp2[0])>0){
				if (Integer.parseInt(temp2[0])==4){
					for (int i=1;i<temp2.length;i++){
						if (temp2[i].equals("Thunderheart")){t2+=6;}
						if (temp2[i].equals("Seraphina")){t2+= (temp2.length-2);}
						if (temp2[i].equals("Zenith") && round== 2){t2+=5;}
						t2+=hm.get(temp2[i]);
					}
				}
				else{
					for (int i=1;i<temp2.length;i++){
						if (temp2[i].equals("Seraphina")){t2+= (temp2.length-2);}
						if (temp2[i].equals("Zenith") && round==2){t2+=5;}
						t2+=hm.get(temp2[i]);
					}
				}
			}
			if (t1>t2){s1++;}
			if (t2>t1){s2++;}
			// System.out.println("score 1 "+t1+" score 2 "+t2);
			round++;
			total1+=t1;
			total2+=t2;

			//Can perform calculations after round 2 for further optimisation
		}
		if (s1>s2){pw.println("Player 1");}
		if (s1==s2){
			if (total1==total2){pw.println("Tie");}
			else if (total1>total2){pw.println("Player 1");}
			else{pw.println("Player 2");}
		}
		if (s2>s1){pw.println("Player 2");}
		pw.flush();
		pw.close();
	}
}