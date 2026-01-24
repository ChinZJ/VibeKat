
/*
https://open.kattis.com/problems/hydrasheads

1-cut one head // new head
2-cut one tail // 2 new tail
3-cut two head // nothing happen
4-cut two tail // new head

*/
import java.util.*;
import java.io.*;
import java.math.*;

public class hydrasheads{
	public static void main (String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));

		String[] temp;
		int head,tail,ans;
		while (true){
			ans=0;
			temp= br.readLine().split(" ");
			head=Integer.parseInt(temp[0]);
			tail=Integer.parseInt(temp[1]);
			//Stop condition
			if (head+tail==0){break;}
			//Base line is to minimize number of heads. Should be left with either 1 or 0
			ans+=(head/2);
			head%=2;
			//First case: head remainder 1
			if (head==1){
				//First case: tail 0: unsolvable
				if (tail==0){pw.println(-1);continue;}
				//Second case: tail has value
				else{
					//We need one more head
					//One more head requires only 2 tails
					if (tail<=2){
						//Attack until we get 2 tails
						//2 tails attack once to get 1 more head
						//2 head attack once to kill
						ans+=2+(2-tail);
					}
					else{
						//We can substract 2 from tails to make heads 0 first
						//Again, attacking 2 tails to get one more head
						//Attacking 2 heads to get 0head
						ans+=2;
						tail-=2;
						//Any extra tails needs to be in multiples of 4
						//For every 4 tails, we attack twice to get 2 heads then once more to get 0 heads
						//That is a total of 3 operations for every 4 tails
						ans+=(3*(tail/4));
						tail%=4;
						//Any additional tails left needs to be topped to 4 to be killed again
						if (tail!=0){
							ans+=3+(4-tail);
						}
					}
				}

			}
			//Second case: head remainder 0
			else{
				//First case: tail is 0: hydra is dead
				//Second case: tail is not 0
				if (tail !=0){
					//First case: tail <= 4
					//4 is the exact number required to convert into 2 heads
					if (tail<=4){
						//Attack until you get 4
						//4tails attack twice to get 2 head
						//2 head attack once to kill
						//Thus add another 3 operations
						ans+=3+(4-tail);
					}
					else{
						//Need to make number of tails % 4, refer to above
						ans+=(3*(tail/4));
						tail%=4;
						//Any additional tails left needs to be topped to 4 to be killed again
						if (tail!=0){
							ans+=3+(4-tail);
						}
					}
				}
			}
			pw.println(ans);
		}
		pw.flush();
		pw.close();
	}
}
