//...................................................................................................................................................
//.................;cccccccccc;......................................................................................................................
//...............,KWMMWWMMMMMWO.......................................................................... ...........................................
//..............;0MMWk..;OMMWK,.....'ooddooodo:.....,oddooooo,......'codooddoo,....coddoddooo,......odooooooo;.....'lol...;odo'...'cccccccccccccccc'.
//.............:NWWMW....dxxd,.....'KMMKdx0WMXl....,KMW0ddddo......lXMXxdxNWMX;...'ddKMMNkddc......OMMKdxXMMWl....;0MN:..:NMWo...:NMNOxONMMXkxxNWMX;.
//..............l0WMMMKc...........OMMK..;KMWc....'0MWx...........dWMN:..cXNK:......,KMNc.........xWMK,..NMWd....cNMWl..;XMMx...;XMXc..dWMNc..lWMWc..
//................c0WMMWKo.......'kMMN..oNMWo....:XWMN0Okl.... ..lWMNl.............cXMWl........,0WMW...XWWx....:XMWd..:KMNd...:KMN:..lWMWo..:NMNo...
//..........;O00....lNMMMO......:XWWXKKKKKOc....:NMWxcccc'......lWMXl..:::'.......cNMWl........,KMWk0MMNo;'....:XMWd..oNMN:...dWMN:..lWMNo..oNMK;....
//.........:KWMW....KWMW0'.....,XWWx..... .....;XMWx...........dNMX;..xMWX,......;NMWd.........KMWO.kMMN,.....:XMNl..lWWWl...lWMWl..dNMX:..xWMX;.....
//........:NWWMMWNNWMWNo......'0MWO.....'dK:..:KMWK000o......dWMMXOOKWWX:......:XMXl........'OMWk'.kMMN,....cNMMNOO0NWXo...:NMWo..dWMX:..oWMN:.......
//.........:lllllllllc'.......wwww.....cXKXO..lllllllll'......,llllllll:........lll;.........;ll:...;lll.....'clllllll:.....coo;...ooo;...loo;.......
//...................................;kWOkWWc........................................................................................................
//.................. ....';:cll:;'.;0WMKoNMMK'.;llooolclodxkO0KKXXXXXNNNXl....l0XNNNNNNNXKo...;OXNNNNNNNNXO'........dXNNNNo...'xXNNNNNNNNNXO'........
//..............,;cldkOKNWKxl;....lNMMW.dMMMMo..,lddoodxo:,,',,;codxkO0XN:...lWMMXkkk0MMMWc..;XMMWOkkONMMWo.......:0MMMMMX'.. :xkkkkkONMMWX;.........
//........oxk0KNWWMWWKko:,......oXWMMM..KMMMMK,....:odooodk000kdoc;'........cXMMX:...kMMXc..:XWMX....xWMWd......,OWMMMMMWc...........dWMW0,..........
//.......OMMMMWKOxl,..........:0MMMMW0.,WMMMMMK;.....'cx0kl;,;oxONWWWKOx;...:cc...;l0WMN:..'XMMMx...kWWWk.....'dNMM.WMMWo..........oXMM0c............
//......kWWKkl,.............,xWMMMMM0..,MMMMMMMk........'dXMXx;...:okXWO'.......OXWWN0o,...'OWMMWXXWWN0l.....lXWMX..WMWx..........kWMWO..............
//.....lo:'...............'xNMMMMWXk,..kWMMMMMMWl.........':xNWXOo;...,.......;.NWMWXd....,o0WMNXNWMWKc... 'kWWWk...MWx.........,0MMNd...............
//.......................cXWMMWK..',Av,.:xXMMMMMX'...........'oKWMWNk'..........'xWMMN;..lNMW....;KWMWx..'dXMWN....MM0.........oXMWO,................
//.....................lKWMNO...okKWMMW0dc:o0WMMMx..............;dKOc...:KNNO'..'OMMWo..lWMMK;..'kWMWO'.;KWMMMWXXWMMMNd......,0WMWx..................
//...................:0NK0Ok.kWMMMMMMMMMMMWKxxk0WWx....................;KMMXl;;cKMMNo..:NMMWd,.;OMMMk...cddddddkWMMWkd' ....lXMMK:...................
//.................c0NXKKNMMMMMMMMMMMMMMMMMMMWWKKNWo..................;XMMMMMMMMMMWo...0MMMMMMMMMMM0...........dWMMk......;0WMWk'....................
//................cododdddddddooooooooooooooooooooocc..................loddddddddo;....:ddddddddddc'...........lddo'......lddd:......................
//...................................................................................................................................................
//...................................................................................................................................................
//...................................................................................................................................................

const int numButtons = 13;

byte allButtons[numButtons];
byte prevButtons[numButtons];

void setup()
{
	Joystick.useManualSend(true);
	for (int i=0; i<numButtons; i++)
	{
		pinMode(i, INPUT_PULLUP);
	}
}

void loop()
{
	// read 3 analog inputs and use them for the joystick axis
	Joystick.X(analogRead(0));
	Joystick.Y(analogRead(1));
	Joystick.Z(analogRead(2));

	// read digital pins and use them for the buttons
	for (int i=0; i<numButtons; i++)
	{
		if (digitalRead(i))
		{
			// when a pin reads high, the button is not pressed
			// the pullup resistor creates the high signal
			allButtons[i] = 0;
		} 
		else
		{
			// when a pin reads low, the button is connected to ground.
			allButtons[i] = 1;
		}
		Joystick.button(i + 1, allButtons[i]);
	}


	// Because setup configured the Joystick manual send,
	// the computer does not see any of the changes yet.
	// This send_now() transmits everything all at once.
	Joystick.send_now();

	// check to see if any button changed since last time
	boolean anyChange = false;
	for (int i=0; i<numButtons; i++)
	{
		if (allButtons[i] != prevButtons[i])
			anyChange = true;
			prevButtons[i] = allButtons[i];
	}

	// a brief delay, so this runs approximately 200 times/sec
	delay(5);
}
