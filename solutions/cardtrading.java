/* T different card types
Each player has a deck, D
If D contains at least 2 cards of that type, it is a combo, C.
Obtain K combos

He can buy up to 2 cards type i at a_i coins
He can sell cards at b_i coins

INPUT
three integers N,T, K
List of N integers from 1 to T (no integers appear more than twice)

Each of the two lines is the buy and sell price of the card

OUTPUT
Single integer assuming optimal trade.


IDEA
Buy all cards to form pairs, then sell those of the maximum value
Note that you can only either BUY TWO or SELL ALL
*/

//Import
import java.io.*;
import java.util.*;
import java.lang.*;

//main class
public class ProblemBCT{

	public static void main(String[] args) throws IOException {
		//Declaring of variables
		int no_cards; 
		int combo_goal;
		int card_type;
		int buy_price;
		int sell_price;
		Long bank = 0L;
		int to_buy;
		Long gains;

		long buy;
		long sell;


		PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out)); //Writing
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); //Reading

		String inpt[] = br.readLine().split(" "); //This reads, N, T, K
		no_cards = Integer.parseInt(inpt[0]);
		card_type = Integer.parseInt(inpt[1]);
		combo_goal = Integer.parseInt(inpt[2]);

		int card_lst[] = new int[card_type]; // Generates an N sized array
		Arrays.fill(card_lst, 0);

		//NOTE: I will subtract all card types by 1 so that type 1 is element 0

		String inpt2[] = br.readLine().split(" "); //This is my list of cards
		for (int i = 0; i < inpt2.length; i++) {
			int val = Integer.parseInt(inpt2[i])-1;
			card_lst[val] += 1;

		}


		//Now, I will create a hashmap containing all my buy and price values
		HashMap<Integer, Card> prices = new HashMap<Integer, Card>();
		for (int i = 0; i < card_type; i++) {
			//Since each card type appears once, I do not need to perform any checks
			String set[] = new String[2]; //I know that it is buy and sell
			set = br.readLine().split(" ");
			Card temp = new Card(Long.parseLong(set[0]), Long.parseLong(set[1]));
			prices.put(i, temp);
		}
		//During this iteration, the goal is to
		//1. Buy cards and subtract it from your bank
		//2. Calculate potential sell cost (eg. buy 1 and sell 2 = price of buy 1 and sell 1)
		//3. Create another Long array that stores all these prices
		//4. Calculate the sum of the array - the first k and add the value to your bank
		//5. Print your output
		Long get_bank[] = new Long[card_type];
		for (int i = 0; i < card_type; i++) {
			to_buy = 2 - card_lst[i];
			buy = -(prices.get(i)).get_buy();
			sell = (prices.get(i)).get_sell();
			//System.out.println(i + " buy price is " + buy + " and sell price is " + sell);
			gains = (to_buy * -buy) + (card_lst[i] * sell);
			bank += (to_buy * buy);	
			//System.out.println("Calculated value is " + (to_buy*buy));
			get_bank[i] = gains;
		}
		//System.out.println("My bank is currently" + bank);
		Arrays.sort(get_bank);



		for (int i = card_type-1; i >= combo_goal; i--){
			//ystem.out.println(get_bank[i]);
			bank += get_bank[i];
		}
		pw.println(bank);
		pw.flush();
		pw.close();
	}
}


class Card{
	//This stores the individual data of runners
	public Long buy, sell;

	//Constructor
	public Card(Long buy, Long sell) { 
    	this.buy = buy;
    	this.sell = sell;
	}
	//get methods
	public Long get_buy() {return buy;}
	public Long get_sell() {return sell;}
}